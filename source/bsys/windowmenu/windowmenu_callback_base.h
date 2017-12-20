#pragma once

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief デバッグメニュー。
*/


/** include
*/
#include "../types/types.h"


/** include
*/
#include "../color/color.h"


/** NBsys::NWindowMenu
*/
#if(BSYS_WINDOWMENU_ENABLE)
namespace NBsys{namespace NWindowMenu
{
	/** WindowMenu_Callback_Base
	*/
	class WindowMenu_Callback_Base
	{
	public:

		/** constructor
		*/
		WindowMenu_Callback_Base()
		{
		}

		/** destructor
		*/
		virtual ~WindowMenu_Callback_Base()
		{
		}

	public:

		/** DrawFontProcType
		*/
		virtual void DrawFont_Callback(s32 a_z_sort,f32 a_x,f32 a_y,f32 a_w,f32 a_h,bool a_clip,f32 a_size,s32 a_fonttexture_type,const NBsys::NColor::Color_F& a_color,const STLWString& a_string,s32 a_alignment_x,s32 a_alignment_y) = 0;

		/** DrawRectProcType
		*/
		virtual void DrawRect_Callback(s32 a_z_sort,f32 a_x,f32 a_y,f32 a_w,f32 a_h,s32 a_texture_id,const NBsys::NColor::Color_F& a_color) = 0;

		/** GetMouseProcType
		*/
		virtual void GetMouse_Callback(f32& a_x,f32& a_y,bool& a_l_on,bool& a_r_on,bool& a_l_down,bool& a_r_down,bool& a_l_up,bool& a_r_up) = 0;

	};


}}
#endif

