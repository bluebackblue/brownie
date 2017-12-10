#pragma once

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


/** DEF_TEST12
*/
#if defined(DEF_TEST12)

/** Test12_WindowMenu
*/
class Test12_WindowMenu : public NBsys::NWindowMenu::WindowMenu_Window_Base
{
public:
	/** constructor
	*/
	Test12_WindowMenu(f32 a_offset_x,f32 a_offset_y);

	/** destructor
	*/
	virtual ~Test12_WindowMenu();
};

#endif

