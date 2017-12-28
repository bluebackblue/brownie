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
#include "../types/types.h"
#pragma warning(pop)


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../color/color.h"
#pragma warning(pop)


/** NBsys::NWindowMenu
*/
#if(BSYS_WINDOWMENU_ENABLE)
namespace NBsys{namespace NWindowMenu
{
	/** WindowMenu_WindowType
	*/
	struct WindowMenu_WindowType
	{
		enum Id
		{
			//カスタム。
			Custom,

			//エリア。
			Area,

			//ボタン。
			Button,

			//閉じるボタン。
			CloseButton,

			//ドラッグ。
			Drag,

			//プレート。
			Plate,

			//テキスト。
			Text,

			//ウィンドウ。
			Window,
		};
	};


	/** WindowMenu_Mode
	*/
	struct WindowMenu_Mode
	{
		enum Id
		{
			//自由配置。
			Free,

			//縦。
			Vertical,

			//横。
			Horizontal,
		};
	};


	/** WindowMenu_SizeType
	*/
	struct WindowMenu_SizeType
	{
		enum Id
		{
			//固定サイズ。
			Fix,

			//親のサイズに合わせる。
			StretchParent,

			//子のサイズに合わせる。
			StretchChild
		};
	};


	/** オフセット。
	*/
	struct WindowMenu_Offset
	{
		/** x
		*/
		f32 x;

		/** y
		*/
		f32 y;

		/** constructor
		*/
		WindowMenu_Offset()
			:
			x(0.0f),
			y(0.0f)
		{
		}

		/** constructor
		*/
		WindowMenu_Offset(f32 a_x,f32 a_y)
			:
			x(a_x),
			y(a_y)
		{
		}

		/** destructor
		*/
		nonvirtual ~WindowMenu_Offset()
		{
		}

		/** Set
		*/
		void Set(f32 a_x,f32 a_y)
		{
			this->x = a_x;
			this->y = a_y;
		}
	};


	/** サイズ。
	*/
	struct WindowMenu_Size
	{
		/** w
		*/
		WindowMenu_SizeType::Id type_w;
		f32 w;

		/** h
		*/
		WindowMenu_SizeType::Id type_h;
		f32 h;

		/** constructor
		*/
		WindowMenu_Size()
			:
			type_w(WindowMenu_SizeType::StretchParent),
			w(0.0f),
			type_h(WindowMenu_SizeType::StretchParent),
			h(0.0f)
		{
		}

		/** constructor
		*/
		WindowMenu_Size(f32 a_w,f32 a_h)
			:
			type_w(WindowMenu_SizeType::StretchParent),
			w(a_w),
			type_h(WindowMenu_SizeType::StretchParent),
			h(a_h)
		{
		}

		/** constructor
		*/
		WindowMenu_Size(WindowMenu_SizeType::Id a_type_w,f32 a_w,WindowMenu_SizeType::Id a_type_h,f32 a_h)
			:
			type_w(a_type_w),
			w(a_w),
			type_h(a_type_h),
			h(a_h)
		{
		}

		/** destructor
		*/
		nonvirtual ~WindowMenu_Size()
		{
		}

		/** SetW
		*/
		void SetW(f32 a_w)
		{
			this->type_w = WindowMenu_SizeType::Fix;
			this->w = a_w;
		}

		/** SetH
		*/
		void SetH(f32 a_h)
		{
			this->type_h = WindowMenu_SizeType::Fix;
			this->h = a_h;
		}

		/** SetW_StretchParent
		*/
		void SetW_StretchParent()
		{
			this->type_w = WindowMenu_SizeType::StretchParent;
			this->w = 0.0f;
		}

		/** SetH_StretchParent
		*/
		void SetH_StretchParent()
		{
			this->type_h = WindowMenu_SizeType::StretchParent;
			this->h = 0.0f;
		}

		/** SetW_StretchChild
		*/
		void SetW_StretchChild()
		{
			this->type_w = WindowMenu_SizeType::StretchChild;
			this->w = 0.0f;
		}

		/** SetH_StretchChild
		*/
		void SetH_StretchChild()
		{
			this->type_h = WindowMenu_SizeType::StretchChild;
			this->h = 0.0f;
		}
	};


}}
#endif

