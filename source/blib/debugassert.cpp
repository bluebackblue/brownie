

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


/** Blib_DebugAssert_Callback
*/
#if(BLIB_DEBUGASSERT_CALLBACK_ENABLE)

extern void Blib_DebugAssert_Callback(const char* a_message,const char* a_filename,NBlib::s32 a_line);

#endif


/** NBlib
*/
namespace NBlib
{
	/** DebugAssert
	*/
	#if defined(ROM_MASTER)
	#else
	void DebugAssert(bool a_flag,const char* a_message,const char* a_filename,s32 a_line)
	{
		if(a_flag == true){
			//停止しない。
		}else{
			//デバッグ出力。

			const char* t_message = a_message;
			if(t_message == nullptr){
				t_message = "";
			}

			#if(BLIB_DEBUGASSERT_CALLBACK_ENABLE)
			{
				Blib_DebugAssert_Callback(a_message,a_filename,a_line);
			}
			#else
			{
				#if defined(PLATFORM_VCWIN)
				{
					DEBUGLOG("%s(%d): [ASSERT]%s\n",a_filename,a_line,t_message);	
					DEBUGBREAK();
				}
				#endif
			}
			#endif

		}
	}
	#endif
}

