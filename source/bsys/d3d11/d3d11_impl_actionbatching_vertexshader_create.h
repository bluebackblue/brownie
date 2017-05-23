#pragma once

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �c�R�c�P�P�B
*/


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./d3d11_impl.h"
#include "../actionbatching/actionbatching.h"


/** NBsys::ND3d11
*/
#if(BSYS_D3D11_ENABLE)
namespace NBsys{namespace ND3d11
{
	/** �o�[�e�b�N�X�V�F�[�_�[�쐬�B
	*/
	class Opengl_Impl_ActionBatching_VertexShader_Create : public NBsys::NActionBatching::ActionBatching_ActionItem_Base
	{
	private:

		/** d3d11_impl
		*/
		D3d11_Impl& d3d11_impl;

		/** vertexshader
		*/
		sharedptr< D3d11_Impl_VertexShader > vertexshader;

		/** asyncresult
		*/
		AsyncResult< bool > asyncresult;

	public:

		/** constructor
		*/
		Opengl_Impl_ActionBatching_VertexShader_Create(D3d11_Impl& a_d3d11_impl,sharedptr< D3d11_Impl_VertexShader >& a_vertexshader,AsyncResult< bool >& a_asyncresult)
			:
			d3d11_impl(a_d3d11_impl),
			vertexshader(a_vertexshader),
			asyncresult(a_asyncresult)
		{
		}

		/** destructor
		*/
		virtual ~Opengl_Impl_ActionBatching_VertexShader_Create()
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

			//���[�h�B
			if(this->vertexshader != nullptr){
				if(this->vertexshader->fileobject != nullptr){
					if(this->vertexshader->fileobject->IsBusy() == true){
						return 0;
					}
				}
			}

			//Render_CreateVertexShader
			this->d3d11_impl.Render_CreateVertexShader(this->vertexshader);

			this->asyncresult.Set(true);

			//�����B
			return 1;
		}

	};

}}
#endif

