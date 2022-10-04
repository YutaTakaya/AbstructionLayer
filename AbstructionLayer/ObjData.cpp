#include "ObjData.h"


int ObjData::ObjInit(VertexData* p_VData, int vNum)
{
    HRESULT sts;

    // ���_���̃R�s�[
    for (int i = 0; i < vNum; i++)
    {
        m_vertex.emplace_back(p_VData[i]);
    }

    // ���_�o�b�t�@�̍쐬
    D3D11_BUFFER_DESC vbDesc = {};
    vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;    // �f�o�C�X�Ƀo�C���h����Ƃ��̎��
    vbDesc.ByteWidth = m_vertex.size() * sizeof(VertexData);    // �쐬����o�b�t�@�̃T�C�Y
    vbDesc.MiscFlags = 0;                           // ���̑��t���O
    vbDesc.StructureByteStride = 0;                 // �\�����o�b�t�@�̏ꍇ���̃T�C�Y
    vbDesc.Usage = D3D11_USAGE_DEFAULT;             // �o�b�t�@�̎g�p�@
    vbDesc.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA initData = { &m_vertex[0],sizeof(m_vertex),0 };
    sts = D3D11Graphics::GetInstance().getDevPtr()->CreateBuffer(&vbDesc, &initData, &m_vertexBuff);
    if (FAILED(sts))
    {
        return -1;
    }

    return 0;
}


int ObjData::ObjDraw()
{
    UINT stride = sizeof(VertexData);
    UINT offset = 0;
    D3D11Graphics::GetInstance().getDevContextPtr()->IASetVertexBuffers(0, 1, m_vertexBuff.GetAddressOf(), &stride, &offset);
    D3D11Graphics::GetInstance().getDevContextPtr()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

    D3D11Graphics::GetInstance().getDevContextPtr()->VSSetShader(D3D11Graphics::GetInstance().getVertexShaderPtr(), 0, 0);
    D3D11Graphics::GetInstance().getDevContextPtr()->PSSetShader(D3D11Graphics::GetInstance().getPixelShaderPtr(), 0, 0);
    D3D11Graphics::GetInstance().getDevContextPtr()->IASetInputLayout(D3D11Graphics::GetInstance().getInputLayoutPtr());

    D3D11Graphics::GetInstance().getDevContextPtr()->Draw(m_vertex.size(), 0);
    return 0;
}


int ObjData::ObjUninit()
{
    //m_vertex.clear();
    m_vertexBuff->Release();
    return 0;
}

