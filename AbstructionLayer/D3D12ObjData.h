//==============================================================================
// Filename: D3D12ObjData.h
// Description: DirectX12のオブジェクトデータ
//              （DirectX12でのデバッグ用であり、最終的には11の物と統合予定）
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================
#pragma once
#include "D3D12Graphics.h"
#include "D3D12Camera.h"
using namespace DirectX;
struct VertexData12
{
    XMFLOAT3 pos;
    XMFLOAT2 uv;
    XMFLOAT4 col;
};

struct TexRGBA
{
    unsigned char R, G, B, A;
};

class D3D12ObjData
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
        /*[in]*/    const VertexData12* p_VData,
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

    //---------------------------------------------
    /// ワールド変換行列の回転角を変更する
    /// 
    /// \param[in] (angleX)     度数法でのX軸回転度数
    /// \param[in] (angleY)     度数法でのY軸回転度数
    /// \param[in] (angleZ)     度数法でのZ軸回転度数
    ///
    /// \return void
    //--------------------------------------------- 
    void ObjRotate(
        /*[in]*/    const float angleX,
        /*[in]*/    const float angleY,
        /*[in]*/    const float angleZ);

    //---------------------------------------------
    /// ワールド変換行列の座標を変更する
    /// 
    /// \param[in] (posX)     X座標
    /// \param[in] (posY)     Y座標
    /// \param[in] (posZ)     Z座標
    ///
    /// \return void
    //--------------------------------------------- 
    void ObjTranslate(
        /*[in]*/    const float posX,
        /*[in]*/    const float posY,
        /*[in]*/    const float posZ);

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

    XMMATRIX m_localMtx;
    XMFLOAT3 m_worldPos;
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
    /// 
    /// m_localMtx          ローカルでの姿勢情報
    /// m_localPos          ローカル座標
    /// </summary>
};

