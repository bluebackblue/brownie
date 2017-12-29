﻿#pragma once

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ＨＴＴＰ。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** NBsys::NHttp
*/
#if(BSYS_HTTP_ENABLE)
namespace NBsys{namespace NHttp
{
	/** Http_BinaryItem
	*/
	struct Http_BinaryItem
	{
		/** サイズ。
		*/
		s32 size;

		/** padding
		*/
		padding64(0,4);

		/** データ。
		*/
		sharedptr<u8> data;
	};


}}
#endif

