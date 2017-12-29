

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


/** include
*/
#include "./common_windowmenu_callback.h"


/** warning

4710 : The given function was selected for inline expansion, but the compiler did not perform the inlining.

*/
#pragma warning(disable:4710)


/** NTest::NCommon
*/
#if(BSYS_WINDOWMENU_ENABLE)
namespace NTest{namespace NCommon
{
	/** DrawFontProcType
	*/
	void WindowMenu_Callback::DrawFont_Callback(s32 a_z_sort,f32 a_x,f32 a_y,f32 a_w,f32 a_h,bool a_clip,f32 a_size,s32 a_fonttexture_type,const NBsys::NColor::Color_F& a_color,const STLWString& a_string,s32 a_alignment_x,s32 a_alignment_y)
	{
		sharedptr<Render2D_Item_Font> t_item = new Render2D_Item_Font(a_z_sort);

		{
			t_item->x = a_x;
			t_item->y = a_y;
			t_item->w = a_w;
			t_item->h = a_h;

			t_item->clip = a_clip;

			t_item->size = a_size;

			t_item->fonttexture_type = static_cast<NBsys::ND3d11::D3d11_FontTextureType::Id>(a_fonttexture_type);

			t_item->color = a_color;

			t_item->alignment_x = a_alignment_x;
			t_item->alignment_y = a_alignment_y;

			t_item->string = a_string;
		}

		this->render2d->Draw(t_item);
	}

	/** DrawRectProcType
	*/
	void WindowMenu_Callback::DrawRect_Callback(s32 a_z_sort,f32 a_x,f32 a_y,f32 a_w,f32 a_h,s32 a_texture_id,const NBsys::NColor::Color_F& a_color)
	{
		sharedptr<Render2D_Item_Rect> t_item = new Render2D_Item_Rect(a_z_sort);

		{
			t_item->x = a_x;
			t_item->y = a_y;
			t_item->w = a_w;
			t_item->h = a_h;

			t_item->texture_id = a_texture_id;

			t_item->color = a_color;
		}

		this->render2d->Draw(t_item);
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

}}
#endif

