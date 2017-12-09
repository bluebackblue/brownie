

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief インクルード。
*/


/** include
*/
#include "../include.h"


/** include
*/
#include "./test12_debugwindow.h"


/** DEF_TEST12
*/
#if defined(DEF_TEST12)

/** constructor
*/
Test12_DebugWindow::Test12_DebugWindow(f32 a_offset_x,f32 a_offset_y)
	:
	NBsys::NDebugMenu::DebugMenu_Window_Base()
{
	this->Initialize(
		NBsys::NDebugMenu::DebugMenu_Window_Base::Mode::Vertical,
		a_offset_x,
		a_offset_y,
		300.0f,
		300.0f,
		0.0f
	);

	//ドラッグ。
	{
		sharedptr<NBsys::NDebugMenu::DebugMenu_Window_Base> t_drag(new NBsys::NDebugMenu::DebugMenu_Window_Drag(
			NBsys::NDebugMenu::DebugMenu_Window_Base::Mode::Vertical,
			0.0f,
			0.0f,
			-1.0f,
			-1.0f,
			0.0f
		));

		this->AddChild(t_drag);

		//下地。
		{
			sharedptr<NBsys::NDebugMenu::DebugMenu_Window_Base> t_plate(new NBsys::NDebugMenu::DebugMenu_Window_Plate(
				NBsys::NDebugMenu::DebugMenu_Window_Base::Mode::Vertical,
				0.0f,
				0.0f,
				-1.0f,
				-1.0f,
				0.0f
			));

			t_drag->AddChild(t_plate);
		}
	}


}

/** destructor
*/
Test12_DebugWindow::~Test12_DebugWindow()
{
}

#endif

