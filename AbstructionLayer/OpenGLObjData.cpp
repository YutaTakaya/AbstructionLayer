//==============================================================================
// Filename: OpenGLObjData.cpp
// Description: OpenGLのオブジェクトデータ
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================
#include "OpenGLObjData.h"
#include "gl/gl.h"

int OpenGLObjData::ObjInit(const VertexData* p_VData, const int vNum, const WORD* p_indexData, const int indexNum)
{
    for (int i = 0; i < vNum; i++)
    {
        m_vartex.push_back(p_VData[i]);
    }

    for (int i = 0; i < indexNum; i++)
    {
        m_index.push_back(p_indexData[i]);
    }

    // テクスチャ生成
    const int texSize = 4;
    byte texData[texSize * texSize * 4] = { 0 };
    for (int x = 0; x < texSize; x++)
    {
        for (int y = 0; y < texSize; y++)
        {
            if ((x + y) % 2 == 0)
            {
                texData[(x * 4) + (y * 4 * texSize)] = 255;        // R
                texData[(x * 4) + (y * 4 * texSize) + 1] = 255;    // G
                texData[(x * 4) + (y * 4 * texSize) + 2] = 255;    // B
            }
        }
    }

    glTexImage2D(
        GL_TEXTURE_2D,
        0,          // mipmap
        GL_RGBA,
        texSize,    // width
        texSize,    // height
        0,          // border
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        texData
    );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // 拡大時近傍
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // 縮小時近傍
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);    // 乗算合成
    glEnable(GL_TEXTURE_2D);

    return 0;
}

void OpenGLObjData::ObjUpdate()
{

}

void OpenGLObjData::ObjDraw()
{
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < m_index.size(); i++)
    {
        glColor4f(m_vartex[m_index[i]].col.x, m_vartex[m_index[i]].col.y, m_vartex[m_index[i]].col.z, m_vartex[m_index[i]].col.w);
        glTexCoord2f(m_vartex[m_index[i]].uv.x, m_vartex[m_index[i]].uv.y);
        glVertex3f(m_vartex[m_index[i]].pos.x, m_vartex[m_index[i]].pos.y, m_vartex[m_index[i]].pos.z);
    }
    glEnd();
}

void OpenGLObjData::ObjUninit()
{

}

void OpenGLObjData::ObjRotate(const float angleX, const float angleY, const float angleZ)
{
    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);
    glRotatef(angleZ, 0.0f, 0.0f, 1.0f);
}
