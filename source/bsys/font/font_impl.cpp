

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief フォント。
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
#include "./font_impl.h"


/** warning

4710 : この関数はインライン展開のために選択されましたが、コンパイラはインライン展開を実行しませんでした。

*/
#pragma warning(disable:4710)


/** NBsys::NFont
*/
#if(BSYS_FONT_ENABLE)
namespace NBsys{namespace NFont
{
	/** constructor
	*/
	Font_Impl::Font_Impl(const STLWString& a_font_name,s32 a_font_size)
		:
		#if defined(PLATFORM_VCWIN)
		font_handle(nullptr),
		#endif

		#if defined(PLATFORM_VCWIN)
		hdc(nullptr),
		#endif

		font_size(a_font_size),
		font_name(a_font_name),

		buffer_size(0),
		buffer(nullptr)
	{
		#if defined(PLATFORM_VCWIN)
		{
			this->font_handle = CreateFontW(
				this->font_size,
				this->font_size / 2,
				0,
				0,
				FW_LIGHT,
				FALSE,
				FALSE,
				FALSE,
				SHIFTJIS_CHARSET,
				OUT_DEFAULT_PRECIS,
				CLIP_DEFAULT_PRECIS,
				ANTIALIASED_QUALITY,
				DEFAULT_PITCH,
				this->font_name.c_str()
			);
		}
		#endif

		#if defined(PLATFORM_VCWIN)
		{
			//デバイスコンテキスト。
			HWND t_handle = GetDesktopWindow();
			HDC t_hdc_desktop = GetDC(t_handle);
			this->hdc = CreateCompatibleDC(t_hdc_desktop);
		}
		#endif
	}


	/** destructor
	*/
	Font_Impl::~Font_Impl()
	{
		#if defined(PLATFORM_VCWIN)
		::DeleteObject(this->font_handle);
		#endif
	}


	/** GetPixel_R8G8B8A8
	*/
	Font_State Font_Impl::GetPixel_R8G8B8A8(sharedptr<u8>& a_dest_data,s32 a_byte_offset,const Size2DType<s32>& a_dest_size,wchar a_code)
	{
		Font_State t_font_state;

		#if defined(PLATFORM_VCWIN)
		{
			GLYPHMETRICS t_glyphmetrics = {0};
			TEXTMETRICW t_text_metric = {0};
			s32 t_buffer_size = 0;
			{
				::SelectObject(this->hdc,this->font_handle);

				UINT t_code = a_code;

				::GetTextMetricsW(this->hdc,&t_text_metric);

				//サイズ取得。
				{
					MAT2 t_mat2 = {
						{0,1,},
						{0,0,},
						{0,0,},
						{0,1,}
					};
					t_buffer_size = static_cast<s32>(::GetGlyphOutlineW(this->hdc,t_code,GGO_GRAY8_BITMAP,&t_glyphmetrics,0,WIN_NULL,&t_mat2));
					if(t_buffer_size >= this->buffer_size){
						this->buffer_size = (((t_buffer_size << 8) + 1) >> 8);
						this->buffer.reset(new u8[this->buffer_size]);
					}
					ASSERT(t_buffer_size <= this->buffer_size);
				}

				//データ取得。
				{
					MAT2 t_mat2 = {
						{0,1,},
						{0,0,},
						{0,0,},
						{0,1,}
					};
					::GetGlyphOutlineW(this->hdc,t_code,GGO_GRAY8_BITMAP,&t_glyphmetrics,t_buffer_size,(LPVOID)this->buffer.get(),&t_mat2);
				}
			}

			//フォントステータス。
			{
				t_font_state.code = a_code;
				t_font_state.x = t_glyphmetrics.gmptGlyphOrigin.x;
				t_font_state.y = t_text_metric.tmAscent - t_glyphmetrics.gmptGlyphOrigin.y;
				t_font_state.black_box_x = static_cast<s32>(t_glyphmetrics.gmBlackBoxX);
				t_font_state.black_box_y = static_cast<s32>(t_glyphmetrics.gmBlackBoxY);
				t_font_state.glyph_origin_x = t_glyphmetrics.gmptGlyphOrigin.x;
				t_font_state.glyph_origin_y = t_glyphmetrics.gmptGlyphOrigin.y;
				t_font_state.cell_inc_x = t_glyphmetrics.gmCellIncX;
				t_font_state.cell_inc_y = t_glyphmetrics.gmCellIncY;
			}

			//ピクセル。
			{
				u8* t_dest_data = &a_dest_data.get()[a_byte_offset];
				NMemory::Set(t_dest_data,0x00,a_dest_size.ww * a_dest_size.hh * 4);

				s32 t_buffer_alignment = static_cast<u16>(t_font_state.black_box_x + 3) & 0xFFFC;

				s32 xx_max = t_font_state.black_box_x;
				s32 yy_max = t_font_state.black_box_y;
				if(t_buffer_size <= 0){
					xx_max = 0;
					yy_max = 0;
				}

				if(xx_max >= a_dest_size.ww){
					xx_max = a_dest_size.ww;
				}
				if(yy_max >= a_dest_size.hh){
					yy_max = a_dest_size.hh;
				}

				u8* t_buffer = this->buffer.get();

				for(s32 xx=0;xx<xx_max;xx++){
					for(s32 yy=0;yy<yy_max;yy++){
						s32 t_dest_offset = xx * 4 + yy * 4 * a_dest_size.ww;
						s32 t_buffer_offset = xx + yy * t_buffer_alignment;

						u8 t_alpha = t_buffer[t_buffer_offset];
						if(t_alpha > 0){
							s32 t_alpha_32 = static_cast<s32>(t_alpha) * 4;
							t_alpha = static_cast<u8>(t_alpha_32 <= 0xFF ? t_alpha_32 : 0xFF);

							t_dest_data[t_dest_offset+0] = 0xFF;
							t_dest_data[t_dest_offset+1] = 0xFF;
							t_dest_data[t_dest_offset+2] = 0xFF;
							t_dest_data[t_dest_offset+3] = t_alpha;
						}

						#if(0)
						if(a_dest_width == 16){
							if((xx % 2 == 0) && (yy % 2 == 0)){
								t_dest_data[t_dest_offset+0] = 0xFF;
								t_dest_data[t_dest_offset+1] = 0xFF;
								t_dest_data[t_dest_offset+2] = 0xFF;
								t_dest_data[t_dest_offset+3] = 0xFF;
							}else{
								t_dest_data[t_dest_offset+0] = 0x00;
								t_dest_data[t_dest_offset+1] = 0x00;
								t_dest_data[t_dest_offset+2] = 0x00;
								t_dest_data[t_dest_offset+3] = 0x00;
							}
						}
						#endif
					}
				}
			}
		}
		#endif

		return t_font_state;
	}


}}
#endif

