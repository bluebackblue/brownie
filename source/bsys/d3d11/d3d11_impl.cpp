

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief Ｄ３Ｄ１１。
*/


/** include
*/
#include <bsys_pch.h>


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./d3d11_impl.h"


/** include
*/
#include "../bsys/window/window_impl.h"


/** include
*/
#include "./d3d11_impl_actionbatching_vertexshader_create.h"
#include "./d3d11_impl_actionbatching_pixelshader_create.h"
#include "./d3d11_impl_actionbatching_vertexbuffer_create.h"
#include "./d3d11_impl_actionbatching_constantbuffer_create.h"
#include "./d3d11_impl_actionbatching_texture_create.h"
#include "./d3d11_impl_actionbatching_blendstate_create.h"
#include "./d3d11_impl_actionbatching_rasterizerstate_create.h"


/** lib
*/
#if(BSYS_D3D11_ENABLE)
	#include <brownie_config/d3d11_lib.h>
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
		id_maker(),
		actionbatching_lockobject(),
		actionbatching(),
		device(),
		devicecontext(),
		swapchain(),
		backbuffer(),
		rendertargetview(),
		depthbuffer(),
		depthstencilstate(),
		depthstencilview(),
		vertexshader_list()
	{
	}

	/** destructor
	*/
	D3d11_Impl::~D3d11_Impl()
	{
		this->Render_Delete();
	}

	/** Render_Create
	*/
	void D3d11_Impl::Render_Create(sharedptr<NWindow::Window>& a_window,s32 a_width,s32 a_height)
	{

		D3D_FEATURE_LEVEL t_featureLevel = D3D_FEATURE_LEVEL_11_0;

		{
			ID3D11Device* t_raw_device = nullptr;
			ID3D11DeviceContext* t_raw_devicecontext = nullptr;
			const HRESULT t_result = D3D11CreateDevice(nullptr,D3D_DRIVER_TYPE_HARDWARE,nullptr,0,&t_featureLevel,1,D3D11_SDK_VERSION,&t_raw_device,nullptr,&t_raw_devicecontext);
			if(t_raw_device != nullptr){
				this->device.reset(t_raw_device,release_delete<ID3D11Device>());
			}
			if(t_raw_devicecontext != nullptr){
				this->devicecontext.reset(t_raw_devicecontext,release_delete<ID3D11DeviceContext>());
			}
			if(FAILED(t_result)){
				this->device.reset();
				this->devicecontext.reset();
			} 
		}

		{
			sharedptr<IDXGIFactory2> t_factory;

			{
				sharedptr<IDXGIDevice> t_dxgidevice;

				if(this->device){
					IDXGIDevice* t_raw = nullptr;
					HRESULT t_result = this->device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&t_raw));
					if(t_raw != nullptr){
						t_dxgidevice.reset(t_raw,release_delete<IDXGIDevice>());
					}
					if(FAILED(t_result)){
						t_dxgidevice.reset();
					}
				}

				sharedptr<IDXGIAdapter> t_adapter;

				if(t_dxgidevice){
					IDXGIAdapter* t_raw = nullptr;
					HRESULT t_result = t_dxgidevice->GetAdapter(&t_raw);
					if(t_raw != nullptr){
						t_adapter.reset(t_raw,release_delete<IDXGIAdapter>());
					}
					if(FAILED(t_result)){
						t_adapter.reset();
					}
				}

				if(t_adapter){
					IDXGIFactory2* t_raw = nullptr;
					HRESULT t_result = t_adapter->GetParent(__uuidof(IDXGIFactory2), reinterpret_cast<void**>(&t_raw));
					if(t_raw != nullptr){
						t_factory.reset(t_raw,release_delete<IDXGIFactory2>());
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

				sharedptr<IDXGISwapChain1> t_swapchain_1;
				{
					IDXGISwapChain1* t_raw = nullptr;
					HRESULT t_result = t_factory->CreateSwapChainForHwnd(this->device.get(),t_hwnd,&t_swapchain_desc_1,nullptr,nullptr,&t_raw);
					if(t_raw != nullptr){
						t_swapchain_1.reset(t_raw,release_delete<IDXGISwapChain1>());
					}
					if(FAILED(t_result)){
						t_swapchain_1.reset();
					}
				}

				if(t_swapchain_1){
					IDXGISwapChain* t_raw = nullptr;
					HRESULT t_result = t_swapchain_1->QueryInterface(__uuidof(IDXGISwapChain),reinterpret_cast<void**>(&t_raw));
					if(t_raw != nullptr){
						this->swapchain.reset(t_raw,release_delete<IDXGISwapChain>());
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
				this->backbuffer.reset(t_raw,release_delete<ID3D11Texture2D>());
			}
			if(FAILED(t_result)){
				this->backbuffer.reset();
			}
		}

		if(this->device){
			ID3D11RenderTargetView* t_raw = nullptr;
			HRESULT t_result = this->device->CreateRenderTargetView(this->backbuffer.get(),nullptr,&t_raw);
			if(t_raw != nullptr){
				this->rendertargetview.reset(t_raw,release_delete<ID3D11RenderTargetView>());
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
				this->depthbuffer.reset(t_raw,release_delete<ID3D11Texture2D>());
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
				this->depthstencilstate.reset(t_raw,release_delete<ID3D11DepthStencilState>());
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
				this->depthstencilview.reset(t_raw,release_delete<ID3D11DepthStencilView>());
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

	/** Render_Delete
	*/
	void D3d11_Impl::Render_Delete()
	{
		this->vertexshader_list.clear();
		this->pixelshader_list.clear();
		this->vertexbuffer_list.clear();
		this->constantbuffer_list.clear();
		this->texture_list.clear();

		this->depthstencilview.reset();
		this->depthstencilstate.reset();
		this->depthbuffer.reset();
		this->rendertargetview.reset();
		this->backbuffer.reset();
		this->swapchain.reset();
		this->devicecontext.reset();
		this->device.reset();
	}

	/** Render_GetDevice
	*/
	sharedptr<ID3D11Device>& D3d11_Impl::GetDevice()
	{
		return this->device;
	}

	/** Render_GetDeviceContext
	*/
	sharedptr<ID3D11DeviceContext>& D3d11_Impl::GetDeviceContext()
	{
		return this->devicecontext;
	}

	/** Render_GetSwapChain
	*/
	sharedptr<IDXGISwapChain>& D3d11_Impl::GetSwapChain()
	{
		return this->swapchain;
	}

	/** Render_GetBackBuffer
	*/
	sharedptr<ID3D11Texture2D>& D3d11_Impl::GetBackBuffer()
	{
		return this->backbuffer;
	}

	/** Render_GetRenderTargetView
	*/
	sharedptr<ID3D11RenderTargetView>& D3d11_Impl::GetRenderTargetView()
	{
		return this->rendertargetview;
	}

	/** Render_GetDepthBuffer
	*/
	sharedptr<ID3D11Texture2D>& D3d11_Impl::GetDepthBuffer()
	{
		return this->depthbuffer;
	}

	/** Render_GetDepthStencilState
	*/
	sharedptr<ID3D11DepthStencilState>& D3d11_Impl::GetDepthStencilState()
	{
		return this->depthstencilstate;
	}

	/** Render_GetDepthStencilView
	*/
	sharedptr<ID3D11DepthStencilView>& D3d11_Impl::GetDepthStencilView()
	{
		return this->depthstencilview;
	}

	/** GetVertexshader
	*/
	sharedptr<D3d11_Impl_VertexShader> D3d11_Impl::GetVertexShader(s32 a_vertexshader_id)
	{
		STLMap<s32,sharedptr<D3d11_Impl_VertexShader>>::iterator t_it = this->vertexshader_list.find(a_vertexshader_id);
		if(t_it->second != nullptr){
			return t_it->second;
		}
		return sharedptr<D3d11_Impl_VertexShader>::null();
	}

	/** GetPixelshader
	*/
	sharedptr<D3d11_Impl_PixelShader> D3d11_Impl::GetPixelShader(s32 a_pixelshader_id)
	{
		STLMap<s32,sharedptr<D3d11_Impl_PixelShader>>::iterator t_it = this->pixelshader_list.find(a_pixelshader_id);
		if(t_it->second != nullptr){
			return t_it->second;
		}
		return sharedptr<D3d11_Impl_PixelShader>::null();
	}

	/** GetVertexbuffer
	*/
	sharedptr<D3d11_Impl_VertexBuffer> D3d11_Impl::GetVertexBuffer(s32 a_vertexbuffer_id)
	{
		STLMap<s32,sharedptr<D3d11_Impl_VertexBuffer>>::iterator t_it = this->vertexbuffer_list.find(a_vertexbuffer_id);
		if(t_it->second != nullptr){
			return t_it->second;
		}
		return sharedptr<D3d11_Impl_VertexBuffer>::null();
	}

	/** GetConstantBuffer
	*/
	sharedptr<D3d11_Impl_ConstantBuffer> D3d11_Impl::GetConstantBuffer(s32 a_constantbuffer_id)
	{
		STLMap<s32,sharedptr<D3d11_Impl_ConstantBuffer>>::iterator t_it = this->constantbuffer_list.find(a_constantbuffer_id);
		if(t_it->second != nullptr){
			return t_it->second;
		}
		return sharedptr<D3d11_Impl_ConstantBuffer>::null();
	}

	/** GetTexture
	*/
	sharedptr<D3d11_Impl_Texture> D3d11_Impl::GetTexture(s32 a_texture_id)
	{
		STLMap<s32,sharedptr<D3d11_Impl_Texture>>::iterator t_it = this->texture_list.find(a_texture_id);
		if(t_it->second != nullptr){
			return t_it->second;
		}
		return sharedptr<D3d11_Impl_Texture>::null();
	}

	/** GetBlendState
	*/
	sharedptr<D3d11_Impl_BlendState> D3d11_Impl::GetBlendState(s32 a_blendstate_id)
	{
		STLMap<s32,sharedptr<D3d11_Impl_BlendState>>::iterator t_it = this->blendstate_list.find(a_blendstate_id);
		if(t_it->second != nullptr){
			return t_it->second;
		}
		return sharedptr<D3d11_Impl_BlendState>::null();
	}

	/** GetRasterizerState
	*/
	sharedptr<D3d11_Impl_RasterizerState> D3d11_Impl::GetRasterizerState(s32 a_rasterizerstate_id)
	{
		STLMap<s32,sharedptr<D3d11_Impl_RasterizerState>>::iterator t_it = this->rasterizerstate_list.find(a_rasterizerstate_id);
		if(t_it->second != nullptr){
			return t_it->second;
		}
		return sharedptr<D3d11_Impl_RasterizerState>::null();
	}


	/** CreateVertexShader
	*/
	s32 D3d11_Impl::CreateVertexShader(AsyncResult<bool>& a_asyncresult,sharedptr<NBsys::NFile::File_Object>& a_fileobject,sharedptr<STLVector<NBsys::ND3d11::D3d11_Layout>::Type>& a_layout)
	{
		//ＩＤ。
		s32 t_vertexshader_id = this->id_maker.MakeID();

		sharedptr<D3d11_Impl_VertexShader> t_vertexshader = new D3d11_Impl_VertexShader();
		{
			t_vertexshader->fileobject = a_fileobject;
			t_vertexshader->layout = a_layout;
		}

		//レンダーコマンド。
		sharedptr<NBsys::NActionBatching::ActionBatching_ActionList> t_actionlist = new NBsys::NActionBatching::ActionBatching_ActionList();
		{
			t_actionlist->Add(new D3d11_Impl_ActionBatching_VertexShader_Create(*this,t_vertexshader,a_asyncresult));
		}
		this->StartBatching(t_actionlist);

		//管理リスト。
		this->vertexshader_list.insert(STLMap<s32,sharedptr<D3d11_Impl_VertexShader>>::value_type(t_vertexshader_id,t_vertexshader));

		return t_vertexshader_id;
	}

	/** CreatePixelShader
	*/
	s32 D3d11_Impl::CreatePixelShader(AsyncResult<bool>& a_asyncresult,sharedptr<NBsys::NFile::File_Object>& a_fileobject)
	{
		//ＩＤ。
		s32 t_pixelshader_id = this->id_maker.MakeID();

		sharedptr<D3d11_Impl_PixelShader> t_pixelshader = new D3d11_Impl_PixelShader();
		{
			t_pixelshader->fileobject = a_fileobject;
		}

		//レンダーコマンド。
		sharedptr<NBsys::NActionBatching::ActionBatching_ActionList> t_actionlist = new NBsys::NActionBatching::ActionBatching_ActionList();
		{
			t_actionlist->Add(new D3d11_Impl_ActionBatching_PixelShader_Create(*this,t_pixelshader,a_asyncresult));
		}
		this->StartBatching(t_actionlist);

		//管理リスト。
		this->pixelshader_list.insert(STLMap<s32,sharedptr<D3d11_Impl_PixelShader>>::value_type(t_pixelshader_id,t_pixelshader));

		return t_pixelshader_id;
	}

	/** CreateVertexBuffer
	*/
	s32 D3d11_Impl::CreateVertexBuffer(const void* a_data,s32 a_stridebyte,s32 a_offset,s32 a_countofvertex,bool a_write_flag)
	{
		//ＩＤ。
		s32 t_vertexbuffer_id = this->id_maker.MakeID();

		sharedptr<D3d11_Impl_VertexBuffer> t_vertexbuffer = new D3d11_Impl_VertexBuffer();
		{
			t_vertexbuffer->data = a_data;
			t_vertexbuffer->stridebyte = a_stridebyte;
			t_vertexbuffer->offset = a_offset;
			t_vertexbuffer->countofvertex = a_countofvertex;
			t_vertexbuffer->write_flag = a_write_flag;
		}

		//レンダーコマンド。
		sharedptr<NBsys::NActionBatching::ActionBatching_ActionList> t_actionlist = new NBsys::NActionBatching::ActionBatching_ActionList();
		{
			t_actionlist->Add(new D3d11_Impl_ActionBatching_VertexBuffer_Create(*this,t_vertexbuffer));
		}
		this->StartBatching(t_actionlist);

		//管理リスト。
		this->vertexbuffer_list.insert(STLMap<s32,sharedptr<D3d11_Impl_VertexBuffer>>::value_type(t_vertexbuffer_id,t_vertexbuffer));

		return t_vertexbuffer_id;
	}

	/** CreateConstantBuffer
	*/
	s32 D3d11_Impl::CreateConstantBuffer(s32 a_register_b_index,s32 a_size)
	{
		//ＩＤ。
		s32 t_constantbuffer_id = this->id_maker.MakeID();

		sharedptr<D3d11_Impl_ConstantBuffer> t_constantbuffer = new D3d11_Impl_ConstantBuffer();
		{
			t_constantbuffer->size = a_size;
			t_constantbuffer->register_b_index = a_register_b_index;
		}

		//レンダーコマンド。
		sharedptr<NBsys::NActionBatching::ActionBatching_ActionList> t_actionlist = new NBsys::NActionBatching::ActionBatching_ActionList();
		{
			t_actionlist->Add(new D3d11_Impl_ActionBatching_ConstantBuffer_Create(*this,t_constantbuffer));
		}
		this->StartBatching(t_actionlist);

		//管理リスト。
		this->constantbuffer_list.insert(STLMap<s32,sharedptr<D3d11_Impl_ConstantBuffer>>::value_type(t_constantbuffer_id,t_constantbuffer));

		return t_constantbuffer_id;
	}

	/** CreateTexture
	*/
	s32 D3d11_Impl::CreateTexture(sharedptr<NBsys::NTexture::Texture>& a_texture)
	{
		//ＩＤ。
		s32 t_texture_id = this->id_maker.MakeID();

		sharedptr<D3d11_Impl_Texture> t_texture = new D3d11_Impl_Texture();
		{
			t_texture->texture = a_texture;
		}

		//レンダーコマンド。
		sharedptr<NBsys::NActionBatching::ActionBatching_ActionList> t_actionlist = new NBsys::NActionBatching::ActionBatching_ActionList();
		{ 
			t_actionlist->Add(new D3d11_Impl_ActionBatching_Texture_Create(*this,t_texture));
		}
		this->StartBatching(t_actionlist);

		//管理リスト。
		this->texture_list.insert(STLMap<s32,sharedptr<D3d11_Impl_Texture>>::value_type(t_texture_id,t_texture));

		return t_texture_id;
	}

	/** CreateBlendState
	*/
	s32 D3d11_Impl::CreateBlendState(bool a_alpha_blend)
	{
		//ＩＤ。
		s32 t_blendstate_id = this->id_maker.MakeID();

		sharedptr<D3d11_Impl_BlendState> t_blendstate = new D3d11_Impl_BlendState();
		{
			t_blendstate->alpha_blend = a_alpha_blend;
		}

		//レンダーコマンド。
		sharedptr<NBsys::NActionBatching::ActionBatching_ActionList> t_actionlist = new NBsys::NActionBatching::ActionBatching_ActionList();
		{
			t_actionlist->Add(new D3d11_Impl_ActionBatching_BlendState_Create(*this,t_blendstate));
		}
		this->StartBatching(t_actionlist);

		//管理リスト。
		this->blendstate_list.insert(STLMap<s32,sharedptr<D3d11_Impl_BlendState>>::value_type(t_blendstate_id,t_blendstate));

		return t_blendstate_id;
	}

	/** CreateRasterizerState
	*/
	s32 D3d11_Impl::CreateRasterizerState(D3d11_CullType::Id a_culltype)
	{
		//ＩＤ。
		s32 t_rasterizerstate_id = this->id_maker.MakeID();

		sharedptr<D3d11_Impl_RasterizerState> t_rasterizerstate = new D3d11_Impl_RasterizerState();
		{
			t_rasterizerstate->culltype = a_culltype;
		}

		//レンダーコマンド。
		sharedptr<NBsys::NActionBatching::ActionBatching_ActionList> t_actionlist = new NBsys::NActionBatching::ActionBatching_ActionList();
		{
			t_actionlist->Add(new D3d11_Impl_ActionBatching_RasterizerState_Create(*this,t_rasterizerstate));
		}
		this->StartBatching(t_actionlist);

		//管理リスト。
		this->rasterizerstate_list.insert(STLMap<s32,sharedptr<D3d11_Impl_RasterizerState>>::value_type(t_rasterizerstate_id,t_rasterizerstate));

		return t_rasterizerstate_id;
	}

	/** Render_CreateVertexShader
	*/
	void D3d11_Impl::Render_CreateVertexShader(sharedptr<D3d11_Impl_VertexShader>& a_vertexshader)
	{
		char* t_data = reinterpret_cast<char*>(a_vertexshader->fileobject->GetLoadData().get());
		s32 t_size = static_cast<s32>(a_vertexshader->fileobject->GetLoadSize());

		if(a_vertexshader->fileobject->GetAddAllocateSize() > 0){
			t_data[t_size] = 0x00;
		}else{
			ASSERT(0);
		}

		/** t_blob
		*/
		sharedptr<ID3DBlob> t_blob;
		{
			sharedptr<ID3DBlob> t_blob_error;
			ID3DBlob* t_raw = nullptr;
			ID3DBlob* t_raw_error = nullptr;
			HRESULT t_result = D3DCompile(t_data,t_size,nullptr,nullptr,nullptr,"VS","vs_4_0",D3DCOMPILE_ENABLE_STRICTNESS|D3DCOMPILE_DEBUG,0,&t_raw,&t_raw_error);
			if(t_raw != nullptr){
				t_blob.reset(t_raw,release_delete<ID3DBlob>());
			}
			if(t_raw_error != nullptr){
				t_blob_error.reset(t_raw_error,release_delete<ID3DBlob>());
			}
			if(FAILED(t_result)){
				t_blob.reset();
			}

			if(t_blob != nullptr){
			}else{
				std::string t_errorstring;
				if(t_blob_error != nullptr){
					t_errorstring = std::string((const char*)t_blob_error->GetBufferPointer(),t_blob_error->GetBufferSize());
				}
				TAGLOG("compile vertex","FAILED");
				TAGLOG("compile vertex",t_errorstring.c_str());
			}

			t_blob_error.reset();
		}

		/** ID3D11VertexShader
		*/
		if(t_blob){
			ID3D11VertexShader* t_raw = nullptr;
			HRESULT t_result = this->device->CreateVertexShader(t_blob->GetBufferPointer(),t_blob->GetBufferSize(),nullptr,&t_raw);
			if(t_raw != nullptr){
				a_vertexshader->vertexshader.reset(t_raw,release_delete<ID3D11VertexShader>());
			}
			if(FAILED(t_result)){
				a_vertexshader->vertexshader.reset();
			}
		}

		/** ID3D11InputLayout
		*/
		if(t_blob){
			s32 t_layout_size = static_cast<s32>(a_vertexshader->layout->size());
			D3D11_INPUT_ELEMENT_DESC* t_layout_data = new D3D11_INPUT_ELEMENT_DESC[t_layout_size];
			sharedptr<D3D11_INPUT_ELEMENT_DESC> t_layout(t_layout_data,default_delete<D3D11_INPUT_ELEMENT_DESC[]>());
			{
				 for(s32 ii=0;ii<t_layout_size;ii++){
					t_layout_data[ii].SemanticName			= a_vertexshader->layout->at(ii).semantic_name.c_str();
					t_layout_data[ii].SemanticIndex			= a_vertexshader->layout->at(ii).semantic_index;
					t_layout_data[ii].InputSlot				= a_vertexshader->layout->at(ii).input_slot;
					t_layout_data[ii].AlignedByteOffset		= a_vertexshader->layout->at(ii).offset;
					t_layout_data[ii].InputSlotClass		= D3D11_INPUT_PER_VERTEX_DATA;
					t_layout_data[ii].InstanceDataStepRate	= 0;

					switch(a_vertexshader->layout->at(ii).format){
					case D3d11_LayoutFormatType::R32G32B32_FLOAT:		t_layout_data[ii].Format = DXGI_FORMAT_R32G32B32_FLOAT;		break;
					case D3d11_LayoutFormatType::R32G32B32A32_FLOAT:	t_layout_data[ii].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;	break;
					case D3d11_LayoutFormatType::R32G32_FLOAT:			t_layout_data[ii].Format = DXGI_FORMAT_R32G32_FLOAT;		break;
					default:ASSERT(0);break;
					}
				 }
			}

			ID3D11InputLayout* t_raw = nullptr;
			HRESULT t_result = this->device->CreateInputLayout(t_layout_data,static_cast<UINT>(t_layout_size),t_blob->GetBufferPointer(),t_blob->GetBufferSize(),&t_raw);
			if(t_raw != nullptr){
				a_vertexshader->inputlayout.reset(t_raw,release_delete<ID3D11InputLayout>());
			}
			if(FAILED(t_result)){
				a_vertexshader->inputlayout.reset();
			}
		}
	}

	/** Render_CreatePixelShader
	*/
	void D3d11_Impl::Render_CreatePixelShader(sharedptr<D3d11_Impl_PixelShader>& a_pixelshader)
	{
		char* t_data = reinterpret_cast<char*>(a_pixelshader->fileobject->GetLoadData().get());
		s32 t_size = static_cast<s32>(a_pixelshader->fileobject->GetLoadSize());

		if(a_pixelshader->fileobject->GetAddAllocateSize() > 0){
			t_data[t_size] = 0x00;
		}else{
			ASSERT(0);
		}

		sharedptr<ID3DBlob> t_blob;
		{
			sharedptr<ID3DBlob> t_blob_error;
			ID3DBlob* t_raw = nullptr;
			ID3DBlob* t_raw_error = nullptr;
			HRESULT t_result = D3DCompile(t_data,t_size,nullptr,nullptr,nullptr,"PS","ps_4_0",D3DCOMPILE_ENABLE_STRICTNESS|D3DCOMPILE_DEBUG,0,&t_raw,&t_raw_error);
			if(t_raw != nullptr){
				t_blob.reset(t_raw,release_delete<ID3DBlob>());
			}
			if(t_raw_error != nullptr){
				t_blob_error.reset(t_raw_error,release_delete<ID3DBlob>());
			}
			if(FAILED(t_result)){
				t_blob.reset();
			}

			if(t_blob != nullptr){
			}else{
				std::string t_errorstring;
				if(t_blob_error != nullptr){
					t_errorstring = std::string((const char*)t_blob_error->GetBufferPointer(),t_blob_error->GetBufferSize());
				}
				TAGLOG("compile vertex","FAILED");
				TAGLOG("compile vertex",t_errorstring.c_str());
			}

			t_blob_error.reset();
		}

		if(t_blob){
			ID3D11PixelShader* t_raw = nullptr;
			HRESULT t_result = this->device->CreatePixelShader(t_blob->GetBufferPointer(),t_blob->GetBufferSize(),nullptr,&t_raw);
			if(t_raw != nullptr){
				a_pixelshader->pixelshader.reset(t_raw,release_delete<ID3D11PixelShader>());
			}
			if(FAILED(t_result)){
				a_pixelshader->pixelshader.reset();
			}
		}
	}

	/** Render_CreateVertexBuffer
	*/
	void D3d11_Impl::Render_CreateVertexBuffer(sharedptr<D3d11_Impl_VertexBuffer>& a_vertexbuffer)
	{
		D3D11_BUFFER_DESC t_desc;
		{
			Memory::memset(&t_desc,0,sizeof(t_desc));
			t_desc.Usage = D3D11_USAGE_DEFAULT;
			t_desc.ByteWidth = a_vertexbuffer->countofvertex * a_vertexbuffer->stridebyte;
			t_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			t_desc.CPUAccessFlags = 0;

			if(a_vertexbuffer->write_flag){
				t_desc.CPUAccessFlags |= D3D11_CPU_ACCESS_WRITE;
				t_desc.Usage = D3D11_USAGE_DYNAMIC;
			}
		}

		D3D11_SUBRESOURCE_DATA t_subresource_data;
		{
			Memory::memset(&t_subresource_data,0,sizeof(t_subresource_data));
			t_subresource_data.pSysMem = a_vertexbuffer->data;
		}

		ID3D11Buffer* t_raw;
		HRESULT t_result = this->device->CreateBuffer(&t_desc,&t_subresource_data,&t_raw);
		if(t_raw != nullptr){
			a_vertexbuffer->buffer.reset(t_raw,release_delete<ID3D11Buffer>());
		}
		if(FAILED(t_result)){
			a_vertexbuffer->buffer.reset();
		}
	}
	
	/** Render_CreateConstantBuffer
	*/
	void D3d11_Impl::Render_CreateConstantBuffer(sharedptr<D3d11_Impl_ConstantBuffer>& a_constantbuffer)
	{
		D3D11_BUFFER_DESC t_desc;
		{
			Memory::memset(&t_desc,0,sizeof(t_desc));
			t_desc.Usage = D3D11_USAGE_DEFAULT;
			t_desc.ByteWidth = a_constantbuffer->size;
			t_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			t_desc.CPUAccessFlags = 0;
		}

		ID3D11Buffer* t_raw = nullptr;
		HRESULT t_result = this->device->CreateBuffer(&t_desc,nullptr,&t_raw);
		if(t_raw != nullptr){
			a_constantbuffer->buffer.reset(t_raw,release_delete<ID3D11Buffer>());
		}
		if(FAILED(t_result)){
			a_constantbuffer->buffer.reset();
		}
	}

	/** Render_CreateTexture
	*/
	void D3d11_Impl::Render_CreateTexture(sharedptr<D3d11_Impl_Texture>& a_texture)
	{
		{
			D3D11_TEXTURE2D_DESC t_desc;
			{
				Memory::memset(&t_desc,0,sizeof(t_desc));
				t_desc.Width = a_texture->texture->GetWidth();
				t_desc.Height = a_texture->texture->GetHeight();
				t_desc.MipLevels = 1;
				t_desc.ArraySize = 1;
				t_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
				t_desc.SampleDesc.Count = 1;
				t_desc.SampleDesc.Quality = 0;
				t_desc.Usage = D3D11_USAGE_DEFAULT;
				t_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
				t_desc.CPUAccessFlags = 0;
				t_desc.MiscFlags = 0;
			}

			D3D11_SUBRESOURCE_DATA t_data;
			{
				Memory::memset(&t_data,0,sizeof(t_data));
				t_data.pSysMem = a_texture->texture->GetPixel().get();
				t_data.SysMemPitch = a_texture->texture->GetPitch();
				t_data.SysMemSlicePitch = 0;
			}

			ID3D11Texture2D* t_raw = nullptr;
			HRESULT t_result = this->device->CreateTexture2D(&t_desc,&t_data,&t_raw);
			if(t_raw != nullptr){
				a_texture->texture2d.reset(t_raw,release_delete<ID3D11Texture2D>());
			}
			if(FAILED(t_result)){
				a_texture->texture2d.reset();
			}
		}

		{
			D3D11_SHADER_RESOURCE_VIEW_DESC t_desc;
			{
				Memory::memset(&t_desc,0,sizeof(t_desc));
				t_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
				t_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
				t_desc.Texture2D.MipLevels = 1;
			}

			ID3D11ShaderResourceView* t_raw = nullptr;
			HRESULT t_result = this->device->CreateShaderResourceView(a_texture->texture2d.get(),&t_desc,&t_raw);
			if(t_raw != nullptr){
				a_texture->resourceview.reset(t_raw,release_delete<ID3D11ShaderResourceView>());
			}
			if(FAILED(t_result)){
				a_texture->resourceview.reset();
			}
		}
	}

	/** Render_CreateBlendState
	*/
	void D3d11_Impl::Render_CreateBlendState(sharedptr<D3d11_Impl_BlendState>& a_blendstate)
	{
		D3D11_BLEND_DESC t_desc;
		{
			Memory::memset(&t_desc,0,sizeof(t_desc));

			if(a_blendstate->alpha_blend == true){
				//アルファブレンド。
				t_desc.AlphaToCoverageEnable = FALSE;
				t_desc.IndependentBlendEnable = FALSE;
				for(s32 ii=0;ii<COUNTOF(t_desc.RenderTarget);ii++){
					t_desc.RenderTarget[ii].BlendEnable = TRUE;
					t_desc.RenderTarget[ii].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
					t_desc.RenderTarget[ii].BlendOp = D3D11_BLEND_OP_ADD;
					t_desc.RenderTarget[ii].BlendOpAlpha = D3D11_BLEND_OP_ADD;
					t_desc.RenderTarget[ii].SrcBlend = D3D11_BLEND_SRC_ALPHA;
					t_desc.RenderTarget[ii].SrcBlendAlpha = D3D11_BLEND_ONE;
					t_desc.RenderTarget[ii].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
					t_desc.RenderTarget[ii].DestBlendAlpha = D3D11_BLEND_ZERO;
				}
			}else{
				t_desc.AlphaToCoverageEnable = FALSE;
				t_desc.IndependentBlendEnable = FALSE;
				for(s32 ii=0;ii<COUNTOF(t_desc.RenderTarget);ii++){
					t_desc.RenderTarget[ii].BlendEnable = TRUE;
					t_desc.RenderTarget[ii].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
					t_desc.RenderTarget[ii].BlendOp = D3D11_BLEND_OP_ADD;
					t_desc.RenderTarget[ii].BlendOpAlpha = D3D11_BLEND_OP_ADD;
					t_desc.RenderTarget[ii].SrcBlend = D3D11_BLEND_ONE;
					t_desc.RenderTarget[ii].SrcBlendAlpha = D3D11_BLEND_ONE;
					t_desc.RenderTarget[ii].DestBlend = D3D11_BLEND_ZERO;
					t_desc.RenderTarget[ii].DestBlendAlpha = D3D11_BLEND_ZERO;
				}
			}
		}

		ID3D11BlendState* t_raw = nullptr;
		HRESULT t_result = this->device->CreateBlendState(&t_desc,&t_raw);
		if(t_raw != nullptr){
			a_blendstate->blendstate.reset(t_raw,release_delete<ID3D11BlendState>());
		}
		if(FAILED(t_result)){
			a_blendstate->blendstate.reset();
		}
	}

	/** Render_CreateRasterizerState
	*/
	void D3d11_Impl::Render_CreateRasterizerState(sharedptr<D3d11_Impl_RasterizerState>& a_rasterizerstate)
	{
		D3D11_RASTERIZER_DESC t_desc;
		{
			Memory::memset(&t_desc,0,sizeof(t_desc));

			t_desc.FillMode = D3D11_FILL_SOLID;
			t_desc.DepthClipEnable = FALSE;
			t_desc.MultisampleEnable = FALSE;
			t_desc.DepthBiasClamp = 0;
			t_desc.SlopeScaledDepthBias = 0;

			switch(a_rasterizerstate->culltype){
			case D3d11_CullType::NONE:		t_desc.CullMode = D3D11_CULL_NONE;		break;
			case D3d11_CullType::FRONT:		t_desc.CullMode = D3D11_CULL_FRONT;		break;
			case D3d11_CullType::BACK:		t_desc.CullMode = D3D11_CULL_BACK;		break;
			}
		}

		ID3D11RasterizerState* t_raw = nullptr;
		HRESULT t_result = this->device->CreateRasterizerState(&t_desc,&t_raw);
		if(t_raw != nullptr){
			a_rasterizerstate->rasterizerstate.reset(t_raw,release_delete<ID3D11RasterizerState>());
		}
		if(FAILED(t_result)){
			a_rasterizerstate->rasterizerstate.reset();
		}
	}

	/** Render_SetFont
	*/
	#if(BSYS_FONT_ENABLE)
	void D3d11_Impl::Render_SetFont(sharedptr<NBsys::NFont::Font>& a_font,s32 a_texture_width,const STLString& a_name)
	{
		//TODO:
	}
	#endif

	/** Render_DrawFont_StartClear
	*/
	#if(BSYS_FONT_ENABLE)
	void D3d11_Impl::Render_DrawFont_StartClear()
	{
		//TODO:
	}
	#endif

	/** Render_DrawFont
	*/
	#if(BSYS_FONT_ENABLE)
	void D3d11_Impl::Render_DrawFont(const STLWString& a_string,f32 a_font_size,f32 a_x,f32 a_y,const NBsys::NColor::Color_F& a_color)
	{
		//TODO:
	}
	#endif

	/** リクエスト処理。
	*/
	void D3d11_Impl::Render_Main()
	{
		//アクションバッチング実行中はロック。
		AutoLock t_autolock_actionbatching(this->actionbatching_lockobject);

		this->actionbatching.Update(1.0f);
	}

	/** StartBatching
	*/
	void D3d11_Impl::StartBatching(sharedptr<NBsys::NActionBatching::ActionBatching_ActionList>& a_actionlist)
	{
		//アクションバッチング登録中はロック。
		AutoLock t_autolock_actionbatching(this->actionbatching_lockobject);

		this->actionbatching.StartBatching(a_actionlist);
	}

	/** Render_ViewPort。
	*/
	void D3d11_Impl::Render_ViewPort(f32 a_x,f32 a_y,f32 a_width,f32 a_height)
	{
		if(this->devicecontext){

			D3D11_VIEWPORT t_viewport;
			{
				t_viewport.Width = a_width;
				t_viewport.Height = a_height;
				t_viewport.MinDepth = 0.0f;
				t_viewport.MaxDepth = 1.0f;
				t_viewport.TopLeftX = a_x;
				t_viewport.TopLeftY = a_y;
			}

			this->devicecontext->RSSetViewports(1,&t_viewport);

			return;

		}

		ASSERT(0);
	}

	/** Render_ClearRenderTargetView
	*/
	void D3d11_Impl::Render_ClearRenderTargetView(NBsys::NColor::Color_F& a_color)
	{
		if(this->devicecontext){

			this->devicecontext->ClearRenderTargetView(this->rendertargetview.get(),a_color.p);

			return;

		}

		ASSERT(0);
	}

	/** Render_ClearDepthStencilView
	*/
	void D3d11_Impl::Render_ClearDepthStencilView()
	{
		if(this->devicecontext){

			this->devicecontext->ClearDepthStencilView(this->depthstencilview.get(),D3D11_CLEAR_DEPTH,1,0);

			return;

		}

		ASSERT(0);
	}

	/** Render_Present
	*/
	bool D3d11_Impl::Render_Present()
	{
		HRESULT t_result = this->swapchain->Present(0,0);

		if(FAILED(t_result)){
			return false;
		}

		return true;
	}

	/** Render_UpdateSubresource
	*/
	void D3d11_Impl::Render_UpdateSubresource(s32 a_constantbuffer_id,const void* a_data)
	{
		if(a_constantbuffer_id >= 0){
			sharedptr<D3d11_Impl_ConstantBuffer>& t_constantbuffer = this->GetConstantBuffer(a_constantbuffer_id);
			if(t_constantbuffer){

				this->devicecontext->UpdateSubresource(t_constantbuffer->buffer.get(),0,nullptr,a_data,0,0);

				return;

			}
		}

		ASSERT(0);
	}

	/** Render_VSSetShader
	*/
	void D3d11_Impl::Render_VSSetShader(s32 a_vertexshader_id)
	{
		if(a_vertexshader_id){
			sharedptr<D3d11_Impl_VertexShader>& t_vertexshader = this->GetVertexShader(a_vertexshader_id);
			if(t_vertexshader){

				this->devicecontext->IASetInputLayout(t_vertexshader->inputlayout.get());
				this->devicecontext->VSSetShader(t_vertexshader->vertexshader.get(),nullptr,0);

				return;

			}
		}

		ASSERT(0);
	}

	/** Render_PSSetShader
	*/
	void D3d11_Impl::Render_PSSetShader(s32 a_pixelshader_id)
	{
		if(a_pixelshader_id >= 0){
			sharedptr<D3d11_Impl_PixelShader>& t_pixelshader = this->GetPixelShader(a_pixelshader_id);
			if(t_pixelshader){

				this->devicecontext->PSSetShader(t_pixelshader->pixelshader.get(),nullptr,0);

				return;

			}
		}

		ASSERT(0);
	}

	/** Render_Draw
	*/
	void D3d11_Impl::Render_Draw(s32 a_count_of_vertex,s32 a_start_of_vertex)
	{
		if(this->devicecontext){

			this->devicecontext->Draw(a_count_of_vertex,a_start_of_vertex);
			
			return;

		}

		ASSERT(0);
	}

	/** Render_VSSetConstantBuffers
	*/
	void D3d11_Impl::Render_VSSetConstantBuffers(s32 a_constantbuffer_id)
	{
		if(a_constantbuffer_id >= 0){
			sharedptr<D3d11_Impl_ConstantBuffer>& t_constantbuffer = this->GetConstantBuffer(a_constantbuffer_id);
			if(t_constantbuffer){

				ID3D11Buffer* t_list[] = 
				{
					t_constantbuffer->buffer.get()
				};

				this->devicecontext->VSSetConstantBuffers(t_constantbuffer->register_b_index,COUNTOF(t_list),t_list);

				return;

			}
		}

		ASSERT(0);
	}

	/** Render_PSSetConstantBuffers
	*/
	void D3d11_Impl::Render_PSSetConstantBuffers(s32 a_constantbuffer_id)
	{
		if(a_constantbuffer_id >= 0){
			sharedptr<D3d11_Impl_ConstantBuffer>& t_constantbuffer = this->GetConstantBuffer(a_constantbuffer_id);
			if(t_constantbuffer){

				ID3D11Buffer* t_list[] = 
				{
					t_constantbuffer->buffer.get()
				};

				this->devicecontext->PSSetConstantBuffers(t_constantbuffer->register_b_index,COUNTOF(t_list),t_list);

				return;

			}
		}

		ASSERT(0);
	}

	/** Render_SetVertexBuffer
	*/
	void D3d11_Impl::Render_SetVertexBuffer(s32 a_vertexbuffer_id)
	{
		if(a_vertexbuffer_id >= 0){
			sharedptr<D3d11_Impl_VertexBuffer>& t_vertexbuffer = this->GetVertexBuffer(a_vertexbuffer_id);
			if(t_vertexbuffer){

				ID3D11Buffer* t_list[] = {
					t_vertexbuffer->buffer.get(),
				};
					
				UINT t_stride = t_vertexbuffer->stridebyte;
					
				UINT t_offset = t_vertexbuffer->offset;

				this->devicecontext->IASetVertexBuffers(0,COUNTOF(t_list),t_list,&t_stride,&t_offset);

				return;
			}
		}

		ASSERT(0);
	}

	/** Render_ReMapVertexBuffer
	*/
	void D3d11_Impl::Render_ReMapVertexBuffer(s32 a_vertexbuffer_id,const void* a_data,s32 a_size)
	{
		if(a_vertexbuffer_id >= 0){
			sharedptr<D3d11_Impl_VertexBuffer>& t_vertexbuffer = this->GetVertexBuffer(a_vertexbuffer_id);
			if(t_vertexbuffer){

				D3D11_MAPPED_SUBRESOURCE t_mapped_resource;

				HRESULT t_result = this->devicecontext->Map(t_vertexbuffer->buffer.get(),0,D3D11_MAP_WRITE_DISCARD,0,&t_mapped_resource);
				if(SUCCEEDED(t_result)){

					s32 t_size = t_vertexbuffer->stridebyte * t_vertexbuffer->countofvertex;
					Memory::memcpy(t_mapped_resource.pData,t_size,a_data,a_size);
					this->devicecontext->Unmap(t_vertexbuffer->buffer.get(),0);

				}
			}
		}
	}

	/** Render_SetPrimitiveTopology
	*/
	void D3d11_Impl::Render_SetPrimitiveTopology(D3d11_TopologyType::Id a_topology_type)
	{
		if(this->devicecontext){

			switch(a_topology_type){
			case D3d11_TopologyType::Id::PointList:			this->devicecontext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_POINTLIST);break;
			case D3d11_TopologyType::Id::LineList:			this->devicecontext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);break;
			case D3d11_TopologyType::Id::LineStrip:			this->devicecontext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINESTRIP);break;
			case D3d11_TopologyType::Id::TriangleList:		this->devicecontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);break;
			case D3d11_TopologyType::Id::TriangleStrip:		this->devicecontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);break;
			}

			return;

		}

		ASSERT(0);
	}

	/** Render_SetTexture
	*/
	void D3d11_Impl::Render_SetTexture(s32 a_register_t_index,s32 a_texture_id)
	{
		if(a_texture_id >= 0){
			sharedptr<D3d11_Impl_Texture>& t_texture = this->GetTexture(a_texture_id);
			if(t_texture){

				ID3D11ShaderResourceView* t_resourceview_list[] = {
					t_texture->resourceview.get()
				};

				this->devicecontext->PSSetShaderResources(a_register_t_index,COUNTOF(t_resourceview_list),t_resourceview_list);

				return;

			}
		}else{

			this->devicecontext->PSSetShaderResources(0,0,nullptr);	//TODO:

			return;

		}

		ASSERT(0);
	}

	/** Render_SetBlendState
	*/
	void D3d11_Impl::Render_SetBlendState(s32 a_blendstate_id)
	{
		if(a_blendstate_id >= 0){
			sharedptr<D3d11_Impl_BlendState>& t_blendstate = this->GetBlendState(a_blendstate_id);
			if(t_blendstate){

				FLOAT t_blendfactor[4] = {
					D3D11_BLEND_ZERO,
					D3D11_BLEND_ZERO,
					D3D11_BLEND_ZERO,
					D3D11_BLEND_ZERO
				};

				this->devicecontext->OMSetBlendState(t_blendstate->blendstate.get(),t_blendfactor,0xFFFFFFFF);

				return;

			}
		}

		ASSERT(0);
	}

	/** Render_SetRasterizerState
	*/
	void D3d11_Impl::Render_SetRasterizerState(s32 a_rasterizerstate_id)
	{
		if(a_rasterizerstate_id >= 0){
			sharedptr<D3d11_Impl_RasterizerState>& t_rasterizerstate = this->GetRasterizerState(a_rasterizerstate_id);
			if(t_rasterizerstate){

				this->devicecontext->RSSetState(t_rasterizerstate->rasterizerstate.get());

				return;
			}
		}

		ASSERT(0);
	}

	/** Render_DrawLine
	*/
	void D3d11_Impl::Render_DrawLine()
	{
		this->devicecontext->DrawAuto();
	}


}}
#endif

