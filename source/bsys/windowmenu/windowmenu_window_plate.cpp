﻿

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
#include "./windowmenu_window_plate.h"


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
	WindowMenu_Window_Plate::WindowMenu_Window_Plate(const STLString& a_name)
		:
		WindowMenu_Window_Base(a_name,WindowMenu_WindowType::Plate),
		color(1.0f,1.0f,1.0f,1.0f),
		texture_id(-1),
		mouseblock(true)
	{
	}


	/** destructor
	*/
	WindowMenu_Window_Plate::~WindowMenu_Window_Plate()
	{
	}


	/** Initialize
	*/
	void WindowMenu_Window_Plate::Initialize(const WindowMenu_Window_Base::InitItem& a_inititem)
	{
		WindowMenu_Window_Base::Initialize(a_inititem);
		{
			/** color
			*/
			this->color = NBsys::NColor::Color_F(1.0f,1.0f,1.0f,1.0f);

			/** texture_id
			*/
			this->texture_id = -1;

			/** mouseblock
			*/
			this->mouseblock = true;
		}
	}


	/** 描画処理。
	*/
	bool WindowMenu_Window_Plate::CallBack_Draw(s32 a_z_sort)
	{
		if((this->calc_rect.ww >= 0.0f)&&(this->calc_rect.hh >= 0.0f)){
			GetSystemInstance()->GetCallback()->DrawRect_Callback(
				a_z_sort + this->z_sort,
				this->calc_rect,
				this->texture_id,
				this->color
			);
		}

		//子の描画を行う。
		return true;
	}


	/** マウス処理。

	a_mousefix	: true = マウスは処理済み。

	*/
	void WindowMenu_Window_Plate::CallBack_MouseUpdate(WindowMenu_Mouse& a_mouse,bool& a_mousefix)
	{
		if(a_mousefix == false){
			if(this->mouseblock){
				if(this->IsRange(a_mouse.pos)){

					//マウス処理。
					a_mousefix = true;

					return;
				}
			}
		}
	}


}}
#pragma warning(pop)
#endif

