//==============================================================================
// Filename: D3D12ObjData.h
// Description: DirectX12のオブジェクトデータ
//              （DirectX12でのデバッグ用であり、最終的には11の物と統合予定）
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================
#pragma once
#include "CommonObjData.h"
#include "D3D12Graphics.h"
#include "D3D12Camera.h"
using namespace DirectX;

struct TexRGBA
{
    byte R, G, B, A;
};

class D3D12ObjData : public CommonObjData
{
public:
    //---------------------------------------------------------------------------

    //---------------------------------------------
    /// 頂点、インデックス情報の保存とそれらのバッファの作成
    ///
    /// \param[in] (p_VData)    頂点情報配列
    /// \param[in] (vNum)       p_VDataの配列数
    /// \param[in] (p_indexData)    インデックス配列
    /// \param[in] (indexNum)   p_indexDataの配列数
    ///
    /// \return エラーが出た場合-1が、正常に終了した場合0が返される
    //--------------------------------------------- 
    int ObjInit(
        /*[in]*/    const VertexData* p_VData,
        /*[in]*/    const int vNum,
        /*[in]*/    const WORD* p_indexData,
        /*[in]*/    const int indexNum);
    
    //---------------------------------------------
    /// 更新処理
    //--------------------------------------------- 
    void ObjUpdate();

    //---------------------------------------------
    /// 頂点情報を用いたDirectX12での描画処理
    ///
    /// \return void
    //--------------------------------------------- 
    void ObjDraw();

    //---------------------------------------------------------------------------

protected:

private:
    //---------------------------------------------------------------------------
    ComPtr<ID3D12Resource>  m_pVertexBuffer;
    D3D12_VERTEX_BUFFER_VIEW    m_vertexBufferView = {};
    ComPtr<ID3D12Resource>  m_pIndexBuffer;
    D3D12_INDEX_BUFFER_VIEW m_indexBufferView = {};
    int m_indexNum = 0;

    ComPtr<ID3D12DescriptorHeap> m_pDescHeap;
    ComPtr<ID3D12Resource>  m_pTextureBuffer;
    //---------------------------------------------------------------------------
    /// <summary>
    /// m_pVertexBuffer     頂点バッファ
    /// m_vertexBufferView  頂点バッファのビュー
    /// m_pIndexBuffer      インデックスバッファ
    /// m_indexBufferView   インデックスバッファのビュー
    /// m_indexNum          インデックス数
    /// 
    /// m_pDescHeap         デスクリプタヒープ
    /// m_pTextureBuffer    テクスチャバッファ
    /// </summary>
};

