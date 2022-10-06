//==============================================================================
// Filename: D3D11Graphics.cpp
// Description: DirectX11�̕`��V�X�e��
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================

#include "D3D11Graphics.h"
#include <windows.h>
#include <string>
#include <vector>

int D3D11Graphics::InitD3D11(HWND hWnd, int width, int height)
{
    HRESULT sts;

    // �t�@�N�g���[�̍쐬
    ComPtr<IDXGIFactory> factory;
    sts = CreateDXGIFactory(IID_PPV_ARGS(&factory));
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

    D3D_FEATURE_LEVEL futureLevel;
    sts = D3D11CreateDevice(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        0,  // D3D11_CREATE_DEVICE_DEBUG�ɂ����D3D�̃f�o�b�O��L���ɂł��邪�d���Ȃ�
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
    // �X���b�v�`�F�C���ݒ�
    //---------------------------------------------------------------------------

    // �X���b�v�`�F�C���̃f�X�N���v�^�q�[�v�̍쐬
    DXGI_SWAP_CHAIN_DESC scDesc = {};
    scDesc.BufferDesc.Width = width;    // ��ʕ�
    scDesc.BufferDesc.Height = height;  // ��ʍ���
    scDesc.BufferDesc.RefreshRate.Numerator = 0;
    scDesc.BufferDesc.RefreshRate.Denominator = 1;
    scDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    scDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;  // �o�b�t�@�̌`��
    scDesc.SampleDesc.Count = 1;        // MSAA�g�p���Ȃ�
    scDesc.SampleDesc.Quality = 0;      // MSAA�g�p���Ȃ�
    scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;   // �o�b�t�@�̎g�p���@
    scDesc.BufferCount = 2; // �o�b�t�@���i�t�����g�o�b�t�@�ƃo�b�N�o�b�t�@�j
    scDesc.OutputWindow = hWnd;
    scDesc.Windowed = TRUE; // �E�B���h�E���[�h
    scDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    scDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    // �X���b�v�`�F�C���̍쐬
    sts = factory->CreateSwapChain(m_device.Get(), &scDesc, &m_swapChain);
    if (FAILED(sts))
    {
        return -1;
    }

    // �X���b�v�`�F�C������o�b�N�o�b�t�@���\�[�X�擾
    ComPtr<ID3D11Texture2D> pBuckBuffer;
    sts = m_swapChain->GetBuffer(0, IID_PPV_ARGS(&pBuckBuffer));
    if (FAILED(sts))
    {
        return -1;
    }

    // �o�b�N�o�b�t�@���\�[�X�p��RTV�쐬
    D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
    rtvDesc.Format = scDesc.BufferDesc.Format;
    rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
    sts = m_device->CreateRenderTargetView(pBuckBuffer.Get(), &rtvDesc, &m_backBufferView);
    if (FAILED(sts))
    {
        return -1;
    }

    // RTV�̐ݒ�
    m_deviceContext->OMSetRenderTargets(1, m_backBufferView.GetAddressOf(), nullptr);

    // �r���[�|�[�g�̐ݒ�
    D3D11_VIEWPORT vp = { 0.0f,0.0f,(float)width,(float)height,0.0f,1.0f };
    m_deviceContext->RSSetViewports(1, &vp);

    //---------------------------------------------------------------------------
    // �V�F�[�_�[�ݒ�
    //---------------------------------------------------------------------------
    ComPtr<ID3DBlob> errorBlob = nullptr;
    // ���_�V�F�[�_�[
    ComPtr<ID3DBlob> compiledVS = nullptr;
    sts = D3DCompileFromFile(L"D3D11Shader.hlsl", nullptr, nullptr, "VSmain", "vs_5_0", 0, 0, &compiledVS, &errorBlob);
    if (FAILED(sts))
    {
        // �G���[�\��
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

    // �s�N�Z���V�F�[�_�[
    ComPtr<ID3DBlob> compiledPS = nullptr;
    sts = D3DCompileFromFile(L"D3D11Shader.hlsl", nullptr, nullptr, "PSmain", "ps_5_0", 0, 0, &compiledPS, &errorBlob);
    if (FAILED(sts))
    {
        // �G���[�\��
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

    // �Z�}���e�B�N�X�̐ݒ�
    std::vector<D3D11_INPUT_ELEMENT_DESC> layout = {
        {"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
        {"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
        {"COLOR",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
    };
    
    // ���_�C���v�b�g���C�A�E�g�쐬
    sts = m_device->CreateInputLayout(&layout[0], (int)layout.size(), compiledVS->GetBufferPointer(), compiledVS->GetBufferSize(), &m_spriteInputLayout);
    if (FAILED(sts))
    {
        return -1;
    }

    // �[�x�o�b�t�@�̍쐬
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
