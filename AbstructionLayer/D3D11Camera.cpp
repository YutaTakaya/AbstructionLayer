//==============================================================================
// Filename: D3D11Camera.cpp
// Description: D3D11のカメラ及びビュー変換行列の管理クラス
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================
#include "D3D11Camera.h"

int D3D11Camera::CameraInit(
    const FLOAT3 eye, 
    const FLOAT3 lookat, 
    const FLOAT3 up)
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
        CreateBuffer(&cbDesc, NULL, &m_pConstBuffer);
    if (FAILED(sts))
    {
        return -1;
    }

    // ワールド変換行列の作成
    m_pWorldMtx = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
    
    // ビュー変換行列の作成
    XMVECTOR eyeVec = XMVectorSet(eye.x, eye.y, eye.z, 0);
    XMVECTOR lookatVec = XMVectorSet(lookat.x, lookat.y, lookat.z, 0);
    XMVECTOR upVec = XMVectorSet(up.x, up.y, up.z, 0);
    m_pViewMtx = XMMatrixLookAtLH(eyeVec, lookatVec, upVec);

    // プロジェクション行列の作成
    constexpr float fov = XMConvertToRadians(45.0f); // 視野角
    float aspect = 16.0f / 9.0f;
    float nearclip = 0.1f;
    float farclip = 1000.0f;
    m_pProjMtx = XMMatrixPerspectiveFovLH(fov, aspect, nearclip, farclip);

    // 定数バッファへの入力
    ConstantBuffer cb;
    XMStoreFloat4x4(&cb.world, XMMatrixTranspose(m_pWorldMtx));
    XMStoreFloat4x4(&cb.view, XMMatrixTranspose(m_pViewMtx));
    XMStoreFloat4x4(&cb.projection, XMMatrixTranspose(m_pProjMtx));
    D3D11Graphics::GetInstance().getDevContextPtr()->
        UpdateSubresource(m_pConstBuffer.Get(), 0, NULL, &cb, 0, 0);
    return 0;
}

int D3D11Camera::CameraUpdateConstBuff(const XMMATRIX worldMtx)
{
    // 定数バッファへの入力
    ConstantBuffer cb;
    XMStoreFloat4x4(&cb.world, XMMatrixTranspose(worldMtx));
    XMStoreFloat4x4(&cb.view, XMMatrixTranspose(m_pViewMtx));
    XMStoreFloat4x4(&cb.projection, XMMatrixTranspose(m_pProjMtx));
    D3D11Graphics::GetInstance().getDevContextPtr()->
        UpdateSubresource(m_pConstBuffer.Get(), 0, NULL, &cb, 0, 0);
    D3D11Graphics::GetInstance().getDevContextPtr()->
        VSSetConstantBuffers(0, 1, m_pConstBuffer.GetAddressOf());
    return 0;
}

void D3D11Camera::CreateInstance()
{
    DeleteInstance();

    s_pInstance = new D3D11Camera();
}

void D3D11Camera::DeleteInstance()
{
    if (s_pInstance != nullptr)
    {
        delete s_pInstance;
        s_pInstance = nullptr;
    }
}
