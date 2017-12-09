#pragma once

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief OpenGL。
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

			/** 配列数。
			*/
			s32 countof;

			/** constructor
			*/
			Uniform(GLint a_location,Opengl_ShaderValueType::Id a_shadervaluetype,s32 a_countof)
				:
				location(a_location),
				shadervaluetype(a_shadervaluetype),
				countof(a_countof)
			{
			}

			/** destructor
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

			/** constructor
			*/
			Attribute(GLint a_location,Opengl_ShaderValueType::Id a_shadervaluetype)
				:
				location(a_location),
				shadervaluetype(a_shadervaluetype)
			{
			}

			/** destructor
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
		STLMap<STLString,Opengl_Impl_ShaderState::Uniform>::Type uniform_list;

		/** attribute_list
		*/
		STLMap<STLString,Opengl_Impl_ShaderState::Attribute>::Type attribute_list;

		/** vertexarray_rawid
		*/
		RawID vertexarray_rawid;

		/** constructor
		*/
		Opengl_Impl_ShaderState()
		{
		}

		/** destructor
		*/
		nonvirtual ~Opengl_Impl_ShaderState()
		{
		}
	};

}}
#endif

