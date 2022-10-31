//==============================================================================
// Filename: OpenGLCamera.cpp
// Description: OpenGL�̃J�����y�уr���[�ϊ��s��̊Ǘ��N���X�A�V���O���g��
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================
#include "OpenGLCamera.h"

int OpenGLCamera::CameraInit(const FLOAT3 eye, const FLOAT3 lookat, const FLOAT3 up)
{
    //�v���W�F�N�V�����s��̐ݒ�
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-8.0 / 200.0, 8.0 / 200.0, -4.5 / 200.0, 4.5 / 200.0, 0.1, 100.0);	// ���Ȃ�]����

    m_eye = eye;
    m_lookat = lookat;
    m_up = up;
    //�r���[�ϊ��s��̐ݒ�
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        m_eye.x, m_eye.y, m_eye.z, // eye
        m_lookat.x, m_lookat.y, m_lookat.z,   // lookat
        m_up.x, m_up.y, m_up.z);  // up
    return 0;
}

void OpenGLCamera::CameraUpdate()
{
    if (m_updateFlag)
    {
        //�r���[�ϊ��s��̐ݒ�
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(
            m_eye.x, m_eye.y, m_eye.z, // eye
            m_lookat.x, m_lookat.y, m_lookat.z,   // lookat
            m_up.x, m_up.y, m_up.z);  // up
        m_updateFlag = false;
    }
}

void OpenGLCamera::CreateInstance()
{
    DeleteInstance();

    s_pInstance = new OpenGLCamera();
    CopyInstance(s_pInstance);
}

void OpenGLCamera::DeleteInstance()
{
    if (s_pInstance != nullptr)
    {
        delete s_pInstance;
        s_pInstance = nullptr;
        DeleteCopyInstance();
    }
}
