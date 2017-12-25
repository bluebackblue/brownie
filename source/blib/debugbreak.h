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
	
		//[include]
		#include <intrin.h>

	#endif

#endif


/** ブレイク。 

	コールバックからの戻り値が「false」の場合処理を中断します。

*/
#if defined(ROM_MASTER)

	#define DEBUGBREAK()
	#define FULLDEBUG_DEBUGBREAK(ENABLE)
	#define DEEPDEBUG_DEBUGBREAK(ENABLE)

#else

	#if defined(PLATFORM_VCWIN)

		#define DEBUGBREAK_PROC() __debugbreak()

	#elif defined(PLATFORM_GNUCWIN)

		#define DEBUGBREAK_PROC() __asm__("int3")

	#else

		#define DEBUGBREAK_PROC()
		#warning

	#endif

	/** !ROM_MASTER
	*/
	#if(BLIB_DEBUGBREAK_CALLBACK_ENABLE)

		bool Blib_DebugBreak_Callback();
		#define DEBUGBREAK() do{if(Blib_DebugBreak_Callback()){DEBUGBREAK_PROC();}}while(0)

	#else

		#define DEBUGBREAK() DEBUGBREAK_PROC()

	#endif

	/** ROM_DEEPDEBUG or ROM_FULLDEBUG
	*/
	#if defined(ROM_DEEPDEBUG) || defined(ROM_FULLDEBUG)
		#define DEEPDEBUG_DEBUGBREAK(ENABLE)					do{if(ENABLE){DEBUGBREAK();}}while(0)
	#else
		#define DEEPDEBUG_DEBUGBREAK(ENABLE)
	#endif

	/** ROM_FULLDEBUG
	*/
	#if defined(ROM_FULLDEBUG)
		#define FULLDEBUG_DEBUGBREAK(ENABLE)					do{if(ENABLE){DEBUGBREAK();}}while(0)
	#else
		#define FULLDEBUG_DEBUGBREAK(ENABLE)
	#endif

#endif

