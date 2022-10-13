//==============================================================================
// Filename: D3D12Camera.cpp
// Description: D3D12のカメラ及びビュー変換行列の管理クラス、シングルトン
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================
#include "D3D12Camera.h"

int D3D12Camera::CameraInit(const XMFLOAT3 eye, const XMFLOAT3 lookat, const XMFLOAT3 up)
{
    HRESULT sts;

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

    // 定数バッファーの作成
    D3D12_HEAP_PROPERTIES heapprop = {};
    heapprop.Type = D3D12_HEAP_TYPE_UPLOAD;
    heapprop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    heapprop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
    heapprop.CreationNodeMask = 1;
    heapprop.VisibleNodeMask = 1;

    D3D12_RESOURCE_DESC cbDesc = {};
    cbDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    cbDesc.Width = ((sizeof(ConstantBuffer12) + 0xff) & ~0xff); // 256バイトアライアメント
    cbDesc.Height = 1;
    cbDesc.DepthOrArraySize = 1;
    cbDesc.MipLevels = 1;
    cbDesc.Format = DXGI_FORMAT_UNKNOWN;
    cbDesc.SampleDesc.Count = 1;
    cbDesc.SampleDesc.Quality = 0;
    cbDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
    cbDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

    sts = D3D12Graphics::GetInstance().getDevPtr()->CreateCommittedResource(
        &heapprop,
        D3D12_HEAP_FLAG_NONE,
        &cbDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&m_pConstBuffer));
    if (FAILED(sts))
    {
        return -1;
    }

    ConstantBuffer12* pMap; // マップ先ポインタ
    sts = m_pConstBuffer.Get()->Map(0, nullptr, (void**)&pMap);
    if (FAILED(sts))
    {
        return -1;
    }
    ConstantBuffer12 mapData = {};
    XMStoreFloat4x4(&mapData.world, XMMatrixTranspose(m_pWorldMtx));
    XMStoreFloat4x4(&mapData.view, XMMatrixTranspose(m_pViewMtx));
    XMStoreFloat4x4(&mapData.projection, XMMatrixTranspose(m_pProjMtx));
    *pMap = mapData;
    m_pConstBuffer.Get()->Unmap(0, nullptr);
    return 0;
}

int D3D12Camera::CameraUpdateConstBuff(const XMMATRIX worldMtx)
{
    ConstantBuffer12* pMap; // マップ先ポインタ
    HRESULT sts = m_pConstBuffer.Get()->Map(0, nullptr, (void**)&pMap);
    if (FAILED(sts))
    {
        return -1;
    }
    ConstantBuffer12 mapData = {};
    XMStoreFloat4x4(&mapData.world, XMMatrixTranspose(worldMtx));
    XMStoreFloat4x4(&mapData.view, XMMatrixTranspose(m_pViewMtx));
    XMStoreFloat4x4(&mapData.projection, XMMatrixTranspose(m_pProjMtx));
    *pMap = mapData;
    m_pConstBuffer.Get()->Unmap(0, nullptr);

    m_pWorldMtx = worldMtx;
    return 0;
}

void D3D12Camera::CreateInstance()
{
    DeleteInstance();

    s_pInstance = new D3D12Camera();
}

void D3D12Camera::DeleteInstance()
{
    if (s_pInstance != nullptr)
    {
        delete s_pInstance;
        s_pInstance = nullptr;
    }
}
