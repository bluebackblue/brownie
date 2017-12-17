

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �f�o�b�O���j���[�B
*/


/** include
*/
#include <bsys_pch.h>


/** include
*/
#include "../types/types.h"


/** include
*/
#include "../color/color.h"


/** include
*/
#include "./windowmenu.h"
#include "./windowmenu_window_window.h"


/** NBsys::NWindowMenu
*/
namespace NBsys{namespace NWindowMenu
{
	/** constructor
	*/
	WindowMenu_Window_Window::WindowMenu_Window_Window(const STLString& a_name)
		:
		WindowMenu_Window_Base(a_name,WindowMenu_WindowType::Window)
	{
		//�^�C�g���h���b�O�B
		this->title_drag = this->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_Drag>("title_drag");

		//�^�C�g���h���b�O -> �^�C�g���w�i�B
		this->title_bg = this->title_drag->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_Plate>("title_bg");

		//�^�C�g���h���b�O -> �^�C�g���w�i -> �^�C�g���G���A�B
		this->title_area = this->title_bg->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_Area>("title_area");

		//�^�C�g���h���b�O -> �^�C�g���w�i -> �^�C�g���G���A -> �^�C�g���e�L�X�g�B
		this->title_text = this->title_area->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_Text>("title_text");

		//�^�C�g���h���b�O -> �^�C�g���w�i -> �^�C�g���G���A -> �^�C�g������{�^���B
		this->title_closebutton = this->title_area->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_CloseButton>("title_closebutton");
	}

	/** destructor
	*/
	WindowMenu_Window_Window::~WindowMenu_Window_Window()
	{
	}

	/** Initialize
	*/
	void WindowMenu_Window_Window::Initialize(const InitItem& a_inititem)
	{
		WindowMenu_Window_Base::InitItem t_inititem;
		{
			t_inititem.mode = a_inititem.mode;
			t_inititem.offset = a_inititem.offset;
			t_inititem.size = a_inititem.size;
		}
		WindowMenu_Window_Base::Initialize(t_inititem);
		{
			this->color_title_bg_normal = a_inititem.color_title_bg_normal;
			this->color_title_bg_active = a_inititem.color_title_bg_active;
			this->color_closebutton_nomal = a_inititem.color_closebutton_nomal;
			this->color_closebutton_on = a_inititem.color_closebutton_on;
			this->color_closebutton_ondown = a_inititem.color_closebutton_ondown;
			this->color_title_text = a_inititem.color_title_text;

			

			
			
			
			//TODO:
			f32 t_title_h = 16.0f;
			f32 t_title_w = a_inititem.size.w;
			//TODO:
			STLWString t_title_string = L"text";













			//�^�C�g���h���b�O�B
			{
				NBsys::NWindowMenu::WindowMenu_Window_Drag::InitItem t_inititem;
				t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Horizontal;	//���ς݁B
				t_inititem.size.SetH(t_title_h);
				t_inititem.size.SetW(t_title_w);
				this->title_drag->Initialize(t_inititem);
			}

			//�^�C�g���h���b�O -> �^�C�g���w�i�B
			{
				NBsys::NWindowMenu::WindowMenu_Window_Plate::InitItem t_inititem;
				t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Horizontal;	//���ς݁B
				{
					t_inititem.color = this->color_title_bg_normal;
					t_inititem.texture_id = -1;
					t_inititem.mouseblock = false;
				}
				this->title_bg->Initialize(t_inititem);
			}

			//�^�C�g���h���b�O -> �^�C�g���w�i -> �^�C�g���G���A�B
			{
				NBsys::NWindowMenu::WindowMenu_Window_Area::InitItem t_inititem;
				t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Horizontal;	//���ς݁B
				{
				}
				this->title_area->Initialize(t_inititem);
			}

			//�^�C�g���h���b�O -> �^�C�g���w�i -> �^�C�g���G���A -> �^�C�g���e�L�X�g�B
			{
				NBsys::NWindowMenu::WindowMenu_Window_Text::InitItem t_inititem;
				t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Horizontal;	//���ς݁B
				{
					t_inititem.color = this->color_title_text;
					t_inititem.string = t_title_string;
				}
				this->title_text->Initialize(t_inititem);
			}

			//�^�C�g���h���b�O -> �^�C�g���w�i -> �^�C�g���G���A -> �^�C�g������{�^���B
			{
				NBsys::NWindowMenu::WindowMenu_Window_CloseButton::InitItem t_inititem;
				t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Horizontal;	//���ς݁B
				t_inititem.size.SetW(t_title_h);
				t_inititem.size.SetH(t_title_h);
				{
					t_inititem.color_nomal = this->color_closebutton_nomal;
					t_inititem.color_on = this->color_closebutton_on;
					t_inititem.color_ondown = this->color_closebutton_ondown;
				}
				this->title_closebutton->Initialize(t_inititem);
			}
		}
	}

	/** �A�N�e�B�u�ύX�B
	*/
	void WindowMenu_Window_Window::CallBack_ChangeActive(bool a_active)
	{
		if(a_active){
			this->title_bg->color = this->color_title_bg_active;
		}else{
			this->title_bg->color = this->color_title_bg_normal;
		}
	}

}}

