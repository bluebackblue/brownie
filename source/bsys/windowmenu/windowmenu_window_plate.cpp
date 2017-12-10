

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
	WindowMenu_Window_Plate::WindowMenu_Window_Plate(WindowMenu_Window_Base::Mode::Id a_mode,f32 a_x,f32 a_y,f32 a_w,f32 a_h,const NBsys::NColor::Color_F& a_color,s32 a_texture_id,s32 a_z)
		:
		color(a_color),
		texture_id(a_texture_id)
	{
		this->Initialize(a_mode,a_x,a_y,a_w,a_h,a_z);
	}

	/** destructor
	*/
	WindowMenu_Window_Plate::~WindowMenu_Window_Plate()
	{
	}

	/** Draw
	*/
	void WindowMenu_Window_Plate::Draw()
	{
		//自分の描画。
		{
			if((this->calc_w >= 0.0f)&&(this->calc_h >= 0.0f)){
				GetSystemInstance()->callback->DrawRect_Callback(this->z,this->calc_x,this->calc_y,this->calc_w,this->calc_h,this->texture_id,this->color);
			}
		}

		//子の描画。
		WindowMenu_Window_Base::Draw();
	}
}}

