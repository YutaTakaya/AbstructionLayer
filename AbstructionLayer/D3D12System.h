//==============================================================================
// Filename: D3D12System.h
// Description: DirectX12�̊�{����
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================

#include "ObjData.h"

//---------------------------------------------
/// �I�u�W�F�N�g�f�[�^�̏���������
///
/// \return ����ɏI�������ꍇ0���Ԃ����
//--------------------------------------------- 
int D3D12Init();

//---------------------------------------------
/// �I�u�W�F�N�g�f�[�^�̃A�b�v�f�[�g����
///
/// \return void
//--------------------------------------------- 
void D3D12Update();

//---------------------------------------------
/// DirectX11�ł̕`�揈��
///
/// \return void
//--------------------------------------------- 
void D3D12Render();

//---------------------------------------------
/// �I�u�W�F�N�g�f�[�^�̉������
///
/// \return void
//--------------------------------------------- 
void D3D12Uninit();