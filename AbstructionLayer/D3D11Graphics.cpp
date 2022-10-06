//==============================================================================
// Filename: D3D11Graphics.cpp
// Description: DirectX11の描画システム
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================

#include "D3D11Graphics.h"
#include <windows.h>
#include <string>
#include <vector>

int D3D11Graphics::InitD3D11(HWND hWnd, int width, int height)
{
    HRESULT sts;

    // ファクトリーの作成
    ComPtr<IDXGIFactory> factory;
    sts = CreateDXGIFactory(IID_PPV_ARGS(&factory));
    if (FAILED(sts))
    {
        return -1;
    }

    // デバイス生成
    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_1,	// Direct3D 11.1
        D3D_FEATURE_LEVEL_11_0,	// Direct3D 11
        D3D_FEATURE_LEVEL_10_1,	// Direct3D 10.1
        D3D_FEATURE_LEVEL_10_0,	// Direct3D 10.0
        D3D_FEATURE_LEVEL_9_3,	// Direct3D 9.3
        D3D_FEATURE_LEVEL_9_2,	// Direct3D 9.2
        D3D_FEATURE_LEVEL_9_1,	// Direct3D 9.1
    };

    D3D_FEATURE_LEVEL futureLevel;
    sts = D3D11CreateDevice(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        0,  // D3D11_CREATE_DEVICE_DEBUGにするとD3Dのデバッグを有効にできるが重くなる
        featureLevels,
        _countof(featureLevels),
        D3D11_SDK_VERSION,
        &m_device,
        &futureLevel,
        &m_deviceContext);

    if (FAILED(sts))
    {
        return -1;
    }

    //---------------------------------------------------------------------------
    // スワップチェイン設定
    //---------------------------------------------------------------------------

    // スワップチェインのデスクリプタヒープの作成
    DXGI_SWAP_CHAIN_DESC scDesc = {};
    scDesc.BufferDesc.Width = width;    // 画面幅
    scDesc.BufferDesc.Height = height;  // 画面高さ
    scDesc.BufferDesc.RefreshRate.Numerator = 0;
    scDesc.BufferDesc.RefreshRate.Denominator = 1;
    scDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    scDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;  // バッファの形式
    scDesc.SampleDesc.Count = 1;        // MSAA使用しない
    scDesc.SampleDesc.Quality = 0;      // MSAA使用しない
    scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;   // バッファの使用方法
    scDesc.BufferCount = 2; // バッファ数（フロントバッファとバックバッファ）
    scDesc.OutputWindow = hWnd;
    scDesc.Windowed = TRUE; // ウィンドウモード
    scDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    scDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    // スワップチェインの作成
    sts = factory->CreateSwapChain(m_device.Get(), &scDesc, &m_swapChain);
    if (FAILED(sts))
    {
        return -1;
    }

    // スワップチェインからバックバッファリソース取得
    ComPtr<ID3D11Texture2D> pBuckBuffer;
    sts = m_swapChain->GetBuffer(0, IID_PPV_ARGS(&pBuckBuffer));
    if (FAILED(sts))
    {
        return -1;
    }

    // バックバッファリソース用のRTV作成
    D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
    rtvDesc.Format = scDesc.BufferDesc.Format;
    rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
    sts = m_device->CreateRenderTargetView(pBuckBuffer.Get(), &rtvDesc, &m_backBufferView);
    if (FAILED(sts))
    {
        return -1;
    }

    // RTVの設定
    m_deviceContext->OMSetRenderTargets(1, m_backBufferView.GetAddressOf(), nullptr);

    // ビューポートの設定
    D3D11_VIEWPORT vp = { 0.0f,0.0f,(float)width,(float)height,0.0f,1.0f };
    m_deviceContext->RSSetViewports(1, &vp);

    //---------------------------------------------------------------------------
    // シェーダー設定
    //---------------------------------------------------------------------------
    ComPtr<ID3DBlob> errorBlob = nullptr;
    // 頂点シェーダー
    ComPtr<ID3DBlob> compiledVS = nullptr;
    sts = D3DCompileFromFile(L"D3D11Shader.hlsl", nullptr, nullptr, "VSmain", "vs_5_0", 0, 0, &compiledVS, &errorBlob);
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
    sts = m_device->CreateVertexShader(compiledVS->GetBufferPointer(), compiledVS->GetBufferSize(), nullptr, &m_spriteVS);
    if (FAILED(sts))
    {
        return -1;
    }

    // ピクセルシェーダー
    ComPtr<ID3DBlob> compiledPS = nullptr;
    sts = D3DCompileFromFile(L"D3D11Shader.hlsl", nullptr, nullptr, "PSmain", "ps_5_0", 0, 0, &compiledPS, &errorBlob);
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
    sts = m_device->CreatePixelShader(compiledPS->GetBufferPointer(), compiledPS->GetBufferSize(), nullptr, &m_spritePS);
    if (FAILED(sts))
    {
        return -1;
    }

    // セマンティクスの設定
    std::vector<D3D11_INPUT_ELEMENT_DESC> layout = {
        {"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
        {"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
        {"COLOR",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
    };
    
    // 頂点インプットレイアウト作成
    sts = m_device->CreateInputLayout(&layout[0], (int)layout.size(), compiledVS->GetBufferPointer(), compiledVS->GetBufferSize(), &m_spriteInputLayout);
    if (FAILED(sts))
    {
        return -1;
    }

    // 深度バッファの作成
    D3D11_TEXTURE2D_DESC txDesc = {};
    txDesc.Width = width;
    txDesc.Height = height;
    txDesc.MipLevels = 1;
    txDesc.ArraySize = 1;
    txDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    txDesc.SampleDesc.Count = 1;
    txDesc.SampleDesc.Quality = 0;
    txDesc.Usage = D3D11_USAGE_DEFAULT;
    txDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    txDesc.CPUAccessFlags = 0;
    txDesc.MiscFlags = 0;
    sts = D3D11Graphics::GetInstance().getDevPtr()->CreateTexture2D(&txDesc, NULL, &m_depthStencilTexture);
    if (FAILED(sts))
    {
        return -1;
    }

    D3D11_DEPTH_STENCIL_VIEW_DESC dsDesc = {};
    dsDesc.Format = txDesc.Format;
    dsDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    dsDesc.Texture2D.MipSlice = 0;
    sts = D3D11Graphics::GetInstance().getDevPtr()->CreateDepthStencilView(m_depthStencilTexture.Get(), &dsDesc, &m_depthStencilView);
    if (FAILED(sts))
    {
        return -1;
    }

    return 0;
}

void D3D11Graphics::CreateInstance()
{
    DeleteInstance();

    s_instance = new D3D11Graphics();
}

void D3D11Graphics::DeleteInstance()
{
    if (s_instance != nullptr)
    {
        delete s_instance;
        s_instance = nullptr;
    }
}
