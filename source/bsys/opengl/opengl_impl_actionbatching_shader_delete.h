#pragma once

/**
 * Copyright (c) blueback
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
#pragma warning(push)
#pragma warning(disable:4464)
#include "../actionbatching/actionbatching.h"
#pragma warning(pop)


/** include
*/
#include "./opengl_impl.h"
#include "./opengl_impl_include.h"


/** NBsys::NOpengl
*/
#if(BSYS_OPENGL_ENABLE)
#pragma warning(push)
#pragma warning(disable:4710)
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
		sharedptr<Opengl_Impl_ShaderState> shaderstate;

	public:

		/** constructor
		*/
		Opengl_Impl_ActionBatching_Shader_Delete(Opengl_Impl& a_opengl_impl,sharedptr<Opengl_Impl_ShaderState>& a_shaderstate)
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

	private:

		/** copy constructor禁止。
		*/
		Opengl_Impl_ActionBatching_Shader_Delete(const Opengl_Impl_ActionBatching_Shader_Delete& a_this) = delete;

		/** コピー禁止。
		*/
		void operator =(const Opengl_Impl_ActionBatching_Shader_Delete& a_this) = delete;

	public:

		/** アクション開始。
		*/
		virtual void Start()
		{
		}

		/** アクション中。
		*/
		virtual s32 Do(f32& /*a_delta*/,bool a_endrequest)
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
#pragma warning(pop)
#endif

