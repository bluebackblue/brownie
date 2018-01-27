

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief フォント。
*/


/** include
*/
#include <bsys_pch.h>


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** include
*/
#include "./font_file_impl.h"


/** warning

4710 : この関数はインライン展開のために選択されましたが、コンパイラはインライン展開を実行しませんでした。

*/
#pragma warning(disable:4710)


/** NBsys::NFont
*/
#if(BSYS_FONT_ENABLE)
namespace NBsys{namespace NFont
{
	/** constructor
	*/
	Font_File_Impl::Font_File_Impl(const sharedptr<u8>& a_data,s32 a_size)
		:
		#if defined(PLATFORM_VCWIN)
		font_file_handle(nullptr)
		#endif
	{
		#if defined(PLATFORM_VCWIN)
		{
			DWORD t_count = 0;
			this->font_file_handle = ::AddFontMemResourceEx(const_cast<u8*>(a_data.get()),a_size,WIN_NULL,&t_count);
			TAGLOG(L"font_file_impl","count = %d",t_count);
			ASSERT(this->font_file_handle != WIN_NULL);
		}
		#endif
	}


	/** destructor
	*/
	Font_File_Impl::~Font_File_Impl()
	{
		#if defined(PLATFORM_VCWIN)
		{
			if(this->font_file_handle != WIN_NULL){
				int t_ret = ::RemoveFontMemResourceEx(this->font_file_handle);
				ASSERT(t_ret != 0);
				this->font_file_handle = WIN_NULL;
			}
		}
		#endif
	}


}}
#endif

