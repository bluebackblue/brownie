#pragma once

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief OpenGL。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** include
*/
#include "./opengl_impl_include.h"


/** NBsys::NOpengl
*/
#if(BSYS_OPENGL_ENABLE)
#pragma warning(push)
#pragma warning(disable:4514 4710)
namespace NBsys{namespace NOpengl
{

	/** Opengl_Impl_Uniform
	*/
	struct Opengl_Impl_Uniform
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
		Opengl_Impl_Uniform(GLint a_location,Opengl_ShaderValueType::Id a_shadervaluetype,s32 a_countof)
			:
			location(a_location),
			shadervaluetype(a_shadervaluetype),
			countof(a_countof)
		{
		}

		/** destructor
		*/
		nonvirtual ~Opengl_Impl_Uniform()
		{
		}
	};


	/** Opengl_Impl_Attribute
	*/
	class Opengl_Impl_Attribute
	{
	public:

		/** location
		*/
		GLint location;

		/** shadervaluetype
		*/
		Opengl_ShaderValueType::Id shadervaluetype;

		/** constructor
		*/
		Opengl_Impl_Attribute(GLint a_location,Opengl_ShaderValueType::Id a_shadervaluetype)
			:
			location(a_location),
			shadervaluetype(a_shadervaluetype)
		{
			this->location = 0;
		}

		/** destructor
		*/
		nonvirtual ~Opengl_Impl_Attribute()
		{
		}

	};


	/** Opengl_Impl_ShaderState
	*/
	struct Opengl_Impl_ShaderState
	{
		/** vertexshader_rawid
		*/
		RawID vertexshader_rawid;

		/** fragmentshader_rawid
		*/
		RawID fragmentshader_rawid;

		/** shaderprogram_rawid
		*/
		RawID shaderprogram_rawid;

		/** padding
		*/
		padding64(0,4);

		/** vertex_uniform_list
		*/
		STLMap<STLString,sharedptr<Opengl_Impl_Uniform>>::Type uniform_list;

		/** attribute_list
		*/
		STLMap<STLString,sharedptr<Opengl_Impl_Attribute>>::Type attribute_list;

		/** vertexarray_rawid
		*/
		RawID vertexarray_rawid;

		/** padding
		*/
		padding64(1,4);

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
#pragma warning(pop)
#endif

