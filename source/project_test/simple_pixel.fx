

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
	float4 t_color_tex = tex_diffuse.Sample(DiffuseSampler,a_vs_in.in_uv);
	float4 t_color = t_color_tex * float4(a_vs_in.in_color,1.0f);
	return t_color;
}

