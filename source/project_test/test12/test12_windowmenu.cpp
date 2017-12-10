

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
Test12_WindowMenu::Test12_WindowMenu(f32 a_offset_x,f32 a_offset_y)
	:
	NBsys::NWindowMenu::WindowMenu_Window_Base()
{
	this->Initialize(
		NBsys::NWindowMenu::WindowMenu_Window_Base::Mode::Vertical,
		a_offset_x,
		a_offset_y,
		300.0f,
		-1.0f,
		0
	);

	//ドラッグ。
	{
		sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Base> t_drag(new NBsys::NWindowMenu::WindowMenu_Window_Drag(
			NBsys::NWindowMenu::WindowMenu_Window_Base::Mode::Vertical,
			0.0f,
			0.0f,
			-1.0f,
			50.0f,
			0
		));

		this->AddChild(t_drag);

		//下地。
		{
			sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Base> t_plate(new NBsys::NWindowMenu::WindowMenu_Window_Plate(
				NBsys::NWindowMenu::WindowMenu_Window_Base::Mode::Vertical,
				0.0f,
				0.0f,
				-1.0f,
				-1.0f,
				NBsys::NColor::Color_F(1.0f,1.0f,1.0f,1.0f),
				-1,
				0
			));

			t_drag->AddChild(t_plate);
		}
	}

	//下地。
	{
		sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Base> t_plate(new NBsys::NWindowMenu::WindowMenu_Window_Plate(
			NBsys::NWindowMenu::WindowMenu_Window_Base::Mode::Vertical,
			0.0f,
			0.0f,
			-1.0f,
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

#endif

