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
#if defined(PLATFORM_VCWIN)

	#include <brownie_config/windows_include.h>

	//[include]
	#pragma warning(push)
	#pragma warning(disable:4710 4514)
	#include <mbstring.h>
	#pragma warning(pop)

#endif


/** include
*/
#include "./font_state.h"


/** NBsys::NFont
*/
#if(BSYS_FONT_ENABLE)
#pragma warning(push)
#pragma warning(disable:4820)
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

		/** buffer_size
		*/
		s32 buffer_size;

		/** buffer
		*/
		sharedptr<u8> buffer;

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
		Font_State GetPixel_R8G8B8A8(sharedptr<u8>& a_dest_data,s32 a_byte_offset,const Size2DType<s32>& a_dest_size,wchar a_code);

	};


}}
#pragma warning(pop)
#endif

