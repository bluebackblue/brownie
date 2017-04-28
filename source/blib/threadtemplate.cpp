

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief スレッドテンプレート。
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
#include "./stlstring.h"


/** include
*/
#if defined(PLATFORM_VCWIN)
	
	#include "./include_windows.h"

#endif


/** NBlib
*/
namespace NBlib
{
	/** ThreadSleep
	*/
	void ThreadSleep(u32 a_millisec)
	{
		#if defined(PLATFORM_VCWIN)

		::Sleep(a_millisec);

		#else

		ASSERT(0);

		#endif
	}

	/** THREADNAME_INFO
	*/
	#if defined(PLATFORM_VCWIN)

		#pragma pack(push,8)  
		struct THREADNAME_INFO  
		{
			/** Must be 0x1000.
			*/
			DWORD	dwType;

			/** Pointer to name (in user addr space).
			*/
			LPCSTR	szName;

			/** // Thread ID (-1=caller thread).
			*/
			DWORD	dwThreadID;

			/** Reserved for future use, must be zero.
			*/
			DWORD	dwFlags;
		};  
		#pragma pack(pop)

	#endif

	/** SetThreadName
	*/
	#if defined(PLATFORM_VCWIN)

		void SetThreadName(const STLString& a_threadname)
		{
			const DWORD MS_VC_EXCEPTION = 0x406D1388;

			THREADNAME_INFO t_info;
			{
				t_info.dwType = 0x1000;  
				t_info.szName = a_threadname.c_str();  
				t_info.dwThreadID = -1;
				t_info.dwFlags = 0;  
			}

			#pragma warning(push)  
			#pragma warning(disable: 6320 6322)  
			__try
			{
				::RaiseException(MS_VC_EXCEPTION,0,sizeof(t_info)/sizeof(ULONG_PTR),(ULONG_PTR*)&t_info);  
			}
			__except(EXCEPTION_EXECUTE_HANDLER)
			{
			}
			#pragma warning(pop)  
		}

	#endif
}

