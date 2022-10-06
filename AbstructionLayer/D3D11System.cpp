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
        {DirectX::XMFLOAT3(0,    0,   5),        DirectX::XMFLOAT2(1.0f,0)},
        {DirectX::XMFLOAT3(0.5f,-0.5f,5),        DirectX::XMFLOAT2(1.0f,1.0f)},
        {DirectX::XMFLOAT3(0,   -0.5f,5),        DirectX::XMFLOAT2(1.0f,1.0f)},
        {DirectX::XMFLOAT3(0.5f,-1,   5),        DirectX::XMFLOAT2(1.0f,0)},

        //{DirectX::XMFLOAT3(0,    0,   10),        DirectX::XMFLOAT2(1.0f,0)},
        //{DirectX::XMFLOAT3(0.5f,-0.5f,10),        DirectX::XMFLOAT2(1.0f,1.0f)},
        //{DirectX::XMFLOAT3(0,   -0.5f,10),        DirectX::XMFLOAT2(0,1.0f)},
        //{DirectX::XMFLOAT3(0.5f,-1,   10),        DirectX::XMFLOAT2(1.0f,0)},
    };

    WORD index[] = {
        0,1,2,
        2,1,3,
        //4,6,5,
        //5,6,7
    };

    g_objdata.ObjInit(
        v, sizeof(v) / sizeof(VertexData),
        index,sizeof(index)/sizeof(WORD));

    D3D11Camera::GetInstance().CreateInstance();

    DirectX::XMFLOAT3 eye = { 0, 0, -10 };
    DirectX::XMFLOAT3 lookat = { 0, 0, 1 };
    DirectX::XMFLOAT3 up = { 0, 1, 0 };
    D3D11Camera::GetInstance().CameraInit(eye, lookat, up);

    return 0;
}


int D3D11Draw()
{
    float color[4] = { 1,0.5f,1,1 };
    D3D11Graphics::GetInstance().getDevContextPtr()->ClearRenderTargetView(
        D3D11Graphics::GetInstance().getBackBufferVierPtr(), 
        color);
    
    D3D11Camera::GetInstance().CameraDraw();

    g_objdata.ObjDraw();
    return 0;
}


int D3D11Uninit()
{
    g_objdata.ObjUninit();
    return 0;
}
