

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief デバッグメニュー。
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
		title_h(16.0f),
		title_string(L""),
		color_title_bg_normal(NBsys::NColor::Color_F(1.0f,1.0f,1.0f,1.0f)),
		color_title_bg_active(NBsys::NColor::Color_F(1.0f,1.0f,1.0f,1.0f))
	{
		//タイトルドラッグ。
		this->window_title_drag = this->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_Drag>("title_drag");

		//タイトルドラッグ -> タイトル背景。
		this->window_title_bg = this->window_title_drag->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_Plate>("title_bg");

		//タイトルドラッグ -> タイトル背景 -> タイトルエリア。
		this->window_title_area = this->window_title_bg->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_Area>("title_area");

		//タイトルドラッグ -> タイトル背景 -> タイトルエリア -> タイトルテキスト。
		this->window_title_text = this->window_title_area->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_Text>("title_text");

		//タイトルドラッグ -> タイトル背景 -> タイトルエリア -> タイトル閉じるボタン。
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
			/** title_h
			*/
			this->title_h = 16.0f;

			/** title_string
			*/
			this->title_string = L"";

			/** color
			*/
			this->color_title_bg_normal = NBsys::NColor::Color_F(1.0f,1.0f,1.0f,1.0f);
			this->color_title_bg_active = NBsys::NColor::Color_F(1.0f,1.0f,1.0f,1.0f);

			//タイトルドラッグ。
			{
				NBsys::NWindowMenu::WindowMenu_Window_Drag::InitItem t_inititem;
				t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Horizontal;	//横積み。
				t_inititem.size.SetW_StretchParent();
				t_inititem.size.SetH(this->title_h);
				this->window_title_drag->Initialize(t_inititem);
			}

			//タイトルドラッグ -> タイトル背景。
			{
				NBsys::NWindowMenu::WindowMenu_Window_Plate::InitItem t_inititem;
				t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Horizontal;	//横積み。
				{
				}
				this->window_title_bg->Initialize(t_inititem);
				{
					this->window_title_bg->color = this->color_title_bg_normal;
					this->window_title_bg->texture_id = -1;
					this->window_title_bg->mouseblock = false;
				}
			}

			//タイトルドラッグ -> タイトル背景 -> タイトルエリア。
			{
				NBsys::NWindowMenu::WindowMenu_Window_Area::InitItem t_inititem;
				t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Horizontal;	//横積み。
				this->window_title_area->Initialize(t_inititem);
			}

			//タイトルドラッグ -> タイトル背景 -> タイトルエリア -> タイトルテキスト。
			{
				NBsys::NWindowMenu::WindowMenu_Window_Text::InitItem t_inititem;
				t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Horizontal;	//横積み。
				this->window_title_text->Initialize(t_inititem);
				{
					this->window_title_text->string = this->title_string;
				}
			}

			//タイトルドラッグ -> タイトル背景 -> タイトルエリア -> タイトル閉じるボタン。
			{
				NBsys::NWindowMenu::WindowMenu_Window_CloseButton::InitItem t_inititem;
				t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Horizontal;	//横積み。
				t_inititem.size.SetW(this->title_h);
				t_inititem.size.SetH(this->title_h);
				this->window_title_closebutton->Initialize(t_inititem);
			}
		}
	}

	/** アクティブ変更。
	*/
	void WindowMenu_Window_Window::CallBack_ChangeActive(bool a_active)
	{
		if(a_active){
			this->window_title_bg->color = this->color_title_bg_active;
		}else{
			this->window_title_bg->color = this->color_title_bg_normal;
		}
	}

}}

