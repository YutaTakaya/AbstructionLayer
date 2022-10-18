//==============================================================================
// Filename: D3D11ObjData.cpp
// Description: ポリゴン情報及び描画システム
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================

#include "D3D11ObjData.h"

int D3D11ObjData::ObjInit(const VertexData* p_VData, const int vNum, const WORD* p_indexData, const int indexNum)
{
    HRESULT sts;

    // 頂点情報のコピー
    for (int i = 0; i < vNum; i++)
    {
        m_vertex.emplace_back(p_VData[i]);
    }
    // インデックス情報のコピー
    for (int i = 0; i < indexNum; i++)
    {
        m_index.emplace_back(p_indexData[i]);
    }

    // 頂点バッファの作成
    D3D11_BUFFER_DESC vbDesc = {};
    vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;    // デバイスにバインドするときの種類
    vbDesc.Usage = D3D11_USAGE_DEFAULT;             // バッファの使用法
    vbDesc.ByteWidth = static_cast<UINT>(m_vertex.size()) * sizeof(VertexData);    // 作成するバッファのサイズ
    vbDesc.MiscFlags = 0;                           // その他フラグ
    vbDesc.StructureByteStride = 0;                 // 構造化バッファの場合そのサイズ
    vbDesc.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA vrData = { &m_vertex[0],sizeof(m_vertex),0 };
    sts = D3D11Graphics::GetInstance().getDevPtr()->CreateBuffer(
        &vbDesc, 
        &vrData, 
        &m_pVertexBuff);
    if (FAILED(sts))
    {
        return -1;
    }

    // インデックスバッファの作成
    D3D11_BUFFER_DESC ibDesc = {};
    ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;    // デバイスにバインドするときの種類
    ibDesc.Usage = D3D11_USAGE_DEFAULT;             // バッファの使用法
    ibDesc.ByteWidth = static_cast<UINT>(m_index.size()) * sizeof(WORD);    // 作成するバッファのサイズ
    ibDesc.MiscFlags = 0;                           // その他フラグ
    ibDesc.StructureByteStride = 0;                 // 構造化バッファの場合そのサイズ
    ibDesc.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA irData = { &m_index[0],sizeof(m_index),0 };
    sts = D3D11Graphics::GetInstance().getDevPtr()->CreateBuffer(
        &ibDesc, 
        &irData, 
        &m_pIndexBuff);
    if (FAILED(sts))
    {
        return -1;
    }

    // テクスチャの作成
    D3D11_TEXTURE2D_DESC texDesc = {};
    texDesc.Width = 16; // 縦ピクセル数
    texDesc.Height = 16;    // 横ピクセル数
    texDesc.MipLevels = 1;
    texDesc.ArraySize = 1;
    texDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    texDesc.SampleDesc.Count = 1;
    texDesc.SampleDesc.Quality = 0;
    texDesc.Usage = D3D11_USAGE_DYNAMIC;
    texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    texDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    texDesc.MiscFlags = 0;
    sts = D3D11Graphics::GetInstance().getDevPtr()->CreateTexture2D(
        &texDesc, 
        nullptr, 
        &m_pTexture);
    if (FAILED(sts))
    {
        return -1;
    }

    // テクスチャ書き換え（チェック柄）
    const int texSize = 32;
    D3D11_MAPPED_SUBRESOURCE msr = {};
    sts = D3D11Graphics::GetInstance().getDevContextPtr()->Map(
        m_pTexture.Get(), 
        0, 
        D3D11_MAP_WRITE_DISCARD, 
        0, &msr);

    if (FAILED(sts))
    {
        return -1;
    }
    byte texData[texSize * texSize * 4] = { 0 };
    for (int x = 0; x < texSize; x++)
    {
        for (int y = 0; y < texSize; y++)
        {
            if ((x + y) % 2 == 0)
            {
                texData[(x * 4) + (y * 4 * texSize)] = 255;        // R
                texData[(x * 4) + (y * 4 * texSize) + 1] = 255;    // G
                texData[(x * 4) + (y * 4 * texSize) + 2] = 255;    // B
            }
        }
    }
    memcpy(msr.pData, texData, sizeof(texData));
    D3D11Graphics::GetInstance().getDevContextPtr()->Unmap(m_pTexture.Get(), 0);

    // シェーダーリソースビューの作成
    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = 1;
    sts = D3D11Graphics::GetInstance().getDevPtr()->CreateShaderResourceView(
        m_pTexture.Get(), 
        &srvDesc, 
        &m_pShaderResourceView);
    if (FAILED(sts))
    {
        return -1;
    }

    // サンプラーステートの作成
    D3D11_SAMPLER_DESC ssDesc = {};
    ssDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    ssDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    ssDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    ssDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sts = D3D11Graphics::GetInstance().getDevPtr()->CreateSamplerState(
        &ssDesc, 
        &m_pSamplerState);
    if (FAILED(sts))
    {
        return -1;
    }

    // ワールド変換行列を単位行列で初期化
    m_localMtx = ::XMMatrixIdentity();
    return 0;
}

