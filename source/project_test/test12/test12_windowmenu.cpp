

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
#include "./test12_windowmenu.h"


/** DEF_TEST12
*/
#if defined(DEF_TEST12)

/** constructor
*/
Test12_WindowMenu::Test12_WindowMenu(f32 a_offset_x,f32 a_offset_y,s32 a_id)
	:
	NBsys::NWindowMenu::WindowMenu_Window_Base("Test12_WindowMenu"),
	id(a_id),
	endrequest(false)
{
	//メイン。
	this->Initialize(
		NBsys::NWindowMenu::WindowMenu_Window_Base::Mode::Vertical,
		a_offset_x,
		a_offset_y,
		NBsys::NWindowMenu::WindowMenu_Window_Base::SizeType::Fix,
		300,
		NBsys::NWindowMenu::WindowMenu_Window_Base::SizeType::StretchChild,
		-1.0f,
		0
	);

	f32 t_title_h = 30.0f;

	//タイトル。
	{
		sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Base> t_titledrag(new NBsys::NWindowMenu::WindowMenu_Window_Drag(
			NBsys::NWindowMenu::WindowMenu_Window_Base::Mode::Horizontal,
			"title->drag",
			0.0f,
			0.0f,
			NBsys::NWindowMenu::WindowMenu_Window_Base::SizeType::StretchParent,
			-1,
			NBsys::NWindowMenu::WindowMenu_Window_Base::SizeType::Fix,
			t_title_h,
			0
		));

		this->AddChild(t_titledrag);

		//タイトル背景。
		{
			sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Base> t_titlebg = new NBsys::NWindowMenu::WindowMenu_Window_Plate(
				NBsys::NWindowMenu::WindowMenu_Window_Base::Mode::Horizontal,
				"title",
				0.0f,
				0.0f,
				NBsys::NWindowMenu::WindowMenu_Window_Base::SizeType::StretchParent,
				-1,
				NBsys::NWindowMenu::WindowMenu_Window_Base::SizeType::Fix,
				t_title_h,
				NBsys::NColor::Color_F(1.0f,0.9f,0.9f,1.0f),
				-1,
				false,
				0
			);

			t_titledrag->AddChild(t_titlebg);
		}

		//閉じるボタン。
		{
			sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Base> t_closebutton(new NBsys::NWindowMenu::WindowMenu_Window_CloseButton(
				NBsys::NWindowMenu::WindowMenu_Window_Base::Mode::Free,
				"title->closebutton",
				0.0f,
				0.0f,
				NBsys::NWindowMenu::WindowMenu_Window_Base::SizeType::Fix,
				t_title_h,
				NBsys::NWindowMenu::WindowMenu_Window_Base::SizeType::Fix,
				t_title_h,
				0
			));

			t_titledrag->AddChild(t_closebutton);
		}
	}

	//ボディー。
	{
		sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Base> t_body(new NBsys::NWindowMenu::WindowMenu_Window_Plate(
			NBsys::NWindowMenu::WindowMenu_Window_Base::Mode::Vertical,
			"body",
			0.0f,
			0.0f,
			NBsys::NWindowMenu::WindowMenu_Window_Base::SizeType::StretchParent,
			-1.0f,
			NBsys::NWindowMenu::WindowMenu_Window_Base::SizeType::Fix,
			300.0f,
			NBsys::NColor::Color_F(0.5f,0.5f,0.5f,0.5f),
			-1,
			true,
			0
		));

		this->AddChild(t_body);
	}
}

/** destructor
*/
Test12_WindowMenu::~Test12_WindowMenu()
{
}

/** 削除リクエスト。取得。
*/
bool Test12_WindowMenu::GetDeleteRequest()
{
	return this->endrequest;
}

/** 削除リクエスト。設定。
*/
void Test12_WindowMenu::SetDeleteRequest()
{
	this->endrequest = true;
}

#endif

