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
    int D3D11Init(
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
		return *s_pInstance;
	}

	//---------------------------------------------
	/// デバイスのポインタを取得する
	/// 
	/// \return デバイスのポインタ
	//--------------------------------------------- 
	ID3D11Device* getDevPtr()
	{
		return m_pDevice.Get();
	}

	//---------------------------------------------
	/// デバイスコンテキストのポインタを取得する
	/// 
	/// \return デバイスコンテキストのポインタ
	//--------------------------------------------- 
	ID3D11DeviceContext* getDevContextPtr()
	{
		return m_pDeviceContext.Get();
	}

	//---------------------------------------------
	/// バックバッファビューのポインタを取得する
	/// 
	/// \return バックバッファビューのポインタ
	//--------------------------------------------- 
	ID3D11RenderTargetView* getBackBufferVierPtr()
	{
		return m_pBackBufferView.Get();
	}

	//---------------------------------------------
	/// バックバッファビューのダブルポインタを取得する
	/// 
	/// \return バックバッファビューのダブルポインタ
	//--------------------------------------------- 
	ID3D11RenderTargetView** getBackBufferVierDPtr()
	{
		return m_pBackBufferView.GetAddressOf();
	}

	//---------------------------------------------
	/// スワップチェインのポインタを取得する
	/// 
	/// \return スワップチェインのポインタ
	//--------------------------------------------- 
	IDXGISwapChain* getSwapChainPtr()
	{
		return m_pSwapChain.Get();
	}

	//---------------------------------------------
	/// ヴァーテックスシェーダー情報のポインタを取得する
	/// 
	/// \return ヴァーテックスシェーダー情報のポインタ
	//--------------------------------------------- 
	ID3D11VertexShader* getVertexShaderPtr()
	{
		return m_pSpriteVS.Get();
	}

	//---------------------------------------------
	/// ピクセルシェーダー情報のポインタを取得する
	/// 
	/// \return ピクセルシェーダー情報のポインタ
	//--------------------------------------------- 
	ID3D11PixelShader* getPixelShaderPtr()
	{
		return m_pSpritePS.Get();
	}

	//---------------------------------------------
	/// インプットレイアウト情報のポインタを取得する
	/// 
	/// \return インプットレイアウト情報のポインタ
	//--------------------------------------------- 
	ID3D11InputLayout* getInputLayoutPtr()
	{
		return m_pSpriteInputLayout.Get();
	}

	//---------------------------------------------
	/// レンダーターゲットビューのダブルポインタを取得する
	/// 
	/// \return レンダーターゲットビューのダブルポインタ
	//--------------------------------------------- 
	ID3D11RenderTargetView** getRenderTargetVierDPtr()
	{
		return m_pRenderTargetView.GetAddressOf();
	}

	//---------------------------------------------
	/// レンダーターゲットビューのポインタを取得する
	/// 
	/// \return レンダーターゲットビューのポインタ
	//--------------------------------------------- 
	ID3D11DepthStencilView* getDepthStencilVierPtr()
	{
		return m_pDepthStencilView.Get();
	}

	//---------------------------------------------------------------------------
protected:

private:
	//---------------------------------------------------------------------------
    ComPtr<ID3D11Device>    m_pDevice;
    ComPtr<ID3D11DeviceContext> m_pDeviceContext;
    ComPtr<ID3D11RenderTargetView>  m_pBackBufferView;
    ComPtr<IDXGISwapChain>  m_pSwapChain;
	ComPtr<ID3D11Texture2D> m_pDepthStencilTexture;
	ComPtr<ID3D11RenderTargetView>	m_pRenderTargetView;
	ComPtr<ID3D11DepthStencilView>	m_pDepthStencilView;

	ComPtr<ID3D11VertexShader> m_pSpriteVS = nullptr;
	ComPtr<ID3D11PixelShader> m_pSpritePS = nullptr;
	ComPtr<ID3D11InputLayout> m_pSpriteInputLayout = nullptr;

	static inline D3D11Graphics* s_pInstance;
	//---------------------------------------------------------------------------
	/// <summary>
	/// m_pDevice				D3D11デバイス
	/// m_pDeviceContext			D3D11デバイスコンテキスト
	/// m_pBackBufferView		D3D11バックバッファ―ビュー
	/// m_pSwapChain				スワップチェイン
	/// m_pDepthStencilTexture	深度ステンシルテクスチャ
	/// m_pRenderTargetView		RTV
	/// m_pDepthStencilView		深度ステンシルビュー

	/// 
	/// m_pSpriteVS				頂点シェーダー情報
	/// m_pSpritePS				ピクセルシェーダー情報
	/// m_pSpriteInputLayout		入力レイアウト情報
	/// 
	/// s_pInstance				インスタンス
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