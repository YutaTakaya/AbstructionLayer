#pragma once
//==============================================================================
// Filename:Application.h
// Description:
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"dxgi.lib")

#include <d3d11.h>
#include <DirectXMath.h>

#include <wrl/client.h>
using Microsoft::WRL::ComPtr;

class CD3D11Graphics
{
public:
    int InitD3D11(HWND hWnd, int width, int height);

	// �C���X�^���X�쐬
	static void CreateInstance()
	{
		DeleteInstance();

		s_instance = new CD3D11Graphics();
	}
	// �C���X�^���X�폜
	static void DeleteInstance()
	{
		if (s_instance != nullptr)
		{
			delete s_instance;
			s_instance = nullptr;
		}
	}
	// �B��̃C���X�^���X���擾
	static CD3D11Graphics& GetInstance()
	{
		return *s_instance;
	}


	// �e��Q�b�^�[
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
protected:

private:
    HWND    m_hWnd;
    HINSTANCE   m_hInst;

    ComPtr<ID3D11Device>    m_device;
    ComPtr<ID3D11DeviceContext> m_deviceContext;
    ComPtr<ID3D11RenderTargetView>  m_backBufferView;
    ComPtr<IDXGISwapChain>  m_swapChain;

	// �B��̃C���X�^���X�p�̃|�C���^
	static inline CD3D11Graphics* s_instance;
	// �R���X�g���N�^��private�ɂ���
	CD3D11Graphics() {}
};


