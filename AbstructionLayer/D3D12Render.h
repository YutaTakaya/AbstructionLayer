//==============================================================================
// Filename: D3D12Render.h
// Description: DirectX12ObjData�̋��ʕ`�揈���p�N���X
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================

#pragma once
#include "D3D12Graphics.h"
#include "D3D12Camera.h"
class D3D12Render
{
public:
    //---------------------------------------------------------------------------

    //---------------------------------------------
    /// ���[�g�V�O�l�`���ƃp�C�v���C���̏�����
    ///
    /// \return �G���[���o���ꍇ-1���A����ɏI�������ꍇ0���Ԃ����
    //--------------------------------------------- 
    int D3D12RenderInit();

    //---------------------------------------------
    /// D3D12ObjData�̕`��O����
    ///
    /// \return void
    //--------------------------------------------- 
    void D3D12RenderSet();

    //---------------------------------------------------------------------------

protected:

private:
    //---------------------------------------------------------------------------
    ComPtr<ID3D12RootSignature> m_pRootSignature;
    ComPtr<ID3D12PipelineState> m_pPipelineState;
    //---------------------------------------------------------------------------
    /// <summary>
    /// m_pRootSignature    ���[�g�V�O�l�`��
    /// m_pPipelineState    �O���t�B�b�N�X�p�C�v���C��
    /// </summary>
};
