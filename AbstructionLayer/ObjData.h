//==============================================================================
// Filename: ObjData.h
// Description: �|���S�����y�ѕ`��V�X�e��
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================
#pragma once

#include "D3D11Graphics.h"
#include <vector>

struct VertexData
{
    DirectX::XMFLOAT3 pos;
    DirectX::XMFLOAT2 uv;
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
    /// ���_����p����DirectX11�ł̕`�揈��
    ///
    /// \return ����ɏI�������ꍇ0���Ԃ����
    //--------------------------------------------- 
    int ObjDraw();

    //---------------------------------------------
    /// �����o�ϐ��̉������
    ///
    /// \return ����ɏI�������ꍇ0���Ԃ����
    //--------------------------------------------- 
    int ObjUninit();

    //---------------------------------------------------------------------------

protected:

private:
    //---------------------------------------------------------------------------
    std::vector<VertexData> m_vertex;
    std::vector<WORD> m_index;
    ComPtr<ID3D11Buffer> m_vertexBuff;
    ComPtr<ID3D11Buffer> m_indexBuff;
    ComPtr<ID3D11Buffer> m_texBuff;
    //---------------------------------------------------------------------------
    /// <summary>
    /// m_vertex        ���_���
    /// m_index         �C���f�b�N�X�f�[�^
    /// m_vertexBuff    ���_�o�b�t�@
    /// m_indexBuff     �C���f�b�N�X�o�b�t�@
    /// m_textureBuff   �e�N�X�`���o�b�t�@
    /// </summary>
};

//  TODO : ���[���h�ϊ��s��̍쐬�y��Camera�N���X����̈�������
