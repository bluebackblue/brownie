#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief プラットフォーム。
*/


/** include
*/
#include "./version.h"


/** include
*/
#include <brownie_config/brownie_config.h>


/** プラットフォーム。
*/
#if defined(PLATFORM_VCWIN)

	//PLATFORM_VCWIN

#elif defined(PLATFORM_GNUCWIN)

	//PLATFORM_GNUCWIN

#elif defined(PLATFORM_UNKNOWN)

	//PLATFORM_UNKNOWN

#else

	#error

#endif


/** ビット。
*/
#if defined(ROM_32BIT)

	//ROM_32BIT

#elif defined(ROM_64BIT)

	//ROM_64BIT

#else

	#error

#endif


/** ロム。
*/
#if defined(ROM_MASTER)

	//ROM_MASTER

#elif defined(ROM_DEVELOP)

	//ROM_DEVELOP

#elif defined(ROM_DEEPDEBUG)

	//ROM_DEEPDEBUG

#elif defined(ROM_FULLDEBUG)

	//ROM_FULLDEBUG

#else

	#error

#endif

