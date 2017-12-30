

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


/** include
*/
#include "./texture_impl_gdiplus.h"
#include "./texture_impl_globalmemory.h"


/** warning

4710 : この関数はインライン展開のために選択されましたが、コンパイラはインライン展開を実行しませんでした。

*/
#pragma warning(disable:4710)


/** NBsys::NTexture
*/
#if(BSYS_TEXTURE_ENABLE)
namespace NBsys{namespace NTexture
{
	/** CreateTexture_GdiPlus
	*/
	#if(BSYS_TEXTURE_GDIPLUS_ENABLE)
	sharedptr<Texture> CreateTexture_GdiPlus(const sharedptr<u8>& a_data,s32 a_size,const STLWString& a_name)
	{
		//サイズチェック。
		if(a_size <= 0){
			return nullptr;
		}

		//GdiPlus開始。
		sharedptr<Texture_Impl_GdiPlus> t_gdiplus(new Texture_Impl_GdiPlus());
		if(t_gdiplus->IsEnable() == false){
			return nullptr;
		}

		//グローバルメモリ。
		sharedptr<Texture_Impl_GlobalMemory> t_globalmemory(new Texture_Impl_GlobalMemory(a_size));
		if(t_globalmemory->IsEnable() == false){
			return nullptr;
		}

		//ストリーム。
		sharedptr<Texture_Impl_GlobalMemory_Stream> t_stream(new Texture_Impl_GlobalMemory_Stream(t_globalmemory));
		if(t_stream->IsEnable() == false){
			return nullptr;
		}

		//グローバルメモリにデータをコピー。
		void* t_global_buffer = t_globalmemory->Map();
		if(t_global_buffer){
			Memory::Copy(t_global_buffer,a_size,a_data.get(),a_size);
			t_globalmemory->Unmap();
		}

		//[busy]ストリームを使用してでコード読み込み。グローバルメモリとビットマップをバインド。
		sharedptr<Gdiplus::Bitmap> t_bitmap;
		#if(PLATFORM_VCWIN)
		t_bitmap.reset(Gdiplus::Bitmap::FromStream(t_stream->GetHandle()),default_delete<Gdiplus::Bitmap>());
		#endif
		t_stream.reset();

		sharedptr<Texture> t_to_texture;

		if(t_bitmap->GetLastStatus() == Gdiplus::Ok){
			s32 t_tex_width = static_cast<s32>(t_bitmap->GetWidth());
			s32 t_tex_height = static_cast<s32>(t_bitmap->GetHeight());
			s32 t_tex_pitch = NTexture::CalcJustWidth(t_tex_width) * 4;

			Gdiplus::BitmapData t_bitmap_data;
			Gdiplus::Rect t_rect(0,0,t_tex_width,t_tex_height);
			Gdiplus::Status t_status = t_bitmap->LockBits(&t_rect,Gdiplus::ImageLockModeRead,PixelFormat32bppARGB,&t_bitmap_data);
			if(t_status == Gdiplus::Status::Ok){

				sharedptr<u8> t_to_pixel(new u8[static_cast<size_t>(t_tex_height * t_tex_pitch)],default_delete<u8[]>());
			
				for(s32 yy=0;yy<t_tex_height;yy++){
					const u8* t_from = reinterpret_cast<const u8*>(t_bitmap_data.Scan0) + yy * t_bitmap_data.Stride;
					u8* t_to = t_to_pixel.get() + yy * t_tex_pitch ;

					for(s32 xx=0;xx<t_tex_width;xx++){

						t_to[0] = t_from[2];	//R
						t_to[1] = t_from[1];	//G
						t_to[2] = t_from[0];	//B
						t_to[3] = t_from[3];	//A

						t_from += 4;
						t_to += 4; 
					}
				}

				t_bitmap->UnlockBits(&t_bitmap_data);

				t_to_texture.reset(new Texture(t_to_pixel,t_tex_width,t_tex_height,t_tex_pitch,TextureType::R8G8B8A8,a_name));
			}
		}

		t_bitmap.reset();
		t_globalmemory.reset();

		t_gdiplus.reset();

		return t_to_texture;
	}
	#endif


