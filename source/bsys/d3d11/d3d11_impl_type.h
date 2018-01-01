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
#if(BSYS_D3D11_ENABLE)
	#include <brownie_config/d3d11_include.h>
#endif


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../file/file.h"
#include "../texture/texture.h"
#pragma warning(pop)


/** include
*/
#include "./d3d11_layout.h"
#include "./d3d11_sampler.h"


/** NBsys::ND3d11
*/
#if(BSYS_D3D11_ENABLE)
#pragma warning(push)
#pragma warning(disable:4710 4820)
namespace NBsys{namespace ND3d11
{
	/** D3d11_Impl_VertexShader
	*/
	struct D3d11_Impl_VertexShader
	{
		/** vertexshader
		*/
		sharedptr<ID3D11VertexShader> vertexshader;
		
		/** inputlayout
		*/
		sharedptr<ID3D11InputLayout> inputlayout;

		/** fileobject
		*/
		#if(BSYS_FILE_ENABLE)
		sharedptr<NBsys::NFile::File_Object> fileobject; 
		#endif

		/** layout
		*/
		sharedptr<STLVector<NBsys::ND3d11::D3d11_Layout>::Type> layout;
	};


	/** D3d11_Impl_PixelShader
	*/
	struct D3d11_Impl_PixelShader
	{
		/** pixelshader
		*/
		sharedptr<ID3D11PixelShader> pixelshader;

		/** fileobject
		*/
		#if(BSYS_FILE_ENABLE)
		sharedptr<NBsys::NFile::File_Object> fileobject; 
		#endif
	};


	/** D3d11_Impl_VertexBuffer
	*/
	struct D3d11_Impl_VertexBuffer
	{
		/** buffer
		*/
		sharedptr<ID3D11Buffer> buffer;

		/** data
		*/
		const void* data;

		/** stridebyte
		*/
		s32 stridebyte;

		/** offset
		*/
		s32 offset;

		/** countofvertex
		*/
		s32 countofvertex;

		/** write_flag
		*/
		bool write_flag;
	};


	/** D3d11_Impl_ConstantBuffer
	*/
	struct D3d11_Impl_ConstantBuffer
	{
		/** buffer
		*/
		sharedptr<ID3D11Buffer> buffer;

		/** size
		*/
		s32 size;

		/** register_b_index
		*/
		s32 register_b_index;
	};


	/** D3d11_Impl_Texture
	*/
	struct D3d11_Impl_Texture
	{
		/** texture2d
		*/
		sharedptr<ID3D11Texture2D> texture2d;

		/** texture
		*/
		sharedptr<NBsys::NTexture::Texture> texture;

		/** resourceview
		*/
		sharedptr<ID3D11ShaderResourceView> resourceview;
	};


	/** D3d11_Impl_BlendState
	*/
	struct D3d11_Impl_BlendState
	{
		/** blendstate
		*/
		sharedptr<ID3D11BlendState> blendstate;

		/** alpha_blend
		*/
		bool alpha_blend;
	};


	/** D3d11_Impl_RasterizerState
	*/
	struct D3d11_Impl_RasterizerState
	{
		/** rasterizerstate
		*/
		sharedptr<ID3D11RasterizerState> rasterizerstate;

		/** culltype
		*/
		D3d11_CullType::Id culltype;
	};


	/** D3d11_Impl_DepthStencilState
	*/
	struct D3d11_Impl_DepthStencilState
	{
		/** rasterizerstate
		*/
		sharedptr<ID3D11DepthStencilState> depthstencilstate;

		/** depthtest_flag
		*/
		bool depthtest_flag;
		
		/** depthwrie_flag
		*/
		bool depthwrie_flag;
	};


	/** D3d11_Impl_SamplerState
	*/
	struct D3d11_Impl_SamplerState
	{
		/** rasterizerstate
		*/
		sharedptr<ID3D11SamplerState> samplerstate;

		/** sampler
		*/
		D3d11_Sampler sampler;
	};


}}
#pragma warning(pop)
#endif

