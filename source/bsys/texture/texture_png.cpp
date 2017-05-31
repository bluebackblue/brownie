

/**
* Copyright (c) 2017 blueback
* Released under the MIT License
* https://github.com/bluebackblue/brownie/blob/master/LICENSE
* http://bbbproject.sakura.ne.jp/wordpress/mitlicense
* @brief テクスチャー。
*/


/** include
*/
#include <bsys_pch.h>


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./texture_png.h"
#include "./texture.h"


/** NBsys::NTexture
*/
namespace NBsys{namespace NTexture
{
	/** CreateTexture_FromPng
	*/
	sharedptr< Texture > CreateTexture_FromPng(const sharedptr< u8 >& a_data,const STLString& a_name)
	{
		sharedptr< u8 > t_pixel(new u8[8 * 8 * 4],default_delete< u8[] >());

		/*
		const HEADER_TGA* t_header = reinterpret_cast< const HEADER_TGA* >(a_data.get());

		sharedptr< u8 > t_pixel(new u8[t_header->h_w * t_header->h_h * 4],default_delete< u8[] >());
		{
			const u8* t_src = a_data.get() + (sizeof(HEADER_TGA) + t_header->h_IDLength);
			u32* t_dst = reinterpret_cast< u32* >(t_pixel.get());
			u32* t_dst_end = t_dst + (t_header->h_w * t_header->h_h);

			s32 stride = t_header->h_bitDepth / 8;
			while(t_dst != t_dst_end){
				u8 val = *t_src;
				t_src++;

				u8 num = (val & 0x7f) + 1;
				if(val & 0x80){
					u32 t_color = 0xffffffff;
					if(stride == 3){
						u32 b = *t_src;
						t_src++;
						u32 g = *t_src;
						t_src++;
						u32 r = *t_src;
						t_src++;
						u32 a = 0xff;

						t_color = (a<<24) | (b<<16) |( g<<8) |(r);
					}else if(stride == 4){
						u32 b = *t_src;
						t_src++;
						u32 g = *t_src;
						t_src++;
						u32 r = *t_src;
						t_src++;
						u32 a = *t_src;
						t_src++;

						t_color = (a<<24) | (b<<16) |( g<<8) |(r);
					}
					for(s32 i=0; i<num; i++){
						*t_dst = t_color;
						t_dst++;
					}
				}else{
					for(s32 i=0; i<num; i++){
						if(stride == 3){
							u32 b = *t_src;
							t_src++;
							u32 g = *t_src;
							t_src++;
							u32 r = *t_src;
							t_src++;
							u32 a = 0xff;

							u32 col = (a<<24) | (b<<16) |( g<<8) |(r);
							*t_dst = col;
							t_dst++;
						}else if(stride == 4){
							u32 b = *t_src;
							t_src++;
							u32 g = *t_src;
							t_src++;
							u32 r = *t_src;
							t_src++;
							u32 a = *t_src;
							t_src++;

							u32 t_color = (a<<24) | (b<<16) |( g<<8) |(r);
							*t_dst = t_color;
							t_dst++;
						}
					}
				}
			}
		}
		*/

		sharedptr< Texture > t_texture(new Texture(t_pixel,8,8,TextureType::R8G8B8A8,a_name));

		return t_texture;
	}

}}

