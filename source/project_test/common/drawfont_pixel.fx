

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
Texture2D tex_diffuse_1 : register(t0);
Texture2D tex_diffuse_2 : register(t1);
Texture2D tex_diffuse_3 : register(t2);
Texture2D tex_diffuse_4 : register(t3);


/** PS_ConstantBuffer_B1
*/
cbuffer PS_ConstantBuffer_B1 : register(b0)
{
	uint flag1;
	uint flag2;
	uint flag3;
	uint flag4;

	uint dummy1;
	uint dummy2;
	uint dummy3;
	uint dummy4;
}


/** VS_IN
*/
struct VS_IN
{
	float4 in_pos				: SV_POSITION0;
	float4 in_color				: COLOR0;
	float2 in_uv				: TEXCOORD0;
	uint   in_texture_index[4]	: BLENDINDICES;
};


/** PS
*/
float4 PS(VS_IN a_vs_in) : SV_Target
{
	//diffuse
	float4 t_color = a_vs_in.in_color;

	//texture index
	uint t_texture_index = a_vs_in.in_texture_index[0];

	if(t_texture_index == 0){
		//小サイズフォント。

		t_color *= tex_diffuse_1.Sample(diffuse_sampler,a_vs_in.in_uv);

		if(t_color.a < 0.2){
			discard;
		}else{
			t_color.a = t_color.a * t_color.a;
			t_color.a = saturate(t_color.a + 0.3);
		}
	}else if(t_texture_index == 1){
		//中サイズフォント。

		t_color *= tex_diffuse_2.Sample(diffuse_sampler,a_vs_in.in_uv);
	}else if(t_texture_index == 2){
		//大サイズフォント。

		t_color *= tex_diffuse_3.Sample(diffuse_sampler,a_vs_in.in_uv);
	}else{
		//特大サイズフォント。

		t_color *= tex_diffuse_4.Sample(diffuse_sampler,a_vs_in.in_uv);
	}
	
	return t_color;
}

