

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
	this->Initialize(
		NBsys::NWindowMenu::WindowMenu_Window_Base::Mode::Vertical,	//縦済み。
		a_offset_x,
		a_offset_y,
		NBsys::NWindowMenu::WindowMenu_Window_Base::SizeType::Fix,
		300.0f,
		NBsys::NWindowMenu::WindowMenu_Window_Base::SizeType::StretchChild,
		-1.0f,
		0
	);

	//ドラッグ。
	{
		sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Base> t_drag(new NBsys::NWindowMenu::WindowMenu_Window_Drag(
			NBsys::NWindowMenu::WindowMenu_Window_Base::Mode::Horizontal,
			"title:drag",
			0.0f,
			0.0f,
			NBsys::NWindowMenu::WindowMenu_Window_Base::SizeType::StretchParent,
			-1.0f,
			NBsys::NWindowMenu::WindowMenu_Window_Base::SizeType::Fix,
			50.0f,
			0
		));

		this->AddChild(t_drag);

		//下地。
		{
			NBsys::NColor::Color_F t_color[] = {
				NBsys::NColor::Color_F(1.0f,0.9f,0.9f,1.0f),
				NBsys::NColor::Color_F(0.9f,1.0f,0.9f,1.0f),
			};

			sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Base> t_plate(new NBsys::NWindowMenu::WindowMenu_Window_Plate(
				NBsys::NWindowMenu::WindowMenu_Window_Base::Mode::Free,
				"title:plate",
				0.0f,
				0.0f,
				NBsys::NWindowMenu::WindowMenu_Window_Base::SizeType::StretchParent,
				-1.0f,
				NBsys::NWindowMenu::WindowMenu_Window_Base::SizeType::StretchParent,
				-1.0f,
				t_color[this->id],
				-1,
				0
			));

			t_drag->AddChild(t_plate);
		}

		//閉じるボタン。
		{
			sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Base> t_closebutton(new NBsys::NWindowMenu::WindowMenu_Window_CloseButton(
				NBsys::NWindowMenu::WindowMenu_Window_Base::Mode::Free,
				"title:closebutton",
				0.0f,
				0.0f,
				NBsys::NWindowMenu::WindowMenu_Window_Base::SizeType::Fix,
				50.0f,
				NBsys::NWindowMenu::WindowMenu_Window_Base::SizeType::Fix,
				50.0f,
				0
			));

			t_drag->AddChild(t_closebutton);
		}
	}

	//下地。
	{
		sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Base> t_plate(new NBsys::NWindowMenu::WindowMenu_Window_Plate(
			NBsys::NWindowMenu::WindowMenu_Window_Base::Mode::Vertical,
			"body:plate",
			0.0f,
			0.0f,
			NBsys::NWindowMenu::WindowMenu_Window_Base::SizeType::StretchParent,
			-1.0f,
			NBsys::NWindowMenu::WindowMenu_Window_Base::SizeType::Fix,
			300.0f,
			NBsys::NColor::Color_F(0.5f,0.5f,0.5f,0.5f),
			-1,
			0
		));

		this->AddChild(t_plate);
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

