﻿

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief デバッグメニュー。
*/


/** include
*/
#include <bsys_pch.h>


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** include
*/
#include "./windowmenu.h"
#include "./windowmenu_window_button.h"


/** warning

4710 : この関数はインライン展開のために選択されましたが、コンパイラはインライン展開を実行しませんでした。

*/
#pragma warning(disable:4710)


/** NBsys::NWindowMenu
*/
#if(BSYS_WINDOWMENU_ENABLE)
namespace NBsys{namespace NWindowMenu
{
	/** constructor
	*/
	WindowMenu_Window_Button::WindowMenu_Window_Button(const STLString& a_name)
		:
		WindowMenu_Window_Base(a_name,WindowMenu_WindowType::Button),
		push_flag(false),
		on_flag(false),
		color_normal(1.0f,1.0f,1.0f,1.0f),
		color_on(1.0f,1.0f,1.0f,1.0f),
		color_ondown(1.0f,1.0f,1.0f,1.0f),
		string(L""),
		action()
	{
	}


	/** destructor
	*/
	WindowMenu_Window_Button::~WindowMenu_Window_Button()
	{
	}


	/** Initialize
	*/
	void WindowMenu_Window_Button::Initialize(const WindowMenu_Window_Base::InitItem& a_inititem)
	{
		WindowMenu_Window_Base::Initialize(a_inititem);
		{
			/** push_flag
			*/
			this->push_flag = false;

			/** on_flag
			*/
			this->on_flag = false;

			/** color
			*/
			this->color_normal = NBsys::NColor::Color_F(1.0f,1.0f,1.0f,1.0f);
			this->color_on = NBsys::NColor::Color_F(1.0f,1.0f,1.0f,1.0f);
			this->color_ondown = NBsys::NColor::Color_F(1.0f,1.0f,1.0f,1.0f);

			/** string
			*/
			this->string = L"";

			/** actions
			*/
			this->action = nullptr;
		}
	}


	/** マウス処理。
	*/
	bool WindowMenu_Window_Button::CallBack_InRangeMouseUpdate(WindowMenu_Mouse& a_mouse)
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
	void WindowMenu_Window_Button::CallBack_Update()
	{
		if(this->push_flag == true){
			WindowMenu_Mouse& t_mouse = GetSystemInstance()->GetMouse();
			if(t_mouse.up_l){
				this->push_flag = false;
				if(this->IsRange(t_mouse.pos)){
					//プッシュ確定。
					if(this->action){
						this->action();
					}
				}else{
					//プッシュキャンセル。
				}
			}
		}

		if(this->on_flag == true){
			WindowMenu_Mouse& t_mouse = GetSystemInstance()->GetMouse();

			//マウスがボタンの上。
			this->on_flag = this->IsRange(t_mouse.pos);
		}
	}


	/** 描画処理。
	*/
	bool WindowMenu_Window_Button::CallBack_Draw(s32 a_z_sort)
	{
		if((this->calc_rect.ww >= 0.0f)&&(this->calc_rect.hh >= 0.0f)){

			s32 t_color_index = 0;

			NBsys::NColor::Color_F* t_color_list[] = {
				&this->color_normal,
				&this->color_on,
				&this->color_ondown,
			};

			NBsys::NColor::Color_F t_font_color(1.0f,1.0f,1.0f,1.0f);

			if((this->push_flag == true)&&(this->on_flag == true)){
				t_color_index = 2;
			}else if(this->on_flag == true){
				t_color_index = 1;
			}

			GetSystemInstance()->GetCallback()->DrawRect_Callback(
				a_z_sort + this->z_sort,
				this->calc_rect + Rect2DType_R<f32>(1.0f,1.0f,-2.0f,-2.0f),
				-1,
				*t_color_list[t_color_index]
			);

			{
				f32 t_font_size = 16.0f;
				s32 t_font_texture_index = 0;

				if(this->string.size() > 0){
					GetSystemInstance()->GetCallback()->DrawFont_Callback(
						a_z_sort + this->z_sort + 1,
						this->calc_rect,
						false,
						t_font_size,
						t_font_texture_index,
						t_font_color,
						this->string,
						NBsys::NFont::Font_Alignment::Center_VCenter
					);
				}
			}
		}

		return true;
	}


}}
#endif

