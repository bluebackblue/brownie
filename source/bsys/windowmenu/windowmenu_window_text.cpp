

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
#include "./windowmenu_window_text.h"


/** NBsys::NWindowMenu
*/
#if(BSYS_WINDOWMENU_ENABLE)
namespace NBsys{namespace NWindowMenu
{
	/** constructor
	*/
	WindowMenu_Window_Text::WindowMenu_Window_Text(const STLString& a_name)
		:
		WindowMenu_Window_Base(a_name,WindowMenu_WindowType::Text),
		color(1.0f,1.0f,1.0f,1.0f),
		string(L"")
	{
	}

	/** destructor
	*/
	WindowMenu_Window_Text::~WindowMenu_Window_Text()
	{
	}

	/** Initialize
	*/
	void WindowMenu_Window_Text::Initialize(const WindowMenu_Window_Base::InitItem& a_inititem)
	{
		WindowMenu_Window_Base::Initialize(a_inititem);
		{
			/** color
			*/
			this->color = NBsys::NColor::Color_F(1.0f,1.0f,1.0f,1.0f);

			/** string
			*/
			this->string = L"";
		}
	}

	/** 描画処理。
	*/
	bool WindowMenu_Window_Text::CallBack_Draw(s32 a_z_sort)
	{
		if((this->calc_w >= 0.0f)&&(this->calc_h >= 0.0f)){

			f32 t_offset_x = 0.0f;
			f32 t_offset_y = 0.0f;
			f32 t_font_size = 16.0f;
			s32 t_font_texture_index = 0;

			GetSystemInstance()->GetCallback()->DrawFont_Callback(a_z_sort + this->z_sort+1,this->calc_x + t_offset_x,this->calc_y + t_offset_y,this->calc_w,this->calc_h,t_font_size,t_font_texture_index,this->color,this->string);
		}

		//子の描画を行う。
		return true;
	}
}}
#endif

