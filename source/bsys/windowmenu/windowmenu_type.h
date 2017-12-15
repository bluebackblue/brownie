#pragma once

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �f�o�b�O���j���[�B
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
	/** WindowMenu_Mode
	*/
	struct WindowMenu_Mode
	{
		enum Id
		{
			//���R�z�u�B
			Free,

			//�c�B
			Vertical,

			//���B
			Horizontal,
		};
	};

	/** WindowMenu_SizeType
	*/
	struct WindowMenu_SizeType
	{
		enum Id
		{
			//�Œ�T�C�Y�B
			Fix,

			//�e�̃T�C�Y�ɍ��킹��B
			StretchParent,

			//�q�̃T�C�Y�ɍ��킹��B
			StretchChild
		};
	};

	/** �I�t�Z�b�g�B
	*/
	struct WindowMenu_Offset
	{
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
		~WindowMenu_Offset()
		{
		}

		f32 x;
		f32 y;
	};

	/** �T�C�Y�B
	*/
	struct WindowMenu_Size
	{
		/** constructor
		*/
		WindowMenu_Size()
			:
			sizetype_w(WindowMenu_SizeType::Fix),
			w(0.0f),
			sizetype_h(WindowMenu_SizeType::Fix),
			h(0.0f)
		{
		}

		/** constructor
		*/
		WindowMenu_Size(WindowMenu_SizeType::Id a_sizetype_w,f32 a_w,WindowMenu_SizeType::Id a_sizetype_h,f32 a_h)
			:
			sizetype_w(a_sizetype_w),//TODO:
			w(a_w),
			sizetype_h(a_sizetype_h),
			h(a_h)
		{
		}

		/** destructor
		*/
		~WindowMenu_Size()
		{
		}

		/** w
		*/
		WindowMenu_SizeType::Id sizetype_w;
		f32 w;

		/** h
		*/
		WindowMenu_SizeType::Id sizetype_h;
		f32 h;
	};
}}
#endif


