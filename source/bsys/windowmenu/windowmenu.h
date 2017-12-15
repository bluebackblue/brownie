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
#include "../color/color.h"


/** include
*/
#include "./windowmenu_mouse.h"
#include "./windowmenu_callback_base.h"
#include "./windowmenu_window_base.h"
#include "./windowmenu_window_area.h"
#include "./windowmenu_window_plate.h"
#include "./windowmenu_window_drag.h"
#include "./windowmenu_window_closebutton.h"


/** NBsys::NWindowMenu
*/
#if(BSYS_WINDOWMENU_ENABLE)
namespace NBsys{namespace NWindowMenu
{
	/** WindowMenu
	*/
	class WindowMenu
	{
	private:
		/** callback
		*/
		sharedptr<WindowMenu_Callback_Base> callback;

		/** list
		*/
		STLList<sharedptr<WindowMenu_Window_Base>>::Type list;

		/** mouse
		*/
		WindowMenu_Mouse mouse;

	public:
		/** constructor
		*/
		WindowMenu(sharedptr<WindowMenu_Callback_Base>& a_callback);

		/** destructor
		*/
		nonvirtual ~WindowMenu();

	public:
		/** Update
		*/
		void Update();

		/** Draw
		*/
		void Draw();

	public:
		/** 追加。
		*/
		void Add(const sharedptr<WindowMenu_Window_Base>& a_window);

		/** GetList
		*/
		STLList<sharedptr<WindowMenu_Window_Base>>::Type& GetList();

		/** GetMouse
		*/
		WindowMenu_Mouse& GetMouse();

		/** GetCallback
		*/
		sharedptr<WindowMenu_Callback_Base>& GetCallback();

	};

	/** システムの開始。
	*/
	void StartSystem(sharedptr<WindowMenu_Callback_Base>& a_callback);

	/** システムの終了。
	*/
	void EndSystem();

	/** システムのインスタンス取得。
	*/
	sharedptr<WindowMenu>& GetSystemInstance();
}}
#endif

