

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

	/** Render_CreateBuffer
	*/
	void D3d11::Render_CreateBuffer()
	{
		this->impl->Render_CreateBuffer();
	}

	/** Render_Present
	*/
	bool D3d11::Render_Present()
	{
		return this->impl->Render_Present();
	}

}}
#endif

