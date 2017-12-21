#pragma once

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ＨＴＴＰ。
*/


/** include
*/
#include "../types/types.h"


/** NBsys::NHttp
*/
#if(BSYS_HTTP_ENABLE)
namespace NBsys{namespace NHttp
{
	/** Http_Mode
	*/
	struct Http_Mode
	{
		enum Id
		{
			//ポスト。
			Post,

			//ゲット。
			Get,
		};
	};


}}
#endif

