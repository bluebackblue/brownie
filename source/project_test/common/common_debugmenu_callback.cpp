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
#include "./common_debugmenu_callback.h"


/** NCommon
*/
#if(BSYS_DEBUGMENU_ENABLE)
namespace NCommon
{
	/** DrawFontProcType
	*/
	void DebugMenu_Callback::DrawFont_Callback(const STLWString& a_string,f32 a_font_size,f32 a_x,f32 a_y,f32 a_z,const NBsys::NColor::Color_F& a_color)
	{
		this->drawfont_manager->DrawFont16(a_string,a_font_size,a_x,a_y,a_z,a_color);
	}

	/** DrawRectProcType
	*/
	void DebugMenu_Callback::DrawRect_Callback(f32 a_x,f32 a_y,f32 a_w,f32 a_h,f32 a_z,s32 a_texture_id,const NBsys::NColor::Color_F& a_color)
	{
		this->drawrect_manager->DrawRect(a_x,a_y,a_w,a_h,a_z,a_texture_id,a_color);
	}

	/** GetMouseProcType
	*/
	void DebugMenu_Callback::GetMouse_Callback(f32& a_x,f32& a_y,bool& a_l_on,bool& a_r_on,bool& a_l_down,bool& a_r_down,bool& a_l_up,bool& a_r_up)
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

