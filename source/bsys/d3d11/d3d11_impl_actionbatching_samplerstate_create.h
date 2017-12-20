#pragma once

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief Ｄ３Ｄ１１。
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
	/** サンプラーステート作成。
	*/
	class D3d11_Impl_ActionBatching_SamplerState_Create : public NBsys::NActionBatching::ActionBatching_ActionItem_Base
	{
	private:

		/** d3d11_impl
		*/
		D3d11_Impl& d3d11_impl;

		/** SamplerState
		*/
		sharedptr<D3d11_Impl_SamplerState> samplerstate;

	public:

		/** constructor
		*/
		D3d11_Impl_ActionBatching_SamplerState_Create(D3d11_Impl& a_d3d11_impl,sharedptr<D3d11_Impl_SamplerState>& a_samplerstate)
			:
			d3d11_impl(a_d3d11_impl),
			samplerstate(a_samplerstate)
		{
		}

		/** destructor
		*/
		virtual ~D3d11_Impl_ActionBatching_SamplerState_Create()
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

			//Render_CreateSamplerState
			this->d3d11_impl.Render_CreateSamplerState(this->samplerstate);

			//成功。
			return 1;
		}

	};


}}
#endif

