//==============================================================================
// Filename: D3D12Graphics.h
// Description: DirectX12�̕`��V�X�e��
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================
#include "D3D12Graphics.h"

int D3D12Graphics::D3D12Init(const HWND hWnd, const int width, const int height)
{
    HRESULT sts;



#ifdef _DEBUG
    // �f�o�b�O���C���[�̗L����
    ID3D12Debug* debugLayer = nullptr;
    sts = D3D12GetDebugInterface(IID_PPV_ARGS(&debugLayer));
    if (FAILED(sts))
    {
        return -1;
    }
    debugLayer->EnableDebugLayer();
    debugLayer->Release();

    // �t�@�N�g���[�̍쐬
    ComPtr<IDXGIFactory6> factory;
    sts = CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(&factory));
#else
    // �t�@�N�g���[�̍쐬
    ComPtr<IDXGIFactory6> factory;
    sts = CreateDXGIFactory1(IID_PPV_ARGS(&factory));
#endif // _DEBUG
    if (FAILED(sts))
    {
        return -1;
    }

    // �f�o�C�X����
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

    // �R�}���h�A���P�[�^�̍쐬
    sts = m_pDevice->CreateCommandAllocator(
        D3D12_COMMAND_LIST_TYPE_DIRECT,
        IID_PPV_ARGS(&m_pCommandAllocator));
    if (FAILED(sts))
    {
        return -1;
    }

    // �R�}���h���X�g�̍쐬
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

    // �R�}���h�L���[�̍쐬
    D3D12_COMMAND_QUEUE_DESC cqDesc = {};
    cqDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;   // �^�C���A�E�g�Ȃ�
    cqDesc.NodeMask = 0;
    cqDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;  // �v���C�I���e�B�͎w��Ȃ�
    cqDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    sts = m_pDevice->CreateCommandQueue(
        &cqDesc,
        IID_PPV_ARGS(m_pCommandQueue.ReleaseAndGetAddressOf())
    );
    if (FAILED(sts))
    {
        return -1;
    }

    // �X���b�v�`�F�C���̍쐬
    DXGI_SWAP_CHAIN_DESC1 scDesc = {};
    scDesc.Width = width;    // ��ʕ�
    scDesc.Height = height;  // ��ʍ���
    scDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;  // �s�N�Z���t�H�[�}�b�g
    scDesc.Stereo = false;
    scDesc.SampleDesc.Count = 1;
    scDesc.SampleDesc.Quality = 0;
    scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scDesc.BufferCount = 2;  // �t�����g�o�b�t�@�ƃo�b�N�o�b�t�@
    scDesc.Scaling = DXGI_SCALING_STRETCH;
    scDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;   // �t���b�v�㑬�₩�ɔj������
    scDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
    scDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;   // �E�B���h�E�ƃt���X�N���[���̐؂�ւ���

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
    hpDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;   // �����_�[�^�[�Q�b�g�r���[�p
    hpDesc.NodeMask = 0;    // GPU1�z��Ȃ̂�0
    hpDesc.NumDescriptors = 2; // �t�����g�o�b�t�@�ƃo�b�N�o�b�t�@
    hpDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE; // �w��Ȃ�

    sts = m_pDevice->CreateDescriptorHeap(
        &hpDesc,
        IID_PPV_ARGS(&m_pRtvHeaps));
    if (FAILED(sts))
    {
        return -1;
    }

    // RTV�q�[�v�̃X���b�v�`�F�C���Ƃ̊֘A�t��
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
        handle.ptr += m_pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);  // �|�C���^�����炷
    }

    // �t�F���X�̍쐬
    UINT64 fenceVal = 0;
    sts = m_pDevice->CreateFence(fenceVal, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_pFence));
    if (FAILED(sts))
    {
        return -1;
    }

    // �r���[�|�[�g�̍쐬
    m_pViewport.Width = width;     // �o�͐�̕�
    m_pViewport.Height = height;   // �o�͐�̍���
    m_pViewport.TopLeftX = 0;      // �o�͐�̍���X���W
    m_pViewport.TopLeftY = 0;      // �o�͐�̍���Y���W
    m_pViewport.MaxDepth = 1.0f;   // �[�x�ő�l
    m_pViewport.MinDepth = 0.0f;   // �[�x�ŏ��l

    // �V�U�[��`�̍쐬
    m_pScissorRect.top = 0;    // �؂蔲������W
    m_pScissorRect.left = 0;   // �؂蔲�������W
    m_pScissorRect.right = m_pScissorRect.left + width;
    m_pScissorRect.bottom = m_pScissorRect.top + height;

    // ����������
    m_pCommandAllocator->Reset();
    m_pCommandList->Reset(m_pCommandAllocator.Get(), nullptr);
    return 0;
}

int D3D12Graphics::D3D12BeforeRender()
{
    // �`���̃o�b�N�o�b�t�@�̔ԍ����擾����
    auto bbIdx = m_pSwapChain->GetCurrentBackBufferIndex();
    // �o���A�̐ݒ�
    D3D12_RESOURCE_BARRIER brDesc = {};
    brDesc.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    brDesc.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    brDesc.Transition.pResource = m_pBackBuffers[bbIdx];
    brDesc.Transition.Subresource = 0;
    brDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
    brDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
    m_pCommandList->ResourceBarrier(1, &brDesc);    // �o���A���s
    // RTV�̃|�C���^�擾
    auto rtvH = m_pRtvHeaps->GetCPUDescriptorHandleForHeapStart();
    rtvH.ptr += bbIdx * m_pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

    float col[4] = { 1,1,0,1 };
    m_pCommandList->ClearRenderTargetView(rtvH, col, 0, nullptr);
    m_pCommandList->RSSetViewports(1, &m_pViewport);
    m_pCommandList->RSSetScissorRects(1, &m_pScissorRect);
    m_pCommandList->OMSetRenderTargets(1, &rtvH, false, nullptr);
    return 0;
}

int D3D12Graphics::D3D12AfterRender()
{
    // �`���̃o�b�N�o�b�t�@�̔ԍ����擾����
    auto bbIdx = m_pSwapChain->GetCurrentBackBufferIndex();
    // �o���A�̐ݒ�
    D3D12_RESOURCE_BARRIER brDesc = {};
    brDesc.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    brDesc.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    brDesc.Transition.pResource = m_pBackBuffers[bbIdx];
    brDesc.Transition.Subresource = 0;
    brDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
    brDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
    m_pCommandList->ResourceBarrier(1, &brDesc);    // �o���A���s

    m_pCommandList->Close();
    // �R�}���h���X�g�̎��s
    ID3D12CommandList* cmdLists[] = { m_pCommandList.Get() };
    m_pCommandQueue->ExecuteCommandLists(1, cmdLists);

    // �҂�����
    UINT64 fenceVal = 0;
    if (m_pFence->GetCompletedValue() < fenceVal) {
        auto event = CreateEvent(nullptr, false, false, nullptr);
        m_pFence->SetEventOnCompletion(fenceVal, event);
        WaitForSingleObject(event, INFINITE);
        CloseHandle(event);
    }

    // ����������
    m_pCommandAllocator->Reset();
    m_pCommandList->Reset(m_pCommandAllocator.Get(), nullptr);

    // �o�b�N�o�b�t�@��\��
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
