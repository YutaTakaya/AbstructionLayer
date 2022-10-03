#include "CD3D11Graphics.h"
#include <windows.h>

int CD3D11Graphics::InitD3D11(HWND hWnd, int width, int height)
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
        D3D11_CREATE_DEVICE_DEBUG,  // D3D11_CREATE_DEVICE_DEBUG�ɂ����D3D�̃f�o�b�O��L���ɂł��邪�d���Ȃ�
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

    // �f�o�C�X�R���e�L�X�g�̍쐬
    
    m_deviceContext->OMSetRenderTargets(1, m_backBufferView.GetAddressOf(), nullptr);

    // �r���[�|�[�g�̐ݒ�
    D3D11_VIEWPORT vp = { 0.0f,0.0f,(float)width,(float)height,0.0f,1.0f };
    m_deviceContext->RSSetViewports(1, &vp);

    return 0;
}
