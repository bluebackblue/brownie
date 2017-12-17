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
	/** WindowMenu_WindowType
	*/
	struct WindowMenu_WindowType
	{
		enum Id
		{
			//�J�X�^���B
			Custom,

			//�G���A�B
			Area,

			//�{�^���B
			Button,

			//����{�^���B
			CloseButton,

			//�h���b�O�B
			Drag,

			//�v���[�g�B
			Plate,

			//�e�L�X�g�B
			Text,
		};
	};

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
		~WindowMenu_Offset()
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

	/** �T�C�Y�B
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
		~WindowMenu_Size()
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

