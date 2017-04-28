#pragma once

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief OpenGL�B
*/


/** include
*/
#include "../types/types.h"


/** NBsys::NOpengl
*/
#if(BSYS_OPENGL_ENABLE)
namespace NBsys{namespace NOpengl
{

	/** Opengl_ShaderType
	*/
	struct Opengl_ShaderType
	{
		enum Id
		{
			/** �o�[�e�b�N�X�B
			*/
			Vertex,

			/** �t���O�����g�B
			*/
			Fragment
		};
	};

	/**  Opengl_ShaderValueType
	*/
	struct Opengl_ShaderValueType
	{
		enum Id
		{
			Texture0,
			Texture1,
			Texture2,
			Texture3,
			Texture4,
			Texture5,
			Texture6,
			Texture7,
			Texture8,
			Texture9,
			Texture10,
			Texture11,
			Texture12,
			Texture13,
			Texture14,
			Texture15,
			Texture16,
			Texture17,
			Texture18,
			Texture19,
			Texture20,
			Texture21,
			Texture22,
			Texture23,
			Texture24,
			Texture25,
			Texture26,
			Texture27,
			Texture28,
			Texture29,
			Texture30,
			Texture31,

			/** Float�B
			*/
			Float,

			/** Float2
			*/
			Float2,
			Vector2,
			
			/** Float3
			*/
			Float3,
			Vector3,

			/** Float4
			*/
			Float4,
			Vector4,

			/** Float16
			*/
			Float16,
			Matrix,

			/** ���_���s32 => �V�F�[�_�[�p�����[�^f32�B
			*/
			IntToFloat,

			/** ���_���s32 => �V�F�[�_�[�p�����[�^f32�B
			*/
			Int2ToFloat2,

			/** ���_���s32 => �V�F�[�_�[�p�����[�^f32�B
			*/
			Int3ToFloat3,

			/** ���_���s32 => �V�F�[�_�[�p�����[�^f32�B
			*/
			Int4ToFloat4,

		};
	};

	/** Opengl_ShadeModelType
	*/
	struct Opengl_ShadeModelType
	{
		enum Id
		{
			/**

			�X���[�X�V���[�e�B���O�̏ꍇ�A�|���S���̉A�e�����炩�ɕ\������`�悳���B

			*/
			Smooth,

			/**

			�t���b�g�V���[�e�B���O�ɐݒ肵���ꍇ�A�ʂ��Ƃ̖��邳�����̏�ԂƂ��ĕ`�悳���B
			�����`�悪�\�B

			*/
			Flat
		};
	};

}}
#endif

