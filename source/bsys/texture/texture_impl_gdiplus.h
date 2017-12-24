#pragma once
#pragma once

/**
* Copyright (c) 2017 blueback
* Released under the MIT License
* https://github.com/bluebackblue/brownie/blob/master/LICENSE
* http://bbbproject.sakura.ne.jp/wordpress/mitlicense
* @brief テクスチャー。
*/


/** include
*/
#include "../types/types.h"


/** include
*/
#if(BSYS_TEXTURE_GDIPLUS_ENABLE)
	#include <brownie_config/texture_gdiplus_include.h>
#endif


/** NBsys::NTexture
*/
#if(BSYS_TEXTURE_GDIPLUS_ENABLE)
namespace NBsys{namespace NTexture
{
	/** Texture_Impl_GdiPlus
	*/
	class Texture_Impl_GdiPlus
	{
	private:

		/** token
		*/
		ULONG_PTR token;

		/** startinput
		*/
		Gdiplus::GdiplusStartupInput startinput;

	public:

		/** constructor
		*/
		Texture_Impl_GdiPlus()
			:
			token(WIN_NULL),
			startinput()
		{
			Gdiplus::Status t_status = Gdiplus::GdiplusStartup(&this->token,&this->startinput,nullptr);
			if(t_status != Gdiplus::Ok){
				this->token = WIN_NULL;
			}
		}

		/** destructor
		*/
		~Texture_Impl_GdiPlus()
		{
			if(this->token){
				Gdiplus::GdiplusShutdown(this->token);
			}
		}

		/** IsEnable
		*/
		bool IsEnable()
		{
			if(this->token != WIN_NULL){
				return true;
			}
			return false;
		}
		
	};


}}
#endif

