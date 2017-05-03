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


/** include
*/
#include "./opengl_impl_include.h"


/** NBsys::NOpengl
*/
#if(BSYS_OPENGL_ENABLE)
namespace NBsys{namespace NOpengl
{
	/** Opengl_Impl_ShaderState
	*/
	struct Opengl_Impl_ShaderState
	{
		/** Uniform
		*/
		struct Uniform
		{
			/** location
			*/
			GLint location;

			/** shadervaluetype
			*/
			Opengl_ShaderValueType::Id shadervaluetype;

			/** �z�񐔁B
			*/
			s32 countof;

			/** �R���X�g���N�^�B
			*/
			Uniform(GLint a_location,Opengl_ShaderValueType::Id a_shadervaluetype,s32 a_countof)
				:
				location(a_location),
				shadervaluetype(a_shadervaluetype),
				countof(a_countof)
			{
			}

			/** �f�X�g���N�^�B
			*/
			nonvirtual ~Uniform()
			{
			}
		};

		/** Attribute
		*/
		struct Attribute
		{
			/** location
			*/
			GLint location;

			/** shadervaluetype
			*/
			Opengl_ShaderValueType::Id shadervaluetype;

			/** �R���X�g���N�^�B
			*/
			Attribute(GLint a_location,Opengl_ShaderValueType::Id a_shadervaluetype)
				:
				location(a_location),
				shadervaluetype(a_shadervaluetype)
			{
			}

			/** �f�X�g���N�^�B
			*/
			nonvirtual ~Attribute()
			{
			}
		};

		/** vertexshader_rawid
		*/
		RawID vertexshader_rawid;

		/** fragmentshader_rawid
		*/
		RawID fragmentshader_rawid;

		/** shaderprogram_rawid
		*/
		RawID shaderprogram_rawid;

		/** vertex_uniform_list
		*/
		STLMap< STLString , Opengl_Impl_ShaderState::Uniform >::Type uniform_list;

		/** attribute_list
		*/
		STLMap< STLString , Opengl_Impl_ShaderState::Attribute >::Type attribute_list;

		/** vertexarray_rawid
		*/
		RawID vertexarray_rawid;

		/** �R���X�g���N�^�B
		*/
		Opengl_Impl_ShaderState()
		{
		}

		/** �f�X�g���N�^�B
		*/
		nonvirtual ~Opengl_Impl_ShaderState()
		{
		}
	};

}}
#endif

