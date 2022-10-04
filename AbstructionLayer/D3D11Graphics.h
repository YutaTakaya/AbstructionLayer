#pragma once
//==============================================================================
// Filename: D3D11Graphics.h
// Description: DirectX11の描画システム
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================

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
	// public methods
	//---------------------------------------------------------------------------

    int InitD3D11(HWND hWnd, int width, int height);

	// インスタンス作成
	static void CreateInstance()
	{
		DeleteInstance();

		s_instance = new D3D11Graphics();
	}
	// インスタンス削除
	static void DeleteInstance()
	{
		if (s_instance != nullptr)
		{
			delete s_instance;
			s_instance = nullptr;
		}
	}
	// 唯一のインスタンスを取得
	static D3D11Graphics& GetInstance()
	{
		return *s_instance;
	}


	// 各種ゲッター
	ID3D11Device* getDevPtr()
	{
		return m_device.Get();
	}

	ID3D11DeviceContext* getDevContextPtr()
	{
		return m_deviceContext.Get();
	}

	ID3D11RenderTargetView* getBackBufferVierPtr()
	{
		return m_backBufferView.Get();
	}

	IDXGISwapChain* getSwapChainPtr()
	{
		return m_swapChain.Get();
	}
	ID3D11VertexShader* getVertexShaderPtr()
	{
		return m_spriteVS.Get();
	}
	ID3D11PixelShader* getPixelShaderPtr()
	{
		return m_spritePS.Get();
	}
	ID3D11InputLayout* getInputLayoutPtr()
	{
		return m_spriteInputLayout.Get();
	}
protected:

private:
	//---------------------------------------------------------------------------
	// private variables
	//---------------------------------------------------------------------------
    
	HWND    m_hWnd;
    HINSTANCE   m_hInst;

    ComPtr<ID3D11Device>    m_device;
    ComPtr<ID3D11DeviceContext> m_deviceContext;
    ComPtr<ID3D11RenderTargetView>  m_backBufferView;
    ComPtr<IDXGISwapChain>  m_swapChain;

	// シェーダー
	ComPtr<ID3D11VertexShader> m_spriteVS = nullptr;
	ComPtr<ID3D11PixelShader> m_spritePS = nullptr;
	ComPtr<ID3D11InputLayout> m_spriteInputLayout = nullptr;

	// 唯一のインスタンス用のポインタ
	static inline D3D11Graphics* s_instance;

	//---------------------------------------------------------------------------
	// private methods
	//---------------------------------------------------------------------------

	// コンストラクタはprivateにする
	D3D11Graphics() {}
};


