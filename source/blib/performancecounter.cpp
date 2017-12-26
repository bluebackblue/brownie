

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief パフォーマンスカウンター。
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
#include "./debugassert.h"
#include "./performancecounter.h"


/** include
*/
#if defined(PLATFORM_VCWIN)
	#include <brownie_config/windows_include.h>
#endif


/** NBlib
*/
namespace NBlib
{
	/** NImpl
	*/
	namespace NImpl
	{
		#if defined(PLATFORM_VCWIN)

		static LARGE_INTEGER s_frequency;

		#endif
	}


	/** [static]InitPerformanceCounter
	*/
	void PerformanceCounter::InitPerformanceCounter()
	{
		#if defined(PLATFORM_VCWIN)
		{
			/** １秒間あたりのカウント数。
			*/
			if(::QueryPerformanceFrequency(&NImpl::s_frequency) == TRUE){
			}else{
				ASSERT(0);
			}
		}
		#else
		{
			ASSERT(0);
		}
		#endif
	}


	/** [static]1秒 = 1000 * 1000 マイクロ秒。
	*/
	u64 PerformanceCounter::GetPerformanceCounter()
	{
		#if defined(PLATFORM_VCWIN)
		{
			LARGE_INTEGER t_value;
			::QueryPerformanceCounter(&t_value);
			return t_value.QuadPart * 1000 * 1000 / NImpl::s_frequency.QuadPart;
		}
		#else
		{
			ASSERT(0);
		}
		#endif
	}


	/** [static]GetPerformanceSecCounter
	*/
	u64 PerformanceCounter::GetPerformanceSecCounter()
	{
		#if defined(PLATFORM_VCWIN)
		{
			return 1 * 1000 * 1000;
		}
		#else
		{
			ASSERT(0);
			return 0;
		}
		#endif
	}


	/** [static]GetPerformanceMicroSecCounter
	*/
	u64 PerformanceCounter::GetPerformanceMicroSecCounter()
	{
		#if defined(PLATFORM_VCWIN)
		{
			return 1;
		}
		#else
		{
			ASSERT(0);
			return 0;
		}
		#endif
	}


}

