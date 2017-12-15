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
			InitItem(WindowMenu_Mode::Id a_mode,const STLString& a_name,const WindowMenu_Offset& a_offset,const WindowMenu_Size& a_size)
				:
				mode(a_mode),
				name(a_name),
				offset(a_offset),
				size(a_size)
			{
			}

			/** destructor
			*/
			nonvirtual ~InitItem()
			{
			}
		};

	public:
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
		virtual bool CallBack_Draw(s32 a_z_sort);

		/** マウス処理。
		*/
		virtual bool CallBack_InRangeMouseUpdate(WindowMenu_Mouse& a_mouse);
	};

}}

