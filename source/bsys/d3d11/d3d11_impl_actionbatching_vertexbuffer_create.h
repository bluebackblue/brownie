﻿#pragma once

/**
 * Copyright (c) blueback
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
	/** バーテックスバッファー作成。
	*/
	class D3d11_Impl_ActionBatching_VertexBuffer_Create : public NBsys::NActionBatching::ActionBatching_ActionItem_Base
	{
	private:

		/** d3d11_impl
		*/
		D3d11_Impl& d3d11_impl;

		/** vertexbuffer
		*/
		sharedptr<D3d11_Impl_VertexBuffer> vertexbuffer;

	public:

		/** constructor
		*/
		D3d11_Impl_ActionBatching_VertexBuffer_Create(D3d11_Impl& a_d3d11_impl,sharedptr<D3d11_Impl_VertexBuffer>& a_vertexbuffer)
			:
			d3d11_impl(a_d3d11_impl),
			vertexbuffer(a_vertexbuffer)
		{
		}

		/** destructor
		*/
		virtual ~D3d11_Impl_ActionBatching_VertexBuffer_Create()
		{
		}

	private:

		/** copy constructor禁止。
		*/
		D3d11_Impl_ActionBatching_VertexBuffer_Create(const D3d11_Impl_ActionBatching_VertexBuffer_Create& a_this) = delete;

		/** コピー禁止。
		*/
		void operator =(const D3d11_Impl_ActionBatching_VertexBuffer_Create& a_this) = delete;

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

			//Render_CreateVertexBuffer
			this->d3d11_impl.Render_CreateVertexBuffer(this->vertexbuffer);

			//成功。
			return 1;
		}

	};


}}
#pragma warning(pop)
#endif

