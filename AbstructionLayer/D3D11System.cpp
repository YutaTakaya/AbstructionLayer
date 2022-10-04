//==============================================================================
// Filename: D3D11System.h
// Description: D3D11�̊�{����
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================

#include "D3D11System.h"
#include "D3D11Graphics.h"

//---------------------------------------------
/// DirectX11�ł̕`�揈��
///
/// \param[] ()
///
/// \return ����ɏI�������ꍇ0���Ԃ����
//--------------------------------------------- 
int D3D11Update()
{
    float color[4] = { 1,0,1,1 };
    D3D11Graphics::GetInstance().getDevContextPtr()->ClearRenderTargetView(D3D11Graphics::GetInstance().getBackBufferVierPtr(), color);

    struct VertexType
    {
        DirectX::XMFLOAT3 Pos;  // ���_���W
    };

    VertexType v[3] = {
        {{0.0f,0.0f,0}},
        {{1.0f,-1.0f,0}},
        {{-1.0f,-1.0f,0}},
    };

    // ���_�o�b�t�@�̍쐬�i�e�X�g�p�̂��ߔ�����A��ŃN���X���j
    D3D11_BUFFER_DESC vbDesc = {};
    vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;    // �f�o�C�X�Ƀo�C���h����Ƃ��̎��
    vbDesc.ByteWidth = sizeof(v);                   // �쐬����o�b�t�@�̃T�C�Y
    vbDesc.MiscFlags = 0;                           // ���̑��t���O
    vbDesc.StructureByteStride = 0;                 // �\�����o�b�t�@�̏ꍇ���̃T�C�Y
    vbDesc.Usage = D3D11_USAGE_DEFAULT;             // �o�b�t�@�̎g�p�@
    vbDesc.CPUAccessFlags = 0;

    ComPtr<ID3D11Buffer> vb;
    D3D11_SUBRESOURCE_DATA initData = { &v[0],sizeof(v),0 };
    D3D11Graphics::GetInstance().getDevPtr()->CreateBuffer(&vbDesc, &initData, &vb);

    UINT stride = sizeof(VertexType);
    UINT offset = 0;
    D3D11Graphics::GetInstance().getDevContextPtr()->IASetVertexBuffers(0, 1, vb.GetAddressOf(), &stride, &offset);
    D3D11Graphics::GetInstance().getDevContextPtr()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

    D3D11Graphics::GetInstance().getDevContextPtr()->VSSetShader(D3D11Graphics::GetInstance().getVertexShaderPtr(), 0, 0);
    D3D11Graphics::GetInstance().getDevContextPtr()->PSSetShader(D3D11Graphics::GetInstance().getPixelShaderPtr(), 0, 0);
    D3D11Graphics::GetInstance().getDevContextPtr()->IASetInputLayout(D3D11Graphics::GetInstance().getInputLayoutPtr());

    D3D11Graphics::GetInstance().getDevContextPtr()->Draw(3, 0);
    return 0;
}
