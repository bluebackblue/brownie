#pragma once

/**
 * Copyright (c) 2016-2017 blueback
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


/** NBsys::NFont
*/
#if(BSYS_FONT_ENABLE)
namespace NBsys{namespace NFont
{
	/** Font_State
	*/
	struct Font_State
	{
		/** code
		*/
		wchar code;

		/** パディング。
		*/
		u8 dummy[2];

		/** x
		*/
		s32 x;

		/** y
		*/
		s32 y;

		/** black_box_x
		*/
		s32 black_box_x;

		/** black_box_y
		*/
		s32 black_box_y;

		/** glyph_origin_x
		*/
		s32 glyph_origin_x;

		/** glyph_origin_y
		*/
		s32 glyph_origin_y;

		/** cell_inc_x
		*/
		s32 cell_inc_x;

		/** cell_inc_y
		*/
		s32 cell_inc_y;

		/** ascent
		*/
		s32 ascent;

		/** constructor
		*/
		Font_State()
			:
			code(0x00),
			x(0),
			y(0),
			black_box_x(0),
			black_box_y(0),
			glyph_origin_x(0),
			glyph_origin_y(0),
			cell_inc_x(0),
			cell_inc_y(0),
			ascent(0)
		{
		}

		/** destructor
		*/
		nonvirtual ~Font_State()
		{
		}
	};


}}
#endif