	/** EncodeToJpg_GdiPlus
	*/
	#if(BSYS_TEXTURE_GDIPLUS_ENABLE)
	std::tuple<sharedptr<u8>,s32> EncodeToJpg_GdiPlus(const sharedptr<Texture>& a_texture)
	{
		//GdiPlus開始。
		sharedptr<Texture_Impl_GdiPlus> t_gdiplus(new Texture_Impl_GdiPlus());
		if(t_gdiplus->IsEnable() == false){
			return std::tuple<sharedptr<u8>,s32>(nullptr,0);
		}

		//エンコーダー選択。
		CLSID t_clsid;
		{
			s32 t_index = -1;

			sharedptr<u8> t_imagecodecinfo_buffer;
			sharedptr<Gdiplus::ImageCodecInfo> t_imagecodecinfo;

			//全エンコーダーの数と必要バイトサイズ取得。
			UINT t_encoder_count = 0;
			UINT t_encoder_buffersize = 0;
			Gdiplus::GetImageEncodersSize(&t_encoder_count,&t_encoder_buffersize);
			if((t_encoder_count > 0)&&(t_encoder_buffersize > 0)){
				t_imagecodecinfo_buffer.reset(new u8[t_encoder_buffersize],default_delete<u8[]>());
				t_imagecodecinfo.reset(reinterpret_cast<Gdiplus::ImageCodecInfo*>(t_imagecodecinfo_buffer.get()),null_delete());

				//全エンコーダー取得。
				Gdiplus::GetImageEncoders(t_encoder_count,t_encoder_buffersize,t_imagecodecinfo.get());
				
				for(s32 ii=0;ii<static_cast<s32>(t_encoder_count);ii++){
					if(Memory::StringCompareW(L"image/jpeg",t_imagecodecinfo.get()[ii].MimeType) == 0){
						t_index = ii;
						break;
					}
				}
			}

			if(t_index >= 0){
				t_clsid = t_imagecodecinfo.get()[t_index].Clsid;
			}else{
				return std::tuple<sharedptr<u8>,s32>(nullptr,0);
			}
		}

		//グローバルメモリ。
		sharedptr<Texture_Impl_GlobalMemory> t_globalmemory(new Texture_Impl_GlobalMemory(a_texture->GetPitch() * a_texture->GetHeight()));
		if(t_globalmemory->IsEnable() == false){
			return std::tuple<sharedptr<u8>,s32>(nullptr,0);
		}

		//ストリーム。
		sharedptr<Texture_Impl_GlobalMemory_Stream> t_stream(new Texture_Impl_GlobalMemory_Stream(t_globalmemory));
		if(t_stream->IsEnable() == false){
			return std::tuple<sharedptr<u8>,s32>(nullptr,0);
		}

		sharedptr<u8> t_jpg_data;
		s32 t_jpg_size = 0;
		{
			//シークを最初に設定。
			t_stream->SetSeekStart();

			//サイズをゼロに設定。
			t_stream->SetSizeZero();

			s32 t_width = a_texture->GetWidth();
			s32 t_height = a_texture->GetHeight();
			Gdiplus::Bitmap t_bitmap(t_width,t_height);

			{
				Gdiplus::Rect t_rect(0,0,t_width,t_height);
				Gdiplus::BitmapData t_bitmap_data;
				Gdiplus::Status t_status = t_bitmap.LockBits(&t_rect,Gdiplus::ImageLockModeRead,PixelFormat32bppARGB,&t_bitmap_data);
				if(t_status == Gdiplus::Status::Ok){

					for(s32 yy=0;yy<t_height;yy++){
						u8* t_to = reinterpret_cast<u8*>(t_bitmap_data.Scan0) + yy * t_bitmap_data.Stride;
						const u8* t_from = a_texture->GetPixel().get() + yy * a_texture->GetPitch();
						for(s32 xx=0;xx<t_width;xx++){
							t_to[2] = t_from[0];	//R
							t_to[1] = t_from[1];	//G
							t_to[0] = t_from[2];	//B
							t_to[3] = t_from[3];	//A

							t_from += 4;
							t_to += 4; 
						}
					}

					t_bitmap.UnlockBits(&t_bitmap_data);
				}
			}

			//ステース更新。
			#if(PLATFORM_VCWIN)
			t_bitmap.Save(t_stream->GetHandle(),&t_clsid);
			#endif
			t_stream->UpdateStatus();

			s32 t_write_size = t_stream->GetStatus_Size();
									
			void* t_global_buffer = t_globalmemory->Map();
			if(t_global_buffer){

				t_jpg_data.reset(new u8[static_cast<u32>(t_write_size)]);
				Memory::Copy(t_jpg_data.get(),t_write_size,t_global_buffer,t_write_size);
				t_jpg_size = t_write_size;

				t_globalmemory->Unmap();
			}
		}

		t_gdiplus.reset();

		return std::tuple<sharedptr<u8>,s32>(t_jpg_data,t_jpg_size);
	}
	#endif


}}
#endif

