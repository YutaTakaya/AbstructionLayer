//==============================================================================
// Filename: D3D11Camera.h
// Description: D3D11のカメラ及びビュー変換行列の管理クラス、シングルトン
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================
#pragma once
#include "D3D11Graphics.h"
#include <wrl/client.h>
using Microsoft::WRL::ComPtr;

struct ConstantBuffer {
    DirectX::XMFLOAT4X4 world;
    DirectX::XMFLOAT4X4 view;
    DirectX::XMFLOAT4X4 projection;
};

class D3D11Camera
{
public:
	//---------------------------------------------------------------------------
	//---------------------------------------------
	/// カメラ情報の初期設定とビュー変換行列、プロジェクション変換行列の初期化
	///
	/// \param[in] (eye)		カメラ位置
	/// \param[in] (lockat)     カメラの注視点
	/// \param[in] (up)		カメラの上方向
	///
	/// \return エラーが出た場合-1が、正常に終了した場合0が返される
	//--------------------------------------------- 
    int CameraInit(
        /*[in]*/    const DirectX::XMFLOAT3 eye, 
        /*[in]*/    const DirectX::XMFLOAT3 lockat,
        /*[in]*/    const DirectX::XMFLOAT3 up);

	//---------------------------------------------
	/// カメラ情報と各種行列をシェーダーにコンパイルする
	//--------------------------------------------- 
    int CameraDraw();

	//---------------------------------------------
	/// インスタンスの作成
	//--------------------------------------------- 
	static void CreateInstance();

	//---------------------------------------------
	/// インスタンスの削除
	//--------------------------------------------- 
	static void DeleteInstance();

	//---------------------------------------------
	/// インスタンスの取得
	/// 
	/// \return インスタンス
	//--------------------------------------------- 
	static D3D11Camera& GetInstance()
	{
		return *s_instance;
	}

protected:


private:
	//---------------------------------------------------------------------------
    ComPtr<ID3D11Buffer> m_constBuffer;
	DirectX::XMMATRIX m_worldMtx;
	DirectX::XMMATRIX m_viewMtx;
	DirectX::XMMATRIX m_projMtx;

	static inline D3D11Camera* s_instance;

	//---------------------------------------------------------------------------
	/// <summary>
	/// m_constBuffer   定数バッファのポインタ
	/// m_worldMtx		ワールド変換行列（削除予定）
	/// m_viewMtx	    ビュー変換行列
	/// m_projMtx		プロジェクション変換行列
	/// 
	/// s_instance      インスタンス
	/// </summary>

	//---------------------------------------------------------------------------
	//---------------------------------------------
	/// コンストラクタ
	/// 
	/// シングルトンのためprivateにして呼び出せなくする
	//--------------------------------------------- 
	D3D11Camera() {}
	//---------------------------------------------------------------------------
};

