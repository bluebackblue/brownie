

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


/** lib
*/
#if(BSYS_TEXTURE_PNG_ENABLE)
	#include <brownie_config/texture_png_lib.h>
#endif


/** include
*/
#if(BSYS_TEXTURE_PNG_ENABLE)
	#include <brownie_config/texture_png_include.h>
#endif


/** NBsys::NTexture
*/
namespace NBsys{namespace NTexture
{

	/** ワーク。
	*/
	struct png_work
	{
		const u8* data;
		u32 data_len;
		u32 data_offset;
	};

	/** 読み込み。
	*/
	void png_memread_func(png_structp a_png_ptr,png_bytep a_buf,png_size_t a_size)
	{
		png_work* t_png_buffer = reinterpret_cast< png_work* >(png_get_io_ptr(a_png_ptr));

		if((t_png_buffer->data_offset + a_size) <= (t_png_buffer->data_len)){
			Memory::memcpy(a_buf,static_cast<s32>(a_size),t_png_buffer->data + t_png_buffer->data_offset,static_cast<s32>(a_size));
			t_png_buffer->data_offset += static_cast<u32>(a_size);
		}else{
			ASSERT(0);
		}
	}

	/** CreateTexture_FromPng
	*/
	sharedptr< Texture > CreateTexture_FromPng(const sharedptr< u8 >& a_data,s32 a_size,const STLWString& a_name)
	{
		png_work t_png_buffer;
		t_png_buffer.data = a_data.get();
		t_png_buffer.data_len = a_size;
		t_png_buffer.data_offset = 0;

		if(png_check_sig(const_cast<png_bytep>(t_png_buffer.data),8) == 0){
			ASSERT(0);
			return nullptr;
		}

		png_structp t_png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,nullptr,nullptr,nullptr);
		if(t_png_ptr == nullptr){
			ASSERT(0);
			return nullptr;
		}

		png_infop t_info_ptr = png_create_info_struct(t_png_ptr);
		if(t_info_ptr == nullptr){
			ASSERT(0);
			png_destroy_read_struct(&t_png_ptr,nullptr,nullptr);
			return nullptr;
		}

		png_set_read_fn(t_png_ptr,reinterpret_cast< png_voidp >(&t_png_buffer),png_memread_func);

		png_uint_32 t_width;
		png_uint_32 t_height;
		s32 t_bit_depth;
		s32 t_color_type;
		s32 t_interlace_type;
		s32 t_compression_type;
		s32 t_filter_type;
		{
			png_read_info(t_png_ptr,t_info_ptr);
			png_get_IHDR(t_png_ptr,t_info_ptr,&t_width,&t_height,&t_bit_depth,&t_color_type,&t_interlace_type,&t_compression_type,&t_filter_type);
		}

		sharedptr< u8 > t_pixel(new u8[t_width * t_height * 4],default_delete< u8[] >());

		s32 t_line_size = (static_cast<s32>(t_width) * t_bit_depth/8 * 4) + 1;

		sharedptr< u8 > t_line_data(new u8[t_line_size],default_delete< u8[] >());
		
		s32 t_offset = 0;
		for(s32 yy=0;yy<static_cast<s32>(t_height);yy++){

			t_line_data.get()[(static_cast<s32>(t_width) * t_bit_depth/8 * 4)] = 0xCC;

			png_read_row(t_png_ptr,t_line_data.get(),nullptr);

			ASSERT(t_line_data.get()[(static_cast<s32>(t_width) * t_bit_depth/8 * 4)] == 0xCC);

			for(s32 xx=0;xx<static_cast<s32>(t_width);xx++){
				t_pixel.get()[(yy * t_width + xx) * 4 + 0] = t_line_data.get()[xx * 4 + 0];
				t_pixel.get()[(yy * t_width + xx) * 4 + 1] = t_line_data.get()[xx * 4 + 1];
				t_pixel.get()[(yy * t_width + xx) * 4 + 2] = t_line_data.get()[xx * 4 + 2];
				t_pixel.get()[(yy * t_width + xx) * 4 + 3] = t_line_data.get()[xx * 4 + 3];
			}
		}

		t_line_data.reset();

		sharedptr< Texture > t_texture(new Texture(t_pixel,t_width,t_height,t_width * 4,TextureType::R8G8B8A8,a_name));

		return t_texture;
	}

}}

