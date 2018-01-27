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
	/** Font_File_Impl
	*/
	class Font_File_Impl;


	/** Font_File
	*/
	class Font_File
	{
	private:

		/** impl
		*/
		sharedptr<Font_File_Impl> impl;

	public:

		/** GetImpl
		*/
		sharedptr<Font_File_Impl>& GetImpl();

	public:

		/** constructor
		*/
		Font_File(const sharedptr<u8>& a_data,s32 a_size);

		/** destructor
		*/
		nonvirtual ~Font_File();

	};


}}
#endif

