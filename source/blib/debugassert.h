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

		void DebugAssert(bool a_flag,const char* a_message,const char* a_filename,s32 a_line);

	#endif
}

/** アサート。
*/
#if defined(ROM_MASTER)

	#define ASSERT(X)

#else

	#define ASSERT(X)				NBlib::DebugAssert((X),"",__FILE__,__LINE__)

#endif

/** アサート。
*/
#if defined(ROM_MASTER)

	#define ASSERT_MSG(X,MSG)

#else

	#define ASSERT_MSG(X,MSG)		NBlib::DebugAssert((X),MSG,__FILE__,__LINE__)

#endif

