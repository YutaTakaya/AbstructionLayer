//==============================================================================
// Filename: CommonObjData.h
// Description: 抽象化レイヤー用共通オブジェクトデータ
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================
#pragma once
#include "CommonResourceManager.h"

struct VertexData
{
    XMFLOAT3 pos;
    XMFLOAT2 uv;
    XMFLOAT4 col;
};

class CommonObjData
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
    virtual int ObjInit(
        /*[in]*/    const VertexData* p_VData,
        /*[in]*/    const int vNum,
        /*[in]*/    const WORD* p_indexData,
        /*[in]*/    const int indexNum);

    //---------------------------------------------
    /// 頂点情報を用いた描画処理
    ///
    /// \return void
    //--------------------------------------------- 
    virtual void ObjDraw();

    //---------------------------------------------
    /// ワールド変換行列の回転角を変更する
    /// 
    /// \param[in] (angleX)     度数法でのX軸回転度数
    /// \param[in] (angleY)     度数法でのY軸回転度数
    /// \param[in] (angleZ)     度数法でのZ軸回転度数
    ///
    /// \return void
    //--------------------------------------------- 
    virtual void ObjRotate(
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
    //---------------------------------------------------------------------------
    XMMATRIX m_localMtx = {};
    XMFLOAT3 m_worldPos = {};
    //---------------------------------------------------------------------------
    /// <summary>
    /// m_localMtx          ローカルでの姿勢情報
    /// m_localPos          ローカル座標
    /// </summary>
private:

};

