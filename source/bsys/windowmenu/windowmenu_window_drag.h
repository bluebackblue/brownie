﻿#pragma once

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief デバッグメニュー。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** include
*/
#include "./windowmenu.h"
#include "./windowmenu_window_base.h"


/** NBsys::NWindowMenu
*/
#if(BSYS_WINDOWMENU_ENABLE)
#pragma warning(push)
#pragma warning(disable:4820)
namespace NBsys{namespace NWindowMenu
{
	/** ドラッグ。
	*/
	class WindowMenu_Window_Drag : public WindowMenu_Window_Base
	{
	public:

		/** drag_flag
		*/
		bool drag_flag;

		/** start_pos
		*/
		Position2DType<f32> start_pos;

		/** old_pos
		*/
		Position2DType<f32> old_pos;

	public:

		/** constructor
		*/
		WindowMenu_Window_Drag(const STLString& a_name);

		/** destructor
		*/
		virtual ~WindowMenu_Window_Drag();

		/** Initialize
		*/
		void Initialize(const WindowMenu_Window_Base::InitItem& a_inititem);

		/** マウス処理。

		a_mousefix	: true = マウスは処理済み。

		*/
		virtual void CallBack_MouseUpdate(WindowMenu_Mouse& a_mouse,bool& a_mousefix);

		/** 更新処理。
		*/
		virtual void CallBack_Update();

	};


}}
#pragma warning(pop)
#endif

