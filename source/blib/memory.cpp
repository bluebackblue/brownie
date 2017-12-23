

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief メモリー。
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
#include "./memory.h"


/** include
*/
#include <memory>


/** NBlib
*/
namespace NBlib
{
	/** [static]memset
	*/
	void Memory::memset(void* a_data,s32 a_value,s32 a_size)
	{
		#if defined(PLATFORM_VCWIN)

		std::memset(a_data,a_value,a_size);

		#else

		#warning

		#endif
	}


	/** [static]memcpy
	*/
	void Memory::memcpy(void* a_dest,s32 a_check_dest_size,const void* a_src,s32 a_src_size)
	{
		#if defined(PLATFORM_VCWIN)

		::memcpy_s(a_dest,a_check_dest_size,a_src,a_src_size);

		#else

		#warning

		#endif
	}


	/** [static]memcmp
	*/
	s32 Memory::memcmp(const void* a_data_1,const void* a_data_2,s32 a_size)
	{
		#if defined(PLATFORM_VCWIN)

		return std::memcmp(a_data_1,a_data_2,a_size);

		#else

		#warning
		return 0;

		#endif
	}


	/** [static]strlen
	*/
	s32 Memory::strlen(const char* a_string,s32 a_max)
	{
		#if defined(PLATFORM_VCWIN)

		return static_cast<s32>(::strnlen_s(a_string,a_max));

		#else

		#warning
		return 0;

		#endif
	}


	/** [static]wstrlen
	*/
	s32 Memory::wstrlen(const wchar* a_strin,s32 a_max)
	{
		#if defined(PLATFORM_VCWIN)

		return static_cast<s32>(::wcsnlen_s(a_strin,a_max));

		#else

		#warning
		return 0;

		#endif
	}


	/** [static]strcmp
	*/
	s32 Memory::strcmp(const char* a_string_1,const char* a_string_2)
	{
		#if defined(PLATFORM_VCWIN)

		return ::strcmp(a_string_1,a_string_2);

		#else

		#warning
		return 0;

		#endif
	}


	/** [static]wcscmp
	*/
	s32 Memory::wcscmp(const wchar* a_string_1,const wchar* a_string_2)
	{
		#if defined(PLATFORM_VCWIN)

		return ::wcscmp(a_string_1,a_string_2);

		#else

		#warning
		return 0;

		#endif
	}


}

