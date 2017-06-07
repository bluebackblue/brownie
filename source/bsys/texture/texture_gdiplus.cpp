

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
#include "./texture_gdiplus.h"
#include "./texture.h"


/** lib
*/
#if(BSYS_TEXTURE_GDIPLUS_ENABLE)
	#include <brownie_config/texture_gdiplus_lib.h>
#endif


/** include
*/
#if(BSYS_TEXTURE_GDIPLUS_ENABLE)
	#include <brownie_config/texture_gdiplus_include.h>
#endif


/** NBsys::NTexture
*/
namespace NBsys{namespace NTexture
{
	/** CreateTexture_GdiPlus
	*/
	#if(BSYS_TEXTURE_GDIPLUS_ENABLE)
	sharedptr< Texture > CreateTexture_GdiPlus(const sharedptr< u8 >& a_data,s32 a_size,const STLWString& a_name)
	{
		ULONG_PTR t_token;
		Gdiplus::GdiplusStartupInput t_gdiplus_startinput;
		Gdiplus::GdiplusStartup(&t_token,&t_gdiplus_startinput,nullptr);

		sharedptr< u8 > t_pixel;
		s32 t_width = 0;
		s32 t_height = 0;

		{
			HGLOBAL t_global_handle = ::GlobalAlloc(GMEM_MOVEABLE,a_size);
			if(t_global_handle){
				void* t_global_buffer = ::GlobalLock(t_global_handle);
				if(t_global_buffer){

					//グローバルメモリにコピー。
					::CopyMemory(t_global_buffer,a_data.get(),a_size);
 
					//ストリーム作成。
					IStream* t_stream = nullptr;
					if(CreateStreamOnHGlobal(t_global_handle,FALSE,&t_stream) == S_OK){

						sharedptr< Gdiplus::Bitmap > t_bitmap(Gdiplus::Bitmap::FromStream(t_stream));
						t_stream->Release();

						if(t_bitmap){
							if(t_bitmap->GetLastStatus() == Gdiplus::Ok){

								t_width = t_bitmap->GetWidth();
								t_height = t_bitmap->GetHeight();

								Gdiplus::Rect t_rect(0,0,t_width,t_height);

								Gdiplus::BitmapData t_bitmap_data;
								t_bitmap->LockBits(&t_rect,Gdiplus::ImageLockModeRead,PixelFormat32bppARGB,&t_bitmap_data);

								const uint8_t* t_bitmap_pixel_data = reinterpret_cast<const uint8_t*>(t_bitmap_data.Scan0);

								t_pixel.reset(new u8[t_width * t_height * 4],default_delete< u8[] >());

								for(s32 yy=0;yy<t_height;yy++){
									for(s32 xx=0;xx<t_width;xx++){
										const uint8_t* t_bitmap_pixel = t_bitmap_pixel_data + yy * t_bitmap_data.Stride + xx * 4;
										t_pixel.get()[(yy * t_width + xx) * 4 + 0] = t_bitmap_pixel[2];	//R
										t_pixel.get()[(yy * t_width + xx) * 4 + 1] = t_bitmap_pixel[1];	//G
										t_pixel.get()[(yy * t_width + xx) * 4 + 2] = t_bitmap_pixel[0];	//B
										t_pixel.get()[(yy * t_width + xx) * 4 + 3] = t_bitmap_pixel[3];	//A
									}
								}

								t_bitmap->UnlockBits(&t_bitmap_data);
							}
						}
					}
					::GlobalUnlock(t_global_handle);
				}
				::GlobalFree(t_global_handle);
			}
		}
		Gdiplus::GdiplusShutdown(t_token);

		sharedptr< Texture > t_texture(new Texture(t_pixel,t_width,t_height,t_width * 4,TextureType::R8G8B8A8,a_name));

		return t_texture;
	}
	#endif

}}

