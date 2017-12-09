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


/** NBsys::NDebugMenu
*/
namespace NBsys{namespace NDebugMenu
{
	/** DebugMenu_Window_Base
	*/
	class DebugMenu_Window_Base
	{
	public:
		/** Mode
		*/
		struct Mode
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

	public:
		/** �����B
		*/
		DebugMenu_Window_Base* me;

		/** �e�B
		*/
		DebugMenu_Window_Base* parent;

	public:
		/** ���[�h�B
		*/
		Mode::Id mode;

		/** child_list
		*/
		STLVector<sharedptr<DebugMenu_Window_Base>>::Type child_list;

		/** [�ݒ�l]�����̈ʒu�B
		*/
		f32 offset_x;
		f32 offset_y;

		/** [�ݒ�l]�����̃T�C�Y�B
		*/
		f32 width;
		f32 height;

		/** �`��D��x�B
		*/
		f32 z;

		/** [�v�Z����]�����̈ʒu�B
		*/
		f32 calc_x;
		f32 calc_y;

		/** [�v�Z����]�����̃T�C�Y�B
		*/
		f32 calc_w;
		f32 calc_h;

		/** [�v�Z����]�e�̈ʒu�B
		*/
		f32 calc_parent_x;
		f32 calc_parent_y;

	public:
		/** constructor
		*/
		DebugMenu_Window_Base();

		/** destructor
		*/
		virtual ~DebugMenu_Window_Base();

		/** Initialize
		*/
		void Initialize(Mode::Id a_mode,f32 a_offset_x,f32 a_offset_y,f32 a_width,f32 a_height,f32 a_z);

		/** CalcWidth
		*/
		f32 CalcWidth();

		/** CalcHeight
		*/
		f32 CalcHeight();

		/** CalcWidthFromParent
		*/
		f32 CalcWidthFromParent();

		/** CalcHeightFromParent
		*/
		f32 CalcHeightFromParent();

		/** CalcWidthFromChild
		*/
		f32 CalcWidthFromChild();

		/** CalcHeightFromChild
		*/
		f32 CalcHeightFromChild();

		/** AddChild
		*/
		void AddChild(const sharedptr<DebugMenu_Window_Base>& a_window);

		/** �\���ʒu�v�Z�B
		*/
		virtual void CalcRect(f32 a_parent_offset_x,f32 a_parent_offset_y);

		/** �X�V�B
		*/
		virtual void Update();

		/** �`��B
		*/
		virtual void Draw();

		/** �폜���N�G�X�g�B�擾�B
		*/
		virtual bool GetDeleteRequest();

		/** �R�[���o�b�N�B�e���ڑ����ꂽ����ɌĂяo�����B
		*/
		virtual void CallBack_SetParent();
	};

}}

