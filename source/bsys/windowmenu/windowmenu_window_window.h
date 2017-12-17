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
		/** InitItem
		*/
		struct InitItem : public WindowMenu_Window_Base::InitItem
		{
			/** color
			*/
			NBsys::NColor::Color_F color_title_bg_normal;
			NBsys::NColor::Color_F color_title_bg_active;
			NBsys::NColor::Color_F color_closebutton_nomal;
			NBsys::NColor::Color_F color_closebutton_on;
			NBsys::NColor::Color_F color_closebutton_ondown;
			NBsys::NColor::Color_F color_title_text;

			/** constructor
			*/
			InitItem()
				:
				WindowMenu_Window_Base::InitItem(),
				color_title_bg_normal(1.0f,1.0f,1.0f,1.0f),
				color_title_bg_active(1.0f,1.0f,1.0f,1.0f),
				color_closebutton_nomal(1.0f,1.0f,1.0f,1.0f),
				color_closebutton_on(1.0f,1.0f,1.0f,1.0f),
				color_closebutton_ondown(1.0f,1.0f,1.0f,1.0f),
				color_title_text(1.0f,1.0f,1.0f,1.0f)
			{
			}

			/** destructor
			*/
			nonvirtual ~InitItem()
			{
			}
		};

	public:
		/** color
		*/
		NBsys::NColor::Color_F color_title_bg_normal;
		NBsys::NColor::Color_F color_title_bg_active;
		NBsys::NColor::Color_F color_closebutton_nomal;
		NBsys::NColor::Color_F color_closebutton_on;
		NBsys::NColor::Color_F color_closebutton_ondown;
		NBsys::NColor::Color_F color_title_text;

		/** title_drag
		*/
		sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Drag> title_drag;

		/** title_bg
		*/
		sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Plate> title_bg;

		/** title_area
		*/
		sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Area> title_area;

		/** title_text
		*/
		sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Text> title_text;

		/** title_closebutton
		*/
		sharedptr<NBsys::NWindowMenu::WindowMenu_Window_CloseButton> title_closebutton;

	public:
		/** constructor
		*/
		WindowMenu_Window_Window(const STLString& a_name);

		/** destructor
		*/
		virtual ~WindowMenu_Window_Window();

		/** Initialize
		*/
		void Initialize(const InitItem& a_inititem);

		/** アクティブ変更。
		*/
		virtual void CallBack_ChangeActive(bool a_active);
	};

}}

