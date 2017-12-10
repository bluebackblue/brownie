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


/** NBsys::NDebugMenu
*/
#if(BSYS_DEBUGMENU_ENABLE)
namespace NBsys{namespace NDebugMenu
{
	/** DebugMenu_Callback_Base
	*/
	class DebugMenu_Callback_Base
	{
	public:
		/** constructor
		*/
		DebugMenu_Callback_Base()
		{
		}

		/** destructor
		*/
		virtual ~DebugMenu_Callback_Base()
		{
		}

	public:
		/** DrawFontProcType
		*/
		virtual void DrawFont_Callback(const STLWString& a_string,f32 a_font_size,f32 a_x,f32 a_y,s32 a_z,const NBsys::NColor::Color_F& a_color) = 0;

		/** DrawRectProcType
		*/
		virtual void DrawRect_Callback(f32 a_x,f32 a_y,f32 a_w,f32 a_h,s32 a_z,s32 a_texture_id,const NBsys::NColor::Color_F& a_color) = 0;

		/** GetMouseProcType
		*/
		virtual void GetMouse_Callback(f32& a_x,f32& a_y,bool& a_l_on,bool& a_r_on,bool& a_l_down,bool& a_r_down,bool& a_l_up,bool& a_r_up) = 0;
	};
}}
#endif

