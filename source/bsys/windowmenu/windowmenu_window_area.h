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


/** include
*/
#include "./windowmenu.h"
#include "./windowmenu_window_base.h"


/** NBsys::NWindowMenu
*/
namespace NBsys{namespace NWindowMenu
{
	/** プレート。
	*/
	class WindowMenu_Window_Area : public WindowMenu_Window_Base
	{
	public:
		/** constructor
		*/
		WindowMenu_Window_Area(WindowMenu_Window_Base::Mode::Id a_mode,const STLString& a_name,f32 a_x,f32 a_y,SizeType::Id a_sizetype_w,f32 a_w,SizeType::Id a_sizetype_h,f32 a_h,s32 a_z);

		/** destructor
		*/
		virtual ~WindowMenu_Window_Area();
	};

}}

