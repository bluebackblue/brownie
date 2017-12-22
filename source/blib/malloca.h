#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief スタックからの領域確保。
*/


/** include
*/
#include "./types.h"
#include "./platform.h"


/*

	スタック領域からメモリーを割り当てます。

*/


#if defined(PLATFORM_VCWIN)

	#define MALLOCA(SIZE)	_malloca(SIZE)

#else

	#define MALLOCA(SIZE)	::malloc(SIZE)

	#warning

#endif


#if defined(PLATFORM_VCWIN)

	#define FREEA(POINTER)	_freea(POINTER)

#else

	#define FREEA(POINTER)	::free(POINTER)

	#warning

#endif

