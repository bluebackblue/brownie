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
#pragma warning(push)
#pragma warning(disable:4820)
namespace NBsys{namespace NWindowMenu
{
	/** ボタン。
	*/
	class WindowMenu_Window_Button : public WindowMenu_Window_Base
	{
	public:

		/** push_flag
		*/
		bool push_flag;

		/** on_flag
		*/
		bool on_flag;

		/** color
		*/
		NBsys::NColor::Color_F color_normal;
		NBsys::NColor::Color_F color_on;
		NBsys::NColor::Color_F color_ondown;

		/** string
		*/
		STLWString string;

		/** action
		*/
		std::function<void(void)> action;

		/** clip
		*/
		bool clip;

	public:

		/** constructor
		*/
		WindowMenu_Window_Button(const STLString& a_name);

		/** destructor
		*/
		virtual ~WindowMenu_Window_Button();

		/** Initialize
		*/
		void Initialize(const WindowMenu_Window_Base::InitItem& a_inititem);

		/** マウス処理。

		a_mousefix	: true = マウスは処理済み。

		*/
		virtual void CallBack_MouseUpdate(WindowMenu_Mouse& a_mouse,bool& a_mousefix);

		/** 描画処理。
		*/
		virtual bool CallBack_Draw(s32 a_z_sort);

	};


}}
#pragma warning(pop)
#endif

