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
#include "../actionbatching/actionbatching.h"


/** include
*/
#include "./opengl_impl.h"
#include "./opengl_impl_include.h"


/** NBsys::NOpengl
*/
#if(BSYS_OPENGL_ENABLE)
namespace NBsys{namespace NOpengl
{
	/** �o�[�e�b�N�X�o�b�t�@�쐬�B
	*/
	class Opengl_Impl_ActionBatching_Shader_Delete : public NBsys::NActionBatching::ActionBatching_ActionItem_Base
	{
	private:

		/** opengl_impl
		*/
		Opengl_Impl& opengl_impl;

		/** shaderstate
		*/
		sharedptr< Opengl_Impl_ShaderState > shaderstate;

	public:

		/** constructor
		*/
		Opengl_Impl_ActionBatching_Shader_Delete(Opengl_Impl& a_opengl_impl,sharedptr< Opengl_Impl_ShaderState >& a_shaderstate)
			:
			opengl_impl(a_opengl_impl),
			shaderstate(a_shaderstate)
		{
		}

		/** destructor
		*/
		virtual ~Opengl_Impl_ActionBatching_Shader_Delete()
		{
		}

	public:

		/** �A�N�V�����J�n�B
		*/
		virtual void Start()
		{
		}

		/** �A�N�V�������B
		*/
		virtual int Do(f32& a_delta,bool a_endrequest)
		{
			if(a_endrequest == true){
				//���f�B
			}

			this->opengl_impl.Render_DeleteShader(this->shaderstate);

			//�����B
			return 1;
		}

	};

}}
#endif

