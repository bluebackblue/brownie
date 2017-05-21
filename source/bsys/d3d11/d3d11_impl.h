#pragma once

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief Ｄ３Ｄ１１。
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
#include "../actionbatching/actionbatching.h"


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

	/** D3d11_Impl_VertexShader
	*/
	struct D3d11_Impl_VertexShader
	{
		/** vertexshader
		*/
		sharedptr< ID3D11VertexShader > vertexshader;
		
		/** inputlayout
		*/
		sharedptr< ID3D11InputLayout > inputlayout;
	};

	/** D3d11_Impl_PixelShader
	*/
	struct D3d11_Impl_PixelShader
	{
		/** pixelshader
		*/
		sharedptr< ID3D11PixelShader > pixelshader;
	};

	/** D3d11_Impl_VertexBuffer
	*/
	struct D3d11_Impl_VertexBuffer
	{
		/** buffer
		*/
		sharedptr< ID3D11Buffer > buffer;

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
	};

	/** D3d11_Impl_ConstantBuffer
	*/
	struct D3d11_Impl_ConstantBuffer
	{
		/** buffer
		*/
		sharedptr< ID3D11Buffer > buffer;

		/** size
		*/
		s32 size;
	};

	/** D3d11_Impl
	*/
	class D3d11_Impl
	{
	private:

		/** id_maker
		*/
		IDMaker id_maker;

		/** アクションバッチング。ロックオブジェクト。
		*/
		LockObject actionbatching_lockobject;

		/** アクションバッチング。
		*/
		NBsys::NActionBatching::ActionBatching actionbatching;

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

	private:

		/** vertexshader_list
		*/
		STLMap< s32 , sharedptr< D3d11_Impl_VertexShader > >::Type vertexshader_list;

		/** pixelshader_list
		*/
		STLMap< s32 , sharedptr< D3d11_Impl_PixelShader > >::Type pixelshader_list;

		/** vertexbuffer_list
		*/
		STLMap< s32 , sharedptr< D3d11_Impl_VertexBuffer > >::Type vertexbuffer_list;

		/** constantbuffer_list
		*/
		STLMap< s32 , sharedptr< D3d11_Impl_ConstantBuffer > >::Type constantbuffer_list;

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

	public:

		/** GetVertexshader
		*/
		sharedptr< D3d11_Impl_VertexShader > GetVertexShader(s32 a_vertexshader_id);

		/** GetPixelshader
		*/
		sharedptr< D3d11_Impl_PixelShader > GetPixelShader(s32 a_pixelshader_id);

		/** GetVertexbuffer
		*/
		sharedptr< D3d11_Impl_VertexBuffer > GetVertexBuffer(s32 a_vertexbuffer_id);

		/** GetConstantBuffer
		*/
		sharedptr< D3d11_Impl_ConstantBuffer > GetConstantBuffer(s32 a_constantbuffer_id);

	public:

		/** CreateVertexShader
		*/
		s32 CreateVertexShader(AsyncResult< bool >& a_asyncresult);

		/** CreatePixelShader
		*/
		s32 CreatePixelShader(AsyncResult< bool >& a_asyncresult);

		/** CreateVertexBuffer
		*/
		s32 CreateVertexBuffer(AsyncResult< bool >& a_asyncresult,const void* a_data,s32 a_stridebyte,s32 a_offset,s32 a_countofvertex);

		/** CreateConstantBuffer
		*/
		s32 CreateConstantBuffer(AsyncResult< bool >& a_asyncresult,s32 a_size);

	public:

		/** Render_CreateVertexShader
		*/
		void Render_CreateVertexShader(sharedptr< D3d11_Impl_VertexShader >& a_vertexshader);

		/** Render_CreatePixelShader
		*/
		void Render_CreatePixelShader(sharedptr< D3d11_Impl_PixelShader >& a_pixelshader);

		/** Render_CreateVertexBuffer
		*/
		void Render_CreateVertexBuffer(sharedptr< D3d11_Impl_VertexBuffer >& a_pixelshader);

		/** Render_CreateConstantBuffer
		*/
		void Render_CreateConstantBuffer(sharedptr< D3d11_Impl_ConstantBuffer >& a_constantbuffer);

	public:

		/** Render_Main
		*/
		void Render_Main();

		/** StartBatching
		*/
		void StartBatching(sharedptr< NBsys::NActionBatching::ActionBatching_ActionList >& a_actionlist);

		/** Render_ViewPort。
		*/
		void Render_ViewPort(f32 a_x,f32 a_y,f32 a_width,f32 a_height);

		/** Render_ClearRenderTargetView
		*/
		void Render_ClearRenderTargetView(NBsys::NColor::Color_F& a_color);

		/** Render_ClearDepthStencilView
		*/
		void Render_ClearDepthStencilView();

		/** Render_Present
		*/
		bool Render_Present();

	public:

		/** Render_UpdateSubresource
		*/
		void Render_UpdateSubresource(s32 a_constantbuffer_id,const void* a_data);

		/** Render_VSSetShader
		*/
		void Render_VSSetShader(s32 a_vertexshader_id);

		/** Render_PSSetShader
		*/
		void Render_PSSetShader(s32 a_pixelshader_id);

		/** Render_Draw
		*/
		void Render_Draw(s32 a_count_of_vertex,s32 a_start_of_vertex);

		/** Render_VSSetConstantBuffers
		*/
		void Render_VSSetConstantBuffers(s32 a_startslot,s32 a_constantbuffer_id);
		
	};

}}
#endif

