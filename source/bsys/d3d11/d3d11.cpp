

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ‚c‚R‚c‚P‚PB
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
	s32 D3d11::CreateVertexShader(AsyncResult< bool >& a_asyncresult)
	{
		return this->impl->CreateVertexShader(a_asyncresult);
	}

	/** CreatePixelShader
	*/
	s32 D3d11::CreatePixelShader(AsyncResult< bool >& a_asyncresult)
	{
		return this->impl->CreatePixelShader(a_asyncresult);
	}

	/** CreatePixelShader
	*/
	s32 D3d11::CreateVertexBuffer(AsyncResult< bool >& a_asyncresult,const void* a_data,s32 a_stridebyte,s32 a_offset,s32 a_countofvertex)
	{
		return this->impl->CreateVertexBuffer(a_asyncresult,a_data,a_stridebyte,a_offset,a_countofvertex);
	}

	/** CreateConstantBuffer
	*/
	s32 D3d11::CreateConstantBuffer(AsyncResult< bool >& a_asyncresult,s32 a_size)
	{
		return this->impl->CreateConstantBuffer(a_asyncresult,a_size);
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

	/** Render_ViewPortB
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
		return this->impl->Render_UpdateSubresource(a_constantbuffer_id,a_data);
	}

	/** Render_VSSetShader
	*/
	void D3d11::Render_VSSetShader(s32 a_vertexshader_id)
	{
		return this->impl->Render_VSSetShader(a_vertexshader_id);
	}

	/** Render_PSSetShader
	*/
	void D3d11::Render_PSSetShader(s32 a_pixelshader_id)
	{
		return this->impl->Render_PSSetShader(a_pixelshader_id);
	}

	/** Render_Draw
	*/
	void D3d11::Render_Draw(s32 a_count_of_vertex,s32 a_start_of_vertex)
	{
		return this->impl->Render_Draw(a_count_of_vertex,a_start_of_vertex);
	}

	/** Render_VSSetConstantBuffers
	*/
	void D3d11::Render_VSSetConstantBuffers(s32 a_startslot,s32 a_constantbuffer_id)
	{
		return this->impl->Render_VSSetConstantBuffers(a_startslot,a_constantbuffer_id);
	}

}}
#endif

