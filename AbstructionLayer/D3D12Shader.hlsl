float4 VSmain( float4 pos : POSITION ) : SV_POSITION
{
	return pos;
}

float4 PSmain(float4 pos : SV_POSITION) : SV_TARGET
{
    return float4(1, 1, 1, 1);
}