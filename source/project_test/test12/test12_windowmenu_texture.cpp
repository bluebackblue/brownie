

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


	#if(0)

	//ボディー。
	{
		NBsys::NWindowMenu::WindowMenu_Window_Plate::InitItem t_body_inititem(
			NBsys::NWindowMenu::WindowMenu_Mode::Vertical,
			"body",
			NBsys::NWindowMenu::WindowMenu_Offset(0.0f,0.0f),
			NBsys::NWindowMenu::WindowMenu_Size(
				NBsys::NWindowMenu::WindowMenu_SizeType::StretchParent,
				-1.0f,
				NBsys::NWindowMenu::WindowMenu_SizeType::StretchChild,
				1024.0f
			)
		);
		{
			t_body_inititem.mouseblock = true;
			t_body_inititem.texture_id = -1;
			t_body_inititem.color = NBsys::NColor::Color_F(0.1f,0.1f,0.1f,1.0f);
		}
		sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Base> t_body(new NBsys::NWindowMenu::WindowMenu_Window_Plate(t_body_inititem));
		this->AddChild(t_body);

		//コントロール。
		{
			NBsys::NWindowMenu::WindowMenu_Window_Area::InitItem t_control_inititem(
				NBsys::NWindowMenu::WindowMenu_Mode::Vertical,
				"control",
				NBsys::NWindowMenu::WindowMenu_Offset(0.0f,0.0f),
				NBsys::NWindowMenu::WindowMenu_Size(
					NBsys::NWindowMenu::WindowMenu_SizeType::StretchParent,
					-1.0f,
					NBsys::NWindowMenu::WindowMenu_SizeType::Fix,
					100.0f
				)
			);
			sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Base> t_control(new NBsys::NWindowMenu::WindowMenu_Window_Area(t_control_inititem));
			t_body->AddChild(t_control);

			//ボタン。
			{
				NBsys::NWindowMenu::WindowMenu_Window_Button::InitItem t_controlbutton_inititem(
					NBsys::NWindowMenu::WindowMenu_Mode::Vertical,
					"controlbutton",
					NBsys::NWindowMenu::WindowMenu_Offset(0.0f,0.0f),
					NBsys::NWindowMenu::WindowMenu_Size(
						NBsys::NWindowMenu::WindowMenu_SizeType::StretchParent,
						-1.0f,
						NBsys::NWindowMenu::WindowMenu_SizeType::Fix,
						30.0f
					)
				);
				{
					t_controlbutton_inititem.color_nomal = NBsys::NColor::Color_F(0.3f,0.3f,0.3f,1.0f);
					t_controlbutton_inititem.color_on = NBsys::NColor::Color_F(0.4f,0.4f,0.4f,1.0f);
					t_controlbutton_inititem.color_ondown = NBsys::NColor::Color_F(0.3f,0.3f,1.0f,1.0f);
					t_controlbutton_inititem.string = L"あいうえお";
				}
				sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Base> t_controlbutton(new NBsys::NWindowMenu::WindowMenu_Window_Button(t_controlbutton_inititem));
				t_control->AddChild(t_controlbutton);
			}
		}

		//テクスチャ。
		{
			NBsys::NWindowMenu::WindowMenu_Window_Plate::InitItem t_texture_inititem(
				NBsys::NWindowMenu::WindowMenu_Mode::Vertical,
				"texture",
				NBsys::NWindowMenu::WindowMenu_Offset(0.0f,0.0f),
				NBsys::NWindowMenu::WindowMenu_Size(
					NBsys::NWindowMenu::WindowMenu_SizeType::StretchParent,
					-1.0f,
					NBsys::NWindowMenu::WindowMenu_SizeType::Fix,
					128.0f
				)
			);
			{
				t_texture_inititem.mouseblock = true;
				t_texture_inititem.texture_id = this->d3d11->Render_GetFontTexture(0);
				t_texture_inititem.color = NBsys::NColor::Color_F(1.0f,0.0f,0.0f,1.0f);
			}
			sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Base> t_texture(new NBsys::NWindowMenu::WindowMenu_Window_Plate(t_texture_inititem));
			t_body->AddChild(t_texture);
		}
	}

	#endif
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
	/*
	if(a_active){
		this->titlebg->color = NBsys::NColor::Color_F(0.7f,0.3f,0.3f,1.0f);
	}else{
		this->titlebg->color = NBsys::NColor::Color_F(0.3f,0.3f,0.3f,1.0f);
	}
	*/
}

#endif

