//==============================================================================
// Filename: D3D11Camera.cpp
// Description: D3D11のカメラ及びビュー変換行列の管理クラス
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================
#include "D3D11Camera.h"

int D3D11Camera::CameraInit(
    const DirectX::XMFLOAT3 eye, 
    const DirectX::XMFLOAT3 lookat, 
    const DirectX::XMFLOAT3 up)
{
    // コンスタントバッファの作成
    D3D11_BUFFER_DESC cbDesc;
    cbDesc.ByteWidth = sizeof(ConstantBuffer);
    cbDesc.Usage = D3D11_USAGE_DEFAULT;
    cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cbDesc.CPUAccessFlags = 0;
    cbDesc.MiscFlags = 0;
    cbDesc.StructureByteStride = 0;

    HRESULT sts = D3D11Graphics::GetInstance().getDevPtr()->
        CreateBuffer(&cbDesc, NULL, &m_constBuffer);
    if (FAILED(sts))
    {
        return -1;
    }

    // ワールド変換行列の作成
    m_worldMtx = DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f);
    
    // ビュー変換行列の作成
    DirectX::XMVECTOR eyeVec = DirectX::XMVectorSet(eye.x, eye.y, eye.z, 0);
    DirectX::XMVECTOR lookatVec = DirectX::XMVectorSet(lookat.x, lookat.y, lookat.z, 0);
    DirectX::XMVECTOR upVec = DirectX::XMVectorSet(up.x, up.y, up.z, 0);
    m_viewMtx = DirectX::XMMatrixLookAtLH(eyeVec, lookatVec, upVec);

    // プロジェクション行列の作成
    constexpr float fov = DirectX::XMConvertToRadians(45.0f); // 視野角
    float aspect = 16.0f / 9.0f;
    float nearclip = 0.1f;
    float farclip = 100.0f;
    m_projMtx = DirectX::XMMatrixPerspectiveFovLH(fov, aspect, nearclip, farclip);

    // 定数バッファへの入力
    ConstantBuffer cb;
    XMStoreFloat4x4(&cb.world, DirectX::XMMatrixTranspose(m_worldMtx));
    XMStoreFloat4x4(&cb.view, DirectX::XMMatrixTranspose(m_viewMtx));
    XMStoreFloat4x4(&cb.projection, DirectX::XMMatrixTranspose(m_projMtx));
    D3D11Graphics::GetInstance().getDevContextPtr()->
        UpdateSubresource(m_constBuffer.Get(), 0, NULL, &cb, 0, 0);
    return 0;
}

int D3D11Camera::CameraDraw()
{
    m_worldMtx = DirectX::XMMatrixMultiply(m_worldMtx, DirectX::XMMatrixRotationX(0.009f));
    m_worldMtx = DirectX::XMMatrixMultiply(m_worldMtx, DirectX::XMMatrixRotationY(0.006f));
    m_worldMtx = DirectX::XMMatrixMultiply(m_worldMtx, DirectX::XMMatrixRotationZ(0.003f));

    // 定数バッファへの入力
    ConstantBuffer cb;
    XMStoreFloat4x4(&cb.world, DirectX::XMMatrixTranspose(m_worldMtx));
    XMStoreFloat4x4(&cb.view, DirectX::XMMatrixTranspose(m_viewMtx));
    XMStoreFloat4x4(&cb.projection, DirectX::XMMatrixTranspose(m_projMtx));
    D3D11Graphics::GetInstance().getDevContextPtr()->
        UpdateSubresource(m_constBuffer.Get(), 0, NULL, &cb, 0, 0);
    D3D11Graphics::GetInstance().getDevContextPtr()->
        VSSetConstantBuffers(0, 1, m_constBuffer.GetAddressOf());
    return 0;
}

void D3D11Camera::CreateInstance()
{
    DeleteInstance();

    s_instance = new D3D11Camera();
}

void D3D11Camera::DeleteInstance()
{
    if (s_instance != nullptr)
    {
        delete s_instance;
        s_instance = nullptr;
    }
}
