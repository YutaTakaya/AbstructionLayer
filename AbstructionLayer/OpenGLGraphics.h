//==============================================================================
// Filename: OpenGLGraphics.h
// Description: OpenGL�̕`��V�X�e��
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================
#pragma once
#pragma comment (lib,"opengl32.lib")
#pragma comment (lib,"glu32.lib")
#include <windows.h>

class OpenGLGraphics
{
public:
    //---------------------------------------------------------------------------
    //---------------------------------------------
    /// OpenGL�̏������֐�
    ///
    /// \param[in] ( hWnd )         �E�B���h�E�n���h��
    /// \param[in] ( width )        �E�B���h�E�̕�
    /// \param[in] ( height )       �E�B���h�E�̍��� 
    ///
    /// \return �G���[�̏ꍇ-1�A����ɏI�������ꍇ0���Ԃ����
    //--------------------------------------------- 
    int OpenGLInit(
        /*[in]*/	const HWND hWnd,
        /*[in]*/	const int width,
        /*[in]*/	const int height);

    //---------------------------------------------
    /// OpenGL�̕`�掖�O����
    ///
    /// \return �G���[�̏ꍇ-1�A����ɏI�������ꍇ0���Ԃ����
    //--------------------------------------------- 
    int OpenGLBeforeRender();

    //---------------------------------------------
    /// OpenGL�̕`�掖�㏈��
    ///
    /// \return �G���[�̏ꍇ-1�A����ɏI�������ꍇ0���Ԃ����
    //--------------------------------------------- 
    int OpenGLAfterRender();

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
    static OpenGLGraphics& GetInstance()
    {
        return *s_pInstance;
    }
    //---------------------------------------------------------------------------

    HGLRC gethglrc()
    {
        return m_RenderingContext;
    }
protected:

private:
    //---------------------------------------------------------------------------
    HDC m_DeviceContext;
    HGLRC m_RenderingContext;

    static inline OpenGLGraphics* s_pInstance;
    //---------------------------------------------------------------------------

};

