//==============================================================================
// Filename: D3D12Shader.hlsl
// Description: DirectX12�̕`��V�X�e���Ŏg�p�����{�V�F�[�_�[
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================

cbuffer ConstantBuffer : register(b0)
{
    float4x4 World; //���[���h�ϊ��s��
    float4x4 View; //�r���[�ϊ��s��
    float4x4 Projection; //�����ˉe�ϊ��s��
}

struct VSOutput
{
    float4 Pos : SV_POSITION; // ���_���W�i�ˉe���W�n�j
    float2 Tex : TEXCOORD; // UV���W
    float4 Col : COLOR; // �F
};

VSOutput VSmain(float4 pos : POSITION, float2 uv : TEXCOORD, float4 col : COLOR)
{
    VSOutput output;
    //output.Pos = pos;
    output.Pos = mul(pos, World);
    output.Pos = mul(output.Pos, View);
    output.Pos = mul(output.Pos, Projection);
    output.Tex = uv;
    output.Col = col;
	return output;
}

float4 PSmain(VSOutput input) : SV_TARGET
{
    return float4(input.Col);
}