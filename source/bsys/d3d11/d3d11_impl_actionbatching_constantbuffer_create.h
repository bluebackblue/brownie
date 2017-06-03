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
	/** �R���X�^���g�o�b�t�@�[�쐬�B
	*/
	class D3d11_Impl_ActionBatching_ConstantBuffer_Create : public NBsys::NActionBatching::ActionBatching_ActionItem_Base
	{
	private:

		/** d3d11_impl
		*/
		D3d11_Impl& d3d11_impl;

		/** constantbuffer
		*/
		sharedptr< D3d11_Impl_ConstantBuffer > constantbuffer;

	public:

		/** constructor
		*/
		D3d11_Impl_ActionBatching_ConstantBuffer_Create(D3d11_Impl& a_d3d11_impl,sharedptr< D3d11_Impl_ConstantBuffer >& a_constantbuffer)
			:
			d3d11_impl(a_d3d11_impl),
			constantbuffer(a_constantbuffer)
		{
		}

		/** destructor
		*/
		virtual ~D3d11_Impl_ActionBatching_ConstantBuffer_Create()
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

			//Render_CreateConstantBuffer
			this->d3d11_impl.Render_CreateConstantBuffer(this->constantbuffer);

			//�����B
			return 1;
		}

	};

}}
#endif

