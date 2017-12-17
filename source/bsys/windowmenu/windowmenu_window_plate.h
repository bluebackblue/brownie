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
		struct InitItem : public WindowMenu_Window_Base::InitItem
		{
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
			InitItem()
				:
				WindowMenu_Window_Base::InitItem(),
				color(NBsys::NColor::Color_F(1.0f,1.0f,1.0f,1.0f)),
				texture_id(-1),
				mouseblock(false)
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
		WindowMenu_Window_Plate(const STLString& a_name);

		/** destructor
		*/
		virtual ~WindowMenu_Window_Plate();

		/** Initialize
		*/
		void Initialize(const InitItem& a_inititem);

		/** 描画処理。
		*/
		virtual bool CallBack_Draw(s32 a_z_sort);

		/** マウス処理。
		*/
		virtual bool CallBack_InRangeMouseUpdate(WindowMenu_Mouse& a_mouse);
	};

}}

