#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief スタックトレース。
*/


/** include
*/
#include "./types.h"
#include "./platform.h"


/** include
*/
#include "./stlstring.h"

/** NBlib
*/
namespace NBlib
{
	/** DebugLog
	*/
	#if defined(ROM_MASTER)

	#else

		#if(BLIB_STACKTRACE_ENABLE)

			void StackTrace(STLString& a_out_string,s32 a_index = 1);

		#endif

	#endif
}

/** スタックトレース。
*/
#if defined(ROM_MASTER)

	#define STACKTRACE	

#else

	#if(BLIB_STACKTRACE_ENABLE)

		#define STACKTRACE NBlib::StackTrace

	#else

		#define STACKTRACE

	#endif

#endif

