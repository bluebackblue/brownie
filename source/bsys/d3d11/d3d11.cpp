

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


/** include
*/
#include "./d3d11.h"


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
	sharedptr< D3d11_Impl >& D3d11::GetImpl()
	{
		return this->impl;
	}

	/** destructor
	*/
	D3d11::~D3d11()
	{
	}

	/** CreateVertexShader
	*/
	s32 D3d11::CreateVertexShader(AsyncResult< bool >& a_asyncresult,sharedptr< NBsys::NFile::File_Object >& a_fileobject,sharedptr< STLVector< NBsys::ND3d11::D3d11_Layout >::Type >& a_layout)
	{
		return this->impl->CreateVertexShader(a_asyncresult,a_fileobject,a_layout);
	}

	/** CreatePixelShader
	*/
	s32 D3d11::CreatePixelShader(AsyncResult< bool >& a_asyncresult,sharedptr< NBsys::NFile::File_Object >& a_fileobject)
	{
		return this->impl->CreatePixelShader(a_asyncresult,a_fileobject);
	}

	/** CreatePixelShader
	*/
	s32 D3d11::CreateVertexBuffer(const void* a_data,s32 a_stridebyte,s32 a_offset,s32 a_countofvertex)
	{
		return this->impl->CreateVertexBuffer(a_data,a_stridebyte,a_offset,a_countofvertex);
	}

	/** CreateConstantBuffer
	*/
	s32 D3d11::CreateConstantBuffer(s32 a_register_b_index,s32 a_size)
	{
		return this->impl->CreateConstantBuffer(a_register_b_index,a_size);
	}
	
	/** CreateTexture
	*/
	s32 D3d11::CreateTexture(sharedptr< NBsys::NTexture::Texture >& a_texture)
	{
		return this->impl->CreateTexture(a_texture);
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

	/** Render_Create
	*/
	void D3d11::Render_Create(sharedptr< NWindow::Window >& a_window,s32 a_width,s32 a_height)
	{
		return this->impl->Render_Create(a_window,a_width,a_height);
	}

	/** Delete
	*/
	void D3d11::Render_Delete()
	{
		this->impl->Render_Delete();
	}

	/** Render_Main
	*/
	void D3d11::Render_Main()
	{
		this->impl->Render_Main();
	}

	/** Render_ViewPort�B
	*/
	void D3d11::Render_ViewPort(f32 a_x,f32 a_y,f32 a_width,f32 a_height)
	{
		this->impl->Render_ViewPort(a_x,a_y,a_width,a_height);
	}

	/** Render_ClearRenderTargetView
	*/
	void D3d11::Render_ClearRenderTargetView(NBsys::NColor::Color_F& a_color)
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
	bool D3d11::Render_Present()
	{
		return this->impl->Render_Present();
	}

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

	/** Render_IASetInputLayout
	*/
	void D3d11::Render_IASetInputLayout(s32 a_vertexshader_id)
	{
		this->impl->Render_IASetInputLayout(a_vertexshader_id);
	}

	/** Render_IASetVertexBuffers
	*/
	void D3d11::Render_IASetVertexBuffers(s32 a_vertexbuffer_id)
	{
		this->impl->Render_IASetVertexBuffers(a_vertexbuffer_id);
	}

	/** Render_IASetPrimitiveTopology_TriangleList
	*/
	void D3d11::Render_IASetPrimitiveTopology_TriangleList()
	{
		this->impl->Render_IASetPrimitiveTopology_TriangleList();
	}

	/** Render_IASetPrimitiveTopology_TriangleStrip
	*/
	void D3d11::Render_IASetPrimitiveTopology_TriangleStrip()
	{
		this->impl->Render_IASetPrimitiveTopology_TriangleStrip();
	}

	/** Render_IASetPrimitiveTopology_PointList
	*/
	void D3d11::Render_IASetPrimitiveTopology_PointList()
	{
		this->impl->Render_IASetPrimitiveTopology_PointList();
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

}}
#endif

