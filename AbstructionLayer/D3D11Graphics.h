//==============================================================================
// Filename: D3D11Graphics.h
// Description: DirectX11の描画システム
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================
#pragma once

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"d3dcompiler.lib")

#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <wrl/client.h>
using Microsoft::WRL::ComPtr;

class D3D11Graphics
{
public:
	//---------------------------------------------------------------------------

	//---------------------------------------------
	/// DirectX11の初期化関数
	///
	/// \param[in] ( hWnd )         ウィンドウハンドル
	/// \param[in] ( width )        ウィンドウの幅
	/// \param[in] ( height )       ウィンドウの高さ
	///
	/// \return エラーの場合-1、正常に終了した場合0が返される
	//--------------------------------------------- 
    int InitD3D11(
		/*[in]*/	const HWND hWnd,
		/*[in]*/	const int width,
		/*[in]*/	const int height);

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
	static D3D11Graphics& GetInstance()
	{
		return *s_instance;
	}


	//---------------------------------------------
	/// デバイスのポインタを取得する
	/// 
	/// \return デバイスのポインタ
	//--------------------------------------------- 
	ID3D11Device* getDevPtr()
	{
		return m_device.Get();
	}

	//---------------------------------------------
	/// デバイスコンテキストのポインタを取得する
	/// 
	/// \return デバイスコンテキストのポインタ
	//--------------------------------------------- 
	ID3D11DeviceContext* getDevContextPtr()
	{
		return m_deviceContext.Get();
	}

	//---------------------------------------------
	/// バックバッファビューのポインタを取得する
	/// 
	/// \return バックバッファビューのポインタ
	//--------------------------------------------- 
	ID3D11RenderTargetView* getBackBufferVierPtr()
	{
		return m_backBufferView.Get();
	}

	//---------------------------------------------
	/// スワップチェインのポインタを取得する
	/// 
	/// \return スワップチェインのポインタ
	//--------------------------------------------- 
	IDXGISwapChain* getSwapChainPtr()
	{
		return m_swapChain.Get();
	}

	//---------------------------------------------
	/// ヴァーテックスシェーダー情報のポインタを取得する
	/// 
	/// \return ヴァーテックスシェーダー情報のポインタ
	//--------------------------------------------- 
	ID3D11VertexShader* getVertexShaderPtr()
	{
		return m_spriteVS.Get();
	}

	//---------------------------------------------
	/// ピクセルシェーダー情報のポインタを取得する
	/// 
	/// \return ピクセルシェーダー情報のポインタ
	//--------------------------------------------- 
	ID3D11PixelShader* getPixelShaderPtr()
	{
		return m_spritePS.Get();
	}

	//---------------------------------------------
	/// インプットレイアウト情報のポインタを取得する
	/// 
	/// \return インプットレイアウト情報のポインタ
	//--------------------------------------------- 
	ID3D11InputLayout* getInputLayoutPtr()
	{
		return m_spriteInputLayout.Get();
	}

	//---------------------------------------------------------------------------
protected:

private:
	//---------------------------------------------------------------------------
	HWND    m_hWnd;
    HINSTANCE   m_hInst;

    ComPtr<ID3D11Device>    m_device;
    ComPtr<ID3D11DeviceContext> m_deviceContext;
    ComPtr<ID3D11RenderTargetView>  m_backBufferView;
    ComPtr<IDXGISwapChain>  m_swapChain;

	ComPtr<ID3D11VertexShader> m_spriteVS = nullptr;
	ComPtr<ID3D11PixelShader> m_spritePS = nullptr;
	ComPtr<ID3D11InputLayout> m_spriteInputLayout = nullptr;

	static inline D3D11Graphics* s_instance;
	//---------------------------------------------------------------------------
	/// <summary>
	/// m_hWnd      ウィンドウハンドル
	/// m_hInst		インスタンスハンドル
	/// 
	/// m_device			D3D11デバイス
	/// m_deviceContext		D3D11デバイスコンテキスト
	/// m_backBufferView	D3D11バックバッファ―ビュー
	/// m_swapChain			スワップチェイン
	/// 
	/// m_spriteVS	頂点シェーダー情報
	/// m_spritePS	ピクセルシェーダー情報
	/// m_spriteInputLayout		入力レイアウト情報
	/// 
	/// s_instance	インスタンス
	/// </summary>


	//---------------------------------------------------------------------------
	//---------------------------------------------
	/// コンストラクタ
	/// 
	/// シングルトンのためprivateにして呼び出せなくする
	//--------------------------------------------- 
	D3D11Graphics() {}
	//---------------------------------------------------------------------------


};


