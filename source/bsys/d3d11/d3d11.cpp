

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief Ｄ３Ｄ１１。
*/


/** include
*/
#include <bsys_pch.h>


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** include
*/
#include "./d3d11_impl.h"


/** include
*/
#include "./d3d11.h"


/** warning

4710 : この関数はインライン展開のために選択されましたが、コンパイラはインライン展開を実行しませんでした。

*/
#pragma warning(disable:4710)


/** NBsys::Nd3d11
*/
#if(BSYS_D3D11_ENABLE)
namespace NBsys{namespace ND3d11
{
	/** constructor
	*/
	D3d11::D3d11()
	{
		this->impl.reset(new D3d11_Impl());
	}


	/** GetImpl
	*/
	sharedptr<D3d11_Impl>& D3d11::GetImpl()
	{
		return this->impl;
	}


	/** destructor
	*/
	D3d11::~D3d11()
	{
	}


	/** GetSize
	*/
	const Size2DType<f32>& D3d11::GetSize()
	{
		return this->impl->GetSize();
	}


	/** IsExistTexture
	*/
	bool D3d11::IsExistTexture(s32 a_texture_id)
	{
		return this->impl->IsExistTexture(a_texture_id);
	}


	/** テクスチャーＩＤを列挙したリストを作成する。
	*/
	void D3d11::CreateTextureIdList(STLVector<s32>::Type& a_list)
	{
		this->impl->CreateTextureIdList(a_list);
	}


	/** CreateVertexShader
	*/
	s32 D3d11::CreateVertexShader(AsyncResult<bool>& a_asyncresult,sharedptr<NBsys::NFile::File_Object>& a_fileobject,sharedptr<STLVector<NBsys::ND3d11::D3d11_Layout>::Type>& a_layout)
	{
		return this->impl->CreateVertexShader(a_asyncresult,a_fileobject,a_layout);
	}


	/** CreatePixelShader
	*/
	s32 D3d11::CreatePixelShader(AsyncResult<bool>& a_asyncresult,sharedptr<NBsys::NFile::File_Object>& a_fileobject)
	{
		return this->impl->CreatePixelShader(a_asyncresult,a_fileobject);
	}


	/** CreatePixelShader
	*/
	s32 D3d11::CreateVertexBuffer(const void* a_data,s32 a_stridebyte,s32 a_offset,s32 a_countofvertex,bool a_write_flag)
	{
		return this->impl->CreateVertexBuffer(a_data,a_stridebyte,a_offset,a_countofvertex,a_write_flag);
	}


	/** CreateConstantBuffer
	*/
	s32 D3d11::CreateConstantBuffer(s32 a_register_b_index,s32 a_size)
	{
		return this->impl->CreateConstantBuffer(a_register_b_index,a_size);
	}

	
	/** CreateTexture
	*/
	s32 D3d11::CreateTexture(sharedptr<NBsys::NTexture::Texture>& a_texture,bool a_write_flag)
	{
		return this->impl->CreateTexture(a_texture,a_write_flag);
	}


	/** CreateBlendState
	*/
	s32 D3d11::CreateBlendState(bool a_blend_state)
	{
		return this->impl->CreateBlendState(a_blend_state);
	}


	/** CreateRasterizerState
	*/
	s32 D3d11::CreateRasterizerState(D3d11_CullType::Id a_culltype)
	{
		return this->impl->CreateRasterizerState(a_culltype);
	}


	/** CreateDepthStencilState
	*/
	s32 D3d11::CreateDepthStencilState(bool a_depthtest_flag,bool a_depthwrie_flag)
	{
		return this->impl->CreateDepthStencilState(a_depthtest_flag,a_depthwrie_flag);
	}


	/** CreateSamplerState
	*/
	s32 D3d11::CreateSamplerState(const D3d11_Sampler& a_sampler)
	{
		return this->impl->CreateSamplerState(a_sampler);
	}


	/** Render_Create
	*/
	void D3d11::Render_Create(sharedptr<NWindow::Window>& a_window,const Size2DType<f32>& a_size)
	{
		return this->impl->Render_Create(a_window,a_size);
	}


	/** Delete
	*/
	void D3d11::Render_Delete()
	{
		this->impl->Render_Delete();
	}


	/** リクエスト処理。
	*/
	void D3d11::Render_Main()
	{
		this->impl->Render_Main();
	}


	/** スクリーンショット。
	*/
	sharedptr<NBsys::NTexture::Texture> D3d11::Render_ScreenShot()
	{
		return this->impl->Render_ScreenShot();
	}


	/** Render_ViewPort。
	*/
	void D3d11::Render_ViewPort(const Rect2DType_R<f32>& a_rect)
	{
		this->impl->Render_ViewPort(a_rect);
	}


	/** Render_ClearRenderTargetView
	*/
	void D3d11::Render_ClearRenderTargetView(const NBsys::NColor::Color_F& a_color)
	{
		this->impl->Render_ClearRenderTargetView(a_color);
	}


	/** Render_ClearDepthStencilView
	*/
	void D3d11::Render_ClearDepthStencilView()
	{
		this->impl->Render_ClearDepthStencilView();
	}


	/** Render_Present
	*/
	bool D3d11::Render_Present(s32 a_sync_interval)
	{
		return this->impl->Render_Present(a_sync_interval);
	}


	/** Render_SetFont
	*/
	#if(BSYS_FONT_ENABLE)
	void D3d11::Render_SetFont(D3d11_FontTextureType::Id a_fonttexture_type,sharedptr<NBsys::NFont::Font>& a_font,s32 a_texture_width,const STLWString& a_name)
	{
		this->impl->Render_SetFont(a_fonttexture_type,a_font,a_texture_width,a_name);
	}
	#endif


