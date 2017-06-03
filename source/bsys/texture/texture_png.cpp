

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
	//#include <brownie_config/texture_png_lib.h>
	#include <brownie_config/windows_include.h>
	#include <gdiplus.h>
#endif


/** include
*/
#if(BSYS_TEXTURE_PNG_ENABLE)
	//#include <brownie_config/texture_png_include.h>
	#pragma	comment(lib,"gdiplus.lib")
#endif


/** NBsys::NTexture
*/
namespace NBsys{namespace NTexture
{
	/** CreateTexture_FromPng
	*/
	sharedptr< Texture > CreateTexture_FromPng(const sharedptr< u8 >& a_data,s32 a_size,const STLWString& a_name)
	{
		Gdiplus::GdiplusStartupInput gpSI;
		ULONG_PTR lpToken;
		Gdiplus::GdiplusStartup(&lpToken, &gpSI, NULL);

		sharedptr< u8 > t_pixel;
		s32 t_width = 0;
		s32 t_height = 0;

		{
			// グローバルメモリを確保してロック
			HGLOBAL aGlobalHandle = GlobalAlloc(GMEM_MOVEABLE, a_size);
			if(aGlobalHandle)
			{
				void* aGlobalBuffer = GlobalLock(aGlobalHandle);
				if(aGlobalBuffer)
				{
					// グローバルメモリにコピー
					CopyMemory(aGlobalBuffer, a_data.get(), a_size);
 
					// ストリーム作成
					IStream* aIStream = NULL;
					if(CreateStreamOnHGlobal(aGlobalHandle, FALSE, &aIStream) == S_OK)
					{
						// GDI+ビットマップ生成(グローバルメモリは解放)
						Gdiplus::Bitmap* aBitmap = Gdiplus::Bitmap::FromStream(aIStream);
						aIStream->Release();
						if(aBitmap && aBitmap->GetLastStatus() == Gdiplus::Ok)
						{
							// バッファにコピー
							UINT aWidth = aBitmap->GetWidth();
							UINT aHeight = aBitmap->GetHeight();
							Gdiplus::Rect aRect(0, 0, aWidth, aHeight);
							Gdiplus::BitmapData aBitmapData;
							aBitmap->LockBits(&aRect, Gdiplus::ImageLockModeRead, PixelFormat32bppARGB, &aBitmapData);
							const uint8_t* aPixels = reinterpret_cast<const uint8_t*>(aBitmapData.Scan0);

							t_width = aWidth;
							t_height = aHeight;
							t_pixel.reset(new u8[aWidth * aHeight * 4],default_delete< u8[] >());
							//std::vector<uint32_t> aBuffer(aWidth * aHeight);
							for(UINT aY = 0; aY != aHeight; ++aY)
							{
								for(UINT aX = 0; aX != aWidth; ++aX)
								{
									const uint8_t* aPixel = aPixels + aY * aBitmapData.Stride + aX * 4;
									uint32_t aR = aPixel[2];
									uint32_t aG = aPixel[1];
									uint32_t aB = aPixel[0];
									uint32_t aA = aPixel[3];
									aR = aR * aA / 255;
									aG = aG * aA / 255;
									aB = aB * aA / 255;
									//aBuffer[aY * aWidth + aX] = (aA << 24) | (aB << 16) | (aG << 8) | aR;

									t_pixel.get()[(aY * aWidth + aX) * 4 + 0] = aR;
									t_pixel.get()[(aY * aWidth + aX) * 4 + 1] = aG;
									t_pixel.get()[(aY * aWidth + aX) * 4 + 2] = aB;
									t_pixel.get()[(aY * aWidth + aX) * 4 + 3] = aA;
								}
							}
							aBitmap->UnlockBits(&aBitmapData);
     
							// 解放
							delete aBitmap;
 
							// ～aBufferにピクセルデータが格納されている～
						}
					}
 
					// アンロック
					GlobalUnlock(aGlobalHandle);
				}
 
				// 解放
				GlobalFree(aGlobalHandle);
			}
		}

		Gdiplus::GdiplusShutdown(lpToken);

		sharedptr< Texture > t_texture(new Texture(t_pixel,t_width,t_height,t_width * 4,TextureType::R8G8B8A8,a_name));
		return t_texture;
	}

}}

