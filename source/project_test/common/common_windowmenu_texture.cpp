

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief テスト。
*/


/** include
*/
#include "../include.h"


/** include
*/
#include "./common_windowmenu_texture.h"


/** NTest
*/
#if(BSYS_WINDOWMENU_ENABLE)
namespace NTest{namespace NCommon
{
	/** constructor
	*/
	WindowMenu_Texture::WindowMenu_Texture(f32 a_offset_x,f32 a_offset_y,sharedptr<NBsys::ND3d11::D3d11>& a_d3d11)
		:
		NBsys::NWindowMenu::WindowMenu_Window_Base("WindowMenu_Texture"),
		endrequest(false),
		window_texture(),
		d3d11(a_d3d11)
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

		//ウィンドウ -> ボディー背景 -> コントロール。
		sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Area> t_control = t_bodybg->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_Area>("control");

		//ウィンドウ -> ボディー背景 -> コントロール -> ボタンエリア。
		sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Area> t_buttonarea = t_control->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_Area>("buttonarea");

		//ウィンドウ -> ボディー背景 -> コントロール -> ボタンエリア -> 左ボタン。
		sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Button> t_lbutton = t_buttonarea->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_Button>("lbutton");

		//ウィンドウ -> ボディー背景 -> コントロール -> ボタンエリア -> 右ボタン。
		sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Button> t_rbutton = t_buttonarea->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_Button>("rbutton");

		//ウィンドウ -> ボディー背景 -> テクスチャー。
		sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Plate> t_texture = t_bodybg->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_Plate>("texture");

		//ウィンドウ。
		{
			NBsys::NWindowMenu::WindowMenu_Window_Window::InitItem t_inititem;
			t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Vertical;	//縦積み。
			t_inititem.offset.Set(a_offset_x,a_offset_y);
			t_inititem.size.SetW(400.0f);
			t_inititem.size.SetH_StretchChild();
			t_window->Initialize(t_inititem);
			{
				t_window->window_title_text->string = L"テクスチャー";

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

		//ウィンドウ -> ボディー背景 -> コントロール。
		{
			NBsys::NWindowMenu::WindowMenu_Window_Area::InitItem t_inititem;
			t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Vertical;	//縦積み。
			t_inititem.size.SetH(32.0f);
			t_control->Initialize(t_inititem);
		}

		//ウィンドウ -> ボディー背景 -> コントロール -> ボタンエリア。
		{
			NBsys::NWindowMenu::WindowMenu_Window_Area::InitItem t_inititem;
			t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Horizontal;	//横積み。
			t_buttonarea->Initialize(t_inititem);
		}

		//ウィンドウ -> ボディー背景 -> コントロール -> ボタンエリア -> 左ボタン。
		{
			NBsys::NWindowMenu::WindowMenu_Window_Button::InitItem t_inititem;
			t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Horizontal;	//横積み。
			t_lbutton->Initialize(t_inititem);
			{
				t_lbutton->color_normal = NBsys::NColor::Color_F(0.3f,0.3f,0.3f,1.0f);
				t_lbutton->color_on = NBsys::NColor::Color_F(0.4f,0.4f,0.4f,1.0f);
				t_lbutton->color_ondown = NBsys::NColor::Color_F(0.3f,0.3f,1.0f,1.0f);
				t_lbutton->string = L"<<<<<<<<<";
				t_lbutton->action = std::bind(&WindowMenu_Texture::PushLeftButton,this);
			}
		}

		//ウィンドウ -> ボディー背景 -> コントロール -> ボタンエリア -> 右ボタン。
		{
			NBsys::NWindowMenu::WindowMenu_Window_Button::InitItem t_inititem;
			t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Horizontal;	//横積み。
			t_rbutton->Initialize(t_inititem);
			{
				t_rbutton->color_normal = NBsys::NColor::Color_F(0.3f,0.3f,0.3f,1.0f);
				t_rbutton->color_on = NBsys::NColor::Color_F(0.4f,0.4f,0.4f,1.0f);
				t_rbutton->color_ondown = NBsys::NColor::Color_F(0.3f,0.3f,1.0f,1.0f);
				t_rbutton->string = L">>>>>>>>>";
				t_rbutton->action = std::bind(&WindowMenu_Texture::PushRightButton,this);
			}
		}

		//ウィンドウ -> ボディー背景 -> テクスチャー。
		{
			NBsys::NWindowMenu::WindowMenu_Window_Plate::InitItem t_inititem;
			t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Horizontal;	//横積み。
			t_inititem.size.SetH(400);
			t_texture->Initialize(t_inititem);
			{
				t_texture->color = NBsys::NColor::Color_F(1.0f,1.0f,1.0f,1.0f);
				t_texture->texture_id = -1;
				t_texture->mouseblock = true;
			}
			this->window_texture = t_texture;
		}
	}


	/** destructor
	*/
	WindowMenu_Texture::~WindowMenu_Texture()
	{
	}


	/** 削除リクエスト。取得。
	*/
	bool WindowMenu_Texture::CallBack_GetDeleteRequest()
	{
		return this->endrequest;
	}


	/** 削除リクエスト。設定。
	*/
	void WindowMenu_Texture::CallBack_SetDeleteRequest()
	{
		this->endrequest = true;
	}


	/** 左ボタン。
	*/
	void WindowMenu_Texture::PushLeftButton()
	{
		STLVector<s32>::Type t_list;
		this->d3d11->CreateTextureIdList(t_list);
		if(t_list.size() <= 0){
			this->window_texture->texture_id = -1;
			return;
		}

		std::sort(t_list.begin(),t_list.end());

		if(this->window_texture->texture_id < 0){
			this->window_texture->texture_id = *t_list.begin();
			return;
		}

		s32 t_texture_id = this->window_texture->texture_id;
		STLVector<s32>::const_iterator t_it_end = t_list.end();
		for(STLVector<s32>::const_iterator t_it = t_list.begin();t_it != t_it_end;++t_it){
			if(t_texture_id < *t_it){
				this->window_texture->texture_id = *t_it;
				return;
			}
		}

		this->window_texture->texture_id = *t_list.begin();
		return;
	}


	/** 右ボタン。
	*/
	void WindowMenu_Texture::PushRightButton()
	{
		STLVector<s32>::Type t_list;
		this->d3d11->CreateTextureIdList(t_list);
		if(t_list.size() <= 0){
			this->window_texture->texture_id = -1;
			return;
		}

		std::sort(t_list.begin(),t_list.end(),std::greater<int>());

		if(this->window_texture->texture_id < 0){
			this->window_texture->texture_id = *t_list.begin();
			return;
		}

		s32 t_texture_id = this->window_texture->texture_id;
		STLVector<s32>::const_iterator t_it_end = t_list.end();
		for(STLVector<s32>::const_iterator t_it = t_list.begin();t_it != t_it_end;++t_it){
			if(t_texture_id > *t_it){
				this->window_texture->texture_id = *t_it;
				return;
			}
		}

		this->window_texture->texture_id = *t_list.begin();
		return;
	}


}}
#endif

