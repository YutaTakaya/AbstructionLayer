//==============================================================================
// Filename: OpenGLCamera.cpp
// Description: OpenGLのカメラ及びビュー変換行列の管理クラス、シングルトン
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================
#include "OpenGLCamera.h"

int OpenGLCamera::CameraInit(const FLOAT3 eye, const FLOAT3 lookat, const FLOAT3 up)
{
    //プロジェクション行列の設定
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-8.0 / 200.0, 8.0 / 200.0, -4.5 / 200.0, 4.5 / 200.0, 0.1, 100.0);	// かなり望遠に

    //ビュー変換行列の設定
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        eye.x, eye.y, eye.z, // eye
        lookat.x, lookat.y, lookat.z,   // lookat
        up.x, up.y, up.z);  // up
    return 0;
}

void OpenGLCamera::CreateInstance()
{
    DeleteInstance();

    s_pInstance = new OpenGLCamera();
}

void OpenGLCamera::DeleteInstance()
{
    if (s_pInstance != nullptr)
    {
        delete s_pInstance;
        s_pInstance = nullptr;
    }
}
