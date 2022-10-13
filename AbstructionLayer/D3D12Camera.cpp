//==============================================================================
// Filename: D3D12Camera.cpp
// Description: D3D12�̃J�����y�уr���[�ϊ��s��̊Ǘ��N���X�A�V���O���g��
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================
#include "D3D12Camera.h"

int D3D12Camera::CameraInit(const XMFLOAT3 eye, const XMFLOAT3 lockat, const XMFLOAT3 up)
{
    // �萔�o�b�t�@�[�̍쐬
    //D3D12Graphics::GetInstance().getDevPtr()->CreateCommittedResource(
    //    &);
    return 0;
}

int D3D12Camera::CameraUpdateConstBuff(const XMMATRIX worldMtx)
{
    return 0;
}

void D3D12Camera::CreateInstance()
{
    DeleteInstance();

    s_pInstance = new D3D12Camera();
}

void D3D12Camera::DeleteInstance()
{
    if (s_pInstance != nullptr)
    {
        delete s_pInstance;
        s_pInstance = nullptr;
    }
}
