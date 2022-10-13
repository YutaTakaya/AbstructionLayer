//==============================================================================
// Filename: D3D12ObjData.cpp
// Description: DirectX12のオブジェクトデータ
//              （DirectX12でのデバッグ用であり、最終的には11の物と統合予定）
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================
#pragma comment (lib,"d3dcompiler.lib")

#include "D3D12ObjData.h"
#include <iterator>
#include <d3dcompiler.h>

int D3D12ObjData::ObjInit(const VertexData12* p_VData, const int vNum, const WORD* p_indexData, const int indexNum)
{
    HRESULT sts;

    XMFLOAT3 vertices[] = {
        {-1.0f,-1.0f, 0.0f},
        {-1.0f, 1.0f, 0.0f},
        { 1.0f,-1.0f, 0.0f},
    };

    // バーテックスバッファーの作成
    D3D12_HEAP_PROPERTIES heapprop = {};
    heapprop.Type = D3D12_HEAP_TYPE_UPLOAD;
    heapprop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    heapprop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
    heapprop.CreationNodeMask = 1;
    heapprop.VisibleNodeMask = 1;

    D3D12_RESOURCE_DESC vbDesc = {};
    vbDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    vbDesc.Width = sizeof(vertices);
    //vbDesc.Width = sizeof(p_VData) * vNum;
    vbDesc.Height = 1;
    vbDesc.DepthOrArraySize = 1;
    vbDesc.MipLevels = 1;
    vbDesc.Format = DXGI_FORMAT_UNKNOWN;
    vbDesc.SampleDesc.Count = 1;
    vbDesc.SampleDesc.Quality = 0;
    vbDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
    vbDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

    sts = D3D12Graphics::GetInstance().getDevPtr()->CreateCommittedResource(
        &heapprop,
        D3D12_HEAP_FLAG_NONE,
        &vbDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&m_pVertexBuffer));
    if (FAILED(sts))
    {
        return -1;
    }

    // 頂点データのマップ
    XMFLOAT3* vertMap = nullptr;
    sts = m_pVertexBuffer->Map(0, nullptr, (void**)&vertMap);
    if (FAILED(sts))
    {
        return -1;
    }
    std::copy(std::begin(vertices), std::end(vertices), vertMap);
    //std::copy(p_VData, p_VData + vNum, vertMap);
    m_pVertexBuffer->Unmap(0, nullptr);

    // バーテックスバッファービューの作成
    m_vertexBufferView.BufferLocation = m_pVertexBuffer.Get()->GetGPUVirtualAddress();
    m_vertexBufferView.SizeInBytes = sizeof(vertices);   // 総バイト数
    //m_vertexBufferView.SizeInBytes = sizeof(VertexData12) * vNum;   // 総バイト数
    m_vertexBufferView.StrideInBytes = sizeof(vertices[0]);    // 1頂点当たりのサイズ
    //m_vertexBufferView.StrideInBytes = sizeof(VertexData12);    // 1頂点当たりのサイズ

    // シェーダーの読み込み
    ComPtr<ID3DBlob> vsBlob = nullptr;
    ComPtr<ID3DBlob> psBlob = nullptr;
    ComPtr<ID3DBlob> errorBlob = nullptr;
    sts = D3DCompileFromFile(
        L"D3D12Shader.hlsl",
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "VSmain", "vs_5_0",
        D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
        0,
        &vsBlob, &errorBlob);
    if (FAILED(sts))
    {
        return -1;
    }
    sts = D3DCompileFromFile(
        L"D3D12Shader.hlsl",
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "PSmain", "ps_5_0",
        D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
        0,
        &psBlob, &errorBlob);
    if (FAILED(sts))
    {
        return -1;
    }

    // インプットレイアウトの作成
    D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
    };

    // ルートシグネチャの作成
    D3D12_ROOT_SIGNATURE_DESC rsDesc = {};
    rsDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;    // 頂点情報のみ引き渡し
    
    ComPtr<ID3DBlob> rootsigBlob = nullptr;
    sts = D3D12SerializeRootSignature(
        &rsDesc,
        D3D_ROOT_SIGNATURE_VERSION_1_0, // ルートシグネチャバージョン
        &rootsigBlob,
        &errorBlob);
    if (FAILED(sts))
    {
        return -1;
    }

    sts = D3D12Graphics::GetInstance().getDevPtr()->CreateRootSignature(
        0,
        rootsigBlob->GetBufferPointer(),
        rootsigBlob->GetBufferSize(),
        IID_PPV_ARGS(&m_pRootSignature));
    if (FAILED(sts))
    {
        return -1;
    }

    // グラフィックスパイプラインの作成
    D3D12_GRAPHICS_PIPELINE_STATE_DESC gpDesc = {};
    gpDesc.pRootSignature = m_pRootSignature.Get();
    // シェーダーセット
    gpDesc.VS.pShaderBytecode = vsBlob->GetBufferPointer();
    gpDesc.VS.BytecodeLength = vsBlob->GetBufferSize();
    gpDesc.PS.pShaderBytecode = psBlob->GetBufferPointer();
    gpDesc.PS.BytecodeLength = psBlob->GetBufferSize();
    
    gpDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;
    gpDesc.RasterizerState.MultisampleEnable = false;   // アンチエイリアス
    gpDesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE; // カリング
    gpDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;    // 中身の塗りつぶし
    gpDesc.RasterizerState.DepthClipEnable = true;  // 深度方向のクリッピング

    gpDesc.BlendState.AlphaToCoverageEnable = false;    // マルチサンプリングによるαテストの有効化
    gpDesc.BlendState.IndependentBlendEnable = false;   // レンダーターゲットの分割

    D3D12_RENDER_TARGET_BLEND_DESC rtbDesc = {};
    // BlendとLogicOpはどちらかしか有効にできないので注意
    rtbDesc.BlendEnable = false;    // ブレンドモード
    rtbDesc.LogicOpEnable = false;  // 論理演算の有効化
    rtbDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

    gpDesc.BlendState.RenderTarget[0] = rtbDesc;    // ここの個数はIndependentBlendに依存

    gpDesc.InputLayout.pInputElementDescs = inputLayout;
    gpDesc.InputLayout.NumElements = _countof(inputLayout);

    gpDesc.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;   // カットなし
    gpDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;  // 三角形で構成
    
    gpDesc.NumRenderTargets = 1;    // マルチレンダーターゲットの個数
    gpDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;

    gpDesc.SampleDesc.Count = 1;    // サンプリングは1ピクセルにつき1
    gpDesc.SampleDesc.Quality = 0;  // サンプリングクォリティ

    sts = D3D12Graphics::GetInstance().getDevPtr()->CreateGraphicsPipelineState(
        &gpDesc, IID_PPV_ARGS(&m_pPipelineState));
    if (FAILED(sts))
    {
        return -1;
    }
    return 0;
}

void D3D12ObjData::ObjDraw()
{
    D3D12Graphics::GetInstance().getCmdPtr()->SetPipelineState(m_pPipelineState.Get());
    D3D12Graphics::GetInstance().getCmdPtr()->SetGraphicsRootSignature(m_pRootSignature.Get());
    D3D12Graphics::GetInstance().getCmdPtr()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    D3D12Graphics::GetInstance().getCmdPtr()->IASetVertexBuffers(0, 1, &m_vertexBufferView);
    D3D12Graphics::GetInstance().getCmdPtr()->DrawInstanced(3, 1, 0, 0);
}