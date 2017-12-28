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
#include "./d3d11_impl.h"
#include "../actionbatching/actionbatching.h"


/** NBsys::ND3d11
*/
#if(BSYS_D3D11_ENABLE)
namespace NBsys{namespace ND3d11
{
	/** テクスチャー作成。
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

		/** write_flag
		*/
		bool write_flag;

	public:

		/** constructor
		*/
		D3d11_Impl_ActionBatching_Texture_Create(D3d11_Impl& a_d3d11_impl,sharedptr<D3d11_Impl_Texture>& a_texture,bool a_write_flag)
			:
			d3d11_impl(a_d3d11_impl),
			texture(a_texture),
			write_flag(a_write_flag)
		{
		}

		/** destructor
		*/
		virtual ~D3d11_Impl_ActionBatching_Texture_Create()
		{
		}

	private:

		/** copy constructor禁止。
		*/
		D3d11_Impl_ActionBatching_Texture_Create(const D3d11_Impl_ActionBatching_Texture_Create& a_this) = delete;

		/** コピー禁止。
		*/
		void operator =(const D3d11_Impl_ActionBatching_Texture_Create& a_this) = delete;

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

			//Render_CreateTexture
			this->d3d11_impl.Render_CreateTexture(this->texture,this->write_flag);

			//成功。
			return 1;
		}

	};


}}
#endif