	/** Render_DrawFont_ClearLockFlag
	*/
	#if(BSYS_FONT_ENABLE)
	void D3d11::Render_DrawFont_ClearLockFlag(D3d11_FontTextureType::Id a_fonttexture_type)
	{
		this->impl->Render_DrawFont_ClearLockFlag(a_fonttexture_type);
	}
	#endif


	/** Render_PreUpdateFontTexture
	*/
	#if(BSYS_FONT_ENABLE)
	bool D3d11::Render_PreUpdateFontTexture(D3d11_FontTextureType::Id a_fonttexture_type,const STLWString& a_string)
	{
		return this->impl->Render_PreUpdateFontTexture(a_fonttexture_type,a_string);
	}
	#endif


	/** Render_WriteFontTexture
	*/
	#if(BSYS_FONT_ENABLE)
	void D3d11::Render_WriteFontTexture(D3d11_FontTextureType::Id a_fonttexture_type)
	{
		this->impl->Render_WriteFontTexture(a_fonttexture_type);
	}
	#endif


	/** Render_MakeFontVertex
	*/
	#if(BSYS_FONT_ENABLE)
	void D3d11::Render_MakeFontVertex(D3d11_FontTextureType::Id a_fonttexture_type,const STLWString& a_string,sharedptr<NBsys::NVertex::Vertex<NBsys::NVertex::Vertex_Data_Pos3Uv2Color4TextureIndex4>>& a_vertex,f32 a_x,f32 a_y,f32 a_w,f32 a_h,s32 a_alignment_x,s32 a_alignment_y,f32 a_z,f32 a_view_size_w,f32 a_view_size_h,const NBsys::NColor::Color_F& a_color)
	{
		this->impl->Render_MakeFontVertex(a_fonttexture_type,a_string,a_vertex,a_x,a_y,a_w,a_h,a_alignment_x,a_alignment_y,a_z,a_view_size_w,a_view_size_h,a_color);
	}
	#endif


	/** Render_GetFontTexture
	*/
	#if(BSYS_FONT_ENABLE)
	s32 D3d11::Render_GetFontTexture(D3d11_FontTextureType::Id a_fonttexture_type)
	{
		return this->impl->Render_GetFontTexture(a_fonttexture_type);
	}
	#endif


	/** Render_UpdateSubresource
	*/
	void D3d11::Render_UpdateSubresource(s32 a_constantbuffer_id,const void* a_data)
	{
		this->impl->Render_UpdateSubresource(a_constantbuffer_id,a_data);
	}


	/** Render_VSSetShader
	*/
	void D3d11::Render_VSSetShader(s32 a_vertexshader_id)
	{
		this->impl->Render_VSSetShader(a_vertexshader_id);
	}


	/** Render_PSSetShader
	*/
	void D3d11::Render_PSSetShader(s32 a_pixelshader_id)
	{
		this->impl->Render_PSSetShader(a_pixelshader_id);
	}


	/** Render_Draw
	*/
	void D3d11::Render_Draw(s32 a_count_of_vertex,s32 a_start_of_vertex)
	{
		this->impl->Render_Draw(a_count_of_vertex,a_start_of_vertex);
	}


	/** Render_VSSetConstantBuffers
	*/
	void D3d11::Render_VSSetConstantBuffers(s32 a_constantbuffer_id)
	{
		this->impl->Render_VSSetConstantBuffers(a_constantbuffer_id);
	}


	/** Render_PSSetConstantBuffers
	*/
	void D3d11::Render_PSSetConstantBuffers(s32 a_constantbuffer_id)
	{
		this->impl->Render_PSSetConstantBuffers(a_constantbuffer_id);
	}


	/** Render_SetVertexBuffer
	*/
	void D3d11::Render_SetVertexBuffer(s32 a_vertexbuffer_id)
	{
		this->impl->Render_SetVertexBuffer(a_vertexbuffer_id);
	}


	/** Render_ReMapVertexBuffer
	*/
	void D3d11::Render_ReMapVertexBuffer(s32 a_vertexbuffer_id,const void* a_data,s32 a_size)
	{
		this->impl->Render_ReMapVertexBuffer(a_vertexbuffer_id,a_data,a_size);
	}


	/** Render_SetPrimitiveTopology
	*/
	void D3d11::Render_SetPrimitiveTopology(D3d11_TopologyType::Id a_topology_type)
	{
		this->impl->Render_SetPrimitiveTopology(a_topology_type);
	}


	/** Render_SetTexture
	*/
	void D3d11::Render_SetTexture(s32 a_register_t_index,s32 a_texture_id)
	{
		this->impl->Render_SetTexture(a_register_t_index,a_texture_id);
	}


	/** Render_SetBlendState
	*/
	void D3d11::Render_SetBlendState(s32 a_blendstate_id)
	{
		this->impl->Render_SetBlendState(a_blendstate_id);
	}


	/** Render_SetRasterizerState
	*/
	void D3d11::Render_SetRasterizerState(s32 a_rasterizerstate_id)
	{
		this->impl->Render_SetRasterizerState(a_rasterizerstate_id);
	}


	/** Render_SetDepthStencilState
	*/
	void D3d11::Render_SetDepthStencilState(s32 a_depthstencilstate_id)
	{
		this->impl->Render_SetDepthStencilState(a_depthstencilstate_id);
	}


	/** Render_SetSamplerState
	*/
	void D3d11::Render_SetSamplerState(s32 a_register_index,s32 a_samplerstate_id)
	{
		this->impl->Render_SetSamplerState(a_register_index,a_samplerstate_id);
	}


}}
#endif

