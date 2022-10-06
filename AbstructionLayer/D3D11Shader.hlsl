cbuffer ConstantBuffer
{
    float4x4 World; //[hÏ·sñ
    float4x4 View; //r[Ï·sñ
    float4x4 Projection; //§ËeÏ·sñ
}

struct VSOutput
{
    float4 Pos : SV_POSITION; // ¸_ÀWiËeÀWnj
    float2 Tex : TEXCOORD; // UVÀW
    float4 Col : COLOR; // F
};

VSOutput VSmain(float4 pos : POSITION, float2 tex : TEXCOORD, float4 col : COLOR)
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
    Out.Pos = mul(Out.Pos, View);
    Out.Pos = mul(Out.Pos, Projection);
    
    Out.Tex = tex;
    Out.Col = col;
	return Out;
}

float4 PSmain(VSOutput In) : SV_TARGET0
{   
    return float4(In.Col);
}