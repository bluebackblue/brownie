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
#if(BSYS_WINDOWMENU_ENABLE)
namespace NBsys{namespace NWindowMenu
{
	/** �E�B���h�E�B
	*/
	class WindowMenu_Window_Window : public WindowMenu_Window_Base
	{
	public:

		/** is_active
		*/
		bool is_active;

		/** color
		*/
		NBsys::NColor::Color_F color_title_bg_normal;
		NBsys::NColor::Color_F color_title_bg_active;

		/** �^�C�g���h���b�O�B
		*/
		sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Drag> window_title_drag;

		/** �^�C�g���h���b�O -> �^�C�g���w�i�B
		*/
		sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Plate> window_title_bg;

		/** �^�C�g���h���b�O -> �^�C�g���w�i -> �^�C�g���G���A�B
		*/
		sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Area> window_title_area;

		/** �^�C�g���h���b�O -> �^�C�g���w�i -> �^�C�g���G���A -> �^�C�g���e�L�X�g�B
		*/
		sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Text> window_title_text;

		/** �^�C�g���h���b�O -> �^�C�g���w�i -> �^�C�g���G���A -> �^�C�g������{�^���B
		*/
		sharedptr<NBsys::NWindowMenu::WindowMenu_Window_CloseButton> window_title_closebutton;

	public:

		/** constructor
		*/
		WindowMenu_Window_Window(const STLString& a_name);

		/** destructor
		*/
		virtual ~WindowMenu_Window_Window();

		/** Initialize
		*/
		void Initialize(const WindowMenu_Window_Base::InitItem& a_inititem);

		/** �A�N�e�B�u�ύX�B
		*/
		virtual void CallBack_ChangeActive(bool a_active);

		/** �^�C�g���̍����ݒ�B
		*/
		void SetTitleHeight(f32 a_h);

		/** �^�C�g���w�i�̐F�ݒ�B
		*/
		void SetTitleBgColor(const NBsys::NColor::Color_F& a_color_normal,const NBsys::NColor::Color_F& a_active);

	};


}}
#endif

