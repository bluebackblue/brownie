

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
	WindowMenu_Window_Plate::WindowMenu_Window_Plate(WindowMenu_Window_Base::Mode::Id a_mode,const STLString& a_name,f32 a_x,f32 a_y,f32 a_w,f32 a_h,const NBsys::NColor::Color_F& a_color,s32 a_texture_id,s32 a_z)
		:
		WindowMenu_Window_Base(a_name),
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

	/** 描画処理。
	*/
	bool WindowMenu_Window_Plate::CallBack_Draw()
	{
		if((this->calc_w >= 0.0f)&&(this->calc_h >= 0.0f)){
			GetSystemInstance()->GetCallback()->DrawRect_Callback(this->z,this->calc_x,this->calc_y,this->calc_w,this->calc_h,this->texture_id,this->color);
		}

		return true;
	}
}}

