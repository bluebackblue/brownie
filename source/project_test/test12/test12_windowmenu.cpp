

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
		WindowMenu_Window_Base::InitItem(
			NBsys::NWindowMenu::WindowMenu_Mode::Vertical,
			NBsys::NWindowMenu::WindowMenu_Offset(a_offset_x,a_offset_y),
			NBsys::NWindowMenu::WindowMenu_Size(
				NBsys::NWindowMenu::WindowMenu_SizeType::Fix,
				300.0f,
				NBsys::NWindowMenu::WindowMenu_SizeType::StretchChild,
				-1.0f
			),
			0
		)
	);

	f32 t_title_h = 30.0f;
	if(a_id == 1){
		t_title_h = 60.0f;
	}


	//タイトル。
	{
		NBsys::NWindowMenu::WindowMenu_Window_Drag::InitItem t_titledrag_inititem(
			NBsys::NWindowMenu::WindowMenu_Mode::Horizontal,
			"title->drag",
			NBsys::NWindowMenu::WindowMenu_Offset(0.0f,0.0f),
			NBsys::NWindowMenu::WindowMenu_Size(
				NBsys::NWindowMenu::WindowMenu_SizeType::StretchParent,
				-1.0f,
				NBsys::NWindowMenu::WindowMenu_SizeType::Fix,
				t_title_h
			)
		);
		sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Base> t_titledrag(new NBsys::NWindowMenu::WindowMenu_Window_Drag(t_titledrag_inititem));
		this->AddChild(t_titledrag);

		//タイトル背景。
		{
			NBsys::NWindowMenu::WindowMenu_Window_Plate::InitItem t_plate_inititem(
				NBsys::NWindowMenu::WindowMenu_Mode::Horizontal,
				"title",
				NBsys::NWindowMenu::WindowMenu_Offset(0.0f,0.0f),
				NBsys::NWindowMenu::WindowMenu_Size(
					NBsys::NWindowMenu::WindowMenu_SizeType::StretchParent,
					-1.0f,
					NBsys::NWindowMenu::WindowMenu_SizeType::Fix,
					t_title_h
				),
				NBsys::NColor::Color_F(1.0f,0.9f,0.9f,1.0f),
				-1,
				false
			);
			sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Base> t_titlebg = new NBsys::NWindowMenu::WindowMenu_Window_Plate(t_plate_inititem);
			t_titledrag->AddChild(t_titlebg);
		}

		//閉じるボタン。
		{
			NBsys::NWindowMenu::WindowMenu_Window_CloseButton::InitItem t_closebutton_inititem(
				NBsys::NWindowMenu::WindowMenu_Mode::Free,
				"title->closebutton",
				NBsys::NWindowMenu::WindowMenu_Offset(0.0f,0.0f),
				NBsys::NWindowMenu::WindowMenu_Size(
					NBsys::NWindowMenu::WindowMenu_SizeType::Fix,
					t_title_h,
					NBsys::NWindowMenu::WindowMenu_SizeType::Fix,
					t_title_h
				)
			);
			sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Base> t_closebutton(new NBsys::NWindowMenu::WindowMenu_Window_CloseButton(t_closebutton_inititem));
			t_titledrag->AddChild(t_closebutton);
		}
	}

	//ボディー。
	{
		NBsys::NWindowMenu::WindowMenu_Window_Plate::InitItem t_body_inititem(
			NBsys::NWindowMenu::WindowMenu_Mode::Vertical,
			"body",
			NBsys::NWindowMenu::WindowMenu_Offset(0.0f,0.0f),
			NBsys::NWindowMenu::WindowMenu_Size(
				NBsys::NWindowMenu::WindowMenu_SizeType::StretchParent,
				-1.0f,
				NBsys::NWindowMenu::WindowMenu_SizeType::Fix,
				300.0f
			),
			NBsys::NColor::Color_F(0.5f,0.5f,0.5f,0.5f),
			-1,
			true
		);
		sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Base> t_body(new NBsys::NWindowMenu::WindowMenu_Window_Plate(t_body_inititem));
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

