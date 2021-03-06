﻿

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
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


/** warning

4710 : この関数はインライン展開のために選択されましたが、コンパイラはインライン展開を実行しませんでした。

*/
#pragma warning(disable:4710)


/** Blib_DebugAssert_Callback

	コールバックからの戻り値が「false」の場合処理を中断します。

*/
#if(BLIB_DEBUGASSERT_CALLBACK_ENABLE)

bool Blib_DebugAssert_Callback(const NBlib::wchar* a_wmessage,const NBlib::wchar* a_wfilename,NBlib::s32 a_line);

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

		#elif defined(PLATFORM_GNUCWIN)

		void DebugAssert(bool a_flag,const wchar* a_wmessage,const char* a_filename,s32 a_line)

		#else

		#warning

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

				const wchar* t_wfilename = nullptr;
				{
					#if defined(PLATFORM_VCWIN)

						t_wfilename = a_wfilename;

					#elif defined(PLATFORM_GNUCWIN)

						const char* t_filename = a_filename;
						STLWString t_wstring;
						CharToWchar(t_filename,t_wstring);
						t_wfilename = t_wstring.c_str();
			
					#else

						#warning

					#endif
				}

				#if(BLIB_DEBUGASSERT_CALLBACK_ENABLE)
				{
					//コールバックからの戻り値が「false」の場合処理を中断します。
					if(Blib_DebugAssert_Callback(a_wmessage,t_wfilename,a_line) == false){
						return;
					}
				}
				#endif

				{
					DEBUGLOG(L"%s(%d): [ASSERT]%s\n",t_wfilename,a_line,t_wmessage);	
					DEBUGBREAK();
				}

			}
		}


	#endif


}

