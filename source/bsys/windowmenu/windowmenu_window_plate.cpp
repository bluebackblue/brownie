

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
#pragma warning(push)
#pragma warning(disable:4464)
#include "../color/color.h"
#pragma warning(pop)


/** include
*/
#include "./windowmenu.h"
#include "./windowmenu_window_plate.h"


/** warning

4710 : The given function was selected for inline expansion, but the compiler did not perform the inlining.

*/
#pragma warning(disable:4710)


/** NBsys::NWindowMenu
*/
#if(BSYS_WINDOWMENU_ENABLE)
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
		if((this->calc_w >= 0.0f)&&(this->calc_h >= 0.0f)){
			GetSystemInstance()->GetCallback()->DrawRect_Callback(a_z_sort + this->z_sort,this->calc_x,this->calc_y,this->calc_w,this->calc_h,this->texture_id,this->color);
		}

		//子の描画を行う。
		return true;
	}


	/** マウス処理。
	*/
	bool WindowMenu_Window_Plate::CallBack_InRangeMouseUpdate(WindowMenu_Mouse& /*a_mouse*/)
	{
		//マウス操作を親に伝えない。
		return this->mouseblock;
	}


}}
#endif

