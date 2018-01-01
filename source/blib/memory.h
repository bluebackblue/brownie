#pragma once

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief メモリー。
*/


/** include
*/
#include "./types.h"
#include "./platform.h"


/** include
*/
#pragma warning(push)
#pragma warning(disable:4710 4711 4987 4365 4820 4514 4623 4626 5027)
#include <memory>
#pragma warning(pop)


/** NBlib
*/
#pragma warning(push)
#pragma warning(disable:4514)
namespace NBlib
{
	/** NMemory
	*/
	namespace NMemory
	{
		/** Copy
		*/
		template <typename T,typename U> inline void Copy(void* a_dest,T a_check_dest_size,const void* a_source,U a_size)
		{
			#if defined(ROM_MASTER)
			{
				UNUSED(a_check_dest_size);
				std::memcpy(a_dest,a_source,static_cast<std::size_t>(a_size));
			}
			#else
			{
				::memcpy_s(a_dest,static_cast<std::size_t>(a_check_dest_size),a_source,static_cast<std::size_t>(a_size));
			}
			#endif
		}


		/** Set
		*/
		template <typename T> inline void Set(void* a_data,s32 a_value,T a_size)
		{
			std::memset(a_data,a_value,static_cast<std::size_t>(a_size));
		}


		/** Compare
		*/
		template <typename T> inline s32 Compare(const void* a_data_1,const void* a_data_2,T a_size)
		{
			return std::memcmp(a_data_1,a_data_2,static_cast<std::size_t>(a_size));
		}


		/** StringLength
		*/
		template <typename T> inline s32 StringLength(const char* a_string,T a_max)
		{
			return NMemory::StringLength(a_string,static_cast<std::size_t>(a_max));
		}


		/** StringLengthW
		*/
		template <typename T> inline s32 StringLengthW(const wchar* a_wstring,T a_max)
		{
			return NMemory::StringLengthW(a_string,static_cast<std::size_t>(a_max));
		}


		/** StringCompare
		*/
		inline s32 StringCompare(const char* a_string_1,const char* a_string_2)
		{
			return std::strcmp(a_string_1,a_string_2);
		}


		/** StringCompareW
		*/
		inline s32 StringCompareW(const wchar* a_string_1,const wchar* a_string_2)
		{
			return std::wcscmp(a_string_1,a_string_2);
		}


		/** ゼロクリア。
		*/
		template <typename T> inline void ZeroClear(T& a_instance)
		{
			NMemory::Set(&a_instance,0,sizeof(T));
		}


		/** StreamCopy
		*/
		template <typename T> inline T StreamCopy(const u8*& a_current_pointer,s32 a_increment = -1)
		{
			T t_ret;
			{
				NMemory::Copy(&t_ret,sizeof(T),a_current_pointer,sizeof(T));
				if(a_increment < 0){
					a_current_pointer += sizeof(T);
				}else{
					a_current_pointer += a_increment;
				}
			}
			return t_ret;
		}


		/** StreamCopy
		*/
		template <typename T> inline T StreamCopy(u8*& a_current_pointer,s32 a_increment = -1)
		{
			T t_ret;
			{
				NMemory::Copy(&t_ret,sizeof(T),a_current_pointer,sizeof(T));
				if(a_increment < 0){
					a_current_pointer += sizeof(T);
				}else{
					a_current_pointer += a_increment;
				}
			}
			return t_ret;
		}


	}


}
#pragma warning(pop)

