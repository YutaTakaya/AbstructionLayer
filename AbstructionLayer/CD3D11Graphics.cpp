#include "CD3D11Graphics.h"
#include <windows.h>

int CD3D11Graphics::InitD3D11(HWND hWnd, int width, int height)
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
        D3D11_CREATE_DEVICE_DEBUG,  // D3D11_CREATE_DEVICE_DEBUGにするとD3Dのデバッグを有効にできるが重くなる
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

    // デバイスコンテキストの作成
    
    m_deviceContext->OMSetRenderTargets(1, m_backBufferView.GetAddressOf(), nullptr);

    // ビューポートの設定
    D3D11_VIEWPORT vp = { 0.0f,0.0f,(float)width,(float)height,0.0f,1.0f };
    m_deviceContext->RSSetViewports(1, &vp);

    return 0;
}
