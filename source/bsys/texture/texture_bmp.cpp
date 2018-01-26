

/**
 * Copyright (c) blueback
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
#include "./texture_bmp.h"
#include "./texture.h"


/** warning

4710 : この関数はインライン展開のために選択されましたが、コンパイラはインライン展開を実行しませんでした。

*/
#pragma warning(disable:4710)


/** NBsys::NTexture
*/
#if(BSYS_TEXTURE_ENABLE)
namespace NBsys{namespace NTexture
{
	/** CreateTexture_Bmp
	*/
	sharedptr<Texture> CreateTexture_Bmp(const sharedptr<u8>& a_data,s32 a_size,const STLWString& a_name)
	{
		const u8* t_raw = reinterpret_cast<const u8*>(a_data.get());

		//タイプ。
		u16 t_header_type =	NMemory::StreamCopy<u16>(t_raw);
		if(t_header_type != 0x4D42){
			ASSERT(0);
			return nullptr;
		}

		//ファイルサイズ。
		u32 t_heaer_filesize = NMemory::StreamCopy<u32>(t_raw);
		if(t_heaer_filesize > static_cast<u32>(a_size)){
			ASSERT(0);
			return nullptr;
		}

		//予約。
		u16 t_header_reserved1 = NMemory::StreamCopy<u16>(t_raw);
		UNUSED(t_header_reserved1);
		u16 t_header_reserved2 = NMemory::StreamCopy<u16>(t_raw);
		UNUSED(t_header_reserved2);

		//オフセット。
		u32 t_data_offset = NMemory::StreamCopy<u32>(t_raw);

		//構造体のサイズ。
		u32 t_size = NMemory::StreamCopy<u32>(t_raw);
		UNUSED(t_size);

		//ビットマップの幅(ピクセル)。
		u32 t_width = NMemory::StreamCopy<u32>(t_raw);

		//ビットマップの高さ(ピクセル)。
		u32 t_height = NMemory::StreamCopy<u32>(t_raw);

		//常に1。
		u16 t_planes = NMemory::StreamCopy<u16>(t_raw);
		UNUSED(t_planes);

		//1ピクセル辺りのビット数。
		u16 t_bit_count = NMemory::StreamCopy<u16>(t_raw);
		UNUSED(t_bit_count);

		//圧縮形態 無圧縮ならばBI_RGB(16,256色の場合)。
		u32 t_compression = NMemory::StreamCopy<u32>(t_raw);
		UNUSED(t_compression);

		//画像のバイト数 biCompressionがBI_RGBの場合は0でもよい。
		u32 t_size_image = NMemory::StreamCopy<u32>(t_raw);
		UNUSED(t_size_image);

		//X方向の1ピクセル辺りのメートル数。
		u32 t_x_pels_per_meter = NMemory::StreamCopy<u32>(t_raw);
		UNUSED(t_x_pels_per_meter);

		//Y方向の1ピクセル辺りのメートル数。
		u32 t_y_pels_per_meter = NMemory::StreamCopy<u32>(t_raw);
		UNUSED(t_y_pels_per_meter);

		//カラーテーブルに含まれる色の数(0場合はその型の最大になる)。
		u32 t_color_size = NMemory::StreamCopy<u32>(t_raw);
		UNUSED(t_color_size);

		//重要な色の数 0の場合は全部重要。
		u32 t_color_size_important = NMemory::StreamCopy<u32>(t_raw);
		UNUSED(t_color_size_important);

		const u8* t_src = reinterpret_cast<const u8*>(a_data.get()) + t_data_offset;

		sharedptr<u8> t_pixel(new u8[t_width * t_height * 4],default_delete<u8[]>());
		u32* t_dst = reinterpret_cast<u32*>(t_pixel.get());

		for(u32 yy=0;yy<t_height;yy++){
			for(u32 xx=0;xx<t_width;xx++){
				u32 t_index = t_width * yy + xx;
				t_dst[t_index] = 0xFF000000 | (static_cast<u32>(t_src[t_index*3+0]))<<16 | (static_cast<u32>(t_src[t_index*3+1]))<<8 | t_src[t_index*3+2]; 
			}
		}

		sharedptr<Texture> t_texture(new Texture(t_pixel,Size2DType<s32>(static_cast<s32>(t_width),static_cast<s32>(t_height)),static_cast<s32>(t_width * 4),TextureType::R8G8B8A8,a_name));

		return t_texture;
	}


}}
#endif

