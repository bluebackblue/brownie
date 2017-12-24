#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief デバッグアサート。
*/


/** include
*/
#include "./types.h"
#include "./platform.h"


/** NBlib
*/
namespace NBlib
{
	/** DebugAssert
	*/
	#if defined(ROM_MASTER)

	#else

		#if defined(PLATFORM_VCWIN)
			void DebugAssert(bool a_flag,const wchar* a_message,const wchar* a_filename,s32 a_line);
		#elif defined(PLATFORM_GNUCWIN)
			void DebugAssert(bool a_flag,const wchar* a_message,const char* a_filename,s32 a_line);
		#else
			#warning
		#endif

	#endif
}


/** アサート。
*/
#if defined(ROM_MASTER)

	#define ASSERT_MSG(X,MSG)

#else

	#if defined(PLATFORM_VCWIN)
		#define ASSERT_MSG(X,MSG)					NBlib::DebugAssert((X),MSG,__FILEW__,__LINE__)
	#elif defined(PLATFORM_GNUCWIN)
		#define ASSERT_MSG(X,MSG)					NBlib::DebugAssert((X),MSG,__FILE__,__LINE__)
	#else
		#warning
	#endif


	#if defined(ROM_DEEPDEBUG) || defined(ROM_FULLDEBUG)
		#define DEEPDEBUG_ASSERT_MSG(X,MSG)			ASSERT_MSG(X,MSG)
	#else
		#define DEEPDEBUG_ASSERT_MSG(X,MSG)
	#endif

#endif


/** アサート。
*/
#if defined(ROM_MASTER)

	#define ASSERT(X)
	#define DEEPDEBUG_ASSERT(X)

#else

	#define ASSERT(X)								ASSERT_MSG((X),L"")

	#if defined(ROM_DEEPDEBUG) || defined(ROM_FULLDEBUG)
		#define DEEPDEBUG_ASSERT(X)					ASSERT(X)
	#else
		#define DEEPDEBUG_ASSERT(X)
	#endif

#endif

