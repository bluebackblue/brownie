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
#if defined(PLATFORM_VCWIN)
	#include <brownie_config/windows_include.h>

	//[include]
	#include <mbstring.h>
#endif


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
	class Font_Impl
	{
	private:

		/** font_handle
		*/
		#if defined(PLATFORM_VCWIN)
		HFONT font_handle;
		#endif

		/** hdc
		*/
		#if defined(PLATFORM_VCWIN)
		HDC hdc;
		#endif

		/** font_size
		*/
		s32 font_size;

		/** font_name
		*/
		STLWString font_name;

	public:

		/** constructor
		*/
		Font_Impl(const STLWString& a_font_name,s32 a_font_size);

		/** destructor
		*/
		nonvirtual ~Font_Impl();

	public:

		/** GetPixel_R8G8B8A8
		*/
		Font_State GetPixel_R8G8B8A8(sharedptr<u8>& a_dest_data,s32 a_offset,s32 a_dest_width,s32 a_dest_height,wchar a_code);

	};


}}
#endif

