

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
		WindowMenu_Window_Base(a_name,WindowMenu_WindowType::Window),
		is_active(false),
		color_title_bg_normal(NBsys::NColor::Color_F(1.0f,1.0f,1.0f,1.0f)),
		color_title_bg_active(NBsys::NColor::Color_F(1.0f,1.0f,1.0f,1.0f))
	{
		//�^�C�g���h���b�O�B
		this->window_title_drag = this->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_Drag>("title_drag");

		//�^�C�g���h���b�O -> �^�C�g���w�i�B
		this->window_title_bg = this->window_title_drag->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_Plate>("title_bg");

		//�^�C�g���h���b�O -> �^�C�g���w�i -> �^�C�g���G���A�B
		this->window_title_area = this->window_title_bg->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_Area>("title_area");

		//�^�C�g���h���b�O -> �^�C�g���w�i -> �^�C�g���G���A -> �^�C�g���e�L�X�g�B
		this->window_title_text = this->window_title_area->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_Text>("title_text");

		//�^�C�g���h���b�O -> �^�C�g���w�i -> �^�C�g���G���A -> �^�C�g������{�^���B
		this->window_title_closebutton = this->window_title_area->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_CloseButton>("title_closebutton");
	}

	/** destructor
	*/
	WindowMenu_Window_Window::~WindowMenu_Window_Window()
	{
	}

	/** Initialize
	*/
	void WindowMenu_Window_Window::Initialize(const WindowMenu_Window_Base::InitItem& a_inititem)
	{
		WindowMenu_Window_Base::Initialize(a_inititem);
		{
			/** color
			*/
			this->color_title_bg_normal = NBsys::NColor::Color_F(1.0f,1.0f,1.0f,1.0f);
			this->color_title_bg_active = NBsys::NColor::Color_F(1.0f,1.0f,1.0f,1.0f);

			//�^�C�g���h���b�O�B
			{
				NBsys::NWindowMenu::WindowMenu_Window_Drag::InitItem t_inititem;
				t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Horizontal;	//���ς݁B
				t_inititem.size.SetW_StretchParent();
				t_inititem.size.SetH(0.0f);
				this->window_title_drag->Initialize(t_inititem);
			}

			//�^�C�g���h���b�O -> �^�C�g���w�i�B
			{
				NBsys::NWindowMenu::WindowMenu_Window_Plate::InitItem t_inititem;
				t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Horizontal;	//���ς݁B
				{
				}
				this->window_title_bg->Initialize(t_inititem);
				{
					this->window_title_bg->color = this->color_title_bg_normal;
					this->window_title_bg->texture_id = -1;
					this->window_title_bg->mouseblock = false;
				}
			}

			//�^�C�g���h���b�O -> �^�C�g���w�i -> �^�C�g���G���A�B
			{
				NBsys::NWindowMenu::WindowMenu_Window_Area::InitItem t_inititem;
				t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Horizontal;	//���ς݁B
				this->window_title_area->Initialize(t_inititem);
			}

			//�^�C�g���h���b�O -> �^�C�g���w�i -> �^�C�g���G���A -> �^�C�g���e�L�X�g�B
			{
				NBsys::NWindowMenu::WindowMenu_Window_Text::InitItem t_inititem;
				t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Horizontal;	//���ς݁B
				this->window_title_text->Initialize(t_inititem);
				{
					this->window_title_text->string = L"";
				}
			}

			//�^�C�g���h���b�O -> �^�C�g���w�i -> �^�C�g���G���A -> �^�C�g������{�^���B
			{
				NBsys::NWindowMenu::WindowMenu_Window_CloseButton::InitItem t_inititem;
				t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Horizontal;	//���ς݁B
				t_inititem.size.SetW(0.0f);
				t_inititem.size.SetH(0.0f);
				this->window_title_closebutton->Initialize(t_inititem);
			}
		}
	}

	/** �A�N�e�B�u�ύX�B
	*/
	void WindowMenu_Window_Window::CallBack_ChangeActive(bool a_active)
	{
		this->is_active = a_active;
		if(this->is_active){
			this->window_title_bg->color = this->color_title_bg_active;
		}else{
			this->window_title_bg->color = this->color_title_bg_normal;
		}
	}

	/** �^�C�g���̍����ݒ�B
	*/
	void WindowMenu_Window_Window::SetTitleHeight(f32 a_h)
	{
		this->window_title_drag->size.SetH(a_h);

		this->window_title_closebutton->size.SetW(a_h);
		this->window_title_closebutton->size.SetH(a_h);
	}

	/** �^�C�g���w�i�̐F�ݒ�B
	*/
	void WindowMenu_Window_Window::SetTitleBgColor(const NBsys::NColor::Color_F& a_color_normal,const NBsys::NColor::Color_F& a_active)
	{
		this->color_title_bg_normal = a_color_normal;
		this->color_title_bg_active = a_active;
		this->CallBack_ChangeActive(this->is_active);
	}

}}

