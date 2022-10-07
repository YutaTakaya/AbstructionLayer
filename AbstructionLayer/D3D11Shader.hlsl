//==============================================================================
// Filename: D3D11Shader.hlsl
// Description: DirectX11の描画システムで使用する基本シェーダー
// Copyright (C) Silicon Studio Co.,Ltd.All rightsreserved.
//==============================================================================

cbuffer ConstantBuffer
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

Texture2D TextureData : register(t0);

SamplerState SamplerData : register(s0);

VSOutput VSmain(float4 pos : POSITION, float2 tex : TEXCOORD, float4 col : COLOR)
{
	VSOutput Out;
    Out = (VSOutput) 0;     //初期化
    
    // 各種行列計算
    Out.Pos = mul(pos, World);
    Out.Pos = mul(Out.Pos, View);
    Out.Pos = mul(Out.Pos, Projection);
    
    // テクスチャと色情報の受け渡し
    Out.Tex = tex;
    Out.Col = col;
	return Out;
}

float4 PSmain(VSOutput In) : SV_TARGET0
{   
    float4 textureCol = TextureData.Sample(SamplerData, In.Tex);
    // テクスチャに色を乗算
    textureCol.r *= In.Col.r;
    textureCol.g *= In.Col.g;
    textureCol.b *= In.Col.b;
    textureCol.a *= In.Col.a;
    return textureCol;
}