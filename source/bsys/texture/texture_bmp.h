#pragma once

/**
* Copyright (c) 2017 blueback
* Released under the MIT License
* https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
* http://bbbproject.sakura.ne.jp/wordpress/mitlicense
* @brief テクスチャー。
*/


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./texture_decl.h"


/** NBsys::NTexture
*/
#if(BSYS_TEXTURE_ENABLE)
namespace NBsys{namespace NTexture
{
	/** CreateTexture_Bmp
	*/
	sharedptr<Texture> CreateTexture_Bmp(const sharedptr<u8>& a_data,s32 a_size,const STLWString& a_name);


}}
#endif

