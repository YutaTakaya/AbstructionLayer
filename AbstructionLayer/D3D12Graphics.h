//==============================================================================
// Filename: D3D12Graphics.h
// Description: DirectX12�̕`��V�X�e��
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================
#pragma once

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"d3dcompiler.lib")

#include <d3d12.h>
#include <dxgi1_6.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <wrl/client.h>
#include <vector>

using Microsoft::WRL::ComPtr;

class D3D12Graphics
{
public:
	//---------------------------------------------------------------------------
	//---------------------------------------------
	/// DirectX12�̏������֐�
	///
	/// \param[in] ( hWnd )         �E�B���h�E�n���h��
	/// \param[in] ( width )        �E�B���h�E�̕�
	/// \param[in] ( height )       �E�B���h�E�̍���
	///
	/// \return �G���[�̏ꍇ-1�A����ɏI�������ꍇ0���Ԃ����
	//--------------------------------------------- 
	int D3D12Init(
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
	static D3D12Graphics& GetInstance()
	{
		return *s_pInstance;
	}

    //---------------------------------------------
    /// �f�o�C�X�̃|�C���^���擾����
    /// 
    /// \return �f�o�C�X�̃|�C���^
    //--------------------------------------------- 
    ID3D12Device* getDevPtr()
    {
        return m_pDevice.Get();
    }

    //---------------------------------------------
    /// �X���b�v�`�F�C���̃|�C���^���擾����
    /// 
    /// \return �X���b�v�`�F�C���̃|�C���^
    //--------------------------------------------- 
    IDXGISwapChain4* getSwapChainPtr()
    {
        return m_pSwapChain.Get();
    }

    //---------------------------------------------
    /// �R�}���h���X�g�̃|�C���^���擾����
    /// 
    /// \return �R�}���h���X�g�̃|�C���^
    //--------------------------------------------- 
    ID3D12GraphicsCommandList* getCmdPtr()
    {
        return m_pCommandList.Get();
    }

    //---------------------------------------------
    /// �R�}���h�L���[�̃|�C���^���擾����
    /// 
    /// \return �R�}���h�L���[�̃|�C���^
    //--------------------------------------------- 
    ID3D12CommandQueue* getQueuePtr()
    {
        return m_pCommandQueue.Get();
    }

    //---------------------------------------------
    /// RTV�q�[�v�̃|�C���^���擾����
    /// 
    /// \return RTV�q�[�v�̃|�C���^
    //--------------------------------------------- 
    ID3D12DescriptorHeap* getRTVHeapPtr()
    {
        return m_pRtvHeaps.Get();
    }


    //---------------------------------------------
    /// �R�}���h�A���P�[�^�[�̃|�C���^���擾����
    /// 
    /// \return �R�}���h�A���P�[�^�[�̃|�C���^
    //--------------------------------------------- 
    ID3D12CommandAllocator* getAllocatorPtr()
    {
        return m_pCommandAllocator.Get();
    }

    //---------------------------------------------
    /// �t�F���X�̃|�C���^���擾����
    /// 
    /// \return �t�F���X�̃|�C���^
    //--------------------------------------------- 
    ID3D12Fence* getFencePtr()
    {
        return m_pFence.Get();
    }

	//---------------------------------------------------------------------------

protected:
    
private:
	//---------------------------------------------------------------------------
	ComPtr<ID3D12Device>    m_pDevice;
	ComPtr<IDXGISwapChain4>  m_pSwapChain;
    ComPtr<ID3D12GraphicsCommandList>   m_pCommandList;
    ComPtr<ID3D12CommandQueue>  m_pCommandQueue;
    ComPtr<ID3D12DescriptorHeap> m_pRtvHeaps;
    std::vector<ID3D12Resource*> m_pBackBuffers;
    ComPtr<ID3D12CommandAllocator>  m_pCommandAllocator;
    ComPtr<ID3D12Fence> m_pFence;

	static inline D3D12Graphics* s_pInstance;
	//---------------------------------------------------------------------------
	/// <summary>
	/// </summary>
};
