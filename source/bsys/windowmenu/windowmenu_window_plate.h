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
#include "./windowmenu.h"
#include "./windowmenu_window_base.h"


/** NBsys::NWindowMenu
*/
namespace NBsys{namespace NWindowMenu
{

	/**
	*/
	struct WindowMenu_Plate
	{
		
	};

	/** プレート。
	*/
	class WindowMenu_Window_Plate : public WindowMenu_Window_Base
	{
	public:
		/** InitItem
		*/
		struct InitItem
		{
			/** mode
			*/
			WindowMenu_Mode::Id mode;

			/** name
			*/
			STLString name;
			
			/** offset
			*/
			WindowMenu_Offset offset;
			
			/** size
			*/
			WindowMenu_Size size;

			/** 色。
			*/
			NBsys::NColor::Color_F color;

			/** テクスチャーＩＤ。
			*/
			s32 texture_id;

			/** マウス操作を親に伝えない。
			*/
			bool mouseblock;

			/** constructor
			*/
			InitItem(WindowMenu_Mode::Id a_mode,const STLString& a_name,const WindowMenu_Offset& a_offset,const WindowMenu_Size& a_size,const NBsys::NColor::Color_F& a_color,s32 a_texture_id,bool a_mouseblock)
				:
				mode(a_mode),
				name(a_name),
				offset(a_offset),
				size(a_size),
				color(a_color),
				texture_id(a_texture_id),
				mouseblock(a_mouseblock)
			{
			}

			/** destructor
			*/
			nonvirtual ~InitItem()
			{
			}
		};

	private:
		/** color
		*/
		NBsys::NColor::Color_F color;

		/** texture_id
		*/
		s32 texture_id;

		/** mouseblock
		*/
		bool mouseblock;

	public:
		/** constructor
		*/
		WindowMenu_Window_Plate(const InitItem& a_inititem);

		/** destructor
		*/
		virtual ~WindowMenu_Window_Plate();

		/** 描画処理。
		*/
		virtual bool CallBack_Draw();

		/** マウス処理。
		*/
		virtual bool CallBack_InRangeMouseUpdate(WindowMenu_Mouse& a_mouse);
	};

}}

