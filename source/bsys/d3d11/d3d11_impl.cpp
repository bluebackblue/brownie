

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
#include "../bsys/window/window_impl.h"


/** lib
*/
#if(BSYS_D3D11_ENABLE)

	#pragma comment(lib,"d3d11.lib")
	#pragma comment(lib,"D3DCompiler.lib")

#endif


/** NBsys::ND3d11
*/
#if(BSYS_D3D11_ENABLE)
namespace NBsys{namespace ND3d11
{
	/** constructor
	*/
	D3d11_Impl::D3d11_Impl()
		:
		device(nullptr),
		devicecontext(nullptr)
		/*
		swapchain(nullptr),
		featurelevel(D3D_FEATURE_LEVEL_9_1),
		rendertarget_view(nullptr),
		depthstencil_texture(nullptr),
		depthstencil_view(nullptr)
		*/
	{
	}

	/** destructor
	*/
	D3d11_Impl::~D3d11_Impl()
	{
		this->Delete();
	}

	/** Create
	*/
	void D3d11_Impl::Create(sharedptr< NWindow::Window >& a_window,s32 a_width,s32 a_height)
	{

		D3D_FEATURE_LEVEL t_featureLevel = D3D_FEATURE_LEVEL_11_0;

		{
			ID3D11Device* t_raw_device = nullptr;
			ID3D11DeviceContext* t_raw_devicecontext = nullptr;
			const HRESULT t_result = D3D11CreateDevice(nullptr,D3D_DRIVER_TYPE_HARDWARE,nullptr,0,&t_featureLevel,1,D3D11_SDK_VERSION,&t_raw_device,nullptr,&t_raw_devicecontext);
			if(t_raw_device != nullptr){
				this->device.reset(t_raw_device,release_delete< ID3D11Device >());
			}
			if(t_raw_devicecontext != nullptr){
				this->devicecontext.reset(t_raw_devicecontext,release_delete< ID3D11DeviceContext >());
			}
			if(FAILED(t_result)){
				this->device.reset();
				this->devicecontext.reset();
			}
		}

		{
			sharedptr< IDXGIFactory2 > t_factory;

			{
				sharedptr< IDXGIDevice > t_dxgidevice;

				if(this->device){
					IDXGIDevice* t_raw = nullptr;
					HRESULT t_result = this->device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&t_raw));
					if(t_raw != nullptr){
						t_dxgidevice.reset(t_raw,release_delete< IDXGIDevice >());
					}
					if(FAILED(t_result)){
						t_dxgidevice.reset();
					}
				}

				sharedptr< IDXGIAdapter > t_adapter;

				if(t_dxgidevice){
					IDXGIAdapter* t_raw = nullptr;
					HRESULT t_result = t_dxgidevice->GetAdapter(&t_raw);
					if(t_raw != nullptr){
						t_adapter.reset(t_raw,release_delete< IDXGIAdapter >());
					}
					if(FAILED(t_result)){
						t_adapter.reset();
					}
				}

				if(t_adapter){
					IDXGIFactory2* t_raw = nullptr;
					HRESULT t_result = t_adapter->GetParent(__uuidof(IDXGIFactory2), reinterpret_cast<void**>(&t_raw));
					if(t_raw != nullptr){
						t_factory.reset(t_raw,release_delete< IDXGIFactory2 >());
					}
					if(FAILED(t_result)){
						t_factory.reset();
					}
				}
			}

			DXGI_SWAP_CHAIN_DESC1 t_swapchain_desc_1;
			{
				Memory::memset(&t_swapchain_desc_1,0,sizeof(t_swapchain_desc_1));
				t_swapchain_desc_1.Width = static_cast<UINT>(a_width);
				t_swapchain_desc_1.Height = static_cast<UINT>(a_height);
				t_swapchain_desc_1.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
				t_swapchain_desc_1.SampleDesc.Count = 1;
				t_swapchain_desc_1.SampleDesc.Quality = 0;
				t_swapchain_desc_1.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
				t_swapchain_desc_1.BufferCount = 1;
			}

