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
	class Opengl_Impl_ActionBatching_Shader_Load : public NBsys::NActionBatching::ActionBatching_ActionItem_Base
	{
	private:

		/** opengl_impl
		*/
		Opengl_Impl& opengl_impl;

		/** shaderlayout
		*/
		sharedptr<Opengl_ShaderLayout> shaderlayout;

		/** asyncresult
		*/
		AsyncResult<bool> asyncresult;

	public:

		/** constructor
		*/
		Opengl_Impl_ActionBatching_Shader_Load(Opengl_Impl& a_opengl_impl,const sharedptr<Opengl_ShaderLayout>& a_shaderlayout,AsyncResult<bool>& a_asyncresult)
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

		/** アクション開始。
		*/
		virtual void Start()
		{
		}

		/** アクション中。
		*/
		virtual s32 Do(f32& a_delta,bool a_endrequest)
		{
			if(a_endrequest == true){
				//中断。
			}

			if(this->shaderlayout->IsBusy() == true){
				//継続。
				a_delta -= 1.0f;
				return 0;
			}

			//Render_LoadShader
			this->opengl_impl.Render_LoadShader(this->shaderlayout);

			//asyncresult
			this->asyncresult.Set(true);

			//成功。
			return 1;
		}

	};

}}
#endif

