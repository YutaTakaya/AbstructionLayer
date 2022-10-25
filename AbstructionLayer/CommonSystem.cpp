//==============================================================================
// Filename: CommonSystem.cpp
// Description: ���ۉ����C���[�̊�{����
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================
#include "CommonSystem.h"
#include "D3D11ObjData.h"
#include "D3D12ObjData.h"
#include "OpenGLObjData.h"

CommonObjData* g_testObj;

int CommonInit()
{
    VertexData v[] = {
        //////          ���W           //////  /////        UV        //////  //////          �J���[          //////
        // �O��
        {DirectX::XMFLOAT3(-3.0f, 3.0f,-3.0f), DirectX::XMFLOAT2(0.0f,0.0f), DirectX::XMFLOAT4(1.0f,1.0f,1.0f,1.0f)},
        {DirectX::XMFLOAT3(3.0f, 3.0f,-3.0f), DirectX::XMFLOAT2(1.0f,0.0f), DirectX::XMFLOAT4(1.0f,1.0f,1.0f,1.0f)},
        {DirectX::XMFLOAT3(-3.0f,-3.0f,-3.0f), DirectX::XMFLOAT2(0.0f,1.0f), DirectX::XMFLOAT4(1.0f,1.0f,1.0f,1.0f)},
        {DirectX::XMFLOAT3(3.0f,-3.0f,-3.0f), DirectX::XMFLOAT2(1.0f,1.0f), DirectX::XMFLOAT4(1.0f,1.0f,1.0f,1.0f)},

        // ����
        {DirectX::XMFLOAT3(-3.0f, 3.0f, 3.0f), DirectX::XMFLOAT2(0.0f,0.0f), DirectX::XMFLOAT4(0.0f,1.0f,1.0f,1.0f)},
        {DirectX::XMFLOAT3(-3.0f, 3.0f,-3.0f), DirectX::XMFLOAT2(1.0f,0.0f), DirectX::XMFLOAT4(0.0f,1.0f,1.0f,1.0f)},
        {DirectX::XMFLOAT3(-3.0f,-3.0f, 3.0f), DirectX::XMFLOAT2(0.0f,1.0f), DirectX::XMFLOAT4(0.0f,1.0f,1.0f,1.0f)},
        {DirectX::XMFLOAT3(-3.0f,-3.0f,-3.0f), DirectX::XMFLOAT2(1.0f,1.0f), DirectX::XMFLOAT4(0.0f,1.0f,1.0f,1.0f)},

        // �E��
        {DirectX::XMFLOAT3(3.0f, 3.0f,-3.0f), DirectX::XMFLOAT2(0.0f,0.0f), DirectX::XMFLOAT4(1.0f,0.0f,1.0f,1.0f)},
        {DirectX::XMFLOAT3(3.0f, 3.0f, 3.0f), DirectX::XMFLOAT2(1.0f,0.0f), DirectX::XMFLOAT4(1.0f,0.0f,1.0f,1.0f)},
        {DirectX::XMFLOAT3(3.0f,-3.0f,-3.0f), DirectX::XMFLOAT2(0.0f,1.0f), DirectX::XMFLOAT4(1.0f,0.0f,1.0f,1.0f)},
        {DirectX::XMFLOAT3(3.0f,-3.0f, 3.0f), DirectX::XMFLOAT2(1.0f,1.0f), DirectX::XMFLOAT4(1.0f,0.0f,1.0f,1.0f)},

        // ���
        {DirectX::XMFLOAT3(3.0f, 3.0f, 3.0f), DirectX::XMFLOAT2(0.0f,0.0f), DirectX::XMFLOAT4(1.0f,1.0f,0.0f,1.0f)},
        {DirectX::XMFLOAT3(-3.0f, 3.0f, 3.0f), DirectX::XMFLOAT2(1.0f,0.0f), DirectX::XMFLOAT4(1.0f,1.0f,0.0f,1.0f)},
        {DirectX::XMFLOAT3(3.0f,-3.0f, 3.0f), DirectX::XMFLOAT2(0.0f,1.0f), DirectX::XMFLOAT4(1.0f,1.0f,0.0f,1.0f)},
        {DirectX::XMFLOAT3(-3.0f,-3.0f, 3.0f), DirectX::XMFLOAT2(1.0f,1.0f), DirectX::XMFLOAT4(1.0f,1.0f,0.0f,1.0f)},

        // ���
        {DirectX::XMFLOAT3(-3.0f, 3.0f, 3.0f), DirectX::XMFLOAT2(0.0f,0.0f), DirectX::XMFLOAT4(0.0f,1.0f,0.0f,1.0f)},
        {DirectX::XMFLOAT3(3.0f, 3.0f, 3.0f), DirectX::XMFLOAT2(1.0f,0.0f), DirectX::XMFLOAT4(0.0f,1.0f,0.0f,1.0f)},
        {DirectX::XMFLOAT3(-3.0f, 3.0f,-3.0f), DirectX::XMFLOAT2(0.0f,1.0f), DirectX::XMFLOAT4(0.0f,1.0f,0.0f,1.0f)},
        {DirectX::XMFLOAT3(3.0f, 3.0f,-3.0f), DirectX::XMFLOAT2(1.0f,1.0f), DirectX::XMFLOAT4(0.0f,1.0f,0.0f,1.0f)},

        // ����
        {DirectX::XMFLOAT3(-3.0f,-3.0f,-3.0f), DirectX::XMFLOAT2(0.0f,0.0f), DirectX::XMFLOAT4(0.0f,0.0f,1.0f,1.0f)},
        {DirectX::XMFLOAT3(3.0f,-3.0f,-3.0f), DirectX::XMFLOAT2(1.0f,0.0f), DirectX::XMFLOAT4(0.0f,0.0f,1.0f,1.0f)},
        {DirectX::XMFLOAT3(-3.0f,-3.0f, 3.0f), DirectX::XMFLOAT2(0.0f,1.0f), DirectX::XMFLOAT4(0.0f,0.0f,1.0f,1.0f)},
        {DirectX::XMFLOAT3(3.0f,-3.0f, 3.0f), DirectX::XMFLOAT2(1.0f,1.0f), DirectX::XMFLOAT4(0.0f,0.0f,1.0f,1.0f)},
    };

    WORD index[] = {
        // �O��
        0,1,2,
        1,3,2,
        // ����
        4,5,6,
        5,7,6,
        // �E��
        8,9,10,
        9,11,10,
        // ���
        12,13,14,
        13,15,14,
        // ���
        16,17,18,
        17,19,18,
        // ����
        20,21,22,
        21,23,22,
    };

    switch (CommonResourceManager::GetInstance().getAPIType())
    {
    case APIType::NONE:
        break;
    case APIType::D3D11:
        g_testObj = new D3D11ObjData;
        break;
    case APIType::D3D12:
        g_testObj = new D3D12ObjData;
        break;
    case APIType::OPENGL:
        g_testObj = new OpenGLObjData;
        break;
    case APIType::VULKAN:
        break;
    default:
        break;
    }

    if (g_testObj->ObjInit(
        v, sizeof(v) / sizeof(VertexData),
        index, sizeof(index) / sizeof(WORD)) == -1)
    {
        return -1;
    }
    return 0;
}

int CommonUpdate()
{
    g_testObj->ObjRotate(0.01f, 0.01f, 0.01f);
    return 0;
}

int CommonDraw()
{
    CommonResourceManager::GetInstance().BeforeRenderer();

    g_testObj->ObjDraw();
    
    CommonResourceManager::GetInstance().AfterRenderer();
    return 0;
}

int CommonUninit()
{
    return 0;
}
