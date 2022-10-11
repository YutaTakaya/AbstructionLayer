//==============================================================================
// Filename: D3D11Graphics.h
// Description: DirectX11�̕`��V�X�e��
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
	/// DirectX11�̏������֐�
	///
	/// \param[in] ( hWnd )         �E�B���h�E�n���h��
	/// \param[in] ( width )        �E�B���h�E�̕�
	/// \param[in] ( height )       �E�B���h�E�̍���
	///
	/// \return �G���[�̏ꍇ-1�A����ɏI�������ꍇ0���Ԃ����
	//--------------------------------------------- 
    int D3D11Init(
		/*[in]*/	const HWND hWnd,
		/*[in]*/	const int width,
		/*[in]*/	const int height);

	//---------------------------------------------
	/// �C���X�^���X�̍쐬
	//--------------------------------------------- 
	static void CreateInstance();

	//---------------------------------------------
	/// �C���X�^���X�̍폜
	//--------------------------------------------- 
	static void DeleteInstance();

	//---------------------------------------------
	/// �C���X�^���X�̎擾
	/// 
	/// \return �C���X�^���X
	//--------------------------------------------- 
	static D3D11Graphics& GetInstance()
	{
		return *s_pInstance;
	}

	//---------------------------------------------
	/// �f�o�C�X�̃|�C���^���擾����
	/// 
	/// \return �f�o�C�X�̃|�C���^
	//--------------------------------------------- 
	ID3D11Device* getDevPtr()
	{
		return m_pDevice.Get();
	}

	//---------------------------------------------
	/// �f�o�C�X�R���e�L�X�g�̃|�C���^���擾����
	/// 
	/// \return �f�o�C�X�R���e�L�X�g�̃|�C���^
	//--------------------------------------------- 
	ID3D11DeviceContext* getDevContextPtr()
	{
		return m_pDeviceContext.Get();
	}

	//---------------------------------------------
	/// �o�b�N�o�b�t�@�r���[�̃|�C���^���擾����
	/// 
	/// \return �o�b�N�o�b�t�@�r���[�̃|�C���^
	//--------------------------------------------- 
	ID3D11RenderTargetView* getBackBufferVierPtr()
	{
		return m_pBackBufferView.Get();
	}

	//---------------------------------------------
	/// �o�b�N�o�b�t�@�r���[�̃_�u���|�C���^���擾����
	/// 
	/// \return �o�b�N�o�b�t�@�r���[�̃_�u���|�C���^
	//--------------------------------------------- 
	ID3D11RenderTargetView** getBackBufferVierDPtr()
	{
		return m_pBackBufferView.GetAddressOf();
	}

	//---------------------------------------------
	/// �X���b�v�`�F�C���̃|�C���^���擾����
	/// 
	/// \return �X���b�v�`�F�C���̃|�C���^
	//--------------------------------------------- 
	IDXGISwapChain* getSwapChainPtr()
	{
		return m_pSwapChain.Get();
	}

	//---------------------------------------------
	/// ���@�[�e�b�N�X�V�F�[�_�[���̃|�C���^���擾����
	/// 
	/// \return ���@�[�e�b�N�X�V�F�[�_�[���̃|�C���^
	//--------------------------------------------- 
	ID3D11VertexShader* getVertexShaderPtr()
	{
		return m_pSpriteVS.Get();
	}

	//---------------------------------------------
	/// �s�N�Z���V�F�[�_�[���̃|�C���^���擾����
	/// 
	/// \return �s�N�Z���V�F�[�_�[���̃|�C���^
	//--------------------------------------------- 
	ID3D11PixelShader* getPixelShaderPtr()
	{
		return m_pSpritePS.Get();
	}

	//---------------------------------------------
	/// �C���v�b�g���C�A�E�g���̃|�C���^���擾����
	/// 
	/// \return �C���v�b�g���C�A�E�g���̃|�C���^
	//--------------------------------------------- 
	ID3D11InputLayout* getInputLayoutPtr()
	{
		return m_pSpriteInputLayout.Get();
	}

	//---------------------------------------------
	/// �����_�[�^�[�Q�b�g�r���[�̃_�u���|�C���^���擾����
	/// 
	/// \return �����_�[�^�[�Q�b�g�r���[�̃_�u���|�C���^
	//--------------------------------------------- 
	ID3D11RenderTargetView** getRenderTargetVierDPtr()
	{
		return m_pRenderTargetView.GetAddressOf();
	}

	//---------------------------------------------
	/// �����_�[�^�[�Q�b�g�r���[�̃|�C���^���擾����
	/// 
	/// \return �����_�[�^�[�Q�b�g�r���[�̃|�C���^
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
	/// m_pDevice				D3D11�f�o�C�X
	/// m_pDeviceContext			D3D11�f�o�C�X�R���e�L�X�g
	/// m_pBackBufferView		D3D11�o�b�N�o�b�t�@�\�r���[
	/// m_pSwapChain				�X���b�v�`�F�C��
	/// m_pDepthStencilTexture	�[�x�X�e���V���e�N�X�`��
	/// m_pRenderTargetView		RTV
	/// m_pDepthStencilView		�[�x�X�e���V���r���[

	/// 
	/// m_pSpriteVS				���_�V�F�[�_�[���
	/// m_pSpritePS				�s�N�Z���V�F�[�_�[���
	/// m_pSpriteInputLayout		���̓��C�A�E�g���
	/// 
	/// s_pInstance				�C���X�^���X
	/// </summary>


	//---------------------------------------------------------------------------
	//---------------------------------------------
	/// �R���X�g���N�^
	/// 
	/// �V���O���g���̂���private�ɂ��ČĂяo���Ȃ�����
	//--------------------------------------------- 
	D3D11Graphics() {}
	//---------------------------------------------------------------------------
};