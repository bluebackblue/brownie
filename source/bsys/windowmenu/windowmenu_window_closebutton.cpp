

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
#include "./windowmenu_window_closebutton.h"


/** NBsys::NWindowMenu
*/
namespace NBsys{namespace NWindowMenu
{
	/** constructor
	*/
	WindowMenu_Window_CloseButton::WindowMenu_Window_CloseButton(WindowMenu_Window_Base::Mode::Id a_mode,const STLString& a_name,f32 a_x,f32 a_y,SizeType::Id a_sizetype_w,f32 a_w,SizeType::Id a_sizetype_h,f32 a_h,s32 a_z)
		:
		WindowMenu_Window_Base(a_name)
	{
		this->Initialize(a_mode,a_x,a_y,a_sizetype_w,a_w,a_sizetype_h,a_h,a_z);
	}

	/** destructor
	*/
	WindowMenu_Window_CloseButton::~WindowMenu_Window_CloseButton()
	{
	}

	/** マウス処理。
	*/
	bool WindowMenu_Window_CloseButton::CallBack_MouseUpdate(WindowMenu_Mouse& a_mouse)
	{
		if(a_mouse.down_l){

			//プッシュ開始。
			this->push_flag = true;

		}

		return true;
	}

	/** 更新処理。
	*/
	bool WindowMenu_Window_CloseButton::CallBack_Update()
	{
		if(this->push_flag == true){
			WindowMenu_Mouse t_mouse = GetSystemInstance()->GetMouse();
			if(t_mouse.up_l){
				this->push_flag = false;
				if(this->IsRange(t_mouse.x,t_mouse.y)){
					this->SetDeleteRequest();
				}
			}
		}

		return true;
	}

	/** 描画処理。
	*/
	bool WindowMenu_Window_CloseButton::CallBack_Draw()
	{
		if((this->calc_w >= 0.0f)&&(this->calc_h >= 0.0f)){
			GetSystemInstance()->GetCallback()->DrawRect_Callback(this->z,this->calc_x,this->calc_y,this->calc_w,this->calc_h,-1,NBsys::NColor::Color_F(0.6f,0.6f,0.6f,1.0f));
		}

		return true;
	}
}}

