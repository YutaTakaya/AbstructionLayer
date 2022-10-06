//==============================================================================
// Filename: ObjData.h
// Description: ポリゴン情報及び描画システム
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================
#pragma once

#include "D3D11Graphics.h"
#include <vector>

struct VertexData
{
    DirectX::XMFLOAT3 pos;
    DirectX::XMFLOAT2 uv;
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
    /// 頂点情報を用いたDirectX11での描画処理
    ///
    /// \return 正常に終了した場合0が返される
    //--------------------------------------------- 
    int ObjDraw();

    //---------------------------------------------
    /// メンバ変数の解放処理
    ///
    /// \return 正常に終了した場合0が返される
    //--------------------------------------------- 
    int ObjUninit();

    //---------------------------------------------------------------------------

protected:

private:
    //---------------------------------------------------------------------------
    std::vector<VertexData> m_vertex;
    std::vector<WORD> m_index;
    ComPtr<ID3D11Buffer> m_vertexBuff;
    ComPtr<ID3D11Buffer> m_indexBuff;
    ComPtr<ID3D11Buffer> m_texBuff;
    //---------------------------------------------------------------------------
    /// <summary>
    /// m_vertex        頂点情報
    /// m_index         インデックスデータ
    /// m_vertexBuff    頂点バッファ
    /// m_indexBuff     インデックスバッファ
    /// m_textureBuff   テクスチャバッファ
    /// </summary>
};

//  TODO : ワールド変換行列の作成及びCameraクラスからの引き離し
