

/** VS_ConstantBuffer_B0
*/
cbuffer VS_ConstantBuffer_B0 : register( b0 )
{
	float4x4 view_projection;
}


/** VS_IN
*/
struct VS_IN
{
	float4 in_pos		: POSITION0;
	float4 in_color		: COLOR0;
	float2 in_uv		: TEXCOORD0;
};


/** VS_OUT
*/
struct VS_OUT
{
	float4 out_pos		: SV_POSITION0;
	float4 out_color	: COLOR0;
	float2 out_uv		: TEXCOORD0;
};


/** VS
*/
VS_OUT VS(VS_IN a_vs_in)
{
	VS_OUT t_out;

	t_out.out_pos = mul(a_vs_in.in_pos,view_projection);
	t_out.out_color = a_vs_in.in_color;
	t_out.out_uv = a_vs_in.in_uv;

	return t_out;
}

