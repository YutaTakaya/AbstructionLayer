struct VSOutput
{
	float4 Pos : SV_Position;	// ���_���W�i�ˉe���W�n�j
};

float4 VSmain(float4 pos : POSITION) : SV_POSITION
{
	VSOutput Out;
	Out.Pos = pos;
	return pos;
}

float4 PSmain(VSOutput In) : SV_TARGET
{
	return float4(0.5f, 1.0f, 1.0f, 1.0f);
}