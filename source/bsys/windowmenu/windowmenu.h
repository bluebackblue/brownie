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
#pragma warning(push)
#pragma warning(disable:4464)
#include "../color/color.h"
#pragma warning(pop)


/** include
*/
#include "./windowmenu_type.h"
#include "./windowmenu_mouse.h"
#include "./windowmenu_callback_base.h"
#include "./windowmenu_window_base.h"
#include "./windowmenu_window_area.h"
#include "./windowmenu_window_plate.h"
#include "./windowmenu_window_drag.h"
#include "./windowmenu_window_closebutton.h"
#include "./windowmenu_window_text.h"
#include "./windowmenu_window_button.h"
#include "./windowmenu_window_window.h"


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

		/** active
		*/
		sharedptr<WindowMenu_Window_Base> active;

		/** アクティブ変更チェック。
		*/
		bool changeactive_check;

		/** 領域再計算、親子関係変更。
		*/
		bool changerect_check;

	public:

		/** constructor
		*/
		WindowMenu(sharedptr<WindowMenu_Callback_Base> a_callback);

		/** destructor
		*/
		nonvirtual ~WindowMenu();

	public:

		/** Update
		*/
		void Update();

		/** Draw
		*/
		void Draw(s32 a_z_sort_add = 100);

	public:

		/** 追加。
		*/
		void Add(const sharedptr<WindowMenu_Window_Base> a_window);

		/** GetList
		*/
		STLList<sharedptr<WindowMenu_Window_Base>>::Type& GetList();

		/** GetMouse
		*/
		WindowMenu_Mouse& GetMouse();

		/** GetCallback
		*/
		sharedptr<WindowMenu_Callback_Base>& GetCallback();

		/** SetChangeRect
		*/
		void SetChangeRect();

	};


	/** システムの開始。
	*/
	void StartSystem(sharedptr<WindowMenu_Callback_Base> a_callback);


	/** システムの終了。
	*/
	void EndSystem();


	/** システムのインスタンス取得。
	*/
	sharedptr<WindowMenu>& GetSystemInstance();


}}
#endif

