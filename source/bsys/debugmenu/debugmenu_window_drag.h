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
	/** ドラッグ。
	*/
	class DebugMenu_Window_Drag : public DebugMenu_Window_Base
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
		DebugMenu_Window_Drag(DebugMenu_Window_Base::Mode::Id a_mode,f32 a_x,f32 a_y,f32 a_w,f32 a_h,f32 a_z);

		/** destructor
		*/
		virtual ~DebugMenu_Window_Drag();

		/** 更新。
		*/
		virtual void Update();
	};

}}

