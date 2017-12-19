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
#if(BSYS_WINDOWMENU_ENABLE)
namespace NCommon
{
	/** WindowMenu_Callback
	*/
	class WindowMenu_Callback : public NBsys::NWindowMenu::WindowMenu_Callback_Base
	{
	private:
		/** render2d
		*/
		sharedptr<NCommon::Render2D> render2d;

	public:
		/** constructor
		*/
		WindowMenu_Callback(sharedptr<NCommon::Render2D>& a_render2d)
			:
			render2d(a_render2d)
		{
		}

		/** destructor
		*/
		virtual ~WindowMenu_Callback()
		{
		}

	public:
		/** DrawFont_Callback
		*/
		virtual void DrawFont_Callback(s32 a_z_sort,f32 a_x,f32 a_y,f32 a_w,f32 a_h,bool a_clip,f32 a_size,s32 a_fonttexture_type,const NBsys::NColor::Color_F& a_color,const STLWString& a_string,s32 a_alignment_x,s32 a_alignment_y);

		/** DrawRect_Callback
		*/
		virtual void DrawRect_Callback(s32 a_z_sort,f32 a_x,f32 a_y,f32 a_w,f32 a_h,s32 a_texture_id,const NBsys::NColor::Color_F& a_color);

		/** GetMouse_Callback
		*/
		virtual void GetMouse_Callback(f32& a_x,f32& a_y,bool& a_l_on,bool& a_r_on,bool& a_l_down,bool& a_r_down,bool& a_l_up,bool& a_r_up);
	};
}
#endif

