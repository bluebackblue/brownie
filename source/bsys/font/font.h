#pragma once

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief フォント。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** include
*/
#include "./font_state.h"
#include "./font_alignment.h"


/** NBsys::NFont
*/
#if(BSYS_FONT_ENABLE)
namespace NBsys{namespace NFont
{
	/** Font_Impl
	*/
	class Font_Impl;


	/** Font
	*/
	class Font
	{
	private:

		/** impl
		*/
		sharedptr<Font_Impl> impl;

	public:

		/** GetImpl
		*/
		sharedptr<Font_Impl>& GetImpl();

	public:

		/** constructor
		*/
		Font(const STLWString& a_font_name,s32 a_font_size);

		/** destructor
		*/
		nonvirtual ~Font();

	public:

		/** GetPixel_R8G8B8A8
		*/
		Font_State GetPixel_R8G8B8A8(sharedptr<u8>& a_dest_data,s32 a_byte_offset,const Size2DType<s32>& a_dest_size,wchar a_code);

	};


}}
#endif

