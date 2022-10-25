//==============================================================================
// Filename: D3D11Camera.h
// Description: D3D11�̃J�����y�уr���[�ϊ��s��̊Ǘ��N���X�A�V���O���g��
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================
#pragma once
#include "CommonCamera.h"
#include "D3D11Graphics.h"
#include <wrl/client.h>
using Microsoft::WRL::ComPtr;
using namespace DirectX;

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
	/// �J�������̏����ݒ�ƃr���[�ϊ��s��A�v���W�F�N�V�����ϊ��s��̏�����
	///
	/// \param[in] (eye)		�J�����ʒu
	/// \param[in] (lookat)     �J�����̒����_
	/// \param[in] (up)		�J�����̏����
	///
	/// \return �G���[���o���ꍇ-1���A����ɏI�������ꍇ0���Ԃ����
	//--------------------------------------------- 
    int CameraInit(
        /*[in]*/    const FLOAT3 eye, 
        /*[in]*/    const FLOAT3 lookat,
        /*[in]*/    const FLOAT3 up);

	//---------------------------------------------
	/// �J�������Ɗe��s����X�V���A�V�F�[�_�[�ɃR���p�C������
	/// \param[in] (worldMtx)		���[���h�ϊ��s��
	/// 
	/// \return void
	//--------------------------------------------- 
    int CameraUpdateConstBuff(
		/*[in]*/	const XMMATRIX worldMtx);

	//---------------------------------------------
	/// �C���X�^���X�̍쐬
	/// 
	/// \return void
	//--------------------------------------------- 
	static void CreateInstance();

	//---------------------------------------------
	/// �C���X�^���X�̍폜
	/// 
	/// \return void
	//--------------------------------------------- 
	static void DeleteInstance();

	//---------------------------------------------
	/// �C���X�^���X�̎擾
	/// 
	/// \return �C���X�^���X
	//--------------------------------------------- 
	static D3D11Camera& GetInstance()
	{
		return *s_pInstance;
	}

protected:


private:
	//---------------------------------------------------------------------------
    ComPtr<ID3D11Buffer> m_pConstBuffer;
	XMMATRIX m_pWorldMtx = {};
	XMMATRIX m_pViewMtx = {};
	XMMATRIX m_pProjMtx = {};

	static inline D3D11Camera* s_pInstance;

	//---------------------------------------------------------------------------
	/// <summary>
	/// m_pConstBuffer   �萔�o�b�t�@�̃|�C���^
	/// m_pWorldMtx		���[���h�ϊ��s��i�폜�\��j
	/// m_pViewMtx	    �r���[�ϊ��s��
	/// m_pProjMtx		�v���W�F�N�V�����ϊ��s��
	/// 
	/// s_pInstance      �C���X�^���X
	/// </summary>

	//---------------------------------------------------------------------------
	//---------------------------------------------
	/// �R���X�g���N�^
	/// 
	/// �V���O���g���̂���private�ɂ��ČĂяo���Ȃ�����
	//--------------------------------------------- 
	D3D11Camera() {}
	//---------------------------------------------------------------------------
};

