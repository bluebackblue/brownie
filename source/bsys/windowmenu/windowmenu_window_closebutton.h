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
	/** 閉じるボタン。
	*/
	class WindowMenu_Window_CloseButton : public WindowMenu_Window_Base
	{
	private:
		/** push_flag
		*/
		bool push_flag;

	public:
		/** constructor
		*/
		WindowMenu_Window_CloseButton(WindowMenu_Window_Base::Mode::Id a_mode,const STLString& a_name,f32 a_x,f32 a_y,SizeType::Id a_sizetype_w,f32 a_w,SizeType::Id a_sizetype_h,f32 a_h,s32 a_z);

		/** destructor
		*/
		virtual ~WindowMenu_Window_CloseButton();

		/** マウス処理。
		*/
		virtual bool CallBack_MouseUpdate(WindowMenu_Mouse& a_mouse);

		/** 更新処理。
		*/
		virtual bool CallBack_Update();

		/** 描画処理。
		*/
		virtual bool CallBack_Draw();
	};

}}

