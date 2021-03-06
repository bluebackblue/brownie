﻿#pragma once

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief デバッグメニュー。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** NBsys::NWindowMenu
*/
#if(BSYS_WINDOWMENU_ENABLE)
#pragma warning(push)
#pragma warning(disable:4820)
namespace NBsys{namespace NWindowMenu
{
	/** WindowMenu_Mouse
	*/
	struct WindowMenu_Mouse
	{
		/** pos
		*/
		Position2DType<f32> pos;

		/** on_l
		*/
		bool on_l;

		/** on_r
		*/
		bool on_r;

		/** down_l
		*/
		bool down_l;

		/** down_r
		*/
		bool down_r;

		/** up_l
		*/
		bool up_l;

		/** up_r
		*/
		bool up_r;

	};


}}
#pragma warning(pop)
#endif

