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
		/** InitItem
		*/
		struct InitItem : public WindowMenu_Window_Base::InitItem
		{
			/** constructor
			*/
			InitItem()
				:
				WindowMenu_Window_Base::InitItem()
			{
			}

			/** destructor
			*/
			nonvirtual ~InitItem()
			{
			}
		};

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
		void Initialize(const InitItem& a_inititem);

		/** マウス処理。
		*/
		virtual bool CallBack_InRangeMouseUpdate(WindowMenu_Mouse& a_mouse);

		/** 更新処理。
		*/
		virtual void CallBack_Update();
	};

}}

