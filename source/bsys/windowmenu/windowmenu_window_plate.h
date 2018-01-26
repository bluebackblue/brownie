#pragma once

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
	/** プレート。
	*/
	class WindowMenu_Window_Plate : public WindowMenu_Window_Base
	{
	public:

		/** color
		*/
		NBsys::NColor::Color_F color;

		/** texture_id
		*/
		s32 texture_id;

		/** mouseblock
		*/
		bool mouseblock;

	public:

		/** constructor
		*/
		WindowMenu_Window_Plate(const STLString& a_name);

		/** destructor
		*/
		virtual ~WindowMenu_Window_Plate();

		/** Initialize
		*/
		void Initialize(const WindowMenu_Window_Base::InitItem& a_inititem);

		/** 描画処理。
		*/
		virtual bool CallBack_Draw(s32 a_z_sort);

		/** マウス処理。

		a_mousefix	: true = マウスは処理済み。

		*/
		virtual void CallBack_MouseUpdate(WindowMenu_Mouse& a_mouse,bool& a_mousefix);

	};


}}
#pragma warning(pop)
#endif

