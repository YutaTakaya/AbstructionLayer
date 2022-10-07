//==============================================================================
// Filename: ObjData.h
// Description: �|���S�����y�ѕ`��V�X�e��
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================
#pragma once

#include "D3D11Graphics.h"
#include "D3D11Camera.h"
#include <vector>

struct VertexData
{
    XMFLOAT3 pos;
    XMFLOAT2 uv;
    XMFLOAT4 col;
};

class ObjData
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
        /*[in]*/    const int indexNum);

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
    void ObjDraw();

    //---------------------------------------------
    /// �����o�ϐ��̉������
    ///
    /// \return void
    //--------------------------------------------- 
    void ObjUninit();

    //---------------------------------------------
    /// ���[���h�ϊ��s��̉�]�p��ύX����
    /// 
    /// \param[in] (angleX)     �x���@�ł�X����]�x��
    /// \param[in] (angleY)     �x���@�ł�Y����]�x��
    /// \param[in] (angleZ)     �x���@�ł�Z����]�x��
    ///
    /// \return void
    //--------------------------------------------- 
    void ObjRotate(
        /*[in]*/    const float angleX,
        /*[in]*/    const float angleY,
        /*[in]*/    const float angleZ);

    //---------------------------------------------
    /// ���[���h�ϊ��s��̍��W��ύX����
    /// 
    /// \param[in] (posX)     X���W
    /// \param[in] (posY)     Y���W
    /// \param[in] (posZ)     Z���W
    ///
    /// \return void
    //--------------------------------------------- 
    void ObjTranslate(
        /*[in]*/    const float posX,
        /*[in]*/    const float posY,
        /*[in]*/    const float posZ);

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

    XMFLOAT3 m_worldPos;
    XMMATRIX m_localMtx;
    //---------------------------------------------------------------------------
    /// <summary>
    /// m_vertex                ���_���
    /// m_index                 �C���f�b�N�X�f�[�^
    /// m_vertexBuff            ���_�o�b�t�@
    /// m_indexBuff             �C���f�b�N�X�o�b�t�@
    /// m_texture               �e�N�X�`���o�b�t�@
    /// m_shaderResourceView	�V�F�[�_�[���\�[�X�r���[
	/// m_samplerState			�T���v���[�X�e�[�g
	/// 
	/// m_worldPos              ���[���h���W
	/// m_localMtx              ���[���h�ϊ��s��
    /// </summary>
};