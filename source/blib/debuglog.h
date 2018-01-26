#pragma once

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
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
	#if defined(ROM_MASTER)

	#else

		/** DebugLog
		*/
		void DebugLog(const wchar* a_tag,const char* a_string);
		void DebugLog(const wchar* a_tag,const wchar* a_wstring);

	#endif
}

/** ログ。
*/
#if defined(ROM_MASTER)

	#define TAGLOG(TAG,...)	
	#define DEBUGLOG(...)

	#define DEEPDEBUG_TAGLOG(ENABLE,TAG,...)	
	#define DEEPDEBUG_DEBUGLOG(ENABLE,...)

	#define FULLDEBUG_TAGLOG(ENABLE,TAG,...)	
	#define FULLDEBUG_DEBUGLOG(ENABLE,...)

#else

	/** !ROM_MASTER
	*/
	#define TAGLOG(TAG,...)										NBlib::DebugLog(TAG,VASTRING_DEBUG(__VA_ARGS__))
	#define DEBUGLOG(...)										NBlib::DebugLog(nullptr,VASTRING_DEBUG(__VA_ARGS__))

	/** ROM_DEEPDEBUG or ROM_FULLDEBUG
	*/
	#if defined(ROM_DEEPDEBUG) || defined(ROM_FULLDEBUG)

		#define DEEPDEBUG_TAGLOG(ENABLE,TAG,...)				do{if(ENABLE){TAGLOG(TAG,__VA_ARGS__);}}while(0)
		#define DEEPDEBUG_DEBUGLOG(ENABLE,...)					do{if(ENABLE){DEBUGLOG(__VA_ARGS__);}}while(0)

	#else

		#define DEEPDEBUG_TAGLOG(ENABLE,TAG,...)
		#define DEEPDEBUG_DEBUGLOG(ENABLE,...)

	#endif

	/** ROM_FULLDEBUG
	*/
	#if defined(ROM_FULLDEBUG)

		#define FULLDEBUG_TAGLOG(ENABLE,TAG,...)				do{if(ENABLE){TAGLOG(TAG,__VA_ARGS__);}}while(0)
		#define FULLDEBUG_DEBUGLOG(ENABLE,...)					do{if(ENABLE){DEBUGLOG(__VA_ARGS__);}}while(0)

	#else

		#define FULLDEBUG_TAGLOG(ENABLE,TAG,...)
		#define FULLDEBUG_DEBUGLOG(ENABLE,...)

	#endif

#endif

