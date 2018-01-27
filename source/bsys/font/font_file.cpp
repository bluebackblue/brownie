

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


/** include
*/
#include "./font_file.h"


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
	Font_File::Font_File(const sharedptr<u8>& a_data,s32 a_size)
	{
		this->impl.reset(new Font_File_Impl(a_data,a_size));
	}


	/** destructor
	*/
	Font_File::~Font_File()
	{
		this->impl.reset();
	}


	/** GetImpl
	*/
	sharedptr<Font_File_Impl>& Font_File::GetImpl()
	{
		return this->impl;
	}



}}
#endif

