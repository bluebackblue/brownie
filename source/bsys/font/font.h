#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief フォント。
*/


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./font_state.h"


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
		const sharedptr<Font_Impl>& GetImpl() const;

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
		Font_State GetPixel_R8G8B8A8(sharedptr<u8>& a_dest_data,s32 a_offset,s32 a_dest_width,s32 a_dest_height,wchar a_code);

	};


}}
#endif

