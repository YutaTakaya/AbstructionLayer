//==============================================================================
// Filename: D3D11Shader.hlsl
// Description: DirectX11�̕`��V�X�e���Ŏg�p�����{�V�F�[�_�[
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================

cbuffer ConstantBuffer
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

Texture2D TextureData : register(t0);

SamplerState SamplerData : register(s0);

VSOutput VSmain(float4 pos : POSITION, float2 tex : TEXCOORD, float4 col : COLOR)
{
	VSOutput Out;
    Out = (VSOutput) 0;     //������
    
    // �e��s��v�Z
    Out.Pos = mul(pos, World);
    Out.Pos = mul(Out.Pos, View);
    Out.Pos = mul(Out.Pos, Projection);
    
    // �e�N�X�`���ƐF���̎󂯓n��
    Out.Tex = tex;
    Out.Col = col;
	return Out;
}

float4 PSmain(VSOutput In) : SV_TARGET0
{   
    float4 textureCol = TextureData.Sample(SamplerData, In.Tex);
    // �e�N�X�`���ɐF����Z
    textureCol.r *= In.Col.r;
    textureCol.g *= In.Col.g;
    textureCol.b *= In.Col.b;
    textureCol.a *= In.Col.a;
    return textureCol;
}