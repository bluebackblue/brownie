

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
	WindowMenu_Window_CloseButton::WindowMenu_Window_CloseButton(const InitItem& a_inititem)
		:
		WindowMenu_Window_Base(a_inititem.name),
		push_flag(false),
		on_flag(false)
	{
		this->Initialize(WindowMenu_Window_Base::InitItem(a_inititem.mode,a_inititem.offset,a_inititem.size,0));
	}

	/** destructor
	*/
	WindowMenu_Window_CloseButton::~WindowMenu_Window_CloseButton()
	{
	}

	/** マウス処理。
	*/
	bool WindowMenu_Window_CloseButton::CallBack_InRangeMouseUpdate(WindowMenu_Mouse& a_mouse)
	{
		if(a_mouse.down_l){
			//プッシュ開始。
			this->push_flag = true;
		}

		//マウスがボタンの上。
		this->on_flag = true;

		//マウス操作を親に伝えない。
		return true;
	}

	/** 更新処理。
	*/
	bool WindowMenu_Window_CloseButton::CallBack_Update()
	{
		if(this->push_flag == true){
			WindowMenu_Mouse& t_mouse = GetSystemInstance()->GetMouse();
			if(t_mouse.up_l){
				this->push_flag = false;
				if(this->IsRange(t_mouse.x,t_mouse.y)){
					//プッシュ確定。
					this->SetDeleteRequest();
				}else{
					//プッシュキャンセル。
				}
			}
		}

		if(this->on_flag == true){
			WindowMenu_Mouse& t_mouse = GetSystemInstance()->GetMouse();

			//マウスがボタンの上。
			this->on_flag = this->IsRange(t_mouse.x,t_mouse.y);
		}

		return true;
	}

	/** 描画処理。
	*/
	bool WindowMenu_Window_CloseButton::CallBack_Draw(s32 a_z_sort)
	{
		if((this->calc_w >= 0.0f)&&(this->calc_h >= 0.0f)){

			s32 t_color_index = 0;

			NBsys::NColor::Color_F t_color_list[] = {
				NBsys::NColor::Color_F(0.3f,0.3f,0.3f,1.0f),	//通常。
				NBsys::NColor::Color_F(0.4f,0.4f,0.4f,1.0f),	//マウスがボタンの上。
				NBsys::NColor::Color_F(0.3f,0.3f,1.0f,1.0f)		//マウスがボタンの上＆マウスダウン中。
			};

			NBsys::NColor::Color_F t_font_color(1.0f,1.0f,1.0f,1.0f);

			if((this->push_flag == true)&&(this->on_flag == true)){
				t_color_index = 2;
			}else if(this->on_flag == true){
				t_color_index = 1;
			}

			f32 t_font_size = 16.0f;
			s32 t_font_texture_index = 2;

			f32 t_offst_x = (this->calc_w - t_font_size) / 2;
			f32 t_offst_y = (this->calc_w - t_font_size) / 2;

			GetSystemInstance()->GetCallback()->DrawRect_Callback(a_z_sort + this->z_sort,this->calc_x,this->calc_y,this->calc_w,this->calc_h,-1,t_color_list[t_color_index]);
			GetSystemInstance()->GetCallback()->DrawFont_Callback(a_z_sort + this->z_sort+1,this->calc_x + t_offst_x,this->calc_y + t_offst_y,t_font_size,t_font_texture_index,t_font_color,L"ｘ");
		}

		return true;
	}
}}

