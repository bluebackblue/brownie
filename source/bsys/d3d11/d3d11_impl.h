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
		/** Create
		*/
		void Create(sharedptr< NWindow::Window >& a_window,s32 a_width,s32 a_height);

		/** Delete
		*/
		void Delete();

		/** GetDevice
		*/
		sharedptr< ID3D11Device >& GetDevice();

		/** GetDeviceContext
		*/
		sharedptr< ID3D11DeviceContext >& GetDeviceContext();

		/** GetSwapChain
		*/
		sharedptr< IDXGISwapChain >& GetSwapChain();

		/** GetBackBuffer
		*/
		sharedptr< ID3D11Texture2D >& GetBackBuffer();

		/** GetRenderTargetView
		*/
		sharedptr< ID3D11RenderTargetView >& GetRenderTargetView();

		/** GetDepthBuffer
		*/
		sharedptr< ID3D11Texture2D >& GetDepthBuffer();

		/** GetDepthStencilState
		*/
		sharedptr< ID3D11DepthStencilState >& GetDepthStencilState();

		/** GetDepthStencilView
		*/
		sharedptr< ID3D11DepthStencilView >& GetDepthStencilView();



		/** Clear
		*/
		/*
		void Clear();
		*/

		/** BeginScene
		*/
		/*
		void BeginScene();
		*/

		/** EndScene
		*/
		/*
		void EndScene();
		*/

		/** device
		*/
		/*
		ID3D11Device* GetDevice();
		*/

		/** devicecontext
		*/
		/*
		ID3D11DeviceContext* GetDeviceContext();
		*/

		/** swapchain
		*/
		/*
		IDXGISwapChain* GetSwapChain();
		*/

		/** rendertargetview
		*/
		/*
		ID3D11RenderTargetView* GetRenderTargetView();
		*/

		/** depthstencil_texture
		*/
		/*
		ID3D11Texture2D* GetDepthstencilTexture();
		*/

		/** depthstencil_view
		*/
		/*
		ID3D11DepthStencilView* GetDepthstencilView();
		*/
	};

}}
#endif

