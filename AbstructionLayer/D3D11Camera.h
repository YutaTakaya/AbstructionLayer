//==============================================================================
// Filename: D3D11Camera.h
// Description: D3D11�̃J�����y�уr���[�ϊ��s��̊Ǘ��N���X�A�V���O���g��
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
	/// �J�������̏����ݒ�ƃr���[�ϊ��s��A�v���W�F�N�V�����ϊ��s��̏�����
	///
	/// \param[in] (eye)		�J�����ʒu
	/// \param[in] (lockat)     �J�����̒����_
	/// \param[in] (up)		�J�����̏����
	///
	/// \return �G���[���o���ꍇ-1���A����ɏI�������ꍇ0���Ԃ����
	//--------------------------------------------- 
    int CameraInit(
        /*[in]*/    const DirectX::XMFLOAT3 eye, 
        /*[in]*/    const DirectX::XMFLOAT3 lockat,
        /*[in]*/    const DirectX::XMFLOAT3 up);

	//---------------------------------------------
	/// �J�������Ɗe��s����V�F�[�_�[�ɃR���p�C������
	//--------------------------------------------- 
    int CameraDraw();

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
	/// m_constBuffer   �萔�o�b�t�@�̃|�C���^
	/// m_worldMtx		���[���h�ϊ��s��i�폜�\��j
	/// m_viewMtx	    �r���[�ϊ��s��
	/// m_projMtx		�v���W�F�N�V�����ϊ��s��
	/// 
	/// s_instance      �C���X�^���X
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

