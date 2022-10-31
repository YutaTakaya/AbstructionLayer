//==============================================================================
// Filename: D3D11Render.h
// Description: DirectX11ObjData�̋��ʕ`�揈���p�N���X
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================
#pragma once
#include "D3D11Graphics.h"
#include "D3D11Camera.h"
class D3D11Render
{
public:
    //---------------------------------------------------------------------------

    //---------------------------------------------
    /// ���[�g�V�O�l�`���ƃp�C�v���C���̏�����
    ///
    /// \return �G���[���o���ꍇ-1���A����ɏI�������ꍇ0���Ԃ����
    //--------------------------------------------- 
    int D3D11RenderInit();

    //---------------------------------------------
    /// D3D12ObjData�̕`��O����
    ///
    /// \return void
    //--------------------------------------------- 
    void D3D11RenderSet();

    //---------------------------------------------------------------------------

protected:

private:
    //---------------------------------------------------------------------------
    ComPtr<ID3D11VertexShader> m_pSpriteVS = nullptr;
    ComPtr<ID3D11PixelShader> m_pSpritePS = nullptr;
    ComPtr<ID3D11InputLayout> m_pSpriteInputLayout = nullptr;
    //---------------------------------------------------------------------------
    /// <summary>
    /// m_pRootSignature    ���[�g�V�O�l�`��
    /// m_pPipelineState    �O���t�B�b�N�X�p�C�v���C��
    /// </summary>
};

