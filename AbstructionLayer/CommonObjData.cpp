#include "CommonObjData.h"

int CommonObjData::ObjInit(const VertexData* p_VData, const int vNum, const WORD* p_indexData, const int indexNum)
{
    return -1;
}

void CommonObjData::ObjDraw()
{
    
}

void CommonObjData::ObjRotate(const float angleX, const float angleY, const float angleZ)
{
    m_localMtx = ::XMMatrixMultiply(m_localMtx, ::XMMatrixRotationX(angleX));
    m_localMtx = ::XMMatrixMultiply(m_localMtx, ::XMMatrixRotationY(angleY));
    m_localMtx = ::XMMatrixMultiply(m_localMtx, ::XMMatrixRotationZ(angleZ));
}

void CommonObjData::ObjTranslate(const float posX, const float posY, const float posZ)
{
    m_worldPos.x = posX;
    m_worldPos.y = posY;
    m_worldPos.z = posZ;
}
