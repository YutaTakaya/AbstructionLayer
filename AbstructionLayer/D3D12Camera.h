//==============================================================================
// Filename: D3D12Camera.h
// Description: D3D12のカメラ及びビュー変換行列の管理クラス、シングルトン
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================
#pragma once
#include "D3D12Graphics.h"
#include <wrl/client.h>
using Microsoft::WRL::ComPtr;
using namespace DirectX;

struct ConstantBuffer12 {
    XMFLOAT4X4 world;
    XMFLOAT4X4 view;
    XMFLOAT4X4 projection;
};

class D3D12Camera
{
public:
    //---------------------------------------------------------------------------
    //---------------------------------------------
    /// カメラ情報の初期設定とビュー変換行列、プロジェクション変換行列の初期化
    ///
    /// \param[in] (eye)		カメラ位置
    /// \param[in] (lookat)     カメラの注視点
    /// \param[in] (up)		カメラの上方向
    ///
    /// \return エラーが出た場合-1が、正常に終了した場合0が返される
    //--------------------------------------------- 
    int CameraInit(
        /*[in]*/    const XMFLOAT3 eye,
        /*[in]*/    const XMFLOAT3 lookat,
        /*[in]*/    const XMFLOAT3 up);
 
    //---------------------------------------------
    /// カメラ情報と各種行列を更新し、シェーダーにコンパイルする
    /// \param[in] (worldMtx)		ワールド変換行列
    /// 
    /// \return void
    //--------------------------------------------- 
    int CameraUpdateConstBuff(
        /*[in]*/	const XMMATRIX worldMtx);

    //---------------------------------------------
    /// インスタンスの作成
    /// 
    /// \return void
    //--------------------------------------------- 
    static void CreateInstance();

    //---------------------------------------------
    /// インスタンスの削除
    /// 
    /// \return void
    //--------------------------------------------- 
    static void DeleteInstance();

    //---------------------------------------------
    /// インスタンスの取得
    /// 
    /// \return インスタンス
    //--------------------------------------------- 
    static D3D12Camera& GetInstance()
    {
        return *s_pInstance;
    }

    //---------------------------------------------
    /// 定数バッファのポインタを取得する
    /// 
    /// \return 定数バッファのポインタ
    //--------------------------------------------- 
    ID3D12Resource* getConstBufferPtr()
    {
        return m_pConstBuffer.Get();
    }
    //---------------------------------------------------------------------------

protected:

private:
    //---------------------------------------------------------------------------
    ComPtr<ID3D12Resource>  m_pConstBuffer;
    XMMATRIX m_pWorldMtx = {};
    XMMATRIX m_pViewMtx = {};
    XMMATRIX m_pProjMtx = {};

    static inline D3D12Camera* s_pInstance;
    //---------------------------------------------------------------------------
    /// <summary>
    /// m_pConstBuffer   定数バッファのポインタ
    /// m_pWorldMtx		ワールド変換行列（削除予定）
    /// m_pViewMtx	    ビュー変換行列
    /// m_pProjMtx		プロジェクション変換行列
    /// 
    /// s_pInstance      インスタンス
    /// </summary>

    //---------------------------------------------------------------------------
    //---------------------------------------------
    /// コンストラクタ
    /// 
    /// シングルトンのためprivateにして呼び出せなくする
    //--------------------------------------------- 
    D3D12Camera() {}
    //---------------------------------------------------------------------------
    
};

