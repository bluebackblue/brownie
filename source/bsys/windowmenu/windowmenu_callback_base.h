#pragma once

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief デバッグメニュー。
*/


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
#include "../font/font.h"
#pragma warning(pop)


/** NBsys::NWindowMenu
*/
#if(BSYS_WINDOWMENU_ENABLE)
#pragma warning(push)
#pragma warning(disable:4514)
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
		virtual void DrawFont_Callback(s32 a_z_sort,const Rect2DType_R<f32>& a_clip_rect,bool a_clip,f32 a_size,s32 a_fonttexture_type,const NBsys::NColor::Color_F& a_color,const STLWString& a_string,NBsys::NFont::Font_Alignment::Id a_alignment,const Rect2DType_R<f32>& a_alignment_rect) = 0;

		/** DrawRectProcType
		*/
		virtual void DrawRect_Callback(s32 a_z_sort,const Rect2DType_R<f32>& a_rect,s32 a_texture_id,const NBsys::NColor::Color_F& a_color) = 0;

		/** GetMouseProcType
		*/
		virtual void GetMouse_Callback(Position2DType<f32>& a_pos,bool& a_l_on,bool& a_r_on,bool& a_l_down,bool& a_r_down,bool& a_l_up,bool& a_r_up) = 0;

	};


}}
#pragma warning(pop)
#endif

