﻿#pragma once

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
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
	/** バーテックスシェーダー作成。
	*/
	class D3d11_Impl_ActionBatching_VertexShader_Create : public NBsys::NActionBatching::ActionBatching_ActionItem_Base
	{
	private:

		/** d3d11_impl
		*/
		D3d11_Impl& d3d11_impl;

		/** vertexshader
		*/
		sharedptr<D3d11_Impl_VertexShader> vertexshader;

		/** asyncresult
		*/
		AsyncResult<bool> asyncresult;

	public:

		/** constructor
		*/
		D3d11_Impl_ActionBatching_VertexShader_Create(D3d11_Impl& a_d3d11_impl,sharedptr<D3d11_Impl_VertexShader>& a_vertexshader,AsyncResult<bool>& a_asyncresult)
			:
			d3d11_impl(a_d3d11_impl),
			vertexshader(a_vertexshader),
			asyncresult(a_asyncresult)
		{
		}

		/** destructor
		*/
		virtual ~D3d11_Impl_ActionBatching_VertexShader_Create()
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

			//ロード。
			if(this->vertexshader != nullptr){
				if(this->vertexshader->fileobject != nullptr){
					if(this->vertexshader->fileobject->IsBusy() == true){
						//１フレーム消費。
						a_delta -= 1.0f;
						return 0;
					}
				}
			}

			//Render_CreateVertexShader
			this->d3d11_impl.Render_CreateVertexShader(this->vertexshader);

			this->asyncresult.Set(true);

			//成功。
			return 1;
		}

	};

}}
#endif

