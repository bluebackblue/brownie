#pragma once

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief Ｄ３Ｄ１１。
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
#include "./d3d11_impl.h"


/** NBsys::ND3d11
*/
#if(BSYS_D3D11_ENABLE)
#pragma warning(push)
#pragma warning(disable:4710)
namespace NBsys{namespace ND3d11
{
	/** ラスタライザステート作成。
	*/
	class D3d11_Impl_ActionBatching_RasterizerState_Create : public NBsys::NActionBatching::ActionBatching_ActionItem_Base
	{
	private:

		/** d3d11_impl
		*/
		D3d11_Impl& d3d11_impl;

		/** RasterizerState
		*/
		sharedptr<D3d11_Impl_RasterizerState> rasterizerstate;

	public:

		/** constructor
		*/
		D3d11_Impl_ActionBatching_RasterizerState_Create(D3d11_Impl& a_d3d11_impl,sharedptr<D3d11_Impl_RasterizerState>& a_rasterizerstate)
			:
			d3d11_impl(a_d3d11_impl),
			rasterizerstate(a_rasterizerstate)
		{
		}

		/** destructor
		*/
		virtual ~D3d11_Impl_ActionBatching_RasterizerState_Create()
		{
		}

	private:

		/** copy constructor禁止。
		*/
		D3d11_Impl_ActionBatching_RasterizerState_Create(const D3d11_Impl_ActionBatching_RasterizerState_Create& a_this) = delete;

		/** コピー禁止。
		*/
		void operator =(const D3d11_Impl_ActionBatching_RasterizerState_Create& a_this) = delete;

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

			//Render_CreateRasterizerState
			this->d3d11_impl.Render_CreateRasterizerState(this->rasterizerstate);

			//成功。
			return 1;
		}

	};


}}
#pragma warning(pop)
#endif

