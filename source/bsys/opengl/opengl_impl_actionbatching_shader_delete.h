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
	/** バーテックスバッファ作成。
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

		/** アクション開始。
		*/
		virtual void Start()
		{
		}

		/** アクション中。
		*/
		virtual int Do(f32& a_delta,bool a_endrequest)
		{
			if(a_endrequest == true){
				//中断。
			}

			this->opengl_impl.Render_DeleteShader(this->shaderstate);

			//成功。
			return 1;
		}

	};

}}
#endif

