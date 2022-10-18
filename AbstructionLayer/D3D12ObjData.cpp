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

    // �e�N�X�`���̐����i���u���j
    std::vector<TexRGBA> textureData(256 * 256);
    for (int x = 0; x < 256; x++)
    {
        for (int y = 0; y < 256; y++)
        {
            if ((((x / 32) + (y / 32)) % 2 == 1))
            {
                textureData[x + (y * 256)].R = 0;
                textureData[x + (y * 256)].G = 0;
                textureData[x + (y * 256)].B = 0;
                textureData[x + (y * 256)].A = 255;
            }
            else
            {
                textureData[x + (y * 256)].R = 255;
                textureData[x + (y * 256)].G = 255;
                textureData[x + (y * 256)].B = 255;
                textureData[x + (y * 256)].A = 255;
            }
        }
    }
 
    // �C���v�b�g���C�A�E�g�̍쐬
    D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
    };

    // �e�N�X�`���o�b�t�@�[�̍쐬
    D3D12_HEAP_PROPERTIES texHeapProp = {};
    texHeapProp.Type = D3D12_HEAP_TYPE_CUSTOM;
    texHeapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
    texHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
    texHeapProp.CreationNodeMask = 0;
    texHeapProp.VisibleNodeMask = 0;

    D3D12_RESOURCE_DESC resDesc = {};
    resDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    resDesc.Width = 256;
    resDesc.Height = 256;
    resDesc.DepthOrArraySize = 1;   //2D�Ȃ�0
    resDesc.SampleDesc.Count = 1;
    resDesc.SampleDesc.Quality = 0;
    resDesc.MipLevels = 1;
    resDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
    resDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
    resDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

    sts = D3D12Graphics::GetInstance().getDevPtr()->CreateCommittedResource(
        &texHeapProp,
        D3D12_HEAP_FLAG_NONE,
        &resDesc,
        D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
        nullptr,
        IID_PPV_ARGS(&m_pTextureBuffer));
    if (FAILED(sts))
    {
        return -1;
    }

    sts = m_pTextureBuffer.Get()->WriteToSubresource(
        0,
        nullptr,
        textureData.data(),
        sizeof(TexRGBA) * 256,
        sizeof(TexRGBA) * (UINT)textureData.size());
    if (FAILED(sts))
    {
        return -1;
    }

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


    // �萔�o�b�t�@�r���[�̍쐬
    D3D12_DESCRIPTOR_HEAP_DESC dhDesc = {};
    dhDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
    dhDesc.NodeMask = 0;
    dhDesc.NumDescriptors = 2;  // SRV��CBV
    dhDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
    sts = D3D12Graphics::GetInstance().getDevPtr()->CreateDescriptorHeap(
        &dhDesc,
        IID_PPV_ARGS(&m_pDescHeap));
    if (FAILED(sts))
    {
        return -1;
    }
    
    auto descHeapHandle = m_pDescHeap.Get()->GetCPUDescriptorHandleForHeapStart();

    D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;    // RGBA�����ꂼ��0.0f~1.0f�Ő��K��
    srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = 1;    // �~�b�v�}�b�v���g�p

    D3D12Graphics::GetInstance().getDevPtr()->CreateShaderResourceView(
        m_pTextureBuffer.Get(),
        &srvDesc,
        descHeapHandle);

    descHeapHandle.ptr += D3D12Graphics::GetInstance().getDevPtr()->
        GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);   // �C���N�������g���|�C���^�����炷

    D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
    cbvDesc.BufferLocation = D3D12Camera::GetInstance().getConstBufferPtr()->GetGPUVirtualAddress();
    cbvDesc.SizeInBytes = (UINT)D3D12Camera::GetInstance().getConstBufferPtr()->GetDesc().Width;

    D3D12Graphics::GetInstance().getDevPtr()->CreateConstantBufferView(&cbvDesc, descHeapHandle);
    
    m_localMtx = XMMatrixIdentity();
    m_worldPos.x = 0.0f;
    m_worldPos.y = 0.0f;
    m_worldPos.z = 0.0f;
    return 0;
}

void D3D12ObjData::ObjUpdate()
{
}

void D3D12ObjData::ObjDraw()
{
    // ���[���h�s��֕ϊ�����
    XMMATRIX worldMtx;
    worldMtx = ::XMMatrixTranslation(m_worldPos.x, m_worldPos.y, m_worldPos.z);
    worldMtx = ::XMMatrixMultiply(m_localMtx, worldMtx);

    auto heapPtr = m_pDescHeap.Get()->GetGPUDescriptorHandleForHeapStart();

    D3D12Camera::GetInstance().CameraUpdateConstBuff(worldMtx);

    D3D12Graphics::GetInstance().getCmdPtr()->IASetVertexBuffers(0, 1, &m_vertexBufferView);
    D3D12Graphics::GetInstance().getCmdPtr()->IASetIndexBuffer(&m_indexBufferView);

    D3D12Graphics::GetInstance().getCmdPtr()->SetDescriptorHeaps(1, m_pDescHeap.GetAddressOf());
    D3D12Graphics::GetInstance().getCmdPtr()->SetGraphicsRootDescriptorTable(0, heapPtr);

    heapPtr.ptr += D3D12Graphics::GetInstance().getDevPtr()->
        GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);   // �C���N�������g���|�C���^�����炷

    D3D12Graphics::GetInstance().getCmdPtr()->SetGraphicsRootDescriptorTable(1, heapPtr);
    D3D12Graphics::GetInstance().getCmdPtr()->DrawIndexedInstanced(m_indexNum, 1, 0, 0, 0);
}

void D3D12ObjData::ObjRotate(const float angleX, const float angleY, const float angleZ)
{
    m_localMtx = ::XMMatrixMultiply(m_localMtx, ::XMMatrixRotationX(angleX));
    m_localMtx = ::XMMatrixMultiply(m_localMtx, ::XMMatrixRotationY(angleY));
    m_localMtx = ::XMMatrixMultiply(m_localMtx, ::XMMatrixRotationZ(angleZ));
}

void D3D12ObjData::ObjTranslate(const float posX, const float posY, const float posZ)
{
    m_worldPos.x = posX;
    m_worldPos.y = posY;
    m_worldPos.z = posZ;
}
