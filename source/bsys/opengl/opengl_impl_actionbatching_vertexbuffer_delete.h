﻿#pragma once

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
#pragma warning(push)
#pragma warning(disable:4464)
#include "../actionbatching/actionbatching.h"
#pragma warning(pop)


/** include
*/
#include "./opengl_impl.h"
#include "./opengl_impl_include.h"
#include "./opengl_impl_vertexbuffer.h"


/** NBsys::NOpengl
*/
#if(BSYS_OPENGL_ENABLE)
namespace NBsys{namespace NOpengl
{
	/** バーテックスバッファ削除。
	*/
	class Opengl_Impl_ActionBatching_VertexBuffer_Delete : public NBsys::NActionBatching::ActionBatching_ActionItem_Base
	{
	private:

		/** opengl_impl
		*/
		Opengl_Impl& opengl_impl;

		/** vertexbuffer
		*/
		sharedptr<Opengl_Impl_VertexBuffer> vertexbuffer;

	public:

		/** constructor
		*/
		Opengl_Impl_ActionBatching_VertexBuffer_Delete(Opengl_Impl& a_opengl_impl,const sharedptr<Opengl_Impl_VertexBuffer>& a_vertexbuffer)
			:
			opengl_impl(a_opengl_impl),
			vertexbuffer(a_vertexbuffer)
		{
		}

		/** destructor
		*/
		virtual ~Opengl_Impl_ActionBatching_VertexBuffer_Delete()
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

			//Render_DeleteVertexBuffer
			this->opengl_impl.Render_DeleteVertexBuffer(this->vertexbuffer);

			//成功。
			return 1;
		}
	};

}}
#endif

