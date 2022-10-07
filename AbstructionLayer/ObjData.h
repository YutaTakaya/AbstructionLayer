//==============================================================================
// Filename: ObjData.h
// Description: ポリゴン情報及び描画システム
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================
#pragma once

#include "D3D11Graphics.h"
#include "D3D11Camera.h"
#include <vector>

struct VertexData
{
    XMFLOAT3 pos;
    XMFLOAT2 uv;
    XMFLOAT4 col;
};

class ObjData
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
    /// 行列の更新
    ///
    /// \return void
    //--------------------------------------------- 
    void ObjUpdate();

    //---------------------------------------------
    /// 頂点情報を用いたDirectX11での描画処理
    ///
    /// \return void
    //--------------------------------------------- 
    void ObjDraw();

    //---------------------------------------------
    /// メンバ変数の解放処理
    ///
    /// \return void
    //--------------------------------------------- 
    void ObjUninit();

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
    std::vector<VertexData> m_vertex;
    std::vector<WORD> m_index;
    ComPtr<ID3D11Buffer> m_pVertexBuff;
    ComPtr<ID3D11Buffer> m_pIndexBuff;

    ComPtr<ID3D11Texture2D>	m_pTexture;
    ComPtr<ID3D11ShaderResourceView>	m_pShaderResourceView;
    ComPtr<ID3D11SamplerState>	m_pSamplerState;

    XMFLOAT3 m_worldPos;
    XMMATRIX m_localMtx;
    //---------------------------------------------------------------------------
    /// <summary>
    /// m_vertex                頂点情報
    /// m_index                 インデックスデータ
    /// m_vertexBuff            頂点バッファ
    /// m_indexBuff             インデックスバッファ
    /// m_texture               テクスチャバッファ
    /// m_shaderResourceView	シェーダーリソースビュー
	/// m_samplerState			サンプラーステート
	/// 
	/// m_worldPos              ワールド座標
	/// m_localMtx              ワールド変換行列
    /// </summary>
};