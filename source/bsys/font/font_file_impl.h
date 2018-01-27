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
	/** Font_File_Impl
	*/
	class Font_File_Impl
	{
	private:

		/** font_handle
		*/
		#if defined(PLATFORM_VCWIN)
		HANDLE font_file_handle;
		#endif

	public:

		/** constructor
		*/
		Font_File_Impl(const sharedptr<u8>& a_data,s32 a_size);

		/** destructor
		*/
		nonvirtual ~Font_File_Impl();

	};


}}
#pragma warning(pop)
#endif

