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