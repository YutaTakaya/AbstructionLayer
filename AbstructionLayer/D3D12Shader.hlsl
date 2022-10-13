//==============================================================================
// Filename: D3D12Shader.hlsl
// Description: DirectX12の描画システムで使用する基本シェーダー
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================

struct VSOutput
{
    float4 Pos : SV_POSITION; // 頂点座標（射影座標系）
    float2 Tex : TEXCOORD; // UV座標
    float4 Col : COLOR; // 色
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