			HWND t_hwnd = a_window->GetImpl()->GetHandle();
			if(t_hwnd != INVALID_HANDLE_VALUE){

				sharedptr< IDXGISwapChain1 > t_swapchain_1;
				{
					IDXGISwapChain1* t_raw = nullptr;
					HRESULT t_result = t_factory->CreateSwapChainForHwnd(this->device.get(),t_hwnd,&t_swapchain_desc_1,nullptr,nullptr,&t_raw);
					if(t_raw != nullptr){
						t_swapchain_1.reset(t_raw,release_delete< IDXGISwapChain1 >());
					}
					if(FAILED(t_result)){
						t_swapchain_1.reset();
					}
				}

				if(t_swapchain_1){
					IDXGISwapChain* t_raw = nullptr;
					HRESULT t_result = t_swapchain_1->QueryInterface(__uuidof(IDXGISwapChain),reinterpret_cast<void**>(&t_raw));
					if(t_raw != nullptr){
						this->swapchain.reset(t_raw,release_delete< IDXGISwapChain >());
					}
					if(FAILED(t_result)){
						this->swapchain.reset();
					}
				}
			}
		}

		if(this->swapchain){
			ID3D11Texture2D* t_raw = nullptr;
			HRESULT t_result = this->swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D),reinterpret_cast<void**>(&t_raw));
			if(t_raw != nullptr){
				this->backbuffer.reset(t_raw,release_delete< ID3D11Texture2D >());
			}
			if(FAILED(t_result)){
				this->backbuffer.reset();
			}
		}

		if(this->device){
			ID3D11RenderTargetView* t_raw = nullptr;
			HRESULT t_result = this->device->CreateRenderTargetView(this->backbuffer.get(),nullptr,&t_raw);
			if(t_raw != nullptr){
				this->rendertargetview.reset(t_raw,release_delete< ID3D11RenderTargetView >());
			}
			if(FAILED(t_result)){
				this->rendertargetview.reset();
			}
		}

		if(this->device){
			D3D11_TEXTURE2D_DESC t_desc;
			{
				Memory::memset(&t_desc,0,sizeof(t_desc));
				t_desc.Width = static_cast<UINT>(a_width);
				t_desc.Height = static_cast<UINT>(a_height);
				t_desc.MipLevels = 0;
				t_desc.ArraySize = 1;
				t_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
				t_desc.SampleDesc.Count = 1;
				t_desc.SampleDesc.Quality = 0;
				t_desc.Usage = D3D11_USAGE_DEFAULT;
				t_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
				t_desc.CPUAccessFlags = 0;
				t_desc.MiscFlags = 0;
			}
			ID3D11Texture2D* t_raw = nullptr;
			HRESULT t_result = this->device->CreateTexture2D(&t_desc,nullptr,&t_raw);
			if(t_raw != nullptr){
				this->depthbuffer.reset(t_raw,release_delete< ID3D11Texture2D >());
			}
			if(FAILED(t_result)){
				this->depthbuffer.reset();
			}
		}

		if(this->device){
			D3D11_DEPTH_STENCIL_DESC t_desc;
			{
				Memory::memset(&t_desc,0,sizeof(t_desc));
				t_desc.DepthEnable = true;
				t_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
				t_desc.DepthFunc = D3D11_COMPARISON_LESS;
			}
			ID3D11DepthStencilState* t_raw = nullptr;
			HRESULT t_result = this->device->CreateDepthStencilState(&t_desc,&t_raw);
			if(t_raw != nullptr){
				this->depthstencilstate.reset(t_raw,release_delete< ID3D11DepthStencilState >());
			}
			if(FAILED(t_result)){
				this->depthstencilstate.reset();
			}
		}

		if(this->device){
			D3D11_DEPTH_STENCIL_VIEW_DESC t_desc;
			{
				Memory::memset(&t_desc,0,sizeof(t_desc));
				t_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
				t_desc.Texture2D.MipSlice = 0;
			}
			ID3D11DepthStencilView* t_raw = nullptr;
			HRESULT t_result = this->device->CreateDepthStencilView(this->depthbuffer.get(),&t_desc,&t_raw);
			if(t_raw != nullptr){
				this->depthstencilview.reset(t_raw,release_delete< ID3D11DepthStencilView >());
			}
			if(FAILED(t_result)){
				this->depthstencilview.reset();
			}
		}


		if(this->devicecontext){
			ID3D11RenderTargetView* t_rendertargetview[] = {
				this->rendertargetview.get()
			};
			this->devicecontext->OMSetRenderTargets(1,t_rendertargetview,this->depthstencilview.get());
			this->devicecontext->OMSetDepthStencilState(this->depthstencilstate.get(),1);
		}
	}

	/** Delete
	*/
	void D3d11_Impl::Delete()
	{
		this->depthstencilview.reset();
		this->depthstencilstate.reset();
		this->depthbuffer.reset();
		this->rendertargetview.reset();
		this->backbuffer.reset();
		this->swapchain.reset();
		this->devicecontext.reset();
		this->device.reset();
	}

	/** GetDevice
	*/
	sharedptr< ID3D11Device >& D3d11_Impl::GetDevice()
	{
		return this->device;
	}

	/** GetDeviceContext
	*/
	sharedptr< ID3D11DeviceContext >& D3d11_Impl::GetDeviceContext()
	{
		return this->devicecontext;
	}

	/** GetSwapChain
	*/
	sharedptr< IDXGISwapChain >& D3d11_Impl::GetSwapChain()
	{
		return this->swapchain;
	}

	/** GetBackBuffer
	*/
	sharedptr< ID3D11Texture2D >& D3d11_Impl::GetBackBuffer()
	{
		return this->backbuffer;
	}

	/** GetRenderTargetView
	*/
	sharedptr< ID3D11RenderTargetView >& D3d11_Impl::GetRenderTargetView()
	{
		return this->rendertargetview;
	}

	/** GetDepthBuffer
	*/
	sharedptr< ID3D11Texture2D >& D3d11_Impl::GetDepthBuffer()
	{
		return this->depthbuffer;
	}

	/** GetDepthStencilState
	*/
	sharedptr< ID3D11DepthStencilState >& D3d11_Impl::GetDepthStencilState()
	{
		return this->depthstencilstate;
	}

	/** GetDepthStencilView
	*/
	sharedptr< ID3D11DepthStencilView >& D3d11_Impl::GetDepthStencilView()
	{
		return this->depthstencilview;
	}

	/** Clear
	*/
	/*
	void D3d11_Impl::Clear()
	{
		#if defined(PLATFORM_WIN)
		{
			static f32 s_color[4] = {0.0f,0.125f,0.3f,1.0f};
			this->devicecontext->ClearRenderTargetView(this->rendertarget_view,s_color);
		}
		#endif
	}
	*/

	/** BeginScene
	*/
	/*
	void D3d11_Impl::BeginScene()
	{
		#if defined(PLATFORM_WIN)
		{
			//this->device->BeginScene();
		}
		#endif
	}
	*/

	/** EndScene
	*/
	/*
	void D3d11_Impl::EndScene()
	{
		#if defined(PLATFORM_WIN)
		{
			//this->device->EndScene();
			//this->device->Present(WIN_NULL,WIN_NULL,WIN_NULL,WIN_NULL);

			this->swapchain->Present(0,0);
		}
		#endif
	}
	*/

	/** device
	*/
	/*
	ID3D11Device* D3d11_Impl::GetDevice() const
	{
		return this->device;
	}
	*/

	/** devicecontext
	*/
	/*
	ID3D11DeviceContext* D3d11_Impl::GetDeviceContext() const
	{
		return this->devicecontext;
	}
	*/

	/** swapchain
	*/
	/*
	IDXGISwapChain* D3d11_Impl::GetSwapChain() const
	{
		return this->swapchain;
	}
	*/

	/** rendertargetview
	*/
	/*
	ID3D11RenderTargetView* D3d11_Impl::GetRenderTargetView() const
	{
		return this->rendertarget_view;
	}
	*/

	/** depthstencil_texture
	*/
	/*
	ID3D11Texture2D* D3d11_Impl::GetDepthstencilTexture() const
	{
		return this->depthstencil_texture;
	}
	*/

	/** depthstencil_view
	*/
	/*
	ID3D11DepthStencilView* D3d11_Impl::GetDepthstencilView() const
	{
		return this->depthstencil_view;
	}
	*/

	/** GetDevice
	*/
	/*
	#if defined(PLATFORM_WIN)
	IDirect3DDevice9* D3d11_Impl::GetDevice() const
	{
		return this->device;
	}
	#endif
	*/

	/** ResistTexture
	*/
	/*
	#if defined(PLATFORM_WIN)
	void D3d11_Impl::ResistTexture(Muid& a_muid,IDirect3DTexture9* a_texture)
	{
		this->texture_list.insert(STLMap< Muid::UniqueNameType , D3d11_Texture >::value_type(a_muid.GetName(),D3d11_Texture(a_muid,a_texture)));
	}
	#endif
	*/

	/** UnResistTexture
	*/
	/*
	#if defined(PLATFORM_WIN)
	void D3d11_Impl::UnResistTexture(Muid::UniqueNameType a_muid_uniqueid)
	{
		this->texture_list.erase(a_muid_uniqueid);
	}
	#endif
	*/

	/** GetTexture
	*/
	/*
	#if defined(PLATFORM_WIN)
	IDirect3DTexture9* D3d11_Impl::GetTexture(Muid::UniqueNameType a_muid_uniqueid) const
	{
		STLMap< Muid::UniqueNameType , D3d11_Texture >::iterator t_it = this->texture_list.find(a_muid_uniqueid);
		if(t_it != this->texture_list.end()){
			return t_it->second.texture;
		}
		return nullptr;
	}
	#endif
	*/

	/** ResistVertexShader
	*/
	/*
	#if defined(PLATFORM_WIN)
	void D3d11_Impl::ResistVertexShader(Muid& a_muid,IDirect3DVertexShader9* a_vertexshader,IDirect3DVertexDeclaration9* a_vertexdeclaration)
	{
		this->vertexshader_list.insert(STLMap< Muid::UniqueNameType , D3d11_VertexShader >::value_type(a_muid.GetName(),D3d11_VertexShader(a_muid,a_vertexshader,a_vertexdeclaration)));
	}
	#endif
	*/

	/** UnResistVertexShader
	*/
	/*
	#if defined(PLATFORM_WIN)
	void D3d11_Impl::UnResistVertexShader(Muid::UniqueNameType a_muid_uniqueid)
	{
		this->vertexshader_list.erase(a_muid_uniqueid);
	}
	#endif
	*/

	/** GetVertexShader
	*/
	/*
	#if defined(PLATFORM_WIN)
	IDirect3DVertexShader9* D3d11_Impl::GetVertexShader(Muid::UniqueNameType a_muid_uniqueid) const
	{
		STLMap< Muid::UniqueNameType , D3d11_VertexShader >::iterator t_it = this->vertexshader_list.find(a_muid_uniqueid);
		if(t_it != this->vertexshader_list.end()){
			return t_it->second.vertexshader;
		}
		return nullptr;
	}
	#endif
	*/

	/** GetVertexShader
	*/
	/*
	#if defined(PLATFORM_WIN)
	IDirect3DVertexDeclaration9* D3d11_Impl::GetVertexDeclaration(Muid::UniqueNameType a_muid_uniqueid) const
	{
		STLMap< Muid::UniqueNameType , D3d11_VertexShader >::iterator t_it = this->vertexshader_list.find(a_muid_uniqueid);
		if(t_it != this->vertexshader_list.end()){
			return t_it->second.vertexdeclaration;
		}
		return nullptr;
	}
	#endif
	*/

}}
#endif

