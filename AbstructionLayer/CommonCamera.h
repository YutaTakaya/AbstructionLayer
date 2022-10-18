//==============================================================================
// Filename: CommonCamera.h
// Description: ���ۉ����C���[�p���ʃJ�����N���X
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================
#pragma once
#include "D3D12Camera.h"
#include "D3D11Camera.h"

class CommonCamera
{
public:
    //---------------------------------------------------------------------------

    //---------------------------------------------------------------------------


protected:

private:
    //---------------------------------------------------------------------------
    XMMATRIX m_pWorldMtx = {};
    XMMATRIX m_pViewMtx = {};
    XMMATRIX m_pProjMtx = {};
    //---------------------------------------------------------------------------
    /// <summary>
    /// m_pWorldMtx		���[���h�ϊ��s��i�폜�\��j
    /// m_pViewMtx	    �r���[�ϊ��s��
    /// m_pProjMtx		�v���W�F�N�V�����ϊ��s��
    /// 
    /// </summary>
};

