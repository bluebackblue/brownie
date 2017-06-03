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

		/** [static]memcpy
		*/
		static void memcpy(void* a_dest,s32 a_check_dest_size,const void* a_src,s32 a_src_size);

		/** [static]memcmp
		*/
		static s32 memcmp(const void* a_data_1,const void* a_data_2,s32 a_size);

		/** [static]memset
		*/
		static void memset(void* a_data,s32 a_value,s32 a_size);

		/** Copy
		*/
		template < typename T > static T Copy(const u8*& a_current_pointer,int a_increment = -1)
		{
			T t_ret;
			{
				Memory::memcpy(&t_ret,static_cast<s32>(sizeof(T)),a_current_pointer,static_cast<s32>(sizeof(T)));

				if(a_increment < 0){
					//自動。
					a_current_pointer += sizeof(T);
				}else{
					//手動。
					a_current_pointer += a_increment;
				}
			}
			return t_ret;
		}
		/** Copy
		*/
		template < typename T > static T Copy(u8*& a_current_pointer,int a_increment = -1)
		{
			T t_ret;
			{
				Memory::memcpy(&t_ret,static_cast<s32>(sizeof(T)),a_current_pointer,static_cast<s32>(sizeof(T)));

				if(a_increment < 0){
					//自動。
					a_current_pointer += sizeof(T);
				}else{
					//手動。
					a_current_pointer += a_increment;
				}
			}
			return t_ret;
		}

	};

}



