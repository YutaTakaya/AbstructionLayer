//==============================================================================
// Filename: D3D12System.cpp
// Description: DirectX12‚ÌŠî–{ˆ—
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================

#include "D3D12System.h"
#include "D3D12Graphics.h"
#include "D3D12ObjData.h"
#include "D3D12Camera.h"

D3D12ObjData g_testObj;

int D3D12Init()
{
    VertexData12 vertData[] = {
        {{-0.5f,-0.5f, 0.0f},{1.0f,0.0f},{1.0f,0.0f,1.0f,1.0f}},
        {{-0.5f, 0.5f, 0.0f},{1.0f,0.0f},{0.0f,1.0f,1.0f,1.0f}},
        {{ 0.5f,-0.5f, 0.0f},{1.0f,0.0f},{1.0f,1.0f,0.0f,1.0f}},
        {{ 0.5f, 0.5f, 0.0f},{1.0f,0.0f},{1.0f,1.0f,1.0f,1.0f}},
    };
    WORD index[] = {
        0,1,2,
        2,1,3,
    };
    g_testObj.ObjInit(
        vertData, sizeof(vertData) / sizeof(VertexData12),
        index, sizeof(index) / sizeof(WORD));

    return 0;
}

void D3D12Update()
{
}

void D3D12Render()
{
    D3D12Graphics::GetInstance().D3D12BeforeRender();
    //   ‚±‚±‚©‚çˆ—‚ğ‘‚­   //

    g_testObj.ObjDraw();

    //  ‚±‚±‚Ü‚Å‚Éˆ—‚ğ‘‚­  //
    D3D12Graphics::GetInstance().D3D12AfterRender();
}

void D3D12Uninit()
{
}
