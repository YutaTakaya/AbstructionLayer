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
};

VSOutput VSmain(float4 pos : POSITION, float2 tex : TEXCOORD)
{
	VSOutput Out;
    Out = (VSOutput) 0;
    float4x4 wor =
    {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
    
    Out.Pos = mul(pos, World);
    Out.Pos = mul(pos, View);
    Out.Pos = mul(pos, Projection);
    
    Out.Tex = tex;
	return Out;
}

float4 PSmain(VSOutput In) : SV_TARGET
{   
    return float4(In.Tex, 1, 1);
}