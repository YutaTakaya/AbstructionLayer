//==============================================================================
// Filename: D3D12ObjData.cpp
// Description: DirectX12�̃I�u�W�F�N�g�f�[�^
//              �iDirectX12�ł̃f�o�b�O�p�ł���A�ŏI�I�ɂ�11�̕��Ɠ����\��j
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================
#pragma comment (lib,"d3dcompiler.lib")

#include "D3D12ObjData.h"
#include <iterator>
#include <d3dcompiler.h>

int D3D12ObjData::ObjInit(const VertexData12* p_VData, const int vNum, const WORD* p_indexData, const int indexNum)
{
    HRESULT sts;

    // �o�[�e�b�N�X�o�b�t�@�[�̍쐬
    D3D12_HEAP_PROPERTIES heapprop = {};
    heapprop.Type = D3D12_HEAP_TYPE_UPLOAD;
    heapprop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    heapprop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
    heapprop.CreationNodeMask = 1;
    heapprop.VisibleNodeMask = 1;

    D3D12_RESOURCE_DESC vbDesc = {};
    vbDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    vbDesc.Width = sizeof(p_VData) * vNum;
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

    // ���_�f�[�^�̃}�b�v
    VertexData12* vertMap = nullptr;
    sts = m_pVertexBuffer->Map(0, nullptr, (void**)&vertMap);
    if (FAILED(sts))
    {
        return -1;
    }

    // �|�C���^�œn���ƃC�e���[�^���擾�ł��Ȃ��̂ŃR�s�[������ăo�b�t�@�ɃR�s�[
    // ��肭�ǂ����@�����Ă�̂ŉ��P�̗]�n�A��
    std::vector<VertexData12> vData;
    for (int i = 0; i < vNum; i++)
    {
        vData.emplace_back();
        vData[i] = p_VData[i];
    }

    std::copy(vData.begin(), vData.end(), vertMap);
    m_pVertexBuffer->Unmap(0, nullptr);

    // �o�[�e�b�N�X�o�b�t�@�[�r���[�̍쐬
    m_vertexBufferView.BufferLocation = m_pVertexBuffer.Get()->GetGPUVirtualAddress();
    m_vertexBufferView.SizeInBytes = sizeof(VertexData12) * vNum;   // ���o�C�g��
    m_vertexBufferView.StrideInBytes = sizeof(VertexData12);    // 1���_������̃T�C�Y


    // �C���f�b�N�X�o�b�t�@�̍쐬
    D3D12_RESOURCE_DESC idxDesc = {};
    idxDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    idxDesc.Width = sizeof(p_indexData) * indexNum;
    idxDesc.Height = 1;
    idxDesc.DepthOrArraySize = 1;
    idxDesc.MipLevels = 1;
    idxDesc.Format = DXGI_FORMAT_UNKNOWN;
    idxDesc.SampleDesc.Count = 1;
    idxDesc.SampleDesc.Quality = 0;
    idxDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
    idxDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
    sts = D3D12Graphics::GetInstance().getDevPtr()->CreateCommittedResource(
        &heapprop,
        D3D12_HEAP_FLAG_NONE,
        &idxDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&m_pIndexBuffer));
    if (FAILED(sts))
    {
        return -1;
    }

    // �C���f�b�N�X�o�b�t�@�ɃR�s�[
    unsigned short* mappedIdx = nullptr;
    sts = m_pIndexBuffer->Map(0, nullptr, (void**)&mappedIdx);
    if (FAILED(sts))
    {
        return -1;
    }
    // ���_�f�[�^�̃R�s�[�Ɠ������R�s�[���Ƃ��Ă���R�s�[
    std::vector<WORD> idxData;
    for (int i = 0; i < indexNum; i++)
    {
        idxData.emplace_back();
        idxData[i] = p_indexData[i];
    }
    std::copy(idxData.begin(), idxData.end(), mappedIdx);
    m_pIndexBuffer->Unmap(0, nullptr);

    m_indexBufferView.BufferLocation = m_pIndexBuffer.Get()->GetGPUVirtualAddress();
    m_indexBufferView.Format = DXGI_FORMAT_R16_UINT;
    m_indexBufferView.SizeInBytes = sizeof(WORD) * indexNum;

    m_indexNum = indexNum;

    // �V�F�[�_�[�̓ǂݍ���
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

    // �C���v�b�g���C�A�E�g�̍쐬
    D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
    };

    // ���[�g�V�O�l�`���̍쐬
    D3D12_ROOT_SIGNATURE_DESC rsDesc = {};
    rsDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;    // ���_���݈̂����n��
    
    ComPtr<ID3DBlob> rootsigBlob = nullptr;
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
    D3D12Graphics::GetInstance().getCmdPtr()->IASetIndexBuffer(&m_indexBufferView);
    //D3D12Graphics::GetInstance().getCmdPtr()->DrawInstanced(3, 1, 0, 0);
    D3D12Graphics::GetInstance().getCmdPtr()->DrawIndexedInstanced(m_indexNum, 1, 0, 0, 0);
}