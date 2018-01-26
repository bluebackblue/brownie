#pragma once

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
	/** ピクセルシェーダー作成。
	*/
	class D3d11_Impl_ActionBatching_PixelShader_Create : public NBsys::NActionBatching::ActionBatching_ActionItem_Base
	{
	private:

		/** d3d11_impl
		*/
		D3d11_Impl& d3d11_impl;

		/** pixelshader
		*/
		sharedptr<D3d11_Impl_PixelShader> pixelshader;

		/** asyncresult
		*/
		AsyncResult<bool> asyncresult;

	public:

		/** constructor
		*/
		D3d11_Impl_ActionBatching_PixelShader_Create(D3d11_Impl& a_d3d11_impl,sharedptr<D3d11_Impl_PixelShader>& a_pixelshader,AsyncResult<bool>& a_asyncresult)
			:
			d3d11_impl(a_d3d11_impl),
			pixelshader(a_pixelshader),
			asyncresult(a_asyncresult)
		{
		}

		/** destructor
		*/
		virtual ~D3d11_Impl_ActionBatching_PixelShader_Create()
		{
		}

	private:

		/** copy constructor禁止。
		*/
		D3d11_Impl_ActionBatching_PixelShader_Create(const D3d11_Impl_ActionBatching_PixelShader_Create& a_this) = delete;

		/** コピー禁止。
		*/
		void operator =(const D3d11_Impl_ActionBatching_PixelShader_Create& a_this) = delete;

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
			if(this->pixelshader != nullptr){
				if(this->pixelshader->fileobject != nullptr){
					if(this->pixelshader->fileobject->IsBusy() == true){
						//１フレーム消費。
						a_delta -= 1.0f;
						return 0;
					}
				}
			}

			//Render_CreatePixelShader
			this->d3d11_impl.Render_CreatePixelShader(this->pixelshader);

			this->asyncresult.Set(true);

			//成功。
			return 1;
		}

	};


}}
#pragma warning(pop)
#endif

