//==============================================================================
// Filename: CommonResourceManager.h
// Description: ���ۉ����C���[�p���\�[�X�Ǘ��N���X
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================
#pragma once
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"d3dcompiler.lib")

#include <d3d11.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <wrl/client.h>
#include <dxgi1_6.h>
#include <vector>
#include <memory>

#include "D3D11Graphics.h"
#include "D3D12Graphics.h"
#include "D3D11Camera.h"
#include "D3D12Camera.h"
#include "D3D12Render.h"
#include "OpenGLGraphics.h"
#include "OpenGLCamera.h"

enum class APIType
{
    NONE,
    D3D11,
    D3D12,
    OPENGL,
    VULKAN
};

// �v���g�^�C�v�錾
class CommonObjData;
class D3D11ObjData;
class D3D12ObjData;
class OpenGLObjData;

class CommonResourceManager
{
public:
    //---------------------------------------------------------------------------
    //---------------------------------------------
    /// �������֐�
    ///
    /// \param[in] ( hWnd )         �E�B���h�E�n���h��
    /// \param[in] ( width )        �E�B���h�E�̕�
    /// \param[in] ( height )       �E�B���h�E�̍���
    /// \param[in] ( type )         API�̎��
    ///
    /// \return �G���[�̏ꍇ-1�A����ɏI�������ꍇ0���Ԃ����
    //--------------------------------------------- 
    int Init(
        /*[in]*/	const HWND hWnd,
        /*[in]*/	const int width,
        /*[in]*/	const int height,
        /*[in]*/    const APIType type);

    //---------------------------------------------
    /// �I�u�W�F�N�g�����֐�
    ///
    /// \param[out] ( hWnd )         �E�B���h�E�n���h��
    ///
    /// \return �G���[�̏ꍇ-1�A����ɏI�������ꍇ0���Ԃ����
    //---------------------------------------------     
    CommonObjData* CreateObject();

    //---------------------------------------------
    /// �`��O�����֐�
    ///
    /// \return void
    //--------------------------------------------- 
    int BeforeRenderer();

    //---------------------------------------------
    /// �`��㏈���֐�
    ///
    /// \return void
    //--------------------------------------------- 
    int AfterRenderer();

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
    static CommonResourceManager& GetInstance()
    {
        return *s_pInstance;
    }

    //---------------------------------------------
    /// �g�pAPI�̎擾
    /// 
    /// \return API�̎��
    //--------------------------------------------- 
    APIType getAPIType()
    {
        return m_nowType;
    }
protected:

private:
    //---------------------------------------------------------------------------
    APIType m_nowType = {};
    D3D12Render m_render = {};
    static inline CommonResourceManager* s_pInstance;
    //---------------------------------------------------------------------------
    /// <summary>
    /// m_nowType   �g�p����API�̎��
    /// D3D12Render DX12�Ŏg�p����`�揈��
    /// s_pInstance �C���X�^���X
    /// </summary>
};

