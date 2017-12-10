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
#include "./debugmenu.h"
#include "./debugmenu_window_base.h"


/** NBsys::NDebugMenu
*/
namespace NBsys{namespace NDebugMenu
{
	/** プレート。
	*/
	class DebugMenu_Window_Plate : public DebugMenu_Window_Base
	{
	private:
		/** color
		*/
		NBsys::NColor::Color_F color;

	public:
		/** constructor
		*/
		DebugMenu_Window_Plate(DebugMenu_Window_Base::Mode::Id a_mode,f32 a_x,f32 a_y,f32 a_w,f32 a_h,const NBsys::NColor::Color_F& a_color,f32 a_z);

		/** destructor
		*/
		virtual ~DebugMenu_Window_Plate();

		/** Draw
		*/
		virtual void Draw();
	};

}}

