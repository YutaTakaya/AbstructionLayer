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
    int InitD3D11(
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
		return *s_instance;
	}


	//---------------------------------------------
	/// �f�o�C�X�̃|�C���^���擾����
	/// 
	/// \return �f�o�C�X�̃|�C���^
	//--------------------------------------------- 
	ID3D11Device* getDevPtr()
	{
		return m_device.Get();
	}

	//---------------------------------------------
	/// �f�o�C�X�R���e�L�X�g�̃|�C���^���擾����
	/// 
	/// \return �f�o�C�X�R���e�L�X�g�̃|�C���^
	//--------------------------------------------- 
	ID3D11DeviceContext* getDevContextPtr()
	{
		return m_deviceContext.Get();
	}

	//---------------------------------------------
	/// �o�b�N�o�b�t�@�r���[�̃|�C���^���擾����
	/// 
	/// \return �o�b�N�o�b�t�@�r���[�̃|�C���^
	//--------------------------------------------- 
	ID3D11RenderTargetView* getBackBufferVierPtr()
	{
		return m_backBufferView.Get();
	}

	//---------------------------------------------
	/// �X���b�v�`�F�C���̃|�C���^���擾����
	/// 
	/// \return �X���b�v�`�F�C���̃|�C���^
	//--------------------------------------------- 
	IDXGISwapChain* getSwapChainPtr()
	{
		return m_swapChain.Get();
	}

	//---------------------------------------------
	/// ���@�[�e�b�N�X�V�F�[�_�[���̃|�C���^���擾����
	/// 
	/// \return ���@�[�e�b�N�X�V�F�[�_�[���̃|�C���^
	//--------------------------------------------- 
	ID3D11VertexShader* getVertexShaderPtr()
	{
		return m_spriteVS.Get();
	}

	//---------------------------------------------
	/// �s�N�Z���V�F�[�_�[���̃|�C���^���擾����
	/// 
	/// \return �s�N�Z���V�F�[�_�[���̃|�C���^
	//--------------------------------------------- 
	ID3D11PixelShader* getPixelShaderPtr()
	{
		return m_spritePS.Get();
	}

	//---------------------------------------------
	/// �C���v�b�g���C�A�E�g���̃|�C���^���擾����
	/// 
	/// \return �C���v�b�g���C�A�E�g���̃|�C���^
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
	/// m_hWnd      �E�B���h�E�n���h��
	/// m_hInst		�C���X�^���X�n���h��
	/// 
	/// m_device			D3D11�f�o�C�X
	/// m_deviceContext		D3D11�f�o�C�X�R���e�L�X�g
	/// m_backBufferView	D3D11�o�b�N�o�b�t�@�\�r���[
	/// m_swapChain			�X���b�v�`�F�C��
	/// 
	/// m_spriteVS	���_�V�F�[�_�[���
	/// m_spritePS	�s�N�Z���V�F�[�_�[���
	/// m_spriteInputLayout		���̓��C�A�E�g���
	/// 
	/// s_instance	�C���X�^���X
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


