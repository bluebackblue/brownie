#pragma once

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief デバッグメニュー。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../include.h"
#pragma warning(pop)


/** inclulde
*/
#include "./common_drawfont.h"
#include "./common_drawrect.h"
#include "./common_pad_device.h"


/** NTest::NCommon
*/
#if(BSYS_WINDOWMENU_ENABLE)
#pragma warning(push)
#pragma warning(disable:4514 4710)
namespace NTest{namespace NCommon
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
		virtual void DrawFont_Callback(s32 a_z_sort,const Rect2DType_R<f32>& a_rect,bool a_clip,f32 a_size,s32 a_fonttexture_type,const NBsys::NColor::Color_F& a_color,const STLWString& a_string,NBsys::NFont::Font_Alignment::Id a_alignment);

		/** DrawRect_Callback
		*/
		virtual void DrawRect_Callback(s32 a_z_sort,const Rect2DType_R<f32>& a_rect,s32 a_texture_id,const NBsys::NColor::Color_F& a_color);

		/** GetMouse_Callback
		*/
		virtual void GetMouse_Callback(Position2DType<f32>& a_pos,bool& a_l_on,bool& a_r_on,bool& a_l_down,bool& a_r_down,bool& a_l_up,bool& a_r_up);

	};


}}
#pragma warning(pop)
#endif

