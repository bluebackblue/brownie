

/** DiffuseSampler
*/
SamplerState DiffuseSampler
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
};


/** tex_diffuse
*/
Texture2D tex_diffuse : register(t0);


/** PS_ConstantBuffer_B1
*/
cbuffer PS_ConstantBuffer_B1 : register( b1 )
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
	float3 in_color		: COLOR0;
	float2 in_uv		: TEXCOORD0;
};


/** PS
*/
float4 PS(VS_IN a_vs_in) : SV_Target
{
	//diffuse
	float4 t_color = float4(a_vs_in.in_color,1.0f);

	//texture
	if(flag1 == 1){
		t_color *= tex_diffuse.Sample(DiffuseSampler,a_vs_in.in_uv);
	}

	return t_color;
}

