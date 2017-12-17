

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
	WindowMenu_Window_CloseButton::WindowMenu_Window_CloseButton(const STLString& a_name)
		:
		WindowMenu_Window_Base(a_name,WindowMenu_WindowType::CloseButton),
		push_flag(false),
		on_flag(false),
		color_nomal(NBsys::NColor::Color_F(1.0f,1.0f,1.0f,1.0f)),
		color_on(NBsys::NColor::Color_F(1.0f,1.0f,1.0f,1.0f)),
		color_ondown(NBsys::NColor::Color_F(1.0f,1.0f,1.0f,1.0f)),
		space(1.0f)
	{
	}

	/** destructor
	*/
	WindowMenu_Window_CloseButton::~WindowMenu_Window_CloseButton()
	{
	}

	/** Initialize
	*/
	void WindowMenu_Window_CloseButton::Initialize(const InitItem& a_inititem)
	{
		WindowMenu_Window_Base::InitItem t_inititem;
		{
			t_inititem.mode = a_inititem.mode;
			t_inititem.offset = a_inititem.offset;
			t_inititem.size = a_inititem.size;
		}
		WindowMenu_Window_Base::Initialize(t_inititem);
		{
			this->push_flag = false;
			this->on_flag = false;

			this->color_nomal = a_inititem.color_nomal;
			this->color_on = a_inititem.color_on;
			this->color_ondown = a_inititem.color_ondown;

			this->space = a_inititem.space;
		}
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
	void WindowMenu_Window_CloseButton::CallBack_Update()
	{
		if(this->push_flag == true){
			WindowMenu_Mouse& t_mouse = GetSystemInstance()->GetMouse();
			if(t_mouse.up_l){
				this->push_flag = false;
				if(this->IsRange(t_mouse.x,t_mouse.y)){
					//プッシュ確定。
					this->CallBack_SetDeleteRequest();
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
	}

	/** 描画処理。
	*/
	bool WindowMenu_Window_CloseButton::CallBack_Draw(s32 a_z_sort)
	{
		if((this->calc_w >= 0.0f)&&(this->calc_h >= 0.0f)){

			s32 t_color_index = 0;

			NBsys::NColor::Color_F* t_color_list[] = {
				&this->color_nomal,
				&this->color_on,
				&this->color_ondown,
			};

			NBsys::NColor::Color_F t_font_color(1.0f,1.0f,1.0f,1.0f);

			if((this->push_flag == true)&&(this->on_flag == true)){
				t_color_index = 2;
			}else if(this->on_flag == true){
				t_color_index = 1;
			}

			GetSystemInstance()->GetCallback()->DrawRect_Callback(a_z_sort + this->z_sort,this->calc_x + this->space,this->calc_y + this->space,this->calc_w - this->space * 2,this->calc_h - this->space * 2,-1,*t_color_list[t_color_index]);

			//TODO:×ボタンをフォントで表現。
			{
				f32 t_font_size = 16.0f;
				s32 t_font_texture_index = 2;

				//L"x"
				f32 t_fontdata_x = 4;
				f32 t_fontdata_y = -2;

				f32 t_offst_x = (this->calc_h - t_font_size) / 2 + t_fontdata_x;
				f32 t_offst_y = (this->calc_w - t_font_size) / 2 + t_fontdata_y;

				GetSystemInstance()->GetCallback()->DrawFont_Callback(a_z_sort + this->z_sort+1,this->calc_x + t_offst_x,this->calc_y + t_offst_y,-1.0f,-1.0f,t_font_size,t_font_texture_index,t_font_color,L"x");
			}
		}

		return true;
	}
}}

