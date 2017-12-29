

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
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
#include "./debuglog.h"


/** include
*/
#if defined(PLATFORM_VCWIN)
	#include <brownie_config/windows_include.h>
#endif


/** Blib_DebugLog_Callback

	コールバックからの戻り値が「false」の場合処理を中断します。

*/
#if(BLIB_DEBUGLOG_CALLBACK_ENABLE)

bool Blib_DebugLog_Callback(const NBlib::wchar* a_tag,const NBlib::wchar* a_wstring);

#endif


/** NBlib
*/
namespace NBlib
{
	#if defined(ROM_MASTER)

	#else

		/** DebugLog
		*/
		void DebugLog(const wchar* a_tag,const char* a_string)
		{
			#if defined(PLATFORM_VCWIN)
			{
				STLWString t_wstring;
				CharToWchar(a_string,t_wstring);
				DebugLog(a_tag,t_wstring.c_str());
			}
			#endif
		}

	#endif

	#if defined(ROM_MASTER)

	#else

		/** DebugLog
		*/
		void DebugLog(const wchar* a_tag,const wchar* a_wstring)
		{
			#if(BLIB_DEBUGLOG_CALLBACK_ENABLE)
			{
				//コールバックからの戻り値が「false」の場合処理を中断します。
				if(Blib_DebugLog_Callback(a_tag,a_wstring) == false){
					return;
				}
			}
			#endif

			#if defined(PLATFORM_VCWIN)
			{
				if(a_tag != nullptr){
					::OutputDebugStringW(L"[");
					::OutputDebugStringW(a_tag);
					::OutputDebugStringW(L"]");
					::OutputDebugStringW(a_wstring);
					::OutputDebugStringW(L"\n");
				}else{
					::OutputDebugStringW(a_wstring);
				}
			}
			#elif defined(PLATFORM_GNUCWIN)
			{
				if(a_tag != nullptr){
					::printf("[%ls]%ls\n",a_tag,a_wstring);
				}else{
					::printf("%ls",a_wstring);
				}
			}
			#else
			{
				#warning
			}
			#endif
		}

	#endif
}

