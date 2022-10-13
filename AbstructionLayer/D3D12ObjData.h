//==============================================================================
// Filename: D3D12ObjData.h
// Description: DirectX12�̃I�u�W�F�N�g�f�[�^
//              �iDirectX12�ł̃f�o�b�O�p�ł���A�ŏI�I�ɂ�11�̕��Ɠ����\��j
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================
#pragma once
#include "D3D12Graphics.h"
using namespace DirectX;
struct VertexData12
{
    XMFLOAT3 pos;
    //XMFLOAT2 uv;
    //XMFLOAT4 col;
};

class D3D12ObjData
{
public:
    //---------------------------------------------------------------------------

    //---------------------------------------------
    /// ���_�A�C���f�b�N�X���̕ۑ��Ƃ����̃o�b�t�@�̍쐬
    ///
    /// \param[in] (p_VData)    ���_���z��
    /// \param[in] (vNum)       p_VData�̔z��
    /// \param[in] (p_indexData)    �C���f�b�N�X�z��
    /// \param[in] (indexNum)   p_indexData�̔z��
    ///
    /// \return �G���[���o���ꍇ-1���A����ɏI�������ꍇ0���Ԃ����
    //--------------------------------------------- 
    int ObjInit(
        /*[in]*/    const VertexData12* p_VData,
        /*[in]*/    const int vNum,
        /*[in]*/    const WORD* p_indexData,
        /*[in]*/    const int indexNum);
    
    //---------------------------------------------
    /// ���_����p����DirectX12�ł̕`�揈��
    ///
    /// \return void
    //--------------------------------------------- 
    void ObjDraw();

    //---------------------------------------------------------------------------

protected:

private:
    //---------------------------------------------------------------------------
    ComPtr<ID3D12Resource>  m_pVertexBuffer;
    D3D12_VERTEX_BUFFER_VIEW    m_vertexBufferView;
    ComPtr<ID3D12PipelineState> m_pPipelineState;
    ComPtr<ID3D12RootSignature> m_pRootSignature;
    //---------------------------------------------------------------------------
    /// <summary>
    /// </summary>
};

