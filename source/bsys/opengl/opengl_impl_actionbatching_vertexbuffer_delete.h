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
#include "./opengl_impl_vertexbuffer.h"


/** NBsys::NOpengl
*/
#if(BSYS_OPENGL_ENABLE)
namespace NBsys{namespace NOpengl
{
	/** �o�[�e�b�N�X�o�b�t�@�폜�B
	*/
	class Opengl_Impl_ActionBatching_VertexBuffer_Delete : public NBsys::NActionBatching::ActionBatching_ActionItem_Base
	{
	private:

		/** opengl_impl
		*/
		Opengl_Impl& opengl_impl;

		/** vertexbuffer
		*/
		sharedptr< Opengl_Impl_VertexBuffer > vertexbuffer;

	public:

		/** constructor
		*/
		Opengl_Impl_ActionBatching_VertexBuffer_Delete(Opengl_Impl& a_opengl_impl,const sharedptr< Opengl_Impl_VertexBuffer >& a_vertexbuffer)
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

			//Render_DeleteVertexBuffer
			this->opengl_impl.Render_DeleteVertexBuffer(this->vertexbuffer);

			//�����B
			return 1;
		}
	};

}}
#endif

