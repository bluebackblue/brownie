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
	/** リサイズ。
	*/
	class WindowMenu_Window_Resize : public WindowMenu_Window_Base
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

		/** limit
		*/
		Size2DType<f32> limit;

	public:

		/** constructor
		*/
		WindowMenu_Window_Resize(const STLString& a_name);

		/** destructor
		*/
		virtual ~WindowMenu_Window_Resize();

		/** Initialize
		*/
		void Initialize(const WindowMenu_Window_Base::InitItem& a_inititem);

		/** システムからのマウス再起処理。

		a_mousefix	: true = マウスは処理済み。

		*/
		virtual void System_MouseUpdate(WindowMenu_Mouse& a_mouse,bool& a_mousefix);

		/** マウス処理。

		a_mousefix	: true = マウスは処理済み。

		*/
		virtual void CallBack_MouseUpdate(WindowMenu_Mouse& a_mouse,bool& a_mousefix);

	};


}}
#pragma warning(pop)
#endif

