

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
	sharedptr<Texture> CreateTexture_GdiPlus(const sharedptr<u8>& a_data,s32 a_size,const STLWString& a_name)
	{
		ULONG_PTR t_token;
		Gdiplus::GdiplusStartupInput t_gdiplus_startinput;
		Gdiplus::GdiplusStartup(&t_token,&t_gdiplus_startinput,nullptr);

		sharedptr<u8> t_pixel;
		s32 t_width = 0;
		s32 t_height = 0;

		{
			HGLOBAL t_global_handle = ::GlobalAlloc(GMEM_MOVEABLE,a_size);
			if(t_global_handle){
				void* t_global_buffer = ::GlobalLock(t_global_handle);
				if(t_global_buffer){

					//グローバルメモリにデータをコピー。
					::CopyMemory(t_global_buffer,a_data.get(),a_size);

					::GlobalUnlock(t_global_handle);
					t_global_buffer = nullptr;
 
					//グローバルメモリ読み込み用のストリーム作成。
					IStream* t_stream = nullptr;
					if(::CreateStreamOnHGlobal(t_global_handle,FALSE,&t_stream) == S_OK){

						//ストリームを使用してでコード読み込み。
						sharedptr<Gdiplus::Bitmap> t_bitmap(Gdiplus::Bitmap::FromStream(t_stream));

						//読み込み後はストリーム破棄。
						t_stream->Release();
						t_stream = nullptr;

						if(t_bitmap){
							if(t_bitmap->GetLastStatus() == Gdiplus::Ok){

								t_width = t_bitmap->GetWidth();
								t_height = t_bitmap->GetHeight();

								Gdiplus::Rect t_rect(0,0,t_width,t_height);

								Gdiplus::BitmapData t_bitmap_data;
								t_bitmap->LockBits(&t_rect,Gdiplus::ImageLockModeRead,PixelFormat32bppARGB,&t_bitmap_data);

								const uint8_t* t_bitmap_pixel_data = reinterpret_cast<const uint8_t*>(t_bitmap_data.Scan0);

								t_pixel.reset(new u8[t_width * t_height * 4],default_delete<u8[]>());

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
				}
				::GlobalFree(t_global_handle);
			}
		}
		Gdiplus::GdiplusShutdown(t_token);

		sharedptr<Texture> t_texture(new Texture(t_pixel,t_width,t_height,t_width * 4,TextureType::R8G8B8A8,a_name));

		return t_texture;
	}
	#endif


	/** EncodeToJpg_GdiPlus
	*/
	#if(BSYS_TEXTURE_GDIPLUS_ENABLE)
	std::tuple<sharedptr<u8>,s32> EncodeToJpg_GdiPlus(const sharedptr<Texture>& a_texture)
	{
		sharedptr<u8> t_jpg_data;
		s32 t_jpg_size = 0;

		ULONG_PTR t_token;
		Gdiplus::GdiplusStartupInput t_gdiplus_startinput;
		Gdiplus::GdiplusStartup(&t_token,&t_gdiplus_startinput,nullptr);

		{
			Gdiplus::Bitmap t_bitmap(a_texture->GetWidth(),a_texture->GetHeight());

			//TODO:遅い。
			for(s32 yy=0;yy<a_texture->GetHeight();yy++){
				for(s32 xx=0;xx<a_texture->GetWidth();xx++){
					const u8* t_pix = &(a_texture->GetPixel().get()[xx * 4 + yy * a_texture->GetPitch()]);
					t_bitmap.SetPixel(xx,yy,Gdiplus::Color(t_pix[3],t_pix[0],t_pix[1],t_pix[2]));
				}
			}

			{
				//全エンコーダーの総数と必要バイトサイズ取得。
				UINT t_encoder_count = 0;
				UINT t_encoder_buffersize = 0;
				Gdiplus::GetImageEncodersSize(&t_encoder_count,&t_encoder_buffersize);
				if((t_encoder_count > 0)&&(t_encoder_buffersize > 0)){
					sharedptr<u8> t_imagecodecinfo_buffer(new u8[t_encoder_buffersize],default_delete<u8[]>());
					sharedptr<Gdiplus::ImageCodecInfo> t_imagecodecinfo(reinterpret_cast<Gdiplus::ImageCodecInfo*>(t_imagecodecinfo_buffer.get()),null_delete());

					//全エンコーダー取得。
					Gdiplus::GetImageEncoders(t_encoder_count,t_encoder_buffersize,t_imagecodecinfo.get());

					s32 t_index = -1;
					for(s32 ii=0;ii<static_cast<s32>(t_encoder_count);ii++){
						if(Memory::wcscmp(t_imagecodecinfo.get()[ii].MimeType,L"image/jpeg") == 0){
							t_index = ii;
							break;
						}
					}

					if(t_index >= 0){

						HGLOBAL t_global_handle = ::GlobalAlloc(GMEM_MOVEABLE,a_texture->GetPitch() * a_texture->GetHeight());
						if(t_global_handle){
							{
								//グローバルメモリ書き込み用のストリーム作成。
								IStream* t_stream = nullptr;
								if(::CreateStreamOnHGlobal(t_global_handle,FALSE,&t_stream) == S_OK){

									//シークを最初に設定。
									LARGE_INTEGER t_pos = {0};
									t_stream->Seek(t_pos,STREAM_SEEK_SET,nullptr);

									//サイズを0に設定。
									ULARGE_INTEGER t_size = {0};
									t_stream->SetSize(t_size);

									//ストリームを使用してエンコード書き込み。
									CLSID t_clsid = t_imagecodecinfo.get()[t_index].Clsid;
									t_bitmap.Save(t_stream,&t_clsid);

									//情報取得。
									STATSTG t_statstg = {0};
									t_stream->Stat(&t_statstg,STATFLAG_DEFAULT);

									s32 t_write_size = static_cast<s32>(t_statstg.cbSize.QuadPart);
									
									void* t_global_buffer = ::GlobalLock(t_global_handle);
									if(t_global_buffer){

										t_jpg_data.reset(new u8[t_write_size]);
										Memory::Copy(t_jpg_data.get(),t_write_size,t_global_buffer,t_write_size);
										t_jpg_size = t_write_size;

										::GlobalUnlock(t_global_handle);
										t_global_buffer = nullptr;

									}
									t_stream->Release();
								}
								
							}
							::GlobalFree(t_global_handle);
						}
					}
				}
			}
		}
		Gdiplus::GdiplusShutdown(t_token);

		return std::tuple<sharedptr<u8>,s32>(t_jpg_data,t_jpg_size);
	}
	#endif


}}

