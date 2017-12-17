

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
	WindowMenu_Window_Area::WindowMenu_Window_Area(const STLString& a_name)
		:
		WindowMenu_Window_Base(a_name,WindowMenu_WindowType::Area)
	{
	}

	/** destructor
	*/
	WindowMenu_Window_Area::~WindowMenu_Window_Area()
	{
	}

	/** Initialize
	*/
	void WindowMenu_Window_Area::Initialize(const InitItem& a_inititem)
	{
		WindowMenu_Window_Base::InitItem t_inititem;
		{
			t_inititem.mode = a_inititem.mode;
			t_inititem.offset = a_inititem.offset;
			t_inititem.size = a_inititem.size;
		}
		WindowMenu_Window_Base::Initialize(t_inititem);
		{
		}
	}
}}

