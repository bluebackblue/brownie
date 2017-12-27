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
namespace NBsys{namespace NWindowMenu
{
	/** テキスト。
	*/
	class WindowMenu_Window_Text: public WindowMenu_Window_Base
	{
	public:

		/** color
		*/
		NBsys::NColor::Color_F color;

		/** string
		*/
		STLWString string;

		/** clip
		*/
		bool clip;

		/** alignment_x
		*/
		s32 alignment_x;

		/** alignment_y
		*/
		s32 alignment_y;

	public:

		/** constructor
		*/
		WindowMenu_Window_Text(const STLString& a_name);

		/** destructor
		*/
		virtual ~WindowMenu_Window_Text();

		/** Initialize
		*/
		void Initialize(const WindowMenu_Window_Base::InitItem& a_inititem);

		/** 描画処理。
		*/
		virtual bool CallBack_Draw(s32 a_z_sort);

	};


}}
#endif

