

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
#include "./texture_bmp.h"
#include "./texture.h"


/** NBsys::NTexture
*/
namespace NBsys{namespace NTexture
{
	/** CreateTexture_FromTga
	*/
	sharedptr< Texture > CreateTexture_FromBmp(const sharedptr< u8 >& a_data,s32 a_size,const STLWString& a_name)
	{
		const u8* t_raw = reinterpret_cast< const u8* >(a_data.get());




		//タイプ。
		u16 t_header_type =	Memory::Copy< u16 >(t_raw);
		if(t_header_type != 0x4D42){
			ASSERT(0);
			return nullptr;
		}

		//ファイルサイズ。
		u32 t_heaer_filesize = Memory::Copy< u32 >(t_raw);
		if(t_heaer_filesize > static_cast<u32>(a_size)){
			ASSERT(0);
			return nullptr;
		}

		//予約。
		u16 t_header_reserved1 = Memory::Copy< u16 >(t_raw);
		u16 t_header_reserved2 = Memory::Copy< u16 >(t_raw);

		//オフセット。
		u32 t_data_offset = Memory::Copy< u32 >(t_raw);




		//構造体のサイズ。
		u32 t_size = Memory::Copy< u32 >(t_raw);

		//ビットマップの幅(ピクセル)。
		u32 t_width = Memory::Copy< u32 >(t_raw);

		//ビットマップの高さ(ピクセル)。
		u32 t_height = Memory::Copy< u32 >(t_raw);

		//常に1。
		u16 t_planes = Memory::Copy< u16 >(t_raw);

		//1ピクセル辺りのビット数。
		u16 t_bit_count = Memory::Copy< u16 >(t_raw);

		//圧縮形態 無圧縮ならばBI_RGB(16,256色の場合)。
		u32 t_compression = Memory::Copy< u32 >(t_raw);

		//画像のバイト数 biCompressionがBI_RGBの場合は0でもよい。
		u32 t_size_image = Memory::Copy< u32 >(t_raw);

		//X方向の1ピクセル辺りのメートル数。
		u32 t_x_pels_per_meter = Memory::Copy< u32 >(t_raw);

		//Y方向の1ピクセル辺りのメートル数。
		u32 t_y_pels_per_meter = Memory::Copy< u32 >(t_raw);

		//カラーテーブルに含まれる色の数(0場合はその型の最大になる)。
		u32 t_color_size = Memory::Copy< u32 >(t_raw);

		//重要な色の数 0の場合は全部重要。
		u32 t_color_size_important = Memory::Copy< u32 >(t_raw);



		const u8* t_src = reinterpret_cast< const u8* >(a_data.get()) + t_data_offset;

		sharedptr< u8 > t_pixel(new u8[t_width * t_height * 4],default_delete< u8[] >());
		u32* t_dst = reinterpret_cast< u32* >(t_pixel.get());

		for(s32 yy=0;yy<static_cast<s32>(t_height);yy++){
			for(s32 xx=0;xx<static_cast<s32>(t_width);xx++){
				s32 t_index = t_width * yy + xx;
				t_dst[t_index] = (static_cast<u32>(t_src[t_index*3+0]))<<24 | (static_cast<u32>(t_src[t_index*3+1]))<<16 | (static_cast<u32>(t_src[t_index*3+2]))<<8 | 0x000000FF; 
			}
		}

		sharedptr< Texture > t_texture(new Texture(t_pixel,t_width,t_height,t_width * 4,TextureType::R8G8B8A8,a_name));

		return t_texture;
	}

}}

