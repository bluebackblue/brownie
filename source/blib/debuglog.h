#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief デバッグログ。
*/


/** include
*/
#include "./types.h"
#include "./platform.h"


/** include
*/
#include "./vastring.h"


/** NBlib
*/
namespace NBlib
{
	/** DebugLog
	*/
	#if defined(ROM_MASTER)

	#else

		void DebugLog(const char* a_tag,const char* a_string);
		void DebugLog(const char* a_tag,const wchar* a_wstring);

	#endif
}

/** ログ。
*/
#if defined(ROM_MASTER)

	#define TAGLOG(TAG,...)	
	#define DEBUGLOG(...)

#else

	#define TAGLOG(TAG,...)				NBlib::DebugLog(TAG,VASTRING_DEBUG(__VA_ARGS__))
	#define DEBUGLOG(...)				NBlib::DebugLog(nullptr,VASTRING_DEBUG(__VA_ARGS__))

#endif

