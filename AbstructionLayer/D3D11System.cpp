//==============================================================================
// Filename: D3D11System.h
// Description: D3D11�̊�{����
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================

#include "D3D11System.h"
#include "D3D11Graphics.h"
#include "D3D11Camera.h"

D3D11ObjData g_testObj1;
D3D11ObjData g_testObj2;

int D3D11Init()
{
    VertexData v[] = {
        //////          ���W           //////  /////        UV        //////  //////          �J���[          //////
        // �O��
        {DirectX::XMFLOAT3(-3.0f, 3.0f,-3.0f), DirectX::XMFLOAT2(0.0f,0.0f), DirectX::XMFLOAT4(1.0f,1.0f,1.0f,1.0f)},
        {DirectX::XMFLOAT3( 3.0f, 3.0f,-3.0f), DirectX::XMFLOAT2(1.0f,0.0f), DirectX::XMFLOAT4(1.0f,1.0f,1.0f,1.0f)},
        {DirectX::XMFLOAT3(-3.0f,-3.0f,-3.0f), DirectX::XMFLOAT2(0.0f,1.0f), DirectX::XMFLOAT4(1.0f,1.0f,1.0f,1.0f)},
        {DirectX::XMFLOAT3( 3.0f,-3.0f,-3.0f), DirectX::XMFLOAT2(1.0f,1.0f), DirectX::XMFLOAT4(1.0f,1.0f,1.0f,1.0f)},

        // ����
        {DirectX::XMFLOAT3(-3.0f, 3.0f, 3.0f), DirectX::XMFLOAT2(0.0f,0.0f), DirectX::XMFLOAT4(0.0f,1.0f,1.0f,1.0f)},
        {DirectX::XMFLOAT3(-3.0f, 3.0f,-3.0f), DirectX::XMFLOAT2(1.0f,0.0f), DirectX::XMFLOAT4(0.0f,1.0f,1.0f,1.0f)},
        {DirectX::XMFLOAT3(-3.0f,-3.0f, 3.0f), DirectX::XMFLOAT2(0.0f,1.0f), DirectX::XMFLOAT4(0.0f,1.0f,1.0f,1.0f)},
        {DirectX::XMFLOAT3(-3.0f,-3.0f,-3.0f), DirectX::XMFLOAT2(1.0f,1.0f), DirectX::XMFLOAT4(0.0f,1.0f,1.0f,1.0f)},

        // �E��
        {DirectX::XMFLOAT3( 3.0f, 3.0f,-3.0f), DirectX::XMFLOAT2(0.0f,0.0f), DirectX::XMFLOAT4(1.0f,0.0f,1.0f,1.0f)},
        {DirectX::XMFLOAT3( 3.0f, 3.0f, 3.0f), DirectX::XMFLOAT2(1.0f,0.0f), DirectX::XMFLOAT4(1.0f,0.0f,1.0f,1.0f)},
        {DirectX::XMFLOAT3( 3.0f,-3.0f,-3.0f), DirectX::XMFLOAT2(0.0f,1.0f), DirectX::XMFLOAT4(1.0f,0.0f,1.0f,1.0f)},
        {DirectX::XMFLOAT3( 3.0f,-3.0f, 3.0f), DirectX::XMFLOAT2(1.0f,1.0f), DirectX::XMFLOAT4(1.0f,0.0f,1.0f,1.0f)},

        // ���
        {DirectX::XMFLOAT3( 3.0f, 3.0f, 3.0f), DirectX::XMFLOAT2(0.0f,0.0f), DirectX::XMFLOAT4(1.0f,1.0f,0.0f,1.0f)},
        {DirectX::XMFLOAT3(-3.0f, 3.0f, 3.0f), DirectX::XMFLOAT2(1.0f,0.0f), DirectX::XMFLOAT4(1.0f,1.0f,0.0f,1.0f)},
        {DirectX::XMFLOAT3( 3.0f,-3.0f, 3.0f), DirectX::XMFLOAT2(0.0f,1.0f), DirectX::XMFLOAT4(1.0f,1.0f,0.0f,1.0f)},
        {DirectX::XMFLOAT3(-3.0f,-3.0f, 3.0f), DirectX::XMFLOAT2(1.0f,1.0f), DirectX::XMFLOAT4(1.0f,1.0f,0.0f,1.0f)},

        // ���
        {DirectX::XMFLOAT3(-3.0f, 3.0f, 3.0f), DirectX::XMFLOAT2(0.0f,0.0f), DirectX::XMFLOAT4(0.0f,1.0f,0.0f,1.0f)},
        {DirectX::XMFLOAT3( 3.0f, 3.0f, 3.0f), DirectX::XMFLOAT2(1.0f,0.0f), DirectX::XMFLOAT4(0.0f,1.0f,0.0f,1.0f)},
        {DirectX::XMFLOAT3(-3.0f, 3.0f,-3.0f), DirectX::XMFLOAT2(0.0f,1.0f), DirectX::XMFLOAT4(0.0f,1.0f,0.0f,1.0f)},
        {DirectX::XMFLOAT3( 3.0f, 3.0f,-3.0f), DirectX::XMFLOAT2(1.0f,1.0f), DirectX::XMFLOAT4(0.0f,1.0f,0.0f,1.0f)},

        // ����
        {DirectX::XMFLOAT3(-3.0f,-3.0f,-3.0f), DirectX::XMFLOAT2(0.0f,0.0f), DirectX::XMFLOAT4(0.0f,0.0f,1.0f,1.0f)},
        {DirectX::XMFLOAT3( 3.0f,-3.0f,-3.0f), DirectX::XMFLOAT2(1.0f,0.0f), DirectX::XMFLOAT4(0.0f,0.0f,1.0f,1.0f)},
        {DirectX::XMFLOAT3(-3.0f,-3.0f, 3.0f), DirectX::XMFLOAT2(0.0f,1.0f), DirectX::XMFLOAT4(0.0f,0.0f,1.0f,1.0f)},
        {DirectX::XMFLOAT3( 3.0f,-3.0f, 3.0f), DirectX::XMFLOAT2(1.0f,1.0f), DirectX::XMFLOAT4(0.0f,0.0f,1.0f,1.0f)},
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

    // �I�u�W�F�N�g������
    g_testObj1.ObjInit(
        v, sizeof(v) / sizeof(VertexData),
        index,sizeof(index)/sizeof(WORD));
    g_testObj1.ObjTranslate(5, 0, 0);

    g_testObj2.ObjInit(
        v, sizeof(v) / sizeof(VertexData),
        index, sizeof(index) / sizeof(WORD));
    g_testObj2.ObjTranslate(0, 0, 10);

    // �J����������
    D3D11Camera::GetInstance().CreateInstance();
    FLOAT3 eye = { 0, 0, -20 };
    FLOAT3 lookat = { 0, 0, 1 };
    FLOAT3 up = { 0, 1, 0 };
    D3D11Camera::GetInstance().CameraInit(eye, lookat, up);

    return 0;
}

void D3D11Update()
{
    g_testObj1.ObjUpdate();
    g_testObj2.ObjUpdate();
    g_testObj1.ObjRotate(0.01f, 0.02f, 0.03f);
    g_testObj2.ObjRotate(-0.01f, -0.02f, -0.01f);
}


void D3D11Render()
{
    float color[4] = { 0.2f,0.2f,0.2f,1.0f };
    D3D11Graphics::GetInstance().getDevContextPtr()->ClearRenderTargetView(
        D3D11Graphics::GetInstance().getBackBufferVierPtr(), 
        color);
    D3D11Graphics::GetInstance().getDevContextPtr()->ClearDepthStencilView(
        D3D11Graphics::GetInstance().getDepthStencilVierPtr(), 
        D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 
        1.0f, 
        0);

    g_testObj1.ObjDraw();
    g_testObj2.ObjDraw();

    // �o�b�N�o�b�t�@��\��
    D3D11Graphics::GetInstance().getSwapChainPtr()->Present(1, 0);
}


void D3D11Uninit()
{
    g_testObj1.ObjUninit();
    g_testObj2.ObjUninit();
}
