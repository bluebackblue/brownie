#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief デバッグメニュー。
*/


/** include
*/
#include "../include.h"


/** include
*/
#include "./common_windowmenu_callback.h"


/** NCommon
*/
#if(BSYS_WINDOWMENU_ENABLE)
namespace NCommon
{
	/** DrawFontProcType
	*/
	void WindowMenu_Callback::DrawFont_Callback(s32 a_z_sort,f32 a_x,f32 a_y,f32 a_size,s32 a_font_texture_index,const NBsys::NColor::Color_F& a_color,const STLWString& a_string)
	{
		this->render2d->DrawFont(a_z_sort,a_x,a_y,a_size,a_font_texture_index,a_color,a_string);
	}

	/** DrawRectProcType
	*/
	void WindowMenu_Callback::DrawRect_Callback(s32 a_z_sort,f32 a_x,f32 a_y,f32 a_w,f32 a_h,s32 a_texture_id,const NBsys::NColor::Color_F& a_color)
	{
		this->render2d->DrawRect(a_z_sort,a_x,a_y,a_w,a_h,a_texture_id,a_color);
	}

	/** GetMouseProcType
	*/
	void WindowMenu_Callback::GetMouse_Callback(f32& a_x,f32& a_y,bool& a_l_on,bool& a_r_on,bool& a_l_down,bool& a_r_down,bool& a_l_up,bool& a_r_up)
	{
		NBsys::NPad::Pad_Virtual* t_pad_virtual_ptr = NBsys::NPad::GetVirtualPad(NCommon::Pad_Device::Type::Pad1).get();

		const NBsys::NPad::TouchValue& t_mouse_l = t_pad_virtual_ptr->GetTouchValue(NBsys::NPad::Pad_Virtual::TouchType::MOUSEL);
		const NBsys::NPad::TouchValue& t_mouse_r = t_pad_virtual_ptr->GetTouchValue(NBsys::NPad::Pad_Virtual::TouchType::MOUSER);

		a_x = t_mouse_l.x;
		a_y = t_mouse_l.y;

		a_l_on = t_mouse_l.flag;
		a_r_on = t_mouse_r.flag;

		a_l_down = t_pad_virtual_ptr->IsButtonDown(NBsys::NPad::Pad_Virtual::ButtonType::MOUSEL);
		a_r_down = t_pad_virtual_ptr->IsButtonDown(NBsys::NPad::Pad_Virtual::ButtonType::MOUSER);

		a_l_up = t_pad_virtual_ptr->IsButtonUp(NBsys::NPad::Pad_Virtual::ButtonType::MOUSEL);
		a_r_up = t_pad_virtual_ptr->IsButtonUp(NBsys::NPad::Pad_Virtual::ButtonType::MOUSER);
	}

}
#endif

