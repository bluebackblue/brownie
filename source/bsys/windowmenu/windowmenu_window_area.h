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
#if(BSYS_WINDOWMENU_ENABLE)
namespace NBsys{namespace NWindowMenu
{
	/** プレート。
	*/
	class WindowMenu_Window_Area : public WindowMenu_Window_Base
	{
	public:

	public:
		/** constructor
		*/
		WindowMenu_Window_Area(const STLString& a_name);

		/** destructor
		*/
		virtual ~WindowMenu_Window_Area();

		/** Initialize
		*/
		void Initialize(const WindowMenu_Window_Base::InitItem& a_inititem);
	};

}}
#endif

