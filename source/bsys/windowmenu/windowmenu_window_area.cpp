

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief デバッグメニュー。
*/


/** include
*/
#include <bsys_pch.h>


/** include
*/
#include "../types/types.h"


/** include
*/
#include "../color/color.h"


/** include
*/
#include "./windowmenu.h"
#include "./windowmenu_window_area.h"


/** NBsys::NWindowMenu
*/
namespace NBsys{namespace NWindowMenu
{
	/** constructor
	*/
	WindowMenu_Window_Area::WindowMenu_Window_Area(WindowMenu_Window_Base::Mode::Id a_mode,const STLString& a_name,f32 a_x,f32 a_y,SizeType::Id a_sizetype_w,f32 a_w,SizeType::Id a_sizetype_h,f32 a_h,s32 a_z)
		:
		WindowMenu_Window_Base(a_name)
	{
		this->Initialize(a_mode,a_x,a_y,a_sizetype_w,a_w,a_sizetype_h,a_h,a_z);
	}

	/** destructor
	*/
	WindowMenu_Window_Area::~WindowMenu_Window_Area()
	{
	}
}}

