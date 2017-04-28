#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ウィンドウズ。
*/


/** include
*/
#include "./types.h"
#include "./platform.h"


/** include
*/
#if defined(PLATFORM_VCWIN)

	#define _WINSOCKAPI_

	#include <windows.h>

#endif

