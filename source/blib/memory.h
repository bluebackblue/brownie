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


/** NBlib
*/
namespace NBlib
{
	namespace NMemory
	{
		/** Set
		*/
		void Set(void* a_data,s32 a_value,std::size_t a_size);


		/** Copy
		*/
		void Copy(void* a_dest,std::size_t a_check_dest_size,const void* a_src,std::size_t a_src_size);


		/** Compare
		*/
		s32 Compare(const void* a_data_1,const void* a_data_2,std::size_t a_size);


		/** [static]StringLength
		*/
		s32 StringLength(const char* a_string,std::size_t a_max);


		/** [static]StringLengthW
		*/
		s32 StringLengthW(const wchar* a_wstring,std::size_t a_max);
	}

	/** Memory
	*/
	class Memory
	{
	public:

		/** Copy
		*/
		template <typename T,typename U> static void Copy(void* a_dest,T a_check_dest_size,const void* a_src,U a_size)
		{
			NMemory::Copy(a_dest,static_cast<std::size_t>(a_check_dest_size),a_src,static_cast<std::size_t>(a_size));
		}

		/** Set
		*/
		template <typename T> static void Set(void* a_data,s32 a_value,T a_size)
		{
			NMemory::Set(a_data,a_value,static_cast<std::size_t>(a_size));
		}

		/** Compare
		*/
		template <typename T> static void Compate(const void* a_data_1,const void* a_data_2,std::size_t a_size)
		{
			NMemory::Compare(a_data_1,a_data_2,a_size);
		}

		/** [static]StringLength
		*/
		template <typename T> static s32 StringLength(const char* a_string,T a_max)
		{
			return NMemory::StringLength(a_string,static_cast<std::size_t>(a_max));
		}

		/** [static]StringLengthW
		*/
		template <typename T> static s32 StringLengthW(const wchar* a_wstring,T a_max)
		{
			return NMemory::StringLengthW(a_string,static_cast<std::size_t>(a_max));
		}

		/** [static]StringCompare
		*/
		static s32 StringCompare(const char* a_string_1,const char* a_string_2);

		/** [static]StringCompareW
		*/
		static s32 StringCompareW(const wchar* a_string_1,const wchar* a_string_2);

		/** [static]ゼロクリア。
		*/
		template <typename T> static void ZeroClear(T& a_instance)
		{
			Memory::Set(&a_instance,0,sizeof(T));
		}

		/** StreamCopy
		*/
		template <typename T> static T StreamCopy(const u8*& a_current_pointer,s32 a_increment = -1)
		{
			T t_ret;
			{
				Memory::Copy(&t_ret,sizeof(T),a_current_pointer,sizeof(T));
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
		template <typename T> static T StreamCopy(u8*& a_current_pointer,s32 a_increment = -1)
		{
			T t_ret;
			{
				Memory::Copy(&t_ret,sizeof(T),a_current_pointer,sizeof(T));
				if(a_increment < 0){
					a_current_pointer += sizeof(T);
				}else{
					a_current_pointer += a_increment;
				}
			}
			return t_ret;
		}


	};


}

