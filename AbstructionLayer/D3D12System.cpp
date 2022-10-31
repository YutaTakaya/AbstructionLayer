//==============================================================================
// Filename: D3D12System.cpp
// Description: DirectX12�P�̂ł̃T���v������
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================

#include "D3D12System.h"
#include "D3D12Graphics.h"
#include "D3D12ObjData.h"
#include "D3D12Camera.h"
#include "D3D12Render.h"

D3D12ObjData g_testObj;
D3D12ObjData g_testObj2;
D3D12Render g_testRend;

int D3D12Init()
{
    D3D12Camera::CreateInstance();
    FLOAT3 eye = {0.0f,0.0f,-20.0f};
    FLOAT3 lookat = { 0.0f,0.0f,0.0f };
    FLOAT3 up = { 0.0f,1.0f,0.0f };
    D3D12Camera::GetInstance().CameraInit(eye, lookat, up);

    VertexData vertData[] = {
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

    g_testRend.D3D12RenderInit();


    g_testObj.ObjInit(
        vertData, sizeof(vertData) / sizeof(VertexData),
        index, sizeof(index) / sizeof(WORD));
    g_testObj.ObjTranslate(0.0f, 0.0f, -2.0f);

    g_testObj2.ObjInit(
        vertData, sizeof(vertData) / sizeof(VertexData),
        index, sizeof(index) / sizeof(WORD));
    g_testObj2.ObjTranslate(-5.0f, 0.0f, -2.0f);
    return 0;
}

void D3D12Update()
{
    g_testObj.ObjUpdate();
    g_testObj.ObjRotate(0.001f, 0.002f, 0.003f);
    g_testObj2.ObjRotate(0.001f, 0.002f, 0.003f);
}

void D3D12Draw()
{
    D3D12Graphics::GetInstance().D3D12BeforeRender();
    //   �������珈��������   //

    g_testRend.D3D12RenderSet();
    g_testObj.ObjDraw();
    g_testObj2.ObjDraw();

    //  �����܂łɏ���������  //
    D3D12Graphics::GetInstance().D3D12AfterRender();
}

void D3D12Uninit()
{
}
