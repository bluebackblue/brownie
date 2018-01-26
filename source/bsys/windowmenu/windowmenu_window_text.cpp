

/**
 * Copyright (c) blueback
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
#pragma warning(push)
#pragma warning(disable:4464)
#include "../color/color.h"
#pragma warning(pop)


/** include
*/
#include "./windowmenu.h"
#include "./windowmenu_window_text.h"


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
	WindowMenu_Window_Text::WindowMenu_Window_Text(const STLString& a_name)
		:
		WindowMenu_Window_Base(a_name,WindowMenu_WindowType::Text),
		color(1.0f,1.0f,1.0f,1.0f),
		string(L""),
		clip(false),
		alignment(NBsys::NFont::Font_Alignment::Left_VCenter)
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
		if((this->calc_rect.ww >= 0.0f)&&(this->calc_rect.hh >= 0.0f)){

			f32 t_font_size = 16.0f;
			s32 t_font_texture_index = 0;

			if(this->string.size() > 0){

				GetSystemInstance()->GetCallback()->DrawFont_Callback(
					a_z_sort + this->z_sort + 1,
					this->calc_rect,
					this->clip,
					t_font_size,
					t_font_texture_index,
					this->color,
					this->string,
					this->alignment,
					this->calc_rect_noclip
				);
			}
		}

		//子の描画を行う。
		return true;
	}


}}
#pragma warning(pop)
#endif

