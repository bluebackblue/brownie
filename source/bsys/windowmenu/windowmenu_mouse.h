#pragma once

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief デバッグメニュー。
*/


/** include
*/
#include "../types/types.h"


/** NBsys::NWindowMenu
*/
#if(BSYS_WINDOWMENU_ENABLE)
namespace NBsys{namespace NWindowMenu
{
	/** WindowMenu_Mouse
	*/
	struct WindowMenu_Mouse
	{
		f32 x;
		f32 y;
		bool on_l;
		bool on_r;
		bool down_l;
		bool down_r;
		bool up_l;
		bool up_r;
	};
}}
#endif

