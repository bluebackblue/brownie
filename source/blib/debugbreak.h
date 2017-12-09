#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief デバッグブレイク。
*/


/** include
*/
#include "./types.h"
#include "./platform.h"


#if defined(ROM_MASTER)

#else

	/** include
	*/
	#if defined(PLATFORM_VCWIN)
	
		#include <intrin.h>

	#endif

#endif


/** ブレイク。 
*/
#if defined(ROM_MASTER)

	#define DEBUGBREAK()

#else

	#if(BLIB_DEBUGBREAK_CALLBACK_ENABLE)

		extern void Blib_DebugBreak_Callback();
		#define DEBUGBREAK() Blib_DebugBreak_Callback();

	#else

		#if defined(PLATFORM_VCWIN)

			#define DEBUGBREAK() __debugbreak();

		#endif

	#endif

#endif

