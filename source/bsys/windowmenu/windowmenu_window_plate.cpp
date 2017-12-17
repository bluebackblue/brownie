﻿

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief デバッグメニュー。
*/


/** include
*/
#include <bsys_pch.h>


/** include
*/
#include "../types/types.h"


/** include
*/
#include "../color/color.h"


/** include
*/
#include "./windowmenu.h"
#include "./windowmenu_window_plate.h"


/** NBsys::NWindowMenu
*/
namespace NBsys{namespace NWindowMenu
{
	/** constructor
	*/
	WindowMenu_Window_Plate::WindowMenu_Window_Plate(const STLString& a_name)
		:
		WindowMenu_Window_Base(a_name,WindowMenu_WindowType::Plate),
		color(1.0f,1.0f,1.0f,1.0f),
		texture_id(-1),
		mouseblock(true)
	{
	}

	/** destructor
	*/
	WindowMenu_Window_Plate::~WindowMenu_Window_Plate()
	{
	}

	/** Initialize
	*/
	void WindowMenu_Window_Plate::Initialize(const WindowMenu_Window_Base::InitItem& a_inititem)
	{
		WindowMenu_Window_Base::Initialize(a_inititem);
		{
			/** color
			*/
			this->color = NBsys::NColor::Color_F(1.0f,1.0f,1.0f,1.0f);

			/** texture_id
			*/
			this->texture_id = -1;

			/** mouseblock
			*/
			this->mouseblock = true;
		}
	}

	/** 描画処理。
	*/
	bool WindowMenu_Window_Plate::CallBack_Draw(s32 a_z_sort)
	{
		if((this->calc_w >= 0.0f)&&(this->calc_h >= 0.0f)){
			GetSystemInstance()->GetCallback()->DrawRect_Callback(a_z_sort + this->z_sort,this->calc_x,this->calc_y,this->calc_w,this->calc_h,this->texture_id,this->color);
		}

		return true;
	}

	/** マウス処理。
	*/
	bool WindowMenu_Window_Plate::CallBack_InRangeMouseUpdate(WindowMenu_Mouse& a_mouse)
	{
		//マウス操作を親に伝えない。
		return this->mouseblock;
	}

}}
