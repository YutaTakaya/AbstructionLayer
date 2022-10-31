//==============================================================================
// Filename: D3D12Render.cpp
// Description: DirectX12ObjData�̋��ʕ`�揈���p�N���X
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================
#include "D3D12Render.h"

int D3D12Render::D3D12RenderInit()
{
    HRESULT sts;

    // ���[�g�V�O�l�`���̏�����

    // �T���v���[�f�X�N�̍쐬
    D3D12_STATIC_SAMPLER_DESC samplerDesc = {};
    samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP; // �������J��Ԃ�
    samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP; // �����J��Ԃ�
    samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP; // �������J��Ԃ�
    samplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;  // �{�[�_�[�����ɂ���
    samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;   // ���`���
    samplerDesc.MaxLOD = D3D12_FLOAT32_MAX; // �~�b�v�}�b�v�ő�l
    samplerDesc.MinLOD = 0.0f;  // �~�b�v�}�b�v�ŏ��l
    samplerDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;   // �V�F�[�_�[���猩����
    samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;   // ���T���v�����O���Ȃ�

    // �e�N�X�`���ƒ萔�o�b�t�@�̎w��
    D3D12_DESCRIPTOR_RANGE descTblRange[2] = {};
    descTblRange[0].NumDescriptors = 1;
    descTblRange[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;   // �V�F�[�_�[���\�[�X�r���[
    descTblRange[0].BaseShaderRegister = 0;    // t0�ԃX���b�g
    descTblRange[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

    descTblRange[1].NumDescriptors = 1;
    descTblRange[1].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;   // �萔�o�b�t�@
    descTblRange[1].BaseShaderRegister = 0;    // b0�ԃX���b�g
    descTblRange[1].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

    D3D12_ROOT_PARAMETER rootParam[2] = {};
    rootParam[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
    rootParam[0].DescriptorTable.pDescriptorRanges = &descTblRange[0];
    rootParam[0].DescriptorTable.NumDescriptorRanges = 1;  // �f�B�X�N���v�^�����W���i�萔��1�j
    rootParam[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

    rootParam[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
    rootParam[1].DescriptorTable.pDescriptorRanges = &descTblRange[1];
    rootParam[1].DescriptorTable.NumDescriptorRanges = 1;  // �f�B�X�N���v�^�����W���i�萔��1�j
    rootParam[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

    // ���[�g�V�O�l�`���̍쐬
    D3D12_ROOT_SIGNATURE_DESC rsDesc = {};
    rsDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;    // ���_���݈̂����n��
    rsDesc.pParameters = &rootParam[0];    // ���[�g�p�����[�^�[�̐擪�A�h���X
    rsDesc.NumParameters = 2;   // ���[�g�p�����[�^�[�̐�
    rsDesc.pStaticSamplers = &samplerDesc;
    rsDesc.NumStaticSamplers = 1;

    ComPtr<ID3DBlob> rootsigBlob = nullptr;
    ComPtr<ID3DBlob> errorBlob = nullptr;

    sts = D3D12SerializeRootSignature(
        &rsDesc,
        D3D_ROOT_SIGNATURE_VERSION_1_0, // ���[�g�V�O�l�`���o�[�W����
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

    ///// �p�C�v���C���̏�����
    // �V�F�[�_�[�̓ǂݍ���
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

    // �C���v�b�g���C�A�E�g�̍쐬
    D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
    };

    // �O���t�B�b�N�X�p�C�v���C���̍쐬
    D3D12_GRAPHICS_PIPELINE_STATE_DESC gpDesc = {};
    gpDesc.pRootSignature = m_pRootSignature.Get();
    // �V�F�[�_�[�Z�b�g
    gpDesc.VS.pShaderBytecode = vsBlob->GetBufferPointer();
    gpDesc.VS.BytecodeLength = vsBlob->GetBufferSize();
    gpDesc.PS.pShaderBytecode = psBlob->GetBufferPointer();
    gpDesc.PS.BytecodeLength = psBlob->GetBufferSize();

    gpDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;
    gpDesc.RasterizerState.MultisampleEnable = false;   // �A���`�G�C���A�X
    gpDesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE; // �J�����O
    gpDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;    // ���g�̓h��Ԃ�
    gpDesc.RasterizerState.DepthClipEnable = true;  // �[�x�����̃N���b�s���O

    gpDesc.BlendState.AlphaToCoverageEnable = false;    // �}���`�T���v�����O�ɂ�郿�e�X�g�̗L����
    gpDesc.BlendState.IndependentBlendEnable = false;   // �����_�[�^�[�Q�b�g�̕���

    D3D12_RENDER_TARGET_BLEND_DESC rtbDesc = {};
    // Blend��LogicOp�͂ǂ��炩�����L���ɂł��Ȃ��̂Œ���
    rtbDesc.BlendEnable = false;    // �u�����h���[�h
    rtbDesc.LogicOpEnable = false;  // �_�����Z�̗L����
    rtbDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

    gpDesc.BlendState.RenderTarget[0] = rtbDesc;    // �����̌���IndependentBlend�Ɉˑ�

    gpDesc.InputLayout.pInputElementDescs = inputLayout;
    gpDesc.InputLayout.NumElements = _countof(inputLayout);

    gpDesc.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;   // �J�b�g�Ȃ�
    gpDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;  // �O�p�`�ō\��

    gpDesc.NumRenderTargets = 1;    // �}���`�����_�[�^�[�Q�b�g�̌�
    gpDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;

    gpDesc.SampleDesc.Count = 1;    // �T���v�����O��1�s�N�Z���ɂ�1
    gpDesc.SampleDesc.Quality = 0;  // �T���v�����O�N�H���e�B

    gpDesc.DepthStencilState.DepthEnable = true;    // �[�x�o�b�t�@�[�̗L����
    gpDesc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;   // �[�x�l����������
    gpDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS;    // �����������g�p
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
