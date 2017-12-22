#pragma once

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �g�s�s�o�B
*/


/** include
*/
#include "../types/types.h"


/** NBsys::NHttp
*/
#if(BSYS_HTTP_ENABLE)
namespace NBsys{namespace NHttp
{
	/** Http_BinaryItem
	*/
	struct Http_BinaryItem
	{
		/** �T�C�Y�B
		*/
		s32 size;

		/** �f�[�^�B
		*/
		sharedptr<u8> data;
	};


}}
#endif

