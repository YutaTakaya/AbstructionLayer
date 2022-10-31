//==============================================================================
// Filename: D3D12Render.cpp
// Description: DirectX12ObjDataの共通描画処理用クラス
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================
#include "D3D12Render.h"

int D3D12Render::D3D12RenderInit()
{
    HRESULT sts;

    // ルートシグネチャの初期化

    // サンプラーデスクの作成
    D3D12_STATIC_SAMPLER_DESC samplerDesc = {};
    samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP; // 横方向繰り返し
    samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP; // 方向繰り返し
    samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP; // 横方向繰り返し
    samplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;  // ボーダーを黒にする
    samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;   // 線形補間
    samplerDesc.MaxLOD = D3D12_FLOAT32_MAX; // ミップマップ最大値
    samplerDesc.MinLOD = 0.0f;  // ミップマップ最小値
    samplerDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;   // シェーダーから見える
    samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;   // リサンプリングしない

    // テクスチャと定数バッファの指定
    D3D12_DESCRIPTOR_RANGE descTblRange[2] = {};
    descTblRange[0].NumDescriptors = 1;
    descTblRange[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;   // シェーダーリソースビュー
    descTblRange[0].BaseShaderRegister = 0;    // t0番スロット
    descTblRange[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

    descTblRange[1].NumDescriptors = 1;
    descTblRange[1].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;   // 定数バッファ
    descTblRange[1].BaseShaderRegister = 0;    // b0番スロット
    descTblRange[1].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

    D3D12_ROOT_PARAMETER rootParam[2] = {};
    rootParam[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
    rootParam[0].DescriptorTable.pDescriptorRanges = &descTblRange[0];
    rootParam[0].DescriptorTable.NumDescriptorRanges = 1;  // ディスクリプタレンジ数（定数は1つ）
    rootParam[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

    rootParam[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
    rootParam[1].DescriptorTable.pDescriptorRanges = &descTblRange[1];
    rootParam[1].DescriptorTable.NumDescriptorRanges = 1;  // ディスクリプタレンジ数（定数は1つ）
    rootParam[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

    // ルートシグネチャの作成
    D3D12_ROOT_SIGNATURE_DESC rsDesc = {};
    rsDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;    // 頂点情報のみ引き渡し
    rsDesc.pParameters = &rootParam[0];    // ルートパラメーターの先頭アドレス
    rsDesc.NumParameters = 2;   // ルートパラメーターの数
    rsDesc.pStaticSamplers = &samplerDesc;
    rsDesc.NumStaticSamplers = 1;

    ComPtr<ID3DBlob> rootsigBlob = nullptr;
    ComPtr<ID3DBlob> errorBlob = nullptr;

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

    ///// パイプラインの初期化
    // シェーダーの読み込み
    ComPtr<ID3DBlob> vsBlob = nullptr;
    ComPtr<ID3DBlob> psBlob = nullptr;
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
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
    };

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

    gpDesc.DepthStencilState.DepthEnable = true;    // 深度バッファーの有効化
    gpDesc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;   // 深度値を書き込む
    gpDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS;    // 小さい方を使用
    gpDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;

    sts = D3D12Graphics::GetInstance().getDevPtr()->CreateGraphicsPipelineState(
        &gpDesc, IID_PPV_ARGS(&m_pPipelineState));
    if (FAILED(sts))
    {
        return -1;
    }

    return 0;
}

void D3D12Render::D3D12RenderSet()
{
    D3D12Graphics::GetInstance().getCmdPtr()->SetPipelineState(m_pPipelineState.Get());
    D3D12Graphics::GetInstance().getCmdPtr()->SetGraphicsRootSignature(m_pRootSignature.Get());
    D3D12Graphics::GetInstance().getCmdPtr()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}
