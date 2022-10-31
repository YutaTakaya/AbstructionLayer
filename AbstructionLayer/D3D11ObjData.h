//==============================================================================
// Filename: D3D11ObjData.h
// Description: �|���S�����y�ѕ`��V�X�e��
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================
#pragma once

#include "CommonObjData.h"
#include "D3D11Graphics.h"
#include "D3D11Camera.h"
#include "D3D11Render.h"
#include <vector>

class D3D11ObjData : public CommonObjData
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
        /*[in]*/    const VertexData* p_VData,
        /*[in]*/    const int vNum,
        /*[in]*/    const WORD* p_indexData,
        /*[in]*/    const int indexNum) override;

    //---------------------------------------------
    /// �s��̍X�V
    ///
    /// \return void
    //--------------------------------------------- 
    void ObjUpdate();

    //---------------------------------------------
    /// ���_����p����DirectX11�ł̕`�揈��
    ///
    /// \return void
    //--------------------------------------------- 
    void ObjDraw() override;

    //---------------------------------------------
    /// �����o�ϐ��̉������
    ///
    /// \return void
    //--------------------------------------------- 
    void ObjUninit();



    //---------------------------------------------------------------------------

protected:

private:
    //---------------------------------------------------------------------------
    std::vector<VertexData> m_vertex;
    std::vector<WORD> m_index;
    ComPtr<ID3D11Buffer> m_pVertexBuff;
    ComPtr<ID3D11Buffer> m_pIndexBuff;

    ComPtr<ID3D11Texture2D>	m_pTexture;
    ComPtr<ID3D11ShaderResourceView>	m_pShaderResourceView;
    ComPtr<ID3D11SamplerState>	m_pSamplerState;

    D3D11Render m_Render;
    //---------------------------------------------------------------------------
    /// <summary>
    /// m_vertex                ���_���
    /// m_index                 �C���f�b�N�X�f�[�^
    /// m_vertexBuff            ���_�o�b�t�@
    /// m_indexBuff             �C���f�b�N�X�o�b�t�@
    /// 
    /// m_texture               �e�N�X�`���o�b�t�@
    /// m_shaderResourceView	�V�F�[�_�[���\�[�X�r���[
	/// m_samplerState			�T���v���[�X�e�[�g
	/// 
	/// m_Render                �I�u�W�F�N�g���Ƃ̕`��V�X�e��
    /// </summary>
};