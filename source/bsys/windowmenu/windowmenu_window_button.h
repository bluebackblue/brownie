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
	/** ボタン。
	*/
	class WindowMenu_Window_Button : public WindowMenu_Window_Base
	{
	public:
		/** InitItem
		*/
		struct InitItem : public WindowMenu_Window_Base::InitItem
		{
			/** color
			*/
			NBsys::NColor::Color_F color_nomal;
			NBsys::NColor::Color_F color_on;
			NBsys::NColor::Color_F color_ondown;

			/** string
			*/
			STLWString string;

			/** constructor
			*/
			InitItem()
				:
				WindowMenu_Window_Base::InitItem(),
				color_nomal(NBsys::NColor::Color_F(1.0f,1.0f,1.0f,1.0f)),
				color_on(NBsys::NColor::Color_F(1.0f,1.0f,1.0f,1.0f)),
				color_ondown(NBsys::NColor::Color_F(1.0f,1.0f,1.0f,1.0f)),
				string(L"")
			{
			}

			/** destructor
			*/
			nonvirtual ~InitItem()
			{
			}
		};

	public:
		/** push_flag
		*/
		bool push_flag;

		/** on_flag
		*/
		bool on_flag;

		/** color
		*/
		NBsys::NColor::Color_F color_nomal;
		NBsys::NColor::Color_F color_on;
		NBsys::NColor::Color_F color_ondown;

		/** string
		*/
		STLWString string;

	public:
		/** constructor
		*/
		WindowMenu_Window_Button(const STLString& a_name);

		/** destructor
		*/
		virtual ~WindowMenu_Window_Button();

		/** Initialize
		*/
		void Initialize(const InitItem& a_inititem);

		/** マウス処理。
		*/
		virtual bool CallBack_InRangeMouseUpdate(WindowMenu_Mouse& a_mouse);

		/** 更新処理。
		*/
		virtual void CallBack_Update();

		/** 描画処理。
		*/
		virtual bool CallBack_Draw(s32 a_z_sort);
	};

}}

