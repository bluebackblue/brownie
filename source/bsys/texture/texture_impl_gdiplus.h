#pragma once

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief テクスチャー。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** include
*/
#if(BSYS_TEXTURE_GDIPLUS_ENABLE)
	#include <brownie_config/texture_gdiplus_include.h>
#endif


/** NBsys::NTexture
*/
#if((BSYS_TEXTURE_ENABLE)&&(BSYS_TEXTURE_GDIPLUS_ENABLE))
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
			token(0)
		{
			Gdiplus::Status t_status = Gdiplus::GdiplusStartup(&this->token,&this->startinput,nullptr);
			if(t_status != Gdiplus::Ok){
				this->token = 0;
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
			if(this->token != 0){
				return true;
			}
			return false;
		}
		
	};


}}
#endif

