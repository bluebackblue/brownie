

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
	void D3d11_Impl::Render_Create(sharedptr< NWindow::Window >& a_window,s32 a_width,s32 a_height)
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

	/** Render_Delete
	*/
	void D3d11_Impl::Render_Delete()
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

	/** Render_GetDevice
	*/
	sharedptr< ID3D11Device >& D3d11_Impl::GetDevice()
	{
		return this->device;
	}

	/** Render_GetDeviceContext
	*/
	sharedptr< ID3D11DeviceContext >& D3d11_Impl::GetDeviceContext()
	{
		return this->devicecontext;
	}

	/** Render_GetSwapChain
	*/
	sharedptr< IDXGISwapChain >& D3d11_Impl::GetSwapChain()
	{
		return this->swapchain;
	}

	/** Render_GetBackBuffer
	*/
	sharedptr< ID3D11Texture2D >& D3d11_Impl::GetBackBuffer()
	{
		return this->backbuffer;
	}

	/** Render_GetRenderTargetView
	*/
	sharedptr< ID3D11RenderTargetView >& D3d11_Impl::GetRenderTargetView()
	{
		return this->rendertargetview;
	}

	/** Render_GetDepthBuffer
	*/
	sharedptr< ID3D11Texture2D >& D3d11_Impl::GetDepthBuffer()
	{
		return this->depthbuffer;
	}

	/** Render_GetDepthStencilState
	*/
	sharedptr< ID3D11DepthStencilState >& D3d11_Impl::GetDepthStencilState()
	{
		return this->depthstencilstate;
	}

	/** Render_GetDepthStencilView
	*/
	sharedptr< ID3D11DepthStencilView >& D3d11_Impl::GetDepthStencilView()
	{
		return this->depthstencilview;
	}

	/** GetVertexshader
	*/
	sharedptr< D3d11_Impl_VertexShader > D3d11_Impl::GetVertexShader(s32 a_vertexshader_id)
	{
		STLMap< s32 , sharedptr< D3d11_Impl_VertexShader > >::iterator t_it = this->vertexshader_list.find(a_vertexshader_id);
		if(t_it->second != nullptr){
			return t_it->second;
		}
		return sharedptr< D3d11_Impl_VertexShader >::null();
	}

	/** GetPixelshader
	*/
	sharedptr< D3d11_Impl_PixelShader > D3d11_Impl::GetPixelShader(s32 a_pixelshader_id)
	{
		STLMap< s32 , sharedptr< D3d11_Impl_PixelShader > >::iterator t_it = this->pixelshader_list.find(a_pixelshader_id);
		if(t_it->second != nullptr){
			return t_it->second;
		}
		return sharedptr< D3d11_Impl_PixelShader >::null();
	}

	/** GetVertexbuffer
	*/
	sharedptr< D3d11_Impl_VertexBuffer > D3d11_Impl::GetVertexBuffer(s32 a_vertexbuffer_id)
	{
		STLMap< s32 , sharedptr< D3d11_Impl_VertexBuffer > >::iterator t_it = this->vertexbuffer_list.find(a_vertexbuffer_id);
		if(t_it->second != nullptr){
			return t_it->second;
		}
		return sharedptr< D3d11_Impl_VertexBuffer >::null();
	}

	/** GetConstantBuffer
	*/
	sharedptr< D3d11_Impl_ConstantBuffer > D3d11_Impl::GetConstantBuffer(s32 a_constantbuffer_id)
	{
		STLMap< s32 , sharedptr< D3d11_Impl_ConstantBuffer > >::iterator t_it = this->constantbuffer_list.find(a_constantbuffer_id);
		if(t_it->second != nullptr){
			return t_it->second;
		}
		return sharedptr< D3d11_Impl_ConstantBuffer >::null();
	}

	/** CreateVertexShader
	*/
	s32 D3d11_Impl::CreateVertexShader(AsyncResult< bool >& a_asyncresult)
	{
		AutoLock t_autolock(this->actionbatching_lockobject);

		{
			//ＩＤ。
			s32 t_vertexshader_id = this->id_maker.MakeID();

			sharedptr< D3d11_Impl_VertexShader > t_vertexshader = new D3d11_Impl_VertexShader();

			//レンダーコマンド。
			sharedptr< NBsys::NActionBatching::ActionBatching_ActionList > t_actionlist = new NBsys::NActionBatching::ActionBatching_ActionList();
			{
				t_actionlist->Add(new Opengl_Impl_ActionBatching_VertexShader_Create(*this,t_vertexshader,a_asyncresult));
			}
			this->StartBatching(t_actionlist);

			//管理リスト。
			this->vertexshader_list.insert(STLMap< s32 , sharedptr< D3d11_Impl_VertexShader > >::value_type(t_vertexshader_id,t_vertexshader));

			return t_vertexshader_id;
		}
	}

	/** CreatePixelShader
	*/
	s32 D3d11_Impl::CreatePixelShader(AsyncResult< bool >& a_asyncresult)
	{
		AutoLock t_autolock(this->actionbatching_lockobject);

		{
			//ＩＤ。
			s32 t_pixelshader_id = this->id_maker.MakeID();

			sharedptr< D3d11_Impl_PixelShader > t_pixelshader = new D3d11_Impl_PixelShader();

			//レンダーコマンド。
			sharedptr< NBsys::NActionBatching::ActionBatching_ActionList > t_actionlist = new NBsys::NActionBatching::ActionBatching_ActionList();
			{
				t_actionlist->Add(new Opengl_Impl_ActionBatching_PixelShader_Create(*this,t_pixelshader,a_asyncresult));
			}
			this->StartBatching(t_actionlist);

			//管理リスト。
			this->pixelshader_list.insert(STLMap< s32 , sharedptr< D3d11_Impl_PixelShader > >::value_type(t_pixelshader_id,t_pixelshader));

			return t_pixelshader_id;
		}
	}

	/** CreateVertexBuffer
	*/
	s32 D3d11_Impl::CreateVertexBuffer(AsyncResult< bool >& a_asyncresult,const void* a_data,s32 a_stridebyte,s32 a_offset,s32 a_countofvertex)
	{
		AutoLock t_autolock(this->actionbatching_lockobject);

		{
			//ＩＤ。
			s32 t_vertexbuffer_id = this->id_maker.MakeID();

			sharedptr< D3d11_Impl_VertexBuffer > t_vertexbuffer = new D3d11_Impl_VertexBuffer();
			{
				t_vertexbuffer->data = a_data;
				t_vertexbuffer->stridebyte = a_stridebyte;
				t_vertexbuffer->offset = a_offset;
				t_vertexbuffer->countofvertex = a_countofvertex;
			}

			//レンダーコマンド。
			sharedptr< NBsys::NActionBatching::ActionBatching_ActionList > t_actionlist = new NBsys::NActionBatching::ActionBatching_ActionList();
			{
				t_actionlist->Add(new Opengl_Impl_ActionBatching_VertexBuffer_Create(*this,t_vertexbuffer,a_asyncresult));
			}
			this->StartBatching(t_actionlist);

			//管理リスト。
			this->vertexbuffer_list.insert(STLMap< s32 , sharedptr< D3d11_Impl_VertexBuffer > >::value_type(t_vertexbuffer_id,t_vertexbuffer));

			return t_vertexbuffer_id;
		}
	}

	/** CreateConstantBuffer
	*/
	s32 D3d11_Impl::CreateConstantBuffer(AsyncResult< bool >& a_asyncresult,s32 a_size)
	{
		AutoLock t_autolock(this->actionbatching_lockobject);

		{
			//ＩＤ。
			s32 t_constantbuffer_id = this->id_maker.MakeID();

			sharedptr< D3d11_Impl_ConstantBuffer > t_constantbuffer = new D3d11_Impl_ConstantBuffer();
			{
				t_constantbuffer->size = a_size;
			}

			//レンダーコマンド。
			sharedptr< NBsys::NActionBatching::ActionBatching_ActionList > t_actionlist = new NBsys::NActionBatching::ActionBatching_ActionList();
			{
				t_actionlist->Add(new Opengl_Impl_ActionBatching_ConstantBuffer_Create(*this,t_constantbuffer,a_asyncresult));
			}
			this->StartBatching(t_actionlist);

			//管理リスト。
			this->constantbuffer_list.insert(STLMap< s32 , sharedptr< D3d11_Impl_ConstantBuffer > >::value_type(t_constantbuffer_id,t_constantbuffer));

			return t_constantbuffer_id;
		}
	}

	/** Render_CreateVertexShader
	*/
	void D3d11_Impl::Render_CreateVertexShader(sharedptr< D3d11_Impl_VertexShader >& a_vertexshader)
	{
		/** t_vertex_source
		*/
		STLString t_vertex_source = 
			"float4x4 modelView;"
			"struct VSI {"
				"float4 p : POSITION0;"
				"float3 c : COLOR;"
			"};"
			"struct VSO {"
				"float4 p : SV_POSITION;"
				"float3 c : COLOR;"
			"};"
			"VSO VS(VSI i) {"
				"VSO ret;"
				"ret.p = mul(i.p, modelView);"
				"ret.c = i.c;"
				"return ret;"
			"}";

		/** t_blob
		*/
		sharedptr< ID3DBlob > t_blob;
		{
			sharedptr< ID3DBlob > t_blob_error;
			ID3DBlob* t_raw = nullptr;
			ID3DBlob* t_raw_error = nullptr;
			HRESULT t_result = D3DCompile(t_vertex_source.c_str(),t_vertex_source.size(),nullptr,nullptr,nullptr,"VS","vs_4_0",D3DCOMPILE_ENABLE_STRICTNESS|D3DCOMPILE_DEBUG,0,&t_raw,&t_raw_error);
			if(t_raw != nullptr){
				t_blob.reset(t_raw,release_delete< ID3DBlob >());
			}
			if(t_raw != nullptr){
				t_blob_error.reset(t_raw_error,release_delete< ID3DBlob >());
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
		{
			ID3D11VertexShader* t_raw = nullptr;
			HRESULT t_result = this->device->CreateVertexShader(t_blob->GetBufferPointer(),t_blob->GetBufferSize(),nullptr,&t_raw);
			if(t_raw != nullptr){
				a_vertexshader->vertexshader.reset(t_raw,release_delete< ID3D11VertexShader >());
			}
			if(FAILED(t_result)){
				a_vertexshader->vertexshader.reset();
			}
		}

		/** ID3D11InputLayout
		*/
		{
			D3D11_INPUT_ELEMENT_DESC t_layout[] = {
				{	"POSITION",		0,	DXGI_FORMAT_R32G32B32_FLOAT,		0,	0,		D3D11_INPUT_PER_VERTEX_DATA,	0},
				{	"COLOR",	    0,	DXGI_FORMAT_R32G32B32A32_FLOAT,		0,	12,		D3D11_INPUT_PER_VERTEX_DATA,	0},
			};

			ID3D11InputLayout* t_raw = nullptr;
			HRESULT t_result = this->device->CreateInputLayout(t_layout,COUNTOF(t_layout),t_blob->GetBufferPointer(),t_blob->GetBufferSize(),&t_raw);
			if(t_raw != nullptr){
				a_vertexshader->inputlayout.reset(t_raw,release_delete< ID3D11InputLayout >());
			}
			if(FAILED(t_result)){
				a_vertexshader->inputlayout.reset();
			}
		}
	}

	/** Render_CreatePixelShader
	*/
	void D3d11_Impl::Render_CreatePixelShader(sharedptr< D3d11_Impl_PixelShader >& a_pixelshader)
	{
		STLString t_pixel_source = 
			"struct VSO {"
				"float4 p : SV_POSITION;"
				"float3 c : COLOR;"
			"};"
			"float4 PS(VSO i) : SV_Target {"
				"return float4(i.c.r, i.c.g, i.c.b, 1.0f);"
			"}";

		sharedptr< ID3DBlob > t_blob;
		{
			sharedptr< ID3DBlob > t_blob_error;
			ID3DBlob* t_raw = nullptr;
			ID3DBlob* t_raw_error = nullptr;
			HRESULT t_result = D3DCompile(t_pixel_source.c_str(),t_pixel_source.size(),nullptr,nullptr,nullptr,"PS","ps_4_0",D3DCOMPILE_ENABLE_STRICTNESS|D3DCOMPILE_DEBUG,0,&t_raw,&t_raw_error);
			if(t_raw != nullptr){
				t_blob.reset(t_raw,release_delete< ID3DBlob >());
			}
			if(t_raw != nullptr){
				t_blob_error.reset(t_raw_error,release_delete< ID3DBlob >());
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

		{
			ID3D11PixelShader* t_raw = nullptr;
			HRESULT t_result = this->device->CreatePixelShader(t_blob->GetBufferPointer(),t_blob->GetBufferSize(),nullptr,&t_raw);
			if(t_raw != nullptr){
				a_pixelshader->pixelshader.reset(t_raw,release_delete< ID3D11PixelShader >());
			}
			if(FAILED(t_result)){
				a_pixelshader->pixelshader.reset();
			}
		}
	}

	/** Render_CreateVertexBuffer
	*/
	void D3d11_Impl::Render_CreateVertexBuffer(sharedptr< D3d11_Impl_VertexBuffer >& a_vertexbuffer)
	{
		D3D11_BUFFER_DESC t_desc;
		{
			Memory::memset(&t_desc,0,sizeof(t_desc));
			t_desc.Usage = D3D11_USAGE_DEFAULT;
			t_desc.ByteWidth = a_vertexbuffer->countofvertex * a_vertexbuffer->stridebyte;
			t_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			t_desc.CPUAccessFlags = 0;
		}

		D3D11_SUBRESOURCE_DATA t_subresource_data;
		{
			Memory::memset(&t_subresource_data,0,sizeof(t_subresource_data));
			t_subresource_data.pSysMem = a_vertexbuffer->data;
		}

		ID3D11Buffer* t_raw;
		HRESULT t_result = this->device->CreateBuffer(&t_desc,&t_subresource_data,&t_raw);
		if(t_raw != nullptr){
			a_vertexbuffer->buffer.reset(t_raw,release_delete< ID3D11Buffer >());
		}
		if(FAILED(t_result)){
			a_vertexbuffer->buffer.reset();
		}
	}
	
	/** Render_CreateConstantBuffer
	*/
	void D3d11_Impl::Render_CreateConstantBuffer(sharedptr< D3d11_Impl_ConstantBuffer >& a_constantbuffer)
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
			a_constantbuffer->buffer.reset(t_raw,release_delete< ID3D11Buffer >());
		}
		if(FAILED(t_result)){
			a_constantbuffer->buffer.reset();
		}
	}

	/** Render_Main
	*/
	void D3d11_Impl::Render_Main()
	{
		AutoLock t_autolock_actionbatching(this->actionbatching_lockobject);
		this->actionbatching.Update(1.0f);
	}

	/** StartBatching
	*/
	void D3d11_Impl::StartBatching(sharedptr< NBsys::NActionBatching::ActionBatching_ActionList >& a_actionlist)
	{
		AutoLock t_autolock_actionbatching(this->actionbatching_lockobject);
		this->actionbatching.StartBatching(a_actionlist);
	}

	/** Render_ViewPort。
	*/
	void D3d11_Impl::Render_ViewPort(f32 a_x,f32 a_y,f32 a_width,f32 a_height)
	{
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
	}

	/** Render_ClearRenderTargetView
	*/
	void D3d11_Impl::Render_ClearRenderTargetView(NBsys::NColor::Color_F& a_color)
	{
		this->devicecontext->ClearRenderTargetView(this->rendertargetview.get(),a_color.p);
	}

	/** Render_ClearDepthStencilView
	*/
	void D3d11_Impl::Render_ClearDepthStencilView()
	{
		this->devicecontext->ClearDepthStencilView(this->depthstencilview.get(),D3D11_CLEAR_DEPTH,1,0);
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
		STLMap< s32 , sharedptr< D3d11_Impl_ConstantBuffer > >::iterator t_it = this->constantbuffer_list.find(a_constantbuffer_id);
		if(t_it != this->constantbuffer_list.end()){

			if(t_it->second != nullptr){
				if(t_it->second->buffer != nullptr){
					if(t_it->second->buffer.get() != nullptr){

						this->devicecontext->UpdateSubresource(t_it->second->buffer.get(),0,nullptr,a_data,0,0);

						return;
					}
				}
			}
		}

		ASSERT(0);
	}

	/** Render_VSSetShader
	*/
	void D3d11_Impl::Render_VSSetShader(s32 a_vertexshader_id)
	{
		STLMap< s32 , sharedptr< D3d11_Impl_VertexShader > >::iterator t_it = this->vertexshader_list.find(a_vertexshader_id);
		if(t_it != this->vertexshader_list.end()){

			if(t_it->second != nullptr){
				if(t_it->second->vertexshader != nullptr){
					if(t_it->second->vertexshader.get() != nullptr){

						this->devicecontext->VSSetShader(t_it->second->vertexshader.get(),nullptr,0);

						return;
					}
				}
			}
		}

		ASSERT(0);
	}

	/** Render_PSSetShader
	*/
	void D3d11_Impl::Render_PSSetShader(s32 a_pixelshader_id)
	{
		STLMap< s32 , sharedptr< D3d11_Impl_PixelShader > >::iterator t_it = this->pixelshader_list.find(a_pixelshader_id);
		if(t_it != this->pixelshader_list.end()){

			if(t_it->second != nullptr){
				if(t_it->second->pixelshader != nullptr){
					if(t_it->second->pixelshader.get() != nullptr){

						this->devicecontext->PSSetShader(t_it->second->pixelshader.get(),nullptr,0);

						return;
					}
				}
			}
		}

		ASSERT(0);
	}

	/** Render_Draw
	*/
	void D3d11_Impl::Render_Draw(s32 a_count_of_vertex,s32 a_start_of_vertex)
	{
		this->devicecontext->Draw(a_count_of_vertex,a_start_of_vertex);
	}

	/** Render_VSSetConstantBuffers
	*/
	void D3d11_Impl::Render_VSSetConstantBuffers(s32 a_startslot,s32 a_constantbuffer_id)
	{
		STLMap< s32 , sharedptr< D3d11_Impl_ConstantBuffer > >::iterator t_it = this->constantbuffer_list.find(a_constantbuffer_id);
		if(t_it != this->constantbuffer_list.end()){

			if(t_it->second != nullptr){
				if(t_it->second->buffer != nullptr){
					if(t_it->second->buffer.get() != nullptr){

						ID3D11Buffer* t_list[] = 
						{
							t_it->second->buffer.get()
						};

						this->devicecontext->VSSetConstantBuffers(0,COUNTOF(t_list),t_list);

						return;
					}
				}
			}
		}

		ASSERT(0);
	}

	/** Render_IASetInputLayout
	*/
	void D3d11_Impl::Render_IASetInputLayout(s32 a_vertexshader_id)
	{
		STLMap< s32 , sharedptr< D3d11_Impl_VertexShader > >::iterator t_it = this->vertexshader_list.find(a_vertexshader_id);
		if(t_it != this->vertexshader_list.end()){

			if(t_it->second != nullptr){
				if(t_it->second->inputlayout != nullptr){
					this->devicecontext->IASetInputLayout(t_it->second->inputlayout.get());
					return;
				}
			}
		}
	}

	/** Render_IASetVertexBuffers
	*/
	void D3d11_Impl::Render_IASetVertexBuffers(s32 a_vertexbuffer_id)
	{
		STLMap< s32 , sharedptr< D3d11_Impl_VertexBuffer > >::iterator t_it = this->vertexbuffer_list.find(a_vertexbuffer_id);
		if(t_it != this->vertexbuffer_list.end()){

			if(t_it->second != nullptr){
				if(t_it->second->buffer != nullptr){

					ID3D11Buffer* t_list[] = {
						t_it->second->buffer.get(),
					};
					
					UINT t_stride = t_it->second->stridebyte;
					
					UINT t_offset = t_it->second->offset;

					this->devicecontext->IASetVertexBuffers(0,COUNTOF(t_list),t_list,&t_stride,&t_offset);
					return;
				}
			}
		}
	}

	/** Render_IASetPrimitiveTopology_TriangleList
	*/
	void D3d11_Impl::Render_IASetPrimitiveTopology_TriangleList()
	{
		if(this->devicecontext){
			this->devicecontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		}
	}

}}
#endif

