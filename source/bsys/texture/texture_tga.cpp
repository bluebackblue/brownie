

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief テクスチャー。
*/


/** include
*/
#include <bsys_pch.h>


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** include
*/
#include "./texture_tga.h"
#include "./texture.h"


/** NBsys::NTexture
*/
#if(BSYS_TEXTURE_ENABLE)
namespace NBsys{namespace NTexture
{
	/** HEADER_TGA
	*/
	#pragma pack(1)
	struct HEADER_TGA
	{
		/** IDフィールド長。
		*/
		u8	h_IDLength;

		/** カラーマップタイプ(カラーマップの有無)。
		*/
		u8	h_colorMap;

		/** 画像タイプ。

		0	: イメージデータ無し
		1	: カラーマップイメージ
		2	: RGBカラーイメージ
		3	: 白黒イメージ
		9	: ランレングス圧縮カラーマップイメージ
		10	: ランレングス圧縮RGBカラーイメージ
		11	: ランレングス圧縮白黒イメージ
		32	: カラーマップデータをハフマン/デルタ/ランレングス圧縮
		33	: カラーマップデータをハフマン/デルタ/ランレングス圧縮 4パス4分木処理

		*/
		u8	h_imgType;

		/** カラーマップ原点。
		*/
		u16	h_colorMapEntry;

		/** カラーマップ長。
		*/
		u16	h_colorMapLength;

		/** カラーマップ深度(カラーマップエントリーサイズ)。
		*/
		u8	h_colorMapSize;

		/** 画像X方向原点。
		*/
		u16	h_x;

		/** 画像Y方向原点。
		*/
		u16	h_y;

		/** 画像幅。
		*/
		u16	h_w;

		/** 画像高さ。
		*/
		u16	h_h;

		/** 画像深度(画像ピクセルサイズ)。
		*/
		u8	h_bitDepth;

		/** 画像デスクリプタ。

		00001111 & 0x0F : アルファチャンネル深度
		00010000 & 0x10 : X方向格納方法 / 0: 左から右方向 / 1: 右から下方向
		00100000 & 0x20 : Y方向格納方法 / 0: 下から上方向 / 1: 上から下方向
		11000000 & 0xC0 : インターリーブフラグ

		*/
		u8	h_img;
	};
	#pragma pack()


	/** CreateTexture_Tga
	*/
	sharedptr<Texture> CreateTexture_Tga(const sharedptr<u8>& a_data,s32 /*a_size*/,const STLWString& a_name)
	{
		const HEADER_TGA* t_header = reinterpret_cast<const HEADER_TGA*>(a_data.get());

		sharedptr<u8> t_pixel(new u8[static_cast<u32>(t_header->h_w * t_header->h_h * 4)],default_delete<u8[]>());
		{
			const u8* t_src = a_data.get() + (sizeof(HEADER_TGA) + t_header->h_IDLength);
			u32* t_dst = reinterpret_cast<u32*>(t_pixel.get());
			u32* t_dst_end = t_dst + (t_header->h_w * t_header->h_h);

			s32 stride = t_header->h_bitDepth / 8;
			while(t_dst != t_dst_end){
				u8 val = *t_src;
				t_src++;

				u8 num = (val & 0x7fU) + 0x01U;
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

		sharedptr<Texture> t_texture(new Texture(t_pixel,t_header->h_w,t_header->h_h,t_header->h_w * 4,TextureType::R8G8B8A8,a_name));

		return t_texture;
	}


}}
#endif

