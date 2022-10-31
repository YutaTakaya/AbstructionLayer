//==============================================================================
// Filename: D3D11Render.cpp
// Description: DirectX11ObjDataの共通描画処理用クラス
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================
#include "D3D11Render.h"
#include <vector>
#include <string>

int D3D11Render::D3D11RenderInit()
{
    HRESULT sts;
    //---------------------------------------------------------------------------
    // シェーダー設定
    //---------------------------------------------------------------------------
    ComPtr<ID3DBlob> errorBlob = nullptr;
    // 頂点シェーダー
    ComPtr<ID3DBlob> compiledVS = nullptr;
    sts = D3DCompileFromFile(
        L"D3D11Shader.hlsl",
        nullptr, nullptr,
        "VSmain", "vs_5_0",
        0, 0,
        &compiledVS,
        &errorBlob);
    if (FAILED(sts))
    {
        // エラー表示
        std::string errorStr;
        errorStr.resize(errorBlob->GetBufferSize());
        std::copy_n((char*)errorBlob->GetBufferPointer(),
            errorBlob->GetBufferSize(),
            errorStr.begin());
        return -1;
    }
    sts = D3D11Graphics::GetInstance().getDevPtr()->CreateVertexShader(
        compiledVS->GetBufferPointer(),
        compiledVS->GetBufferSize(),
        nullptr, &m_pSpriteVS);
    if (FAILED(sts))
    {
        return -1;
    }

    // ピクセルシェーダー
    ComPtr<ID3DBlob> compiledPS = nullptr;
    sts = D3DCompileFromFile(
        L"D3D11Shader.hlsl",
        nullptr, nullptr,
        "PSmain", "ps_5_0",
        0, 0,
        &compiledPS,
        &errorBlob);
    if (FAILED(sts))
    {
        // エラー表示
        std::string errorStr;
        errorStr.resize(errorBlob->GetBufferSize());
        std::copy_n((char*)errorBlob->GetBufferPointer(),
            errorBlob->GetBufferSize(),
            errorStr.begin());
        return -1;
    }
    sts = D3D11Graphics::GetInstance().getDevPtr()->CreatePixelShader(compiledPS->GetBufferPointer(), compiledPS->GetBufferSize(), nullptr, &m_pSpritePS);
    if (FAILED(sts))
    {
        return -1;
    }

    // セマンティクスの設定
    std::vector<D3D11_INPUT_ELEMENT_DESC> layout = {
        {"POSITION" ,0,DXGI_FORMAT_R32G32B32_FLOAT,     0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
        {"TEXCOORD" ,0,DXGI_FORMAT_R32G32_FLOAT,        0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
        {"COLOR"    ,0,DXGI_FORMAT_R32G32B32A32_FLOAT,  0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
    };

    // 頂点インプットレイアウト作成
    sts = D3D11Graphics::GetInstance().getDevPtr()->CreateInputLayout(
        &layout[0], static_cast<UINT>(layout.size()),
        compiledVS->GetBufferPointer(),
        compiledVS->GetBufferSize(),
        &m_pSpriteInputLayout);
    if (FAILED(sts))
    {
        return -1;
    }
    return 0;
}

void D3D11Render::D3D11RenderSet()
{
    D3D11Graphics::GetInstance().getDevContextPtr()->
        VSSetShader(m_pSpriteVS.Get(), 0, 0);
    D3D11Graphics::GetInstance().getDevContextPtr()->
        PSSetShader(m_pSpritePS.Get(), 0, 0);
    D3D11Graphics::GetInstance().getDevContextPtr()->
        IASetInputLayout(m_pSpriteInputLayout.Get());
}
