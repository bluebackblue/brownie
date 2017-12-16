

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
	WindowMenu_Window_Drag::WindowMenu_Window_Drag(const InitItem& a_inititem)
		:
		WindowMenu_Window_Base(a_inititem.name),
		drag_flag(false),
		start_x(0.0f),
		start_y(0.0f),
		old_x(0.0f),
		old_y(0.0f)
	{
		this->Initialize(WindowMenu_Window_Base::InitItem(a_inititem.mode,a_inititem.offset,a_inititem.size,0));
	}

	/** destructor
	*/
	WindowMenu_Window_Drag::~WindowMenu_Window_Drag()
	{
	}

	/** マウス処理。
	*/
	bool WindowMenu_Window_Drag::CallBack_InRangeMouseUpdate(WindowMenu_Mouse& a_mouse)
	{
		if(a_mouse.down_l){
			//ドラッグ開始。
			if(this->parent){
				this->drag_flag = true;
				this->start_x = a_mouse.x;
				this->start_y = a_mouse.y;
				this->old_x = this->parent->offset.x;
				this->old_y = this->parent->offset.y;
			}
		}

		//マウス操作を親に伝えない。
		return true;
	}

	/** 更新処理。
	*/
	void WindowMenu_Window_Drag::CallBack_Update()
	{
		if(this->drag_flag == true){
			WindowMenu_Mouse& t_mouse = GetSystemInstance()->GetMouse();
			if(t_mouse.on_l){
				//ドラッグ中。
				if(this->parent){
					this->parent->offset.x = this->old_x + (t_mouse.x - this->start_x);
					this->parent->offset.y = this->old_y + (t_mouse.y - this->start_y);
					
					this->CallBack_CalcRectClear(this->calc_it,this->calc_child_index);
					this->parent->CalcRect();
				}
			}else{
				//ドラッグ終了。
				this->drag_flag = false;
			}
		}
	}

}}

