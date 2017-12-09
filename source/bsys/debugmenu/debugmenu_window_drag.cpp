

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
#include "./debugmenu.h"
#include "./debugmenu_window_drag.h"


/** NBsys::NDebugMenu
*/
namespace NBsys{namespace NDebugMenu
{
	/** constructor
	*/
	DebugMenu_Window_Drag::DebugMenu_Window_Drag(DebugMenu_Window_Base::Mode::Id a_mode,f32 a_x,f32 a_y,f32 a_w,f32 a_h,f32 a_z)
		:
		drag_flag(false),
		start_x(0.0f),
		start_y(0.0f),
		old_x(0.0f),
		old_y(0.0f)
	{
		this->Initialize(a_mode,a_x,a_y,a_w,a_h,a_z);
	}

	/** destructor
	*/
	DebugMenu_Window_Drag::~DebugMenu_Window_Drag()
	{
	}

	/** Update
	*/
	void DebugMenu_Window_Drag::Update()
	{
		f32 t_x = 0.0f;
		f32 t_y = 0.0f;
		bool t_on_l = false;
		bool t_on_r = false;
		bool t_down_l = false;
		bool t_down_r = false;
		bool t_up_l = false;
		bool t_up_r = false;
		GetSystemInstance()->callback->GetMouse_Callback(t_x,t_y,t_on_l,t_on_r,t_down_l,t_down_r,t_up_l,t_up_r);

		//範囲内チェック。
		bool t_in_range = false;
		if((this->calc_x < t_x)&&(t_x < this->calc_x + this->calc_w)&&(this->calc_y < t_y)&&(t_y < this->calc_y + this->calc_h)){
			t_in_range = true;
		}

		if(this->parent != nullptr){
			if((this->drag_flag == false)&&(t_in_range == true)&&(t_down_l == true)){

				//ドラッグ開始。

				this->drag_flag = true;
				this->start_x = t_x;
				this->start_y = t_y;
				this->old_x = this->parent->offset_x;
				this->old_y = this->parent->offset_y;

			}else if((this->drag_flag == true)&&(t_on_l == true)){

				//ドラッグ中。

				this->parent->offset_x = this->old_x + (t_x - this->start_x);
				this->parent->offset_y = this->old_y + (t_y - this->start_y);
				this->parent->CalcRect(this->parent->calc_parent_x,this->parent->calc_parent_y);

			}else if((this->drag_flag == true)&&(t_on_l == false)){

				//ドラッグ終了。

				this->drag_flag = false;

			}
		}
	}

}}

