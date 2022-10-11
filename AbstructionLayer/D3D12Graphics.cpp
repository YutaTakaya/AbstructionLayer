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
    for (int i = 0; i < scDesc.BufferCount; i++)
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
    UINT64 fenceVal = 0;
    sts = m_pDevice->CreateFence(fenceVal, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_pFence));
    if (FAILED(sts))
    {
        return -1;
    }

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
