

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


/** BlendState
*/
BlendState SrcAlphaBlend
{
   BlendEnable[0]           = TRUE;
   SrcBlend                 = SRC_ALPHA;
   DestBlend                = INV_SRC_ALPHA;
   BlendOp                  = ADD;
   SrcBlendAlpha            = ONE;
   DestBlendAlpha           = ONE;
   BlendOpAlpha             = ADD;
   RenderTargetWriteMask[0] = 0x0F;
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
	return float4(t_diff.r,t_diff.g,t_diff.b,t_diff.a);

	//return float4(a_vs_in.in_color.r,a_vs_in.in_color.g,a_vs_in.in_color.b,1.0f);
}

