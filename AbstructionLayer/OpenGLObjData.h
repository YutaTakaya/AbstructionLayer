//==============================================================================
// Filename: OpenGLObjData.h
// Description: OpenGL�̃I�u�W�F�N�g�f�[�^
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================
#pragma once
#include "CommonObjData.h"
class OpenGLObjData : public CommonObjData
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
        /*[in]*/    const float angleZ) override;
protected:

private:
    //---------------------------------------------------------------------------
    std::vector<VertexData> m_vartex;
    std::vector<WORD> m_index;
    //---------------------------------------------------------------------------
    /// <summary>
    /// m_vertex        ���_�f�[�^
    /// m_index         �C���f�b�N�X�f�[�^
    /// </summary>
};

