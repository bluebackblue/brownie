

/** DiffuseSampler
*/
SamplerState DiffuseSampler
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
};


/** PS_ConstantBuffer_B1
*/
cbuffer PS_ConstantBuffer_B1 : register(b0)
{
	uint flag1;
	uint flag2;
	uint flag3;
	uint flag4;
}


/** VS_IN
*/
struct VS_IN
{
	float4 in_pos		: SV_POSITION0;
	float4 in_color		: COLOR0;
};


/** PS
*/
float4 PS(VS_IN a_vs_in) : SV_Target
{
	return a_vs_in.in_color;
}

