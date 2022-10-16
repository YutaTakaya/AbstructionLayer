//==============================================================================
// Filename: D3D12Graphics.h
// Description: DirectX12の描画システム
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================
#include "D3D12Graphics.h"

int D3D12Graphics::D3D12Init(const HWND hWnd, const int width, const int height)
{
    HRESULT sts;



#ifdef _DEBUG
    // デバッグレイヤーの有効化
    ID3D12Debug* debugLayer = nullptr;
    sts = D3D12GetDebugInterface(IID_PPV_ARGS(&debugLayer));
    if (FAILED(sts))
    {
        return -1;
    }
    debugLayer->EnableDebugLayer();
    debugLayer->Release();

    // ファクトリーの作成
    ComPtr<IDXGIFactory6> factory;
    sts = CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(&factory));
#else
    // ファクトリーの作成
    ComPtr<IDXGIFactory6> factory;
    sts = CreateDXGIFactory1(IID_PPV_ARGS(&factory));
#endif // _DEBUG
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
    for (auto flv : featureLevels)
    {
        if ((D3D12CreateDevice(nullptr, flv, IID_PPV_ARGS(&m_pDevice)) == S_OK))
        {
            break;
        }
    }
    if (m_pDevice == nullptr)
    {
        return -1;
    }

    // コマンドアロケータの作成
    sts = m_pDevice->CreateCommandAllocator(
        D3D12_COMMAND_LIST_TYPE_DIRECT,
        IID_PPV_ARGS(&m_pCommandAllocator));
    if (FAILED(sts))
    {
        return -1;
    }

    // コマンドリストの作成
    sts = m_pDevice->CreateCommandList(
        0,
        D3D12_COMMAND_LIST_TYPE_DIRECT,
        m_pCommandAllocator.Get(),
        nullptr,
        IID_PPV_ARGS(&m_pCommandList)
    );
    if (FAILED(sts))
    {
        return -1;
    }

    // コマンドキューの作成
    D3D12_COMMAND_QUEUE_DESC cqDesc = {};
    cqDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;   // タイムアウトなし
    cqDesc.NodeMask = 0;
    cqDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;  // プライオリティは指定なし
    cqDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    sts = m_pDevice->CreateCommandQueue(
        &cqDesc,
        IID_PPV_ARGS(m_pCommandQueue.ReleaseAndGetAddressOf())
    );
    if (FAILED(sts))
    {
        return -1;
    }

    // スワップチェインの作成
    DXGI_SWAP_CHAIN_DESC1 scDesc = {};
    scDesc.Width = width;    // 画面幅
    scDesc.Height = height;  // 画面高さ
    scDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;  // ピクセルフォーマット
    scDesc.Stereo = false;
    scDesc.SampleDesc.Count = 1;
    scDesc.SampleDesc.Quality = 0;
    scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scDesc.BufferCount = 2;  // フロントバッファとバックバッファ
    scDesc.Scaling = DXGI_SCALING_STRETCH;
    scDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;   // フリップ後速やかに破棄する
    scDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
    scDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;   // ウィンドウとフルスクリーンの切り替え可

    sts = factory->CreateSwapChainForHwnd(
        m_pCommandQueue.Get(),
        hWnd,
        &scDesc,
        nullptr,
        nullptr,
        (IDXGISwapChain1**)m_pSwapChain.ReleaseAndGetAddressOf());
    if (FAILED(sts))
    {
        return -1;
    }

    D3D12_DESCRIPTOR_HEAP_DESC hpDesc = {};
    hpDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;   // レンダーターゲットビュー用
    hpDesc.NodeMask = 0;    // GPU1つ想定なので0
    hpDesc.NumDescriptors = 2; // フロントバッファとバックバッファ
    hpDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE; // 指定なし

    sts = m_pDevice->CreateDescriptorHeap(
        &hpDesc,
        IID_PPV_ARGS(&m_pRtvHeaps));
    if (FAILED(sts))
    {
        return -1;
    }

    // RTVヒープのスワップチェインとの関連付け
    D3D12_CPU_DESCRIPTOR_HANDLE handle = m_pRtvHeaps->GetCPUDescriptorHandleForHeapStart();
    for (unsigned int i = 0; i < scDesc.BufferCount; i++)
    {
        m_pBackBuffers.emplace_back();
        sts = m_pSwapChain->GetBuffer(i, IID_PPV_ARGS(&m_pBackBuffers[i]));
        if (FAILED(sts))
        {
            return -1;
        }
        m_pDevice->CreateRenderTargetView(
            m_pBackBuffers[i],
            nullptr,
            handle);
        handle.ptr += m_pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);  // ポインタをずらす
    }

    // フェンスの作成
    sts = m_pDevice->CreateFence(m_fenceVal, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_pFence));
    if (FAILED(sts))
    {
        return -1;
    }

    // ビューポートの作成
    m_pViewport.Width = (float)width;     // 出力先の幅
    m_pViewport.Height = (float)height;   // 出力先の高さ
    m_pViewport.TopLeftX = 0;      // 出力先の左上X座標
    m_pViewport.TopLeftY = 0;      // 出力先の左上Y座標
    m_pViewport.MaxDepth = 1.0f;   // 深度最大値
    m_pViewport.MinDepth = 0.0f;   // 深度最小値

    // シザー矩形の作成
    m_pScissorRect.top = 0;    // 切り抜き上座標
    m_pScissorRect.left = 0;   // 切り抜き左座標
    m_pScissorRect.right = m_pScissorRect.left + width;
    m_pScissorRect.bottom = m_pScissorRect.top + height;

    // 深度バッファの作成
    D3D12_RESOURCE_DESC drDesc = {};
    drDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
    drDesc.Width = width;
    drDesc.Height = height;
    drDesc.DepthOrArraySize = 1;
    drDesc.Format = DXGI_FORMAT_D32_FLOAT;
    drDesc.SampleDesc.Count = 1;
    drDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

    D3D12_HEAP_PROPERTIES depthHeapProp = {};
    depthHeapProp.Type = D3D12_HEAP_TYPE_DEFAULT;
    depthHeapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    depthHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;

    D3D12_CLEAR_VALUE depthClearValue = {};
    depthClearValue.DepthStencil.Depth = 1.0f;   //深さ1.0f(最大値)でクリア
    depthClearValue.Format = DXGI_FORMAT_D32_FLOAT; // 32ビットfloat値としてクリア

    sts = m_pDevice.Get()->CreateCommittedResource(
        &depthHeapProp,
        D3D12_HEAP_FLAG_NONE,
        &drDesc,
        D3D12_RESOURCE_STATE_DEPTH_WRITE,
        &depthClearValue,
        IID_PPV_ARGS(&m_pDepthBuffer));
    if (FAILED(sts))
    {
        return -1;
    }

    D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc = {};
    dsvHeapDesc.NumDescriptors = 1;
    dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
    sts = m_pDevice.Get()->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&m_pDepthStencilViewHeap));
    if (FAILED(sts))
    {
        return -1;
    }

    // 深度ビュー作成
    D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
    dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
    dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
    dsvDesc.Flags = D3D12_DSV_FLAG_NONE;

    m_pDevice.Get()->CreateDepthStencilView(
        m_pDepthBuffer.Get(),
        &dsvDesc,
        m_pDepthStencilViewHeap.Get()->GetCPUDescriptorHandleForHeapStart());


    // 初期化処理
    m_pCommandAllocator->Reset();
    m_pCommandList->Reset(m_pCommandAllocator.Get(), nullptr);
    return 0;
}

int D3D12Graphics::D3D12BeforeRender()
{
    // 描画先のバックバッファの番号を取得する
    auto bbIdx = m_pSwapChain->GetCurrentBackBufferIndex();
    // バリアの設定
    D3D12_RESOURCE_BARRIER brDesc = {};
    brDesc.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    brDesc.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    brDesc.Transition.pResource = m_pBackBuffers[bbIdx];
    brDesc.Transition.Subresource = 0;
    brDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
    brDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
    m_pCommandList->ResourceBarrier(1, &brDesc);    // バリア実行
    // RTVのポインタ取得
    auto rtvH = m_pRtvHeaps->GetCPUDescriptorHandleForHeapStart();
    rtvH.ptr += static_cast<__int64>(bbIdx) * m_pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
    
    auto dsvH = m_pDepthStencilViewHeap.Get()->GetCPUDescriptorHandleForHeapStart();

    float col[4] = { 0.3f,0.3f,0.3f,1 };
    m_pCommandList->ClearRenderTargetView(rtvH, col, 0, nullptr);
    m_pCommandList->ClearDepthStencilView(dsvH, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
    m_pCommandList->RSSetViewports(1, &m_pViewport);
    m_pCommandList->RSSetScissorRects(1, &m_pScissorRect);
    m_pCommandList->OMSetRenderTargets(1, &rtvH, false, &dsvH);
    return 0;
}

int D3D12Graphics::D3D12AfterRender()
{
    // 描画先のバックバッファの番号を取得する
    auto bbIdx = m_pSwapChain->GetCurrentBackBufferIndex();
    // バリアの設定
    D3D12_RESOURCE_BARRIER brDesc = {};
    brDesc.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    brDesc.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    brDesc.Transition.pResource = m_pBackBuffers[bbIdx];
    brDesc.Transition.Subresource = 0;
    brDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
    brDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
    m_pCommandList->ResourceBarrier(1, &brDesc);    // バリア実行

    m_pCommandList->Close();
    // コマンドリストの実行
    ID3D12CommandList* cmdLists[] = { m_pCommandList.Get() };
    m_pCommandQueue->ExecuteCommandLists(1, cmdLists);

    // 待ち処理
    m_pCommandQueue->Signal(m_pFence.Get(), ++m_fenceVal);
    if (m_pFence->GetCompletedValue() < m_fenceVal) {
        auto event = CreateEvent(nullptr, false, false, nullptr);
        m_pFence->SetEventOnCompletion(m_fenceVal, event);
        if (event != 0)
        {
            WaitForSingleObject(event, INFINITE);
            CloseHandle(event);
        }
    }

    // 初期化処理
    m_pCommandAllocator->Reset();
    m_pCommandList->Reset(m_pCommandAllocator.Get(), nullptr);

    // バックバッファを表示
    m_pSwapChain->Present(1, 0);
    return 0;
}

void D3D12Graphics::CreateInstance()
{
    DeleteInstance();

    s_pInstance = new D3D12Graphics();
}

void D3D12Graphics::DeleteInstance()
{
    if (s_pInstance != nullptr)
    {
        delete s_pInstance;
        s_pInstance = nullptr;
    }
}
