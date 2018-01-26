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
#pragma warning(pop)


/** NBsys::NWindowMenu
*/
#if(BSYS_WINDOWMENU_ENABLE)
#pragma warning(push)
#pragma warning(disable:4514)
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


	/** サイズ。
	*/
	struct WindowMenu_Size
	{
		/** type_w
		*/
		WindowMenu_SizeType::Id type_w;
		
		/** type_h
		*/
		WindowMenu_SizeType::Id type_h;

		/** size
		*/
		Size2DType<f32> size;

		/** constructor
		*/
		WindowMenu_Size()
			:
			type_w(WindowMenu_SizeType::StretchParent),
			type_h(WindowMenu_SizeType::StretchParent),
			size(0.0f)
		{
		}

		/** constructor
		*/
		WindowMenu_Size(f32 a_w,f32 a_h)
			:
			type_w(WindowMenu_SizeType::StretchParent),
			type_h(WindowMenu_SizeType::StretchParent),
			size(a_w,a_h)
		{
		}

		/** constructor
		*/
		WindowMenu_Size(WindowMenu_SizeType::Id a_type_w,f32 a_w,WindowMenu_SizeType::Id a_type_h,f32 a_h)
			:
			type_w(a_type_w),
			type_h(a_type_h),
			size(a_w,a_h)
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
			this->size.ww = a_w;
		}

		/** SetH
		*/
		void SetH(f32 a_h)
		{
			this->type_h = WindowMenu_SizeType::Fix;
			this->size.hh = a_h;
		}

		/** SetW_StretchParent
		*/
		void SetW_StretchParent()
		{
			this->type_w = WindowMenu_SizeType::StretchParent;
			this->size.ww = 0.0f;
		}

		/** SetH_StretchParent
		*/
		void SetH_StretchParent()
		{
			this->type_h = WindowMenu_SizeType::StretchParent;
			this->size.hh = 0.0f;
		}

		/** SetW_StretchChild
		*/
		void SetW_StretchChild()
		{
			this->type_w = WindowMenu_SizeType::StretchChild;
			this->size.ww = 0.0f;
		}

		/** SetH_StretchChild
		*/
		void SetH_StretchChild()
		{
			this->type_h = WindowMenu_SizeType::StretchChild;
			this->size.hh = 0.0f;
		}
	};


}}
#pragma warning(pop)
#endif

