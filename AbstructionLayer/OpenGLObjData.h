//==============================================================================
// Filename: OpenGLObjData.h
// Description: OpenGLのオブジェクトデータ
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================
#pragma once
#include "CommonObjData.h"
class OpenGLObjData : public CommonObjData
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
        /*[in]*/    const float angleZ) override;
protected:

private:
    //---------------------------------------------------------------------------
    std::vector<VertexData> m_vartex;
    std::vector<WORD> m_index;
    //---------------------------------------------------------------------------
    /// <summary>
    /// m_vertex        頂点データ
    /// m_index         インデックスデータ
    /// </summary>
};

