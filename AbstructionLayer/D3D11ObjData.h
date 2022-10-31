//==============================================================================
// Filename: D3D11ObjData.h
// Description: ポリゴン情報及び描画システム
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================
#pragma once

#include "CommonObjData.h"
#include "D3D11Graphics.h"
#include "D3D11Camera.h"
#include "D3D11Render.h"
#include <vector>

class D3D11ObjData : public CommonObjData
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
        /*[in]*/    const int indexNum) override;

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
    void ObjDraw() override;

    //---------------------------------------------
    /// メンバ変数の解放処理
    ///
    /// \return void
    //--------------------------------------------- 
    void ObjUninit();



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

    D3D11Render m_Render;
    //---------------------------------------------------------------------------
    /// <summary>
    /// m_vertex                頂点情報
    /// m_index                 インデックスデータ
    /// m_vertexBuff            頂点バッファ
    /// m_indexBuff             インデックスバッファ
    /// 
    /// m_texture               テクスチャバッファ
    /// m_shaderResourceView	シェーダーリソースビュー
	/// m_samplerState			サンプラーステート
	/// 
	/// m_Render                オブジェクトごとの描画システム
    /// </summary>
};