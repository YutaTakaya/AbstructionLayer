//==============================================================================
// Filename: D3D11Render.h
// Description: DirectX11ObjDataの共通描画処理用クラス
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================
#pragma once
#include "D3D11Graphics.h"
#include "D3D11Camera.h"
class D3D11Render
{
public:
    //---------------------------------------------------------------------------

    //---------------------------------------------
    /// ルートシグネチャとパイプラインの初期化
    ///
    /// \return エラーが出た場合-1が、正常に終了した場合0が返される
    //--------------------------------------------- 
    int D3D11RenderInit();

    //---------------------------------------------
    /// D3D12ObjDataの描画前処理
    ///
    /// \return void
    //--------------------------------------------- 
    void D3D11RenderSet();

    //---------------------------------------------------------------------------

protected:

private:
    //---------------------------------------------------------------------------
    ComPtr<ID3D11VertexShader> m_pSpriteVS = nullptr;
    ComPtr<ID3D11PixelShader> m_pSpritePS = nullptr;
    ComPtr<ID3D11InputLayout> m_pSpriteInputLayout = nullptr;
    //---------------------------------------------------------------------------
    /// <summary>
    /// m_pRootSignature    ルートシグネチャ
    /// m_pPipelineState    グラフィックスパイプライン
    /// </summary>
};

