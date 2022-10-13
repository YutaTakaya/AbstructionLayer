//==============================================================================
// Filename: D3D12Shader.hlsl
// Description: DirectX12�̕`��V�X�e���Ŏg�p�����{�V�F�[�_�[
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================

struct VSOutput
{
    float4 Pos : SV_POSITION; // ���_���W�i�ˉe���W�n�j
    float2 Tex : TEXCOORD; // UV���W
    float4 Col : COLOR; // �F
};

VSOutput VSmain(float4 pos : POSITION, float2 uv : TEXCOORD, float4 col : COLOR)
{
    VSOutput output;
    output.Pos = pos;
    output.Tex = uv;
    output.Col = col;
	return output;
}

float4 PSmain(VSOutput input) : SV_TARGET
{
    return float4(input.Col);
}