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
	/** ドラッグ。
	*/
	class WindowMenu_Window_Drag : public WindowMenu_Window_Base
	{
	public:
		/** drag
		*/
		bool drag_flag;

		/** start
		*/
		f32 start_x;
		f32 start_y;

		/** old
		*/
		f32 old_x;
		f32 old_y;

	public:
		/** constructor
		*/
		WindowMenu_Window_Drag(WindowMenu_Window_Base::Mode::Id a_mode,f32 a_x,f32 a_y,f32 a_w,f32 a_h,s32 a_z);

		/** destructor
		*/
		virtual ~WindowMenu_Window_Drag();

		/** 更新。
		*/
		virtual void Update();
	};

}}

