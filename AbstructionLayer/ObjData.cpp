//==============================================================================
// Filename: ObjData.cpp
// Description: ポリゴン情報及び描画システム
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================

#include "ObjData.h"
#include "D3D11Camera.h"

int ObjData::ObjInit(const VertexData* p_VData, const int vNum, const WORD* p_indexData, const int indexNum)
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
    vbDesc.ByteWidth = (int)m_vertex.size() * sizeof(VertexData);    // 作成するバッファのサイズ
    vbDesc.MiscFlags = 0;                           // その他フラグ
    vbDesc.StructureByteStride = 0;                 // 構造化バッファの場合そのサイズ
    vbDesc.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA vrData = { &m_vertex[0],sizeof(m_vertex),0 };
    sts = D3D11Graphics::GetInstance().getDevPtr()->CreateBuffer(&vbDesc, &vrData, &m_vertexBuff);
    if (FAILED(sts))
    {
        return -1;
    }

    // インデックスバッファの作成
    D3D11_BUFFER_DESC ibDesc = {};
    ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;    // デバイスにバインドするときの種類
    ibDesc.Usage = D3D11_USAGE_DEFAULT;             // バッファの使用法
    ibDesc.ByteWidth = (int)m_index.size() * sizeof(WORD);    // 作成するバッファのサイズ
    ibDesc.MiscFlags = 0;                           // その他フラグ
    ibDesc.StructureByteStride = 0;                 // 構造化バッファの場合そのサイズ
    ibDesc.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA irData = { &m_index[0],sizeof(m_index),0 };
    sts = D3D11Graphics::GetInstance().getDevPtr()->CreateBuffer(&ibDesc, &irData, &m_indexBuff);
    if (FAILED(sts))
    {
        return -1;
    }

    // TODO : テクスチャバッファの作成

    return 0;
}


int ObjData::ObjDraw()
{
    UINT stride = sizeof(VertexData);
    UINT offset = 0;
    D3D11Graphics::GetInstance().getDevContextPtr()->
        IASetVertexBuffers(0, 1, m_vertexBuff.GetAddressOf(), &stride, &offset);
    D3D11Graphics::GetInstance().getDevContextPtr()->
        IASetIndexBuffer(m_indexBuff.Get(), DXGI_FORMAT_R16_UINT, 0);
    D3D11Graphics::GetInstance().getDevContextPtr()->
        IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    D3D11Camera::GetInstance().CameraDraw();
    D3D11Graphics::GetInstance().getDevContextPtr()->
        VSSetShader(D3D11Graphics::GetInstance().getVertexShaderPtr(), 0, 0);
    D3D11Graphics::GetInstance().getDevContextPtr()->
        PSSetShader(D3D11Graphics::GetInstance().getPixelShaderPtr(), 0, 0);
    D3D11Graphics::GetInstance().getDevContextPtr()->
        IASetInputLayout(D3D11Graphics::GetInstance().getInputLayoutPtr());
    //D3D11Graphics::GetInstance().getDevContextPtr()->OMSetRenderTargets(
    //    1,
    //    D3D11Graphics::GetInstance().getRenderTargetVierPtr(),
    //    D3D11Graphics::GetInstance().getDepthStencilVierPtr());

    D3D11Graphics::GetInstance().getDevContextPtr()->
        DrawIndexed((int)m_index.size(), 0, 0);
    return 0;
}


int ObjData::ObjUninit()
{
    m_vertex.clear();
    m_vertexBuff->Release();
    return 0;
}

