

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
#include "./debugmenu.h"
#include "./debugmenu_window_plate.h"


/** NBsys::NDebugMenu
*/
namespace NBsys{namespace NDebugMenu
{
	/** constructor
	*/
	DebugMenu_Window_Plate::DebugMenu_Window_Plate(DebugMenu_Window_Base::Mode::Id a_mode,f32 a_x,f32 a_y,f32 a_w,f32 a_h,f32 a_z)
	{
		this->Initialize(a_mode,a_x,a_y,a_w,a_h,a_z);
	}

	/** destructor
	*/
	DebugMenu_Window_Plate::~DebugMenu_Window_Plate()
	{
	}

	/** Draw
	*/
	void DebugMenu_Window_Plate::Draw()
	{
		//自分の描画。
		{
			if((this->calc_w >= 0.0f)&&(this->calc_h >= 0.0f)){
				GetSystemInstance()->callback->DrawRect_Callback(this->calc_x,this->calc_y,this->calc_w,this->calc_h,0.0f,-1,NBsys::NColor::Color_F(0.6f,0.6f,0.6f,1.0f));
			}
		}

		//子の描画。
		DebugMenu_Window_Base::Draw();
	}

}}

