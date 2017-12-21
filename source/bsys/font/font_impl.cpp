

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief フォント。
*/


/** include
*/
#include <bsys_pch.h>


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./font_impl.h"


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
		font_name(a_font_name)
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
		DeleteObject(this->font_handle);
	}


	/** GetPixel_R8G8B8A8
	*/
	Font_State Font_Impl::GetPixel_R8G8B8A8(sharedptr<u8>& a_dest_data,s32 a_offset,s32 a_dest_width,s32 a_dest_height,wchar a_code)
	{
		Font_State t_font_state;

		#if defined(PLATFORM_VCWIN)
		{
			GLYPHMETRICS t_glyphmetrics = {0};
			TEXTMETRICW t_text_metric = {0};
			DWORD t_buffer_size = 0;
			u8 t_buffer[256*256*4];
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
					t_buffer_size = ::GetGlyphOutlineW(this->hdc,t_code,GGO_GRAY8_BITMAP,&t_glyphmetrics,0,WIN_NULL,&t_mat2);
					ASSERT(t_buffer_size <= sizeof(t_buffer));
				}

				//データ取得。
				{
					MAT2 t_mat2 = {
						{0,1,},
						{0,0,},
						{0,0,},
						{0,1,}
					};
					::GetGlyphOutlineW(this->hdc,t_code,GGO_GRAY8_BITMAP,&t_glyphmetrics,t_buffer_size,(LPVOID)&t_buffer[0],&t_mat2);
				}
			}

			//フォントステータス。
			{
				t_font_state.code = a_code;
				t_font_state.x = t_glyphmetrics.gmptGlyphOrigin.x;
				t_font_state.y = t_text_metric.tmAscent - t_glyphmetrics.gmptGlyphOrigin.y;
				t_font_state.black_box_x = t_glyphmetrics.gmBlackBoxX;
				t_font_state.black_box_y = t_glyphmetrics.gmBlackBoxY;
				t_font_state.glyph_origin_x = t_glyphmetrics.gmptGlyphOrigin.x;
				t_font_state.glyph_origin_y = t_glyphmetrics.gmptGlyphOrigin.y;
				t_font_state.cell_inc_x = t_glyphmetrics.gmCellIncX;
				t_font_state.cell_inc_y = t_glyphmetrics.gmCellIncY;
			}

			//ピクセル。
			{
				u8* t_dest_data = &a_dest_data.get()[a_offset];
				Memory::memset(t_dest_data,0x00,a_dest_width * a_dest_height * 4);

				s32 t_buffer_alignment = static_cast<u16>(t_font_state.black_box_x + 3) & 0xFFFC;

				s32 xx_max = t_font_state.black_box_x;
				s32 yy_max = t_font_state.black_box_y;
				if(t_buffer_size <= 0){
					xx_max = 0;
					yy_max = 0;
				}

				if(xx_max >= a_dest_width){
					xx_max = a_dest_width;
				}
				if(yy_max >= a_dest_height){
					yy_max = a_dest_height;
				}

				for(s32 xx=0;xx<xx_max;xx++){
					for(s32 yy=0;yy<yy_max;yy++){
						s32 t_dest_offset = xx * 4 + yy * 4 * a_dest_width;
						s32 t_buffer_offset = xx + yy * t_buffer_alignment;

						u8 t_alpha = t_buffer[t_buffer_offset];
						if(t_alpha > 0){
							s32 t_alpha_32 = static_cast<s32>(t_alpha) * 4;
							t_alpha = (t_alpha_32 <= 0xFF ? static_cast<u8>(t_alpha_32) : 0xFF);

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

