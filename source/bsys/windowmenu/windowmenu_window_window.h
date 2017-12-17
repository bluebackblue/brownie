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
	/** ウィンドウ。
	*/
	class WindowMenu_Window_Window : public WindowMenu_Window_Base
	{
	public:
		/** title_h
		*/
		f32 title_h;

		/** title_string
		*/
		STLWString title_string;

		/** color
		*/
		NBsys::NColor::Color_F color_title_bg_normal;
		NBsys::NColor::Color_F color_title_bg_active;

		/** タイトルドラッグ。
		*/
		sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Drag> window_title_drag;

		/** タイトルドラッグ -> タイトル背景。
		*/
		sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Plate> window_title_bg;

		/** タイトルドラッグ -> タイトル背景 -> タイトルエリア。
		*/
		sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Area> window_title_area;

		/** タイトルドラッグ -> タイトル背景 -> タイトルエリア -> タイトルテキスト。
		*/
		sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Text> window_title_text;

		/** タイトルドラッグ -> タイトル背景 -> タイトルエリア -> タイトル閉じるボタン。
		*/
		sharedptr<NBsys::NWindowMenu::WindowMenu_Window_CloseButton> window_title_closebutton;

	public:
		/** constructor
		*/
		WindowMenu_Window_Window(const STLString& a_name);

		/** destructor
		*/
		virtual ~WindowMenu_Window_Window();

		/** Initialize
		*/
		void Initialize(const WindowMenu_Window_Base::InitItem& a_inititem);

		/** アクティブ変更。
		*/
		virtual void CallBack_ChangeActive(bool a_active);
	};

}}

