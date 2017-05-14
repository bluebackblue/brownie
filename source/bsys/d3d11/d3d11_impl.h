#pragma once

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ÇcÇRÇcÇPÇPÅB
*/


/** include
*/
#include "../types/types.h"


/** include
*/
#include "../../blib/include_windows.h"


/** include
*/
#include "../window/window.h"
#include "../color/color.h"


/** include
*/
#if(BSYS_D3D11_ENABLE)

	#include <dxgi1_2.h>
	#include <d3d11.h>
	#include <d3dcompiler.h>
	
#endif


/** NBsys::ND3d11
*/
#if(BSYS_D3D11_ENABLE)
namespace NBsys{namespace ND3d11
{

	/** D3d11_Impl
	*/
	class D3d11_Impl
	{
	private:
		/** device
		*/
		sharedptr< ID3D11Device > device;

		/** devicecontext
		*/
		sharedptr< ID3D11DeviceContext > devicecontext;
		
		/** swapchain
		*/
		sharedptr< IDXGISwapChain > swapchain;

		/** backbuffer
		*/
		sharedptr< ID3D11Texture2D > backbuffer;

		/** rendertargetview
		*/
		sharedptr< ID3D11RenderTargetView > rendertargetview;

		/** depthbuffer
		*/
		sharedptr< ID3D11Texture2D > depthbuffer;

		/** depthstencilstate
		*/
		sharedptr< ID3D11DepthStencilState > depthstencilstate;

		/** depthstencilview
		*/
		sharedptr< ID3D11DepthStencilView > depthstencilview;

		/** buffer
		*/
		sharedptr< ID3D11Buffer > buffer;

		/** texture_list
		*/
		//STLMap< Muid::UniqueNameType , D3d11_Texture >::Type texture_list;
		
		/** vertexshader_list
		*/
		//STLMap< Muid::UniqueNameType , D3d11_VertexShader >::Type vertexshader_list;

	public:
		/** constructor
		*/
		D3d11_Impl();

		/** destructor
		*/
		nonvirtual ~D3d11_Impl();

	public:
		/** Render_Create
		*/
		void Render_Create(sharedptr< NWindow::Window >& a_window,s32 a_width,s32 a_height);

		/** Render_Delete
		*/
		void Render_Delete();

		/** Render_GetDevice
		*/
		sharedptr< ID3D11Device >& GetDevice();

		/** Render_GetDeviceContext
		*/
		sharedptr< ID3D11DeviceContext >& GetDeviceContext();

		/** Render_GetSwapChain
		*/
		sharedptr< IDXGISwapChain >& GetSwapChain();

		/** Render_GetBackBuffer
		*/
		sharedptr< ID3D11Texture2D >& GetBackBuffer();

		/** Render_GetRenderTargetView
		*/
		sharedptr< ID3D11RenderTargetView >& GetRenderTargetView();

		/** Render_GetDepthBuffer
		*/
		sharedptr< ID3D11Texture2D >& GetDepthBuffer();

		/** Render_GetDepthStencilState
		*/
		sharedptr< ID3D11DepthStencilState >& GetDepthStencilState();

		/** Render_GetDepthStencilView
		*/
		sharedptr< ID3D11DepthStencilView >& GetDepthStencilView();

		/** Render_GetBuffer
		*/
		sharedptr< ID3D11Buffer >& GetBuffer();

	public:

		/** Render_ViewPortÅB
		*/
		void Render_ViewPort(f32 a_x,f32 a_y,f32 a_width,f32 a_height);

		/** Render_ClearRenderTargetView
		*/
		void Render_ClearRenderTargetView(NBsys::NColor::Color_F& a_color);

		/** Render_ClearDepthStencilView
		*/
		void Render_ClearDepthStencilView();

		/** Render_CreateBuffer
		*/
		void Render_CreateBuffer();

		/** Render_Present
		*/
		bool Render_Present();
	};

}}
#endif

