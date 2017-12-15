

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
	WindowMenu_Window_Area::WindowMenu_Window_Area(const InitItem& a_inititem)
		:
		WindowMenu_Window_Base(a_inititem.name)
	{
		this->Initialize(WindowMenu_Window_Base::InitItem(a_inititem.mode,a_inititem.offset,a_inititem.size,0));
	}

	/** destructor
	*/
	WindowMenu_Window_Area::~WindowMenu_Window_Area()
	{
	}
}}

