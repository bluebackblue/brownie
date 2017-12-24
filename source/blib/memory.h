#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
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
	/** Memory
	*/
	class Memory
	{
	public:

		/** [static]Set
		*/
		static void Set(void* a_data,s32 a_value,s32 a_size);

		/** [static]Copy
		*/
		static void Copy(void* a_dest,s32 a_check_dest_size,const void* a_src,s32 a_src_size);

		/** [static]Compare
		*/
		static s32 Compare(const void* a_data_1,const void* a_data_2,s32 a_size);

		/** [static]StringLength
		*/
		static s32 StringLength(const char* a_string,s32 a_max);

		/** [static]StringLengthW
		*/
		static s32 StringLengthW(const wchar* a_wstring,s32 a_max);

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
				Memory::Copy(&t_ret,static_cast<s32>(sizeof(T)),a_current_pointer,static_cast<s32>(sizeof(T)));

				if(a_increment < 0){
					//自動インクリメント。
					a_current_pointer += sizeof(T);
				}else{
					//手動インクリメント。
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
				Memory::Copy(&t_ret,static_cast<s32>(sizeof(T)),a_current_pointer,static_cast<s32>(sizeof(T)));

				if(a_increment < 0){
					//自動インクリメント。
					a_current_pointer += sizeof(T);
				}else{
					//手動インクリメント。
					a_current_pointer += a_increment;
				}
			}
			return t_ret;
		}

	};


}

