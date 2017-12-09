

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief デバッグログ。
*/


/** include
*/
#include <blib_pch.h>


/** include
*/
#include "./types.h"
#include "./platform.h"


/** include
*/
#include "./stringtool.h"


/** include
*/
#if defined(PLATFORM_VCWIN)
	#include <brownie_config/windows_include.h>
#endif


/** Blib_DebugLog_Callback
*/
#if(BLIB_DEBUGLOG_CALLBACK_ENABLE)

extern void Blib_DebugLog_Callback(const char* a_tag,const char* a_string);

#endif


/** NBlib
*/
namespace NBlib
{
	/** DebugLog
	*/
	#if defined(ROM_MASTER)

	#else

		void DebugLog(const char* a_tag,const char* a_string)
		{
			#if(BLIB_DEBUGLOG_CALLBACK_ENABLE)
			{
				Blib_DebugLog_Callback(a_tag,a_string);
			}
			#else
			{
				#if defined(PLATFORM_VCWIN)
				{
					if(a_tag != nullptr){
						::OutputDebugStringA("[");
						::OutputDebugStringA(a_tag);
						::OutputDebugStringA("]");
						::OutputDebugStringA(a_string);
						::OutputDebugStringA("\n");
					}else{
						::OutputDebugStringA(a_string);
					}
				}
				#endif
			}
			#endif
		}

	#endif

	/** DebugLog
	*/
	#if defined(ROM_MASTER)

	#else

		void DebugLog(const char* a_tag,const wchar* a_wstring)
		{
			#if defined(PLATFORM_VCWIN)
			{
				STLString t_string;
				WcharToSjis(STLWString(a_wstring),t_string);
				DebugLog(a_tag,t_string.c_str());
			}
			#endif
		}

	#endif
}