void D3D11ObjData::ObjUpdate()
{
    // 毎フレームでの更新処理を書く
}


void D3D11ObjData::ObjDraw()
{
    // ワールド行列へ変換処理
    XMMATRIX worldMtx;
    worldMtx = ::XMMatrixTranslation(m_worldPos.x, m_worldPos.y, m_worldPos.z);
    worldMtx = ::XMMatrixMultiply(m_localMtx, worldMtx);


    UINT stride = sizeof(VertexData);
    UINT offset = 0;
    D3D11Graphics::GetInstance().getDevContextPtr()->
        IASetVertexBuffers(0, 1, m_pVertexBuff.GetAddressOf(), &stride, &offset);
    D3D11Graphics::GetInstance().getDevContextPtr()->
        IASetIndexBuffer(m_pIndexBuff.Get(), DXGI_FORMAT_R16_UINT, 0);
    D3D11Graphics::GetInstance().getDevContextPtr()->
        IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    D3D11Camera::GetInstance().CameraUpdateConstBuff(worldMtx);
    D3D11Graphics::GetInstance().getDevContextPtr()->
        VSSetShader(D3D11Graphics::GetInstance().getVertexShaderPtr(), 0, 0);
    D3D11Graphics::GetInstance().getDevContextPtr()->
        PSSetShader(D3D11Graphics::GetInstance().getPixelShaderPtr(), 0, 0);
    D3D11Graphics::GetInstance().getDevContextPtr()->
        IASetInputLayout(D3D11Graphics::GetInstance().getInputLayoutPtr());

    D3D11Graphics::GetInstance().getDevContextPtr()->
        PSSetSamplers(0, 1, m_pSamplerState.GetAddressOf());
    D3D11Graphics::GetInstance().getDevContextPtr()->
        PSSetShaderResources(0, 1, m_pShaderResourceView.GetAddressOf());
    D3D11Graphics::GetInstance().getDevContextPtr()->OMSetRenderTargets(
        1,
        D3D11Graphics::GetInstance().getBackBufferVierDPtr(),
        D3D11Graphics::GetInstance().getDepthStencilVierPtr());

    D3D11Graphics::GetInstance().getDevContextPtr()->
        DrawIndexed(static_cast<UINT>(m_index.size()), 0, 0);
}


void D3D11ObjData::ObjUninit()
{
    m_vertex.clear();
    m_pVertexBuff->Release();
}

void D3D11ObjData::ObjRotate(const float angleX, const float angleY, const float angleZ)
{
    m_localMtx = ::XMMatrixMultiply(m_localMtx, ::XMMatrixRotationX(angleX));
    m_localMtx = ::XMMatrixMultiply(m_localMtx, ::XMMatrixRotationY(angleY));
    m_localMtx = ::XMMatrixMultiply(m_localMtx, ::XMMatrixRotationZ(angleZ));
}

void D3D11ObjData::ObjTranslate(const float posX, const float posY, const float posZ)
{
    m_worldPos.x = posX;
    m_worldPos.y = posY;
    m_worldPos.z = posZ;
}

