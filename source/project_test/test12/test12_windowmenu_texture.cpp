

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief テスト。
*/


/** include
*/
#include "../include.h"


/** include
*/
#include "./test12_windowmenu_texture.h"


/** DEF_TEST12
*/
#if defined(DEF_TEST12)

/** constructor
*/
Test12_WindowMenu_Texture::Test12_WindowMenu_Texture(s32 a_id,const STLWString& a_string,f32 a_offset_x,f32 a_offset_y,sharedptr<NBsys::ND3d11::D3d11>& a_d3d11)
	:
	NBsys::NWindowMenu::WindowMenu_Window_Base(),
	id(a_id),
	endrequest(false),
	titlebg(),
	d3d11(a_d3d11)
{
	//自分。
	{
		WindowMenu_Window_Base::InitItem t_inititem;
		t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Vertical;
		t_inititem.offset.Set(a_offset_x,a_offset_y);
		t_inititem.size.SetW(400.0f);
		t_inititem.size.SetH_StretchChild();
		this->Initialize(t_inititem);
	}

	//タイトルドラッグ。
	sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Drag> t_titledrag = this->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_Drag>();

	//タイトルドラッグ -> タイトル背景。
	this->titlebg = t_titledrag->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_Plate>();

	//タイトルドラッグ -> タイトル背景 -> タイトルラベル。
	sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Text> t_titlelabel = this->titlebg->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_Text>();

	//タイトルドラッグ -> タイトル閉じるボタン。
	sharedptr<NBsys::NWindowMenu::WindowMenu_Window_CloseButton> t_titleclosebutton = t_titledrag->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_CloseButton>();

	//ボディー背景。
	sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Plate> t_bodybg = this->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_Plate>();

	//ボディー背景 -> コントロール。
	sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Area> t_control = t_bodybg->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_Area>();

	//ボディー背景 -> コントロール -> ボタンエリア。
	sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Area> t_buttonarea = t_control->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_Area>();

	//ボディー背景 -> コントロール -> ボタンエリア -> 左ボタン。
	sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Button> t_lbutton = t_buttonarea->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_Button>();

	//ボディー背景 -> コントロール -> ボタンエリア -> 右ボタン。
	sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Button> t_rbutton = t_buttonarea->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_Button>();

	//ボディー背景 -> テクスチャー。
	sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Plate> t_texture = t_bodybg->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_Plate>();
	{
		f32 t_titile_h = 16.0f;
		STLWString t_titile_string = L"Texture";

		//タイトルドラッグ。
		{
			NBsys::NWindowMenu::WindowMenu_Window_Drag::InitItem t_inititem;
			t_inititem.name = "titledrag";
			t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Horizontal;	//横積み。
			t_inititem.size.SetH(t_titile_h);
			t_titledrag->Initialize(t_inititem);
		}

		//タイトルドラッグ -> タイトル背景。
		{
			NBsys::NWindowMenu::WindowMenu_Window_Plate::InitItem t_inititem;
			t_inititem.name = "titledrag->titlebg";
			t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Horizontal;	//横積み。
			{
				t_inititem.color = NBsys::NColor::Color_F(0.3f,0.3f,0.3f,1.0f);
				t_inititem.texture_id = -1;
				t_inititem.mouseblock = false;
			}
			this->titlebg->Initialize(t_inititem);
		}

		//タイトルドラッグ -> タイトル背景 -> タイトルラベル。
		{
			NBsys::NWindowMenu::WindowMenu_Window_Text::InitItem t_inititem;
			t_inititem.name = "titledrag->titlebg->titlelabel";
			t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Horizontal;	//横積み。
			{
				t_inititem.color = NBsys::NColor::Color_F(1.0f,1.0f,1.0f,1.0f);
				t_inititem.string = t_titile_string;
			}
			t_titlelabel->Initialize(t_inititem);
		}

		//タイトルドラッグ -> タイトル閉じるボタン。
		{
			NBsys::NWindowMenu::WindowMenu_Window_CloseButton::InitItem t_inititem;
			t_inititem.name = "titledrag->closebutton";
			t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Horizontal;	//横積み。
			t_inititem.size.SetW(t_titile_h);
			t_inititem.size.SetH(t_titile_h);
			{
				t_inititem.color_nomal = NBsys::NColor::Color_F(0.3f,0.3f,0.3f,1.0f);
				t_inititem.color_on = NBsys::NColor::Color_F(0.4f,0.4f,0.4f,1.0f);
				t_inititem.color_ondown = NBsys::NColor::Color_F(0.3f,0.3f,1.0f,1.0f);
			}
			t_titleclosebutton->Initialize(t_inititem);
		}

		//ボディー背景。
		{
			NBsys::NWindowMenu::WindowMenu_Window_Plate::InitItem t_inititem;
			t_inititem.name = "bodybg";
			t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Vertical;	//縦積み。
			t_inititem.size.SetH_StretchChild();
			{
				t_inititem.color = NBsys::NColor::Color_F(0.1f,0.1f,0.1f,1.0f);
				t_inititem.texture_id = -1;
				t_inititem.mouseblock = true;
			}
			t_bodybg->Initialize(t_inititem);
		}

		//ボディー背景 -> コントロール。
		{
			NBsys::NWindowMenu::WindowMenu_Window_Area::InitItem t_inititem;
			t_inititem.name = "bodybg->control";
			t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Vertical;	//縦積み。
			t_inititem.size.SetH(100);
			{
			}
			t_control->Initialize(t_inititem);
		}

		//ボディー背景 -> コントロール -> ボタンエリア。
		{
			NBsys::NWindowMenu::WindowMenu_Window_Area::InitItem t_inititem;
			t_inititem.name = "bodybg->control->buttonarea";
			t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Horizontal;	//横積み。
			t_inititem.size.SetH(100);
			{
			}
			t_buttonarea->Initialize(t_inititem);
		}

		//ボディー背景 -> コントロール -> ボタンエリア -> 左ボタン。
		{
			NBsys::NWindowMenu::WindowMenu_Window_Button::InitItem t_inititem;
			t_inititem.name = "bodybg->control->buttonarea->lbutton";
			t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Horizontal;	//横積み。
			{
				t_inititem.color_nomal = NBsys::NColor::Color_F(0.3f,0.3f,0.3f,1.0f);
				t_inititem.color_on = NBsys::NColor::Color_F(0.4f,0.4f,0.4f,1.0f);
				t_inititem.color_ondown = NBsys::NColor::Color_F(0.3f,0.3f,1.0f,1.0f);
				t_inititem.string = L"<";
			}
			t_lbutton->Initialize(t_inititem);
		}

		//ボディー背景 -> コントロール -> ボタンエリア -> 右ボタン。
		{
			NBsys::NWindowMenu::WindowMenu_Window_Button::InitItem t_inititem;
			t_inititem.name = "bodybg->control->buttonarea->rbutton";
			t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Horizontal;	//横積み。
			{
				t_inititem.color_nomal = NBsys::NColor::Color_F(0.3f,0.3f,0.3f,1.0f);
				t_inititem.color_on = NBsys::NColor::Color_F(0.4f,0.4f,0.4f,1.0f);
				t_inititem.color_ondown = NBsys::NColor::Color_F(0.3f,0.3f,1.0f,1.0f);
				t_inititem.string = L">";
			}
			t_rbutton->Initialize(t_inititem);
		}

		//ボディー背景 -> テクスチャー。
		{
			NBsys::NWindowMenu::WindowMenu_Window_Plate::InitItem t_inititem;
			t_inititem.name = "bodybg->titlebg";
			t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Horizontal;	//横積み。
			t_inititem.size.SetH(100);
			{
				t_inititem.color = NBsys::NColor::Color_F(1.0f,0.0f,0.0f,1.0f);
				t_inititem.texture_id = -1;
				t_inititem.mouseblock = false;
			}
			t_texture->Initialize(t_inititem);
		}

	}
}

/** destructor
*/
Test12_WindowMenu_Texture::~Test12_WindowMenu_Texture()
{
}

/** 削除リクエスト。取得。
*/
bool Test12_WindowMenu_Texture::CallBack_GetDeleteRequest()
{
	return this->endrequest;
}

/** 削除リクエスト。設定。
*/
void Test12_WindowMenu_Texture::CallBack_SetDeleteRequest()
{
	this->endrequest = true;
}

/** アクティブ変更。
*/
void Test12_WindowMenu_Texture::CallBack_ChangeActive(bool a_active)
{
	if(a_active){
		this->titlebg->color = NBsys::NColor::Color_F(0.7f,0.3f,0.3f,1.0f);
	}else{
		this->titlebg->color = NBsys::NColor::Color_F(0.3f,0.3f,0.3f,1.0f);
	}
}

#endif

