#pragma once

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
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

#elif defined(PLATFORM_GNUCWIN)

	#define MALLOCA(SIZE)	::alloca(SIZE)

#else

	#define MALLOCA(SIZE)	::malloc(SIZE)
	#warning

#endif


#if defined(PLATFORM_VCWIN)

	#define FREEA(POINTER)	_freea(POINTER)

#elif defined(PLATFORM_GNUCWIN)

	#define FREEA(POINTER) 

#else

	#define FREEA(POINTER)	::free(POINTER)
	#warning

#endif

