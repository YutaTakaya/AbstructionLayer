//==============================================================================
// Filename: CommonObjData.h
// Description: ���ۉ����C���[�p���ʃI�u�W�F�N�g�f�[�^
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================
#pragma once
#include "CommonResourceManager.h"

struct VertexData
{
    XMFLOAT3 pos;
    XMFLOAT2 uv;
    XMFLOAT4 col;
};

class CommonObjData
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
    virtual int ObjInit(
        /*[in]*/    const VertexData* p_VData,
        /*[in]*/    const int vNum,
        /*[in]*/    const WORD* p_indexData,
        /*[in]*/    const int indexNum);

    //---------------------------------------------
    /// ���_����p�����`�揈��
    ///
    /// \return void
    //--------------------------------------------- 
    virtual void ObjDraw();

    //---------------------------------------------
    /// ���[���h�ϊ��s��̉�]�p��ύX����
    /// 
    /// \param[in] (angleX)     �x���@�ł�X����]�x��
    /// \param[in] (angleY)     �x���@�ł�Y����]�x��
    /// \param[in] (angleZ)     �x���@�ł�Z����]�x��
    ///
    /// \return void
    //--------------------------------------------- 
    virtual void ObjRotate(
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
    //---------------------------------------------------------------------------
    XMMATRIX m_localMtx = {};
    XMFLOAT3 m_worldPos = {};
    //---------------------------------------------------------------------------
    /// <summary>
    /// m_localMtx          ���[�J���ł̎p�����
    /// m_localPos          ���[�J�����W
    /// </summary>
private:

};

