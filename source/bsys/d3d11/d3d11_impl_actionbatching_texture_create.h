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
	/** �e�N�X�`���[�쐬�B
	*/
	class D3d11_Impl_ActionBatching_Texture_Create : public NBsys::NActionBatching::ActionBatching_ActionItem_Base
	{
	private:

		/** d3d11_impl
		*/
		D3d11_Impl& d3d11_impl;

		/** texture
		*/
		sharedptr<D3d11_Impl_Texture> texture;

	public:

		/** constructor
		*/
		D3d11_Impl_ActionBatching_Texture_Create(D3d11_Impl& a_d3d11_impl,sharedptr<D3d11_Impl_Texture>& a_texture)
			:
			d3d11_impl(a_d3d11_impl),
			texture(a_texture)
		{
		}

		/** destructor
		*/
		virtual ~D3d11_Impl_ActionBatching_Texture_Create()
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

			//Render_CreateTexture
			this->d3d11_impl.Render_CreateTexture(this->texture);

			//�����B
			return 1;
		}

	};

}}
#endif

