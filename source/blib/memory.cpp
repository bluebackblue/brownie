

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
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
#pragma warning(disable:4710)
#pragma warning(push)
#pragma warning(disable:4987 4365 4820 4514 4623 4626 5027)
#include <memory>
#pragma warning(pop)


/** include
*/
#if defined(PLATFORM_GNUCWIN)

	//[include]
	#include <memory.h>

#endif


/** NBlib
*/
namespace NBlib
{
	namespace NMemory
	{
		/** Set
		*/
		void Set(void* a_data,s32 a_value,std::size_t a_size)
		{
			#if defined(PLATFORM_VCWIN)

			std::memset(a_data,a_value,a_size);

			#elif defined(PLATFORM_GNUCWIN)

			memset(a_data,a_value,a_size);

			#else

			#warning

			#endif
		}


		/** Copy
		*/
		void Copy(void* a_dest,std::size_t a_check_dest_size,const void* a_src,std::size_t a_size)
		{
			#if defined(PLATFORM_VCWIN)

			::memcpy_s(a_dest,a_check_dest_size,a_src,a_size);

			#elif defined(PLATFORM_GNUCWIN)

			::memcpy(a_dest,a_src,a_size);

			#else

			#warning

			#endif
		}


		/** Compare
		*/
		s32 Compare(const void* a_data_1,const void* a_data_2,std::size_t a_size)
		{
			#if defined(PLATFORM_VCWIN)

			return std::memcmp(a_data_1,a_data_2,a_size);

			#elif defined(PLATFORM_GNUCWIN)

			memcmp(a_data_1,a_data_2,a_size);

			#else

			#warning
			return 0;

			#endif
		}


		/** StringLength
		*/
		s32 StringLength(const char* a_string,std::size_t a_max)
		{
			#if defined(PLATFORM_VCWIN)

			return static_cast<s32>(::strnlen_s(a_string,a_max));

			#elif defined(PLATFORM_GNUCWIN)

			return static_cast<s32>(strnlen(a_string,a_max));

			#else

			#warning
			return 0;

			#endif
		}


		/** StringLengthW
		*/
		s32 StringLengthW(const wchar* a_strin,std::size_t a_max)
		{
			#if defined(PLATFORM_VCWIN)

			return static_cast<s32>(::wcsnlen_s(a_strin,a_max));

			#elif defined(PLATFORM_GNUCWIN)

			return static_cast<s32>(wcsnlen(a_strin,a_max));

			#else

			#warning
			return 0;

			#endif
		}


	}

	/** StringCompare
	*/
	s32 Memory::StringCompare(const char* a_string_1,const char* a_string_2)
	{
		#if defined(PLATFORM_VCWIN)

		return ::strcmp(a_string_1,a_string_2);

		#elif defined(PLATFORM_GNUCWIN)

		return strcmp(a_string_1,a_string_2);

		#else

		#warning
		return 0;

		#endif
	}


	/** StringCompare
	*/
	s32 Memory::StringCompareW(const wchar* a_string_1,const wchar* a_string_2)
	{
		#if defined(PLATFORM_VCWIN)

		return ::wcscmp(a_string_1,a_string_2);

		#elif defined(PLATFORM_GNUCWIN)

		return ::wcscmp(a_string_1,a_string_2);

		#else
		#warning
		return 0;

		#endif
	}


}

