//==============================================================================
// Filename: D3D11System.h
// Description: D3D11‚ÌŠî–{ˆ—
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================

#include "D3D11System.h"
#include "D3D11Graphics.h"

ObjData g_objdata;

int D3D11Init()
{
    VertexData v[3] = {
        {{0,0,0}},
        {{0.5f,-0.5f,0}},
        {{0,-0.5f,0}},
    };

    g_objdata.ObjInit(v, sizeof(v) / sizeof(VertexData));
    return 0;
}


int D3D11Draw()
{
    float color[4] = { 1,0,1,1 };
    D3D11Graphics::GetInstance().getDevContextPtr()->ClearRenderTargetView(D3D11Graphics::GetInstance().getBackBufferVierPtr(), color);
    
    g_objdata.ObjDraw();
    return 0;
}


int D3D11Uninit()
{
    g_objdata.ObjUninit();
    return 0;
}
