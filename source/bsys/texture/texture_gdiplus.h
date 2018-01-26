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
#include "./texture_decl.h"


/** NBsys::NTexture
*/
#if(BSYS_TEXTURE_ENABLE)
namespace NBsys{namespace NTexture
{
	/** CreateTexture_GdiPlus
	*/
	#if(BSYS_TEXTURE_GDIPLUS_ENABLE)
	sharedptr<Texture> CreateTexture_GdiPlus(const sharedptr<u8>& a_data,s32 a_size,const STLWString& a_name);
	#endif


	/** EncodeToJpg_GdiPlus
	*/
	#if(BSYS_TEXTURE_GDIPLUS_ENABLE)
	std::tuple<sharedptr<u8>,s32> EncodeToJpg_GdiPlus(const sharedptr<Texture>& a_texture);
	#endif


}}
#endif

