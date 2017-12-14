

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
#include "./windowmenu.h"
#include "./windowmenu_window_drag.h"


/** NBsys::NWindowMenu
*/
namespace NBsys{namespace NWindowMenu
{
	/** constructor
	*/
	WindowMenu_Window_Drag::WindowMenu_Window_Drag(WindowMenu_Window_Base::Mode::Id a_mode,const STLString& a_name,f32 a_x,f32 a_y,SizeType::Id a_sizetype_w,f32 a_w,SizeType::Id a_sizetype_h,f32 a_h,s32 a_z)
		:
		WindowMenu_Window_Base(a_name),
		drag_flag(false),
		start_x(0.0f),
		start_y(0.0f),
		old_x(0.0f),
		old_y(0.0f)
	{
		this->Initialize(a_mode,a_x,a_y,a_sizetype_w,a_w,a_sizetype_h,a_h,a_z);
	}

	/** destructor
	*/
	WindowMenu_Window_Drag::~WindowMenu_Window_Drag()
	{
	}

	/** マウス処理。
	*/
	bool WindowMenu_Window_Drag::CallBack_MouseUpdate(WindowMenu_Mouse& a_mouse)
	{
		if(a_mouse.down_l){
			//ドラッグ開始。
			this->drag_flag = true;
			this->start_x = a_mouse.x;
			this->start_y = a_mouse.y;
			this->old_x = this->parent->offset_x;
			this->old_y = this->parent->offset_y;
		}

		return true;
	}

	/** 更新処理。
	*/
	bool WindowMenu_Window_Drag::CallBack_Update()
	{
		if(this->drag_flag == true){
			WindowMenu_Mouse t_mouse = GetSystemInstance()->GetMouse();
			if(t_mouse.on_l){
				//ドラッグ中。
				this->parent->offset_x = this->old_x + (t_mouse.x - this->start_x);
				this->parent->offset_y = this->old_y + (t_mouse.y - this->start_y);

				WindowMenu_Window_Base::CalcRectClear(this->parent->calc_it,0);
				WindowMenu_Window_Base::CalcRect(this->parent);
			}else{
				//ドラッグ終了。
				this->drag_flag = false;
			}
		}

		return true;
	}

}}

