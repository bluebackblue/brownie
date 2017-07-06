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
	class Opengl_Impl_ActionBatching_Shader_Load : public NBsys::NActionBatching::ActionBatching_ActionItem_Base
	{
	private:

		/** opengl_impl
		*/
		Opengl_Impl& opengl_impl;

		/** shaderlayout
		*/
		sharedptr< Opengl_ShaderLayout > shaderlayout;

		/** asyncresult
		*/
		AsyncResult< bool > asyncresult;

	public:

		/** constructor
		*/
		Opengl_Impl_ActionBatching_Shader_Load(Opengl_Impl& a_opengl_impl,const sharedptr< Opengl_ShaderLayout >& a_shaderlayout,AsyncResult< bool >& a_asyncresult)
			:
			opengl_impl(a_opengl_impl),
			shaderlayout(a_shaderlayout),
			asyncresult(a_asyncresult)
		{
		}

		/** destructor
		*/
		virtual ~Opengl_Impl_ActionBatching_Shader_Load()
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
		virtual s32 Do(f32& a_delta,bool a_endrequest)
		{
			if(a_endrequest == true){
				//���f�B
			}

			if(this->shaderlayout->IsBusy() == true){
				//�p���B
				a_delta -= 1.0f;
				return 0;
			}

			//Render_LoadShader
			this->opengl_impl.Render_LoadShader(this->shaderlayout);

			//asyncresult
			this->asyncresult.Set(true);

			//�����B
			return 1;
		}

	};

}}
#endif

