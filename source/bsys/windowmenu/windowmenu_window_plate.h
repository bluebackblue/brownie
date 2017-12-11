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
	class WindowMenu_Window_Plate : public WindowMenu_Window_Base
	{
	private:
		/** color
		*/
		NBsys::NColor::Color_F color;

		/** texture_id
		*/
		s32 texture_id;

	public:
		/** constructor
		*/
		WindowMenu_Window_Plate(WindowMenu_Window_Base::Mode::Id a_mode,f32 a_x,f32 a_y,f32 a_w,f32 a_h,const NBsys::NColor::Color_F& a_color,s32 a_texture_id,s32 a_z);

		/** destructor
		*/
		virtual ~WindowMenu_Window_Plate();

		/** 描画処理。
		*/
		virtual bool CallBack_Draw();
	};

}}

