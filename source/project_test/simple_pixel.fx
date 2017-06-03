

/** tex_diffuse
*/
Texture2D tex_diffuse : register(t0);


/** DiffuseSampler
*/
SamplerState DiffuseSampler
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
};


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
	float4 t_diff = tex_diffuse.Sample(DiffuseSampler,a_vs_in.in_uv);
	return float4(t_diff.r,t_diff.g,t_diff.b,0.5f);

	//return float4(a_vs_in.in_color.r,a_vs_in.in_color.g,a_vs_in.in_color.b,1.0f);
}

