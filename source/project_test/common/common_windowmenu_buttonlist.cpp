

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief テスト。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../include.h"
#pragma warning(pop)


/** include
*/
#include "./common_windowmenu_buttonlist.h"


/** warning

4710 : この関数はインライン展開のために選択されましたが、コンパイラはインライン展開を実行しませんでした。

*/
#pragma warning(disable:4710)


/** NTest
*/
#if(BSYS_WINDOWMENU_ENABLE)
#pragma warning(push)
#pragma warning(disable:4711)
namespace NTest{namespace NCommon
{
	/** constructor
	*/
	WindowMenu_ButtonList::WindowMenu_ButtonList(f32 a_offset_x,f32 a_offset_y,sharedptr<NBsys::ND3d11::D3d11>& a_d3d11)
		:
		NBsys::NWindowMenu::WindowMenu_Window_Base("WindowMenu_ButtonList"),
		endrequest(false),
		window_texture(),
		d3d11(a_d3d11),
		count(0)
	{
		//自分。
		{
			WindowMenu_Window_Base::InitItem t_inititem;
			t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Free;
			t_inititem.size.SetW(0.0f);
			t_inititem.size.SetH(0.0f);
			this->Initialize(t_inititem);
			{
				this->outrange_mouseevent = true;
			}
		}

		/** ウィンドウ。
		*/
		sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Window> t_window = this->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_Window>("window");

		//ウィンドウ -> ボディー背景。
		sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Plate> t_bodybg = t_window->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_Plate>("bodybg");

		//ウィンドウ。
		{
			NBsys::NWindowMenu::WindowMenu_Window_Window::InitItem t_inititem;
			t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Vertical;	//縦積み。
			t_inititem.offset.Set(a_offset_x,a_offset_y);
			t_inititem.size.SetW(400.0f);
			t_inititem.size.SetH_StretchChild();
			t_window->Initialize(t_inititem);
			{
				t_window->window_title_text->string = L"ボタンリスト";

				t_window->window_title_bg->color = t_window->color_title_bg_normal;
				t_window->window_title_closebutton->color_normal = NBsys::NColor::Color_F(0.3f,0.3f,0.3f,1.0f);
				t_window->window_title_closebutton->color_on = NBsys::NColor::Color_F(0.4f,0.4f,0.4f,1.0f);
				t_window->window_title_closebutton->color_ondown = NBsys::NColor::Color_F(0.3f,0.3f,1.0f,1.0f);
				t_window->window_title_text->color = NBsys::NColor::Color_F(1.0f,1.0f,1.0f,1.0f);

				t_window->SetTitleHeight(16.0f);
				t_window->SetTitleBgColor(NBsys::NColor::Color_F(0.3f,0.3f,0.3f,1.0f),NBsys::NColor::Color_F(0.7f,0.3f,0.3f,1.0f));
			}
		}

		//ウィンドウ -> ボディー背景。
		{
			NBsys::NWindowMenu::WindowMenu_Window_Plate::InitItem t_inititem;
			t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Vertical;	//縦積み。
			t_inititem.size.SetH_StretchChild();
			t_bodybg->Initialize(t_inititem);
			{
				t_bodybg->color = NBsys::NColor::Color_F(0.1f,0.1f,0.1f,1.0f);
				t_bodybg->texture_id = -1;
				t_bodybg->mouseblock = true;
			}
		}
	}


	/** destructor
	*/
	WindowMenu_ButtonList::~WindowMenu_ButtonList()
	{
	}


	/** 削除リクエスト。取得。
	*/
	bool WindowMenu_ButtonList::CallBack_GetDeleteRequest() const
	{
		return this->endrequest;
	}


	/** 削除リクエスト。設定。
	*/
	void WindowMenu_ButtonList::CallBack_SetDeleteRequest()
	{
		this->endrequest = true;
	}


	/** AddButton
	*/
	void WindowMenu_ButtonList::AddButton(const STLWString& a_string,const std::function<void(void)>& a_function)
	{
		//ウィンドウ -> ボディー背景。
		sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Base> t_bodybg = this->FindChild("bodybg");

		this->count++;
		char t_buffer[8];
		STLString t_button_name = VASTRING(t_buffer,sizeof(t_buffer),"button_%d",this->count);

		//ウィンドウ -> ボディー背景 -> ボタン。
		sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Button> t_button = t_bodybg->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_Button>(t_button_name);

		//ウィンドウ -> ボディー背景 -> ボタン。
		{
			NBsys::NWindowMenu::WindowMenu_Window_Button::InitItem t_inititem;
			t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Horizontal;
			t_inititem.size.SetH(100);
			t_button->Initialize(t_inititem);
			{
				t_button->color_normal = NBsys::NColor::Color_F(0.3f,0.3f,0.3f,1.0f);
				t_button->color_on = NBsys::NColor::Color_F(0.4f,0.4f,0.4f,1.0f);
				t_button->color_ondown = NBsys::NColor::Color_F(0.3f,0.3f,1.0f,1.0f);
				t_button->string = a_string;
				t_button->action = a_function;
			}
		}
	}


}}
#pragma warning(pop)
#endif

