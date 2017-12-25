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
	#define DEEPDEBUG_ASSERT_MSG(ENABLE,X,MSG)
	#define FULLDEBUG_ASSERT_MSG(ENABLE,X,MSG)

#else

	/** !ROM_MASTER
	*/
	#if defined(PLATFORM_VCWIN)
		#define ASSERT_MSG(X,MSG)								NBlib::DebugAssert((X),MSG,__FILEW__,__LINE__)
	#elif defined(PLATFORM_GNUCWIN)
		#define ASSERT_MSG(X,MSG)								NBlib::DebugAssert((X),MSG,__FILE__,__LINE__)
	#else
		#warning
	#endif

	/** ROM_DEEPDEBUG or ROM_FULLDEBUG
	*/
	#if defined(ROM_DEEPDEBUG) || defined(ROM_FULLDEBUG)
		#define DEEPDEBUG_ASSERT_MSG(ENABLE,X,MSG)				do{if(ENABLE){ASSERT_MSG(X,MSG);}}while(0)
	#else
		#define DEEPDEBUG_ASSERT_MSG(ENABLE,X,MSG)
	#endif

	/** ROM_FULLDEBUG
	*/
	#if defined(ROM_FULLDEBUG)
		#define FULLDEBUG_ASSERT_MSG(ENABLE,X,MSG)				do{if(ENABLE){ASSERT_MSG(X,MSG);}}while(0)
	#else
		#define FULLDEBUG_ASSERT_MSG(ENABLE,X,MSG)
	#endif

#endif


/** アサート。
*/
#if defined(ROM_MASTER)

	#define ASSERT(X)
	#define DEEPDEBUG_ASSERT(ENABLE,X)
	#define FULLDEBUG_ASSERT(ENABLE,X)

#else

	/** !ROM_MASTER
	*/
	#define ASSERT(X)											ASSERT_MSG((X),L"")

	/** ROM_DEEPDEBUG or ROM_FULLDEBUG
	*/
	#if defined(ROM_DEEPDEBUG) || defined(ROM_FULLDEBUG)
		#define DEEPDEBUG_ASSERT(ENABLE,X)						do{if(ENABLE){ASSERT(X);}}while(0)
	#else
		#define DEEPDEBUG_ASSERT(ENABLE,X)
	#endif

	/** ROM_FULLDEBUG
	*/
	#if defined(ROM_FULLDEBUG)
		#define FULLDEBUG_ASSERT(ENABLE,X)						do{if(ENABLE){ASSERT(X);}}while(0)
	#else
		#define FULLDEBUG_ASSERT(ENABLE,X)
	#endif

#endif

