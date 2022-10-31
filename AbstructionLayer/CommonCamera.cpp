#include "CommonCamera.h"

int CommonCamera::CameraInit(const FLOAT3 eye, const FLOAT3 lookat, const FLOAT3 up)
{
    eye;
    lookat;
    up;
    return 0;
}

void CommonCamera::SetEye(const FLOAT3 eye)
{
    m_eye = eye;
    m_updateFlag = true;
}

void CommonCamera::SetLookat(const FLOAT3 lookat)
{
    m_lookat = lookat;
    m_updateFlag = true;
}

void CommonCamera::SetUp(const FLOAT3 up)
{
    m_up = up;
    m_updateFlag = true;
}

void CommonCamera::CopyInstance(CommonCamera* pInstance)
{
    DeleteCopyInstance();
    s_pCopyInstance = pInstance;
}

void CommonCamera::DeleteCopyInstance()
{
    s_pCopyInstance = nullptr;
}
