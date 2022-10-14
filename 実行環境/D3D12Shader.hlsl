//==============================================================================
// Filename: D3D12Shader.hlsl
// Description: DirectX12の描画システムで使用する基本シェーダー
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================
Texture2D TextureData : register(t0);

SamplerState SamplerData : register(s0);

cbuffer ConstantBuffer : register(b0)
{
    float4x4 World; //ワールド変換行列
    float4x4 View; //ビュー変換行列
    float4x4 Projection; //透視射影変換行列
}

struct VSOutput
{
    float4 Pos : SV_POSITION; // 頂点座標（射影座標系）
    float2 Tex : TEXCOORD; // UV座標
    float4 Col : COLOR; // 色
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
    float4 outTex = TextureData.Sample(SamplerData, input.Tex);
    outTex.r *= input.Col.r;
    outTex.g *= input.Col.g;
    outTex.b *= input.Col.b;
    outTex.a *= input.Col.a;
    return float4(outTex);
}