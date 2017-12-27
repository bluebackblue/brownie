#pragma once

/**
 * Copyright (c) 2016-2017 blueback
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
		WindowMenu_Window_Drag(const STLString& a_name);

		/** destructor
		*/
		virtual ~WindowMenu_Window_Drag();

		/** Initialize
		*/
		void Initialize(const WindowMenu_Window_Base::InitItem& a_inititem);

		/** マウス処理。
		*/
		virtual bool CallBack_InRangeMouseUpdate(WindowMenu_Mouse& a_mouse);

		/** 更新処理。
		*/
		virtual void CallBack_Update();

	};


}}
#endif

