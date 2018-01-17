

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
#include "./windowmenu_window_closebutton.h"


/** warning

4710 : この関数はインライン展開のために選択されましたが、コンパイラはインライン展開を実行しませんでした。

*/
#pragma warning(disable:4710)


/** NBsys::NWindowMenu
*/
#if(BSYS_WINDOWMENU_ENABLE)
#pragma warning(push)
#pragma warning(disable:4711)
namespace NBsys{namespace NWindowMenu
{
	/** constructor
	*/
	WindowMenu_Window_CloseButton::WindowMenu_Window_CloseButton(const STLString& a_name)
		:
		WindowMenu_Window_Base(a_name,WindowMenu_WindowType::CloseButton),
		push_flag(false),
		on_flag(false),
		color_normal(1.0f,1.0f,1.0f,1.0f),
		color_on(1.0f,1.0f,1.0f,1.0f),
		color_ondown(1.0f,1.0f,1.0f,1.0f),
		space(1.0f),
		to_callback_fonttexture_type(0),
		to_callback_font_view_size(16.0f),
		to_callback_font_offset_x(0.0f),
		to_callback_font_offset_y(0.0f)
	{
	}


	/** destructor
	*/
	WindowMenu_Window_CloseButton::~WindowMenu_Window_CloseButton()
	{
	}


	/** Initialize
	*/
	void WindowMenu_Window_CloseButton::Initialize(const WindowMenu_Window_Base::InitItem& a_inititem)
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

			/** space
			*/
			this->space = 1.0f;
		}
	}


	/** マウス処理。

	a_mousefix	: true = マウスは処理済み。

	*/
	void WindowMenu_Window_CloseButton::CallBack_MouseUpdate(WindowMenu_Mouse& a_mouse,bool& a_mousefix)
	{
		if(this->push_flag == true){
			//プッシュ中。

			if(a_mouse.on_l == true){
				//監視。
			}else{
				//プッシュ終了。
				this->push_flag = false;

				//アクション。
				if(this->IsRange(a_mouse.pos)){
					this->CallBack_SetDeleteRequest();
				}
			}
		}

		if(a_mousefix == false){
			if(this->IsRange(a_mouse.pos)){
				//マウス処理。
				a_mousefix = true;

				//プッシュ開始。
				if((this->push_flag == false)&&(a_mouse.down_l == true)){
					this->push_flag = true;
				}

				//マウスが乗っている。
				this->on_flag =  true;

				return;
			}
		}

		//マウスが乗っていない。
		this->on_flag = false;
	}


	/** 描画処理。
	*/
	bool WindowMenu_Window_CloseButton::CallBack_Draw(s32 a_z_sort)
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

			{
				GetSystemInstance()->GetCallback()->DrawRect_Callback(
					a_z_sort + this->z_sort,
					this->calc_rect + Rect2DType_R<f32>(this->space,this->space,-this->space*2,-this->space*2),
					-1,
					*t_color_list[t_color_index]
				);
			}

			//×ボタンをフォントで表現。
			{
				//L"x"
				GetSystemInstance()->GetCallback()->DrawFont_Callback(
					a_z_sort + this->z_sort + 1,
					this->calc_rect + Rect2DType_R<f32>(this->to_callback_font_offset_x,this->to_callback_font_offset_y,0,0),
					false,
					this->to_callback_font_view_size,
					this->to_callback_fonttexture_type,
					t_font_color,
					L"×",
					NBsys::NFont::Font_Alignment::Center_VCenter
				);
			}
		}

		//子の描画を行う。
		return true;
	}


}}
#pragma warning(pop)
#endif

