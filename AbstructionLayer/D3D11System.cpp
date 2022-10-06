//==============================================================================
// Filename: D3D11System.h
// Description: D3D11の基本処理
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================

#include "D3D11System.h"
#include "D3D11Graphics.h"
#include "D3D11Camera.h"


ObjData g_objdata;

struct TexColor 
{
    unsigned char R, G, B, A;
};
std::vector<TexColor> g_texData(256 * 256); // テクスチャデータ（仮置き）

int D3D11Init()
{
    for (auto& tex : g_texData)
    {
        tex.R = rand() % 256;
        tex.G = rand() % 256;
        tex.B = rand() % 256;
        tex.A = rand() % 256;
    }

    VertexData v[] = {
        // 前面
        {DirectX::XMFLOAT3(-1.0f, 1.0f,-1.0f),      DirectX::XMFLOAT2(1.0f,0.0f)    ,DirectX::XMFLOAT4(1.0f,1.0f,1.0f,1.0f)},
        {DirectX::XMFLOAT3( 1.0f, 1.0f,-1.0f),      DirectX::XMFLOAT2(1.0f,0.0f)    ,DirectX::XMFLOAT4(1.0f,1.0f,1.0f,1.0f)},
        {DirectX::XMFLOAT3(-1.0f,-1.0f,-1.0f),      DirectX::XMFLOAT2(1.0f,0.0f)    ,DirectX::XMFLOAT4(1.0f,1.0f,1.0f,1.0f)},
        {DirectX::XMFLOAT3( 1.0f,-1.0f,-1.0f),      DirectX::XMFLOAT2(1.0f,0.0f)    ,DirectX::XMFLOAT4(1.0f,1.0f,1.0f,1.0f)},

        // 左面
        {DirectX::XMFLOAT3(-1.0f, 1.0f, 1.0f),      DirectX::XMFLOAT2(0.0f,0.0f)    ,DirectX::XMFLOAT4(0.0f,1.0f,1.0f,1.0f)},
        {DirectX::XMFLOAT3(-1.0f, 1.0f,-1.0f),      DirectX::XMFLOAT2(0.0f,0.0f)    ,DirectX::XMFLOAT4(0.0f,1.0f,1.0f,1.0f)},
        {DirectX::XMFLOAT3(-1.0f,-1.0f, 1.0f),      DirectX::XMFLOAT2(0.0f,0.0f)    ,DirectX::XMFLOAT4(0.0f,1.0f,1.0f,1.0f)},
        {DirectX::XMFLOAT3(-1.0f,-1.0f,-1.0f),      DirectX::XMFLOAT2(0.0f,0.0f)    ,DirectX::XMFLOAT4(0.0f,1.0f,1.0f,1.0f)},

        // 右面
        {DirectX::XMFLOAT3( 1.0f, 1.0f,-1.0f),      DirectX::XMFLOAT2(0.0f,0.0f)    ,DirectX::XMFLOAT4(1.0f,0.0f,1.0f,1.0f)},
        {DirectX::XMFLOAT3( 1.0f, 1.0f, 1.0f),      DirectX::XMFLOAT2(0.0f,0.0f)    ,DirectX::XMFLOAT4(1.0f,0.0f,1.0f,1.0f)},
        {DirectX::XMFLOAT3( 1.0f,-1.0f,-1.0f),      DirectX::XMFLOAT2(0.0f,0.0f)    ,DirectX::XMFLOAT4(1.0f,0.0f,1.0f,1.0f)},
        {DirectX::XMFLOAT3( 1.0f,-1.0f, 1.0f),      DirectX::XMFLOAT2(0.0f,0.0f)    ,DirectX::XMFLOAT4(1.0f,0.0f,1.0f,1.0f)},

        // 後面
        {DirectX::XMFLOAT3( 1.0f, 1.0f, 1.0f),      DirectX::XMFLOAT2(0.0f,0.0f)    ,DirectX::XMFLOAT4(1.0f,1.0f,0.0f,1.0f)},
        {DirectX::XMFLOAT3(-1.0f, 1.0f, 1.0f),      DirectX::XMFLOAT2(0.0f,0.0f)    ,DirectX::XMFLOAT4(1.0f,1.0f,0.0f,1.0f)},
        {DirectX::XMFLOAT3( 1.0f,-1.0f, 1.0f),      DirectX::XMFLOAT2(0.0f,0.0f)    ,DirectX::XMFLOAT4(1.0f,1.0f,0.0f,1.0f)},
        {DirectX::XMFLOAT3(-1.0f,-1.0f, 1.0f),      DirectX::XMFLOAT2(0.0f,0.0f)    ,DirectX::XMFLOAT4(1.0f,1.0f,0.0f,1.0f)},

        // 上面
        {DirectX::XMFLOAT3(-1.0f, 1.0f, 1.0f),      DirectX::XMFLOAT2(0.0f,0.0f)    ,DirectX::XMFLOAT4(0.0f,1.0f,0.0f,1.0f)},
        {DirectX::XMFLOAT3( 1.0f, 1.0f, 1.0f),      DirectX::XMFLOAT2(0.0f,0.0f)    ,DirectX::XMFLOAT4(0.0f,1.0f,0.0f,1.0f)},
        {DirectX::XMFLOAT3(-1.0f, 1.0f,-1.0f),      DirectX::XMFLOAT2(0.0f,0.0f)    ,DirectX::XMFLOAT4(0.0f,1.0f,0.0f,1.0f)},
        {DirectX::XMFLOAT3( 1.0f, 1.0f,-1.0f),      DirectX::XMFLOAT2(0.0f,0.0f)    ,DirectX::XMFLOAT4(0.0f,1.0f,0.0f,1.0f)},

        // 下面
        {DirectX::XMFLOAT3(-1.0f,-1.0f,-1.0f),      DirectX::XMFLOAT2(0.0f,0.0f)    ,DirectX::XMFLOAT4(0.0f,0.0f,1.0f,1.0f)},
        {DirectX::XMFLOAT3( 1.0f,-1.0f,-1.0f),      DirectX::XMFLOAT2(0.0f,0.0f)    ,DirectX::XMFLOAT4(0.0f,0.0f,1.0f,1.0f)},
        {DirectX::XMFLOAT3(-1.0f,-1.0f, 1.0f),      DirectX::XMFLOAT2(0.0f,0.0f)    ,DirectX::XMFLOAT4(0.0f,0.0f,1.0f,1.0f)},
        {DirectX::XMFLOAT3( 1.0f,-1.0f, 1.0f),      DirectX::XMFLOAT2(0.0f,0.0f)    ,DirectX::XMFLOAT4(0.0f,0.0f,1.0f,1.0f)},
    };

    WORD index[] = {
        // 前面
        0,1,2,
        1,3,2,
        // 左面
        4,5,6,
        5,7,6,
        // 右面
        8,9,10,
        9,11,10,
        // 後面
        12,13,14,
        13,15,14,
        // 上面
        16,17,18,
        17,19,18,
        // 下面
        20,21,22,
        21,23,22
    };

    g_objdata.ObjInit(
        v, sizeof(v) / sizeof(VertexData),
        index,sizeof(index)/sizeof(WORD));

    D3D11Camera::GetInstance().CreateInstance();

    DirectX::XMFLOAT3 eye = { 0, 0, -20 };
    DirectX::XMFLOAT3 lookat = { 0, 0, 1 };
    DirectX::XMFLOAT3 up = { 0, 1, 0 };
    D3D11Camera::GetInstance().CameraInit(eye, lookat, up);


    return 0;
}


int D3D11Render()
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
    
    D3D11Camera::GetInstance().CameraDraw();

    g_objdata.ObjDraw();
    return 0;
}


int D3D11Uninit()
{
    g_objdata.ObjUninit();
    return 0;
}
