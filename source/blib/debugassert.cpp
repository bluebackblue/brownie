

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief デバッグアサート。
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
#include "./debugbreak.h"
#include "./debuglog.h"
#include "./stringtool.h"


/** Blib_DebugAssert_Callback

	コールバックからの戻り値が「false」の場合処理を中断します。

*/
#if(BLIB_DEBUGASSERT_CALLBACK_ENABLE)

extern bool Blib_DebugAssert_Callback(const NBlib::wchar* a_wmessage,const NBlib::wchar* a_wfilename,NBlib::s32 a_line);

#endif


/** NBlib
*/
namespace NBlib
{
	/** DebugAssert
	*/
	#if defined(ROM_MASTER)
	#else

	#if defined(PLATFORM_VCWIN)
	void DebugAssert(bool a_flag,const wchar* a_wmessage,const wchar* a_wfilename,s32 a_line)
	#else
	void DebugAssert(bool a_flag,const wchar* a_wmessage,const char* a_filename,s32 a_line)
	#endif
	{
		if(a_flag == true){
			//停止しない。
		}else{
			//デバッグ出力。

			const wchar* t_wmessage = a_wmessage;
			if(t_wmessage == nullptr){
				t_wmessage = L"";
			}

			#if defined(PLATFORM_VCWIN)

			const wchar* t_wfilename = a_wfilename;

			#else

			const char* t_filename = a_filename;
			STLWString t_wstring;
			CharToWchar(t_filename,t_wstring);
			t_wfilename = t_wstring.c_str();
			
			#endif

			#if(BLIB_DEBUGASSERT_CALLBACK_ENABLE)
			{
				//コールバックからの戻り値が「false」の場合処理を中断します。
				if(Blib_DebugAssert_Callback(a_wmessage,t_wfilename,a_line) == false){
					return;
				}
			}
			#endif

			#if defined(PLATFORM_VCWIN)
			{
				DEBUGLOG(L"%s(%d): [ASSERT]%s\n",t_wfilename,a_line,t_wmessage);	
				DEBUGBREAK();
			}
			#endif

		}
	}
	#endif
}

