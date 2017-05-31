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
#include "./texture_decl.h"


/** NBsys::NTexture
*/
namespace NBsys{namespace NTexture
{
	/** CreateTexture_FromTga
	*/
	sharedptr< Texture > CreateTexture_FromTga(const sharedptr< u8 >& a_data,const STLString& a_name);

}}

