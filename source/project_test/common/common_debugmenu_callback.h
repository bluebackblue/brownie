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


/** inclulde
*/
#include "./common_drawfont.h"
#include "./common_drawrect.h"
#include "./common_pad_device.h"


/** NCommon
*/
#if(BSYS_DEBUGMENU_ENABLE)
namespace NCommon
{
	/** DebugMenu_Callback
	*/
	class DebugMenu_Callback : public NBsys::NDebugMenu::DebugMenu_Callback_Base
	{
	private:
		/** drawrect_manager
		*/
		sharedptr<NCommon::DrawRect_Manager> drawrect_manager;

		/** drawfont_manager
		*/
		sharedptr<NCommon::DrawFont_Manager> drawfont_manager;

	public:
		/** constructor
		*/
		DebugMenu_Callback(sharedptr<NCommon::DrawRect_Manager>& a_drawrect_manager,sharedptr<NCommon::DrawFont_Manager>& a_drawfont_manager)
			:
			drawrect_manager(a_drawrect_manager),
			drawfont_manager(a_drawfont_manager)
		{
		}

		/** destructor
		*/
		virtual ~DebugMenu_Callback()
		{
		}

	public:
		/** DrawFont_Callback
		*/
		virtual void DrawFont_Callback(const STLWString& a_string,f32 a_font_size,f32 a_x,f32 a_y,f32 a_z,const NBsys::NColor::Color_F& a_color);

		/** DrawRect_Callback
		*/
		virtual void DrawRect_Callback(f32 a_x,f32 a_y,f32 a_w,f32 a_h,f32 a_z,s32 a_texture_id,const NBsys::NColor::Color_F& a_color);

		/** GetMouse_Callback
		*/
		virtual void GetMouse_Callback(f32& a_x,f32& a_y,bool& a_l_on,bool& a_r_on,bool& a_l_down,bool& a_r_down,bool& a_l_up,bool& a_r_up);
	};
}
#endif

