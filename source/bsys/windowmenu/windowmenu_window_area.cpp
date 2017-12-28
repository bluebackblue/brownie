

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief デバッグメニュー。
*/


/** include
*/
#include <bsys_pch.h>


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../color/color.h"
#pragma warning(pop)


/** include
*/
#include "./windowmenu.h"
#include "./windowmenu_window_area.h"


/** NBsys::NWindowMenu
*/
#if(BSYS_WINDOWMENU_ENABLE)
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
	void WindowMenu_Window_Area::Initialize(const WindowMenu_Window_Base::InitItem& a_inititem)
	{
		WindowMenu_Window_Base::Initialize(a_inititem);
		{
		}
	}


}}
#endif

