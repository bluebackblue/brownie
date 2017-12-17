#pragma once

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �f�o�b�O���j���[�B
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
	/** �{�^���B
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
		NBsys::NColor::Color_F color_nomal;
		NBsys::NColor::Color_F color_on;
		NBsys::NColor::Color_F color_ondown;

		/** string
		*/
		STLWString string;

		/** action
		*/
		std::function< void(void) > action;

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

		/** �}�E�X�����B
		*/
		virtual bool CallBack_InRangeMouseUpdate(WindowMenu_Mouse& a_mouse);

		/** �X�V�����B
		*/
		virtual void CallBack_Update();

		/** �`�揈���B
		*/
		virtual bool CallBack_Draw(s32 a_z_sort);
	};

}}

