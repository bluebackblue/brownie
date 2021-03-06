﻿

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
#include "./font_impl.h"


/** include
*/
#include "./font.h"


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
	Font::Font(const STLWString& a_font_name,s32 a_font_size)
	{
		this->impl.reset(new Font_Impl(a_font_name,a_font_size));
	}


	/** destructor
	*/
	Font::~Font()
	{
		this->impl.reset();
	}


	/** GetImpl
	*/
	sharedptr<Font_Impl>& Font::GetImpl()
	{
		return this->impl;
	}


	/** GetPixel_R8G8B8A8
	*/
	Font_State Font::GetPixel_R8G8B8A8(sharedptr<u8>& a_dest_data,s32 a_byte_offset,const Size2DType<s32>& a_dest_size,wchar a_code)
	{
		return this->impl->GetPixel_R8G8B8A8(a_dest_data,a_byte_offset,a_dest_size,a_code);
	}


}}
#endif

