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
#include "./windowmenu_callback_base.h"
#include "./windowmenu_window_base.h"
#include "./windowmenu_window_plate.h"
#include "./windowmenu_window_drag.h"


/** NBsys::NWindowMenu
*/
#if(BSYS_WINDOWMENU_ENABLE)
namespace NBsys{namespace NWindowMenu
{
	/** WindowMenu
	*/
	class WindowMenu
	{
	public:
		/** callback
		*/
		sharedptr<WindowMenu_Callback_Base> callback;

		/** list
		*/
		STLList<sharedptr<WindowMenu_Window_Base>>::Type list;

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

