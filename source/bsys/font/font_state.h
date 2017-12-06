#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �t�H���g�B
*/


/** include
*/
#include "../types/types.h"


/** NBsys::NFont
*/
#if(BSYS_FONT_ENABLE)
namespace NBsys{namespace NFont
{
	/** Font_State
	*/
	struct Font_State
	{
		s32 x;
		s32 y;
		s32 black_box_x;
		s32 black_box_y;
		s32 glyph_origin_x;
		s32 glyph_origin_y;
		s32 cell_inc_x;
		s32 cell_inc_y;
		s32 ascent;
	};

}}
#endif

