

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief シェーダー。
*/


/** diffuse_sampler
*/
SamplerState diffuse_sampler : register(s0);



/** tex_diffuse
*/
Texture2D tex_diffuse : register(t0);


/** PS_ConstantBuffer_B0
*/
cbuffer PS_ConstantBuffer_B0 : register(b0)
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
	float2 in_uv		: TEXCOORD0;
};


/** PS
*/
float4 PS(VS_IN a_vs_in) : SV_Target
{
	//diffuse
	float4 t_color = a_vs_in.in_color;

	if(flag1 & 0x00000001){
		//use texture
		t_color *= tex_diffuse.Sample(diffuse_sampler,a_vs_in.in_uv);
	}

	//debug
	//if(t_color.a <= 0.5){
	//	t_color.a = 0.5;
	//}

	return t_color;
}

