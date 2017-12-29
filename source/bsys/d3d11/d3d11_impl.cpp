

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
#pragma warning(push)
#pragma warning(disable:4464)
#include "../window/window_impl.h"
#pragma warning(pop)


/** include
*/
#include "./d3d11_impl.h"
#include "./d3d11_impl_font.h"




/** include
*/
#include "./d3d11_impl_actionbatching_vertexshader_create.h"
#include "./d3d11_impl_actionbatching_pixelshader_create.h"
#include "./d3d11_impl_actionbatching_vertexbuffer_create.h"
#include "./d3d11_impl_actionbatching_constantbuffer_create.h"
#include "./d3d11_impl_actionbatching_texture_create.h"
#include "./d3d11_impl_actionbatching_blendstate_create.h"
#include "./d3d11_impl_actionbatching_rasterizerstate_create.h"
#include "./d3d11_impl_actionbatching_depthstencilstate_create.h"
#include "./d3d11_impl_actionbatching_samplerstate_create.h"


/** lib
*/
#if(BSYS_D3D11_ENABLE)
	#include <brownie_config/d3d11_lib.h>
#endif


/** warning

4710 : この関数はインライン展開のために選択されましたが、コンパイラはインライン展開を実行しませんでした。

*/
#pragma warning(disable:4710)


/** NBsys::ND3d11
*/
#if(BSYS_D3D11_ENABLE)
namespace NBsys{namespace ND3d11
{
	/** constructor
	*/
	D3d11_Impl::D3d11_Impl()
		:
		width(),
		height(),
		testpresent_mode(false),
		id_maker(),
		actionbatching_lockobject(),
		actionbatching(),
		device(),
		devicecontext(),
		swapchain(),
		backbuffer(),
		backbuffer_rendertargetview(),
		backbuffer_shaderresourceview(),
		depthbuffer(),
		depthbuffer_depthstencilview(),
		depthbuffer_shaderresourceview(),
		depthbuffer_depthstencilstate(),
		//font_list(),
		vertexshader_list(),
		pixelshader_list(),
		vertexbuffer_list(),
		constantbuffer_list(),
		texture_list(),
		blendstate_list(),
		rasterizerstate_list(),
		depthstencilstate_list(),
		samplerstate_list()
	{
	}


	/** destructor
	*/
	D3d11_Impl::~D3d11_Impl()
	{
		this->Render_Delete();
	}


	/** GetWidth
	*/
	s32 D3d11_Impl::GetWidth()
	{
		return this->width;
	}


	/** GetHeight
	*/
	s32 D3d11_Impl::GetHeight()
	{
		return this->height;
	}


	/** IsExistTexture
	*/
	bool D3d11_Impl::IsExistTexture(s32 a_texture_id)
	{
		sharedptr<D3d11_Impl_Texture>& t_texture = this->GetTexture(a_texture_id);
		if(t_texture){
			return true;
		}
		return false;
	}


	/** CreateTextureIdList
	*/
	void D3d11_Impl::CreateTextureIdList(STLVector<s32>::Type& a_list)
	{
		a_list.clear();

		auto t_it_end = this->texture_list.cend();
		for(auto t_it = this->texture_list.cbegin();t_it != t_it_end;++t_it){
			a_list.push_back(t_it->first);
		}
	}


	/** Render_Create
	*/
	void D3d11_Impl::Render_Create(sharedptr<NWindow::Window>& a_window,s32 a_width,s32 a_height)
	{
		this->width = a_width;
		this->height = a_height;

		D3D_FEATURE_LEVEL t_featurelevel_list[] = {D3D_FEATURE_LEVEL_11_0};

		HWND t_hwnd = a_window->GetImpl()->GetHandle();
		if(t_hwnd != INVALID_HANDLE_VALUE){

			DXGI_SWAP_CHAIN_DESC t_swapchain_desc = {0};
			{
				//スワップ チェーンのバッファー数を表す値です。フロント バッファーを含みます。
				t_swapchain_desc.BufferCount = 3;

				//バックバッファーの表示モードを表す。
				t_swapchain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
				t_swapchain_desc.BufferDesc.Height = static_cast<UINT>(this->height);
				t_swapchain_desc.BufferDesc.RefreshRate.Denominator = 60;
				t_swapchain_desc.BufferDesc.RefreshRate.Numerator = 1;
				t_swapchain_desc.BufferDesc.Scaling;
				t_swapchain_desc.BufferDesc.ScanlineOrdering;
				t_swapchain_desc.BufferDesc.Width = static_cast<UINT>(this->width);

				//バックバッファーのサーフェス使用法およびCPUアクセス オプションを表すDXGI_USAGE 列挙型のメンバーです。
				//バック バッファーは、シェーダー入力またはレンダー ターゲット出力に使用することができます。
				t_swapchain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;

				//スワップ チェーンの動作のオプションを表すDXGI_SWAP_CHAIN_FLAG列挙型のメンバーです。
				t_swapchain_desc.Flags = 0;

				//出力ウィンドウへの HWND ハンドルです。
				//このメンバーをNULLにすることはできません。
				t_swapchain_desc.OutputWindow = t_hwnd;

				//マルチサンプリング パラメーターを表すDXGI_SAMPLE_DESC構造体です。
				t_swapchain_desc.SampleDesc.Count = 1;
				t_swapchain_desc.SampleDesc.Quality = 0;

				//サーフェスの表示後に表示バッファーの内容を処理するためのオプションを表すDXGI_SWAP_EFFECT列挙型のメンバーです。
				t_swapchain_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

				//出力がウィンドウモードの場合はTRUE です。
				//それ以外の場合はFALSEです。詳細については「IDXGIFactory::CreateSwapChain」を参照してください。
				t_swapchain_desc.Windowed = TRUE;
			}

			{
				D3D_FEATURE_LEVEL t_feature_level = D3D_FEATURE_LEVEL_11_0;

				IDXGISwapChain* t_raw_swapchain = nullptr;
				ID3D11Device* t_raw_device = nullptr;
				ID3D11DeviceContext* t_raw_devicecontext = nullptr;
				const HRESULT t_result = ::D3D11CreateDeviceAndSwapChain(
					WIN_NULL,
					D3D_DRIVER_TYPE_HARDWARE,
					WIN_NULL,
					#if defined(ROM_DEVELOP) || defined(ROM_DEEPDEBUG) || defined(ROM_FULLDEBUG)
					D3D11_CREATE_DEVICE_DEBUG,
					#else
					0,
					#endif
					t_featurelevel_list,
					COUNTOF(t_featurelevel_list),
					D3D11_SDK_VERSION,
					&t_swapchain_desc,
					&t_raw_swapchain,
					&t_raw_device,
					&t_feature_level,
					&t_raw_devicecontext
				);
				if(t_raw_swapchain != nullptr){
					this->swapchain.reset(t_raw_swapchain,release_delete<IDXGISwapChain>());
				}
				if(t_raw_device != nullptr){
					this->device.reset(t_raw_device,release_delete<ID3D11Device>());
				}
				if(t_raw_devicecontext != nullptr){
					this->devicecontext.reset(t_raw_devicecontext,release_delete<ID3D11DeviceContext>());
				}
				if(FAILED(t_result)){
					DEEPDEBUG_ASSERT(BSYS_D3D11_DEBUG_ENABLE,0);
					this->swapchain.reset();
					this->devicecontext.reset();
					this->device.reset();
				}
			}
		}

		//バックバッファ。
		{
			if(this->swapchain){
				ID3D11Texture2D* t_raw = nullptr;
				HRESULT t_result = this->swapchain->GetBuffer(0,__uuidof(ID3D11Texture2D),reinterpret_cast<void**>(&t_raw));
				if(t_raw != nullptr){
					this->backbuffer.reset(t_raw,release_delete<ID3D11Texture2D>());
				}
				if(FAILED(t_result)){
					DEEPDEBUG_ASSERT(BSYS_D3D11_DEBUG_ENABLE,0);
					this->backbuffer.reset();
				}
			}

			if(this->device){
				ID3D11RenderTargetView* t_raw = nullptr;
				HRESULT t_result = this->device->CreateRenderTargetView(this->backbuffer.get(),nullptr,&t_raw);
				if(t_raw != nullptr){
					this->backbuffer_rendertargetview.reset(t_raw,release_delete<ID3D11RenderTargetView>());
				}
				if(FAILED(t_result)){
					DEEPDEBUG_ASSERT(BSYS_D3D11_DEBUG_ENABLE,0);
					this->backbuffer_rendertargetview.reset();
				}
			}

			if(this->device){
				ID3D11ShaderResourceView* t_raw = nullptr;
				HRESULT t_result = this->device->CreateShaderResourceView(this->backbuffer.get(),nullptr,&t_raw);
				if(t_raw != nullptr){
					this->backbuffer_shaderresourceview.reset(t_raw,release_delete<ID3D11ShaderResourceView>());
				}
				if(FAILED(t_result)){
					DEEPDEBUG_ASSERT(BSYS_D3D11_DEBUG_ENABLE,0);
					this->backbuffer_shaderresourceview.reset();
				}
			}
		}

		//深度ステンシル。
		{
			DXGI_FORMAT t_format_depthstencil = DXGI_FORMAT_D24_UNORM_S8_UINT;
			DXGI_FORMAT t_format_depthstencil_texture  = DXGI_FORMAT_R24G8_TYPELESS;
			DXGI_FORMAT t_format_depthstencil_resource = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
		
			if(this->device){
				D3D11_TEXTURE2D_DESC t_desc = {0};
				{
					t_desc.Width = static_cast<UINT>(this->width);
					t_desc.Height = static_cast<UINT>(this->height);
					t_desc.MipLevels = 1;
					t_desc.ArraySize = 1;
					t_desc.Format = t_format_depthstencil_texture;
					t_desc.SampleDesc.Count = 1;
					t_desc.SampleDesc.Quality = 0;
					t_desc.Usage = D3D11_USAGE_DEFAULT;
					t_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
					t_desc.CPUAccessFlags = 0;
					t_desc.MiscFlags = 0;
				}
				ID3D11Texture2D* t_raw = nullptr;
				HRESULT t_result = this->device->CreateTexture2D(&t_desc,nullptr,&t_raw);
				if(t_raw != nullptr){
					this->depthbuffer.reset(t_raw,release_delete<ID3D11Texture2D>());
				}
				if(FAILED(t_result)){
					DEEPDEBUG_ASSERT(BSYS_D3D11_DEBUG_ENABLE,0);
					this->depthbuffer.reset();
				}
			}

			if(this->device){
				D3D11_DEPTH_STENCIL_VIEW_DESC t_desc;
				{
					Memory::ZeroClear(t_desc);
					t_desc.Format = t_format_depthstencil;
					t_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
					t_desc.Texture2D.MipSlice = 0;
				}
				ID3D11DepthStencilView* t_raw = nullptr;
				HRESULT t_result = this->device->CreateDepthStencilView(this->depthbuffer.get(),&t_desc,&t_raw);
				if(t_raw != nullptr){
					this->depthbuffer_depthstencilview.reset(t_raw,release_delete<ID3D11DepthStencilView>());
				}
				if(FAILED(t_result)){
					DEEPDEBUG_ASSERT(BSYS_D3D11_DEBUG_ENABLE,0);
					this->depthbuffer_depthstencilview.reset();
				}
			}

			if(this->device){
				D3D11_SHADER_RESOURCE_VIEW_DESC t_desc;
				{
					Memory::ZeroClear(t_desc);
					t_desc.Format = t_format_depthstencil_resource;
					t_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
					t_desc.Texture2D.MipLevels = 1;
					t_desc.Texture2D.MostDetailedMip = 0;
				}

				ID3D11ShaderResourceView* t_raw = nullptr;
				HRESULT t_result = this->device->CreateShaderResourceView(this->depthbuffer.get(),&t_desc,&t_raw);
				if(t_raw != nullptr){
					this->depthbuffer_shaderresourceview.reset(t_raw,release_delete<ID3D11ShaderResourceView>());
				}
				if(FAILED(t_result)){
					DEEPDEBUG_ASSERT(BSYS_D3D11_DEBUG_ENABLE,0);
					this->depthbuffer_shaderresourceview.reset();
				}
			}

			if(this->device){
				D3D11_DEPTH_STENCIL_DESC t_desc = {0};
				{
					t_desc.DepthEnable = TRUE;
					t_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
					t_desc.DepthFunc = D3D11_COMPARISON_LESS;
				}
				ID3D11DepthStencilState* t_raw = nullptr;
				HRESULT t_result = this->device->CreateDepthStencilState(&t_desc,&t_raw);
				if(t_raw != nullptr){
					this->depthbuffer_depthstencilstate.reset(t_raw,release_delete<ID3D11DepthStencilState>());
				}
				if(FAILED(t_result)){
					DEEPDEBUG_ASSERT(BSYS_D3D11_DEBUG_ENABLE,0);
					this->depthbuffer_depthstencilstate.reset();
				}
			}
		}

		//レンダーターゲット設定。
		if(this->devicecontext){
			if(this->depthbuffer_depthstencilview){
				ID3D11RenderTargetView* t_rendertargetview[] = {
					this->backbuffer_rendertargetview.get()
				};
				this->devicecontext->OMSetRenderTargets(1,t_rendertargetview,this->depthbuffer_depthstencilview.get());
			}
		}
	}


	/** Render_Delete
	*/
	void D3d11_Impl::Render_Delete()
	{
		if(this->devicecontext){
			this->devicecontext->ClearState();
			this->devicecontext->Flush();
		}

		this->vertexshader_list.clear();
		this->pixelshader_list.clear();
		this->vertexbuffer_list.clear();
		this->constantbuffer_list.clear();
		this->texture_list.clear();
		this->blendstate_list.clear();
		this->rasterizerstate_list.clear();
		this->depthstencilstate_list.clear();
		this->samplerstate_list.clear();

		this->depthbuffer_depthstencilstate.reset();
		this->depthbuffer_shaderresourceview.reset();
		this->depthbuffer_depthstencilview.reset();
		this->depthbuffer.reset();

		this->backbuffer_shaderresourceview.reset();
		this->backbuffer_rendertargetview.reset();
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
		return this->backbuffer_rendertargetview;
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
		return this->depthbuffer_depthstencilstate;
	}


	/** Render_GetDepthStencilView
	*/
	sharedptr<ID3D11DepthStencilView>& D3d11_Impl::GetDepthStencilView()
	{
		return this->depthbuffer_depthstencilview;
	}


	/** GetVertexshader
	*/
	sharedptr<D3d11_Impl_VertexShader>& D3d11_Impl::GetVertexShader(s32 a_vertexshader_id)
	{
		auto t_it = this->vertexshader_list.find(a_vertexshader_id);
		if(t_it != this->vertexshader_list.cend()){
			if(t_it->second != nullptr){
				return t_it->second;
			}
		}
		return sharedptr<D3d11_Impl_VertexShader>::null();
	}


	/** GetPixelshader
	*/
	sharedptr<D3d11_Impl_PixelShader>& D3d11_Impl::GetPixelShader(s32 a_pixelshader_id)
	{
		auto t_it = this->pixelshader_list.find(a_pixelshader_id);
		if(t_it != this->pixelshader_list.cend()){
			if(t_it->second != nullptr){
				return t_it->second;
			}
		}
		return sharedptr<D3d11_Impl_PixelShader>::null();
	}


	/** GetVertexbuffer
	*/
	sharedptr<D3d11_Impl_VertexBuffer>& D3d11_Impl::GetVertexBuffer(s32 a_vertexbuffer_id)
	{
		auto t_it = this->vertexbuffer_list.find(a_vertexbuffer_id);
		if(t_it != this->vertexbuffer_list.cend()){
			if(t_it->second != nullptr){
				return t_it->second;
			}
		}
		return sharedptr<D3d11_Impl_VertexBuffer>::null();
	}


	/** GetConstantBuffer
	*/
	sharedptr<D3d11_Impl_ConstantBuffer>& D3d11_Impl::GetConstantBuffer(s32 a_constantbuffer_id)
	{
		auto t_it = this->constantbuffer_list.find(a_constantbuffer_id);
		if(t_it != this->constantbuffer_list.cend()){
			if(t_it->second != nullptr){
				return t_it->second;
			}
		}
		return sharedptr<D3d11_Impl_ConstantBuffer>::null();
	}


	/** GetTexture
	*/
	sharedptr<D3d11_Impl_Texture>& D3d11_Impl::GetTexture(s32 a_texture_id)
	{
		auto t_it = this->texture_list.find(a_texture_id);
		if(t_it != this->texture_list.cend()){
			if(t_it->second != nullptr){
				return t_it->second;
			}
		}
		return sharedptr<D3d11_Impl_Texture>::null();
	}


	/** GetBlendState
	*/
	sharedptr<D3d11_Impl_BlendState>& D3d11_Impl::GetBlendState(s32 a_blendstate_id)
	{
		auto t_it = this->blendstate_list.find(a_blendstate_id);
		if(t_it != this->blendstate_list.cend()){
			if(t_it->second != nullptr){
				return t_it->second;
			}
		}
		return sharedptr<D3d11_Impl_BlendState>::null();
	}


	/** GetRasterizerState
	*/
	sharedptr<D3d11_Impl_RasterizerState>& D3d11_Impl::GetRasterizerState(s32 a_rasterizerstate_id)
	{
		auto t_it = this->rasterizerstate_list.find(a_rasterizerstate_id);
		if(t_it != this->rasterizerstate_list.cend()){
			if(t_it->second != nullptr){
				return t_it->second;
			}
		}
		return sharedptr<D3d11_Impl_RasterizerState>::null();
	}


	/** GetDepthStencilState
	*/
	sharedptr<D3d11_Impl_DepthStencilState>& D3d11_Impl::GetDepthStencilState(s32 a_depthstencilstate_id)
	{
		auto t_it = this->depthstencilstate_list.find(a_depthstencilstate_id);
		if(t_it != this->depthstencilstate_list.cend()){
			if(t_it->second != nullptr){
				return t_it->second;
			}
		}
		return sharedptr<D3d11_Impl_DepthStencilState>::null();
	}


	/** GetSamplerState
	*/
	sharedptr<D3d11_Impl_SamplerState>& D3d11_Impl::GetSamplerState(s32 a_samplerstate_id)
	{
		auto t_it = this->samplerstate_list.find(a_samplerstate_id);
		if(t_it != this->samplerstate_list.cend()){
			if(t_it->second != nullptr){
				return t_it->second;
			}
		}
		return sharedptr<D3d11_Impl_SamplerState>::null();
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
			ASSERT(a_size % 16 == 0);

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
	s32 D3d11_Impl::CreateTexture(sharedptr<NBsys::NTexture::Texture>& a_texture,bool a_write_flag)
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
			t_actionlist->Add(new D3d11_Impl_ActionBatching_Texture_Create(*this,t_texture,a_write_flag));
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


	/** CreateDepthStencilState
	*/
	s32 D3d11_Impl::CreateDepthStencilState(bool a_depthtest_flag,bool a_depthwrie_flag)
	{
		//ＩＤ。
		s32 t_depthstencilstate_id = this->id_maker.MakeID();

		sharedptr<D3d11_Impl_DepthStencilState> t_depthstencilstate = new D3d11_Impl_DepthStencilState();
		{
			t_depthstencilstate->depthtest_flag = a_depthtest_flag;
			t_depthstencilstate->depthwrie_flag = a_depthwrie_flag;
		}

		//レンダーコマンド。
		sharedptr<NBsys::NActionBatching::ActionBatching_ActionList> t_actionlist = new NBsys::NActionBatching::ActionBatching_ActionList();
		{
			t_actionlist->Add(new D3d11_Impl_ActionBatching_DepthStencilState_Create(*this,t_depthstencilstate));
		}
		this->StartBatching(t_actionlist);

		//管理リスト。
		this->depthstencilstate_list.insert(STLMap<s32,sharedptr<D3d11_Impl_DepthStencilState>>::value_type(t_depthstencilstate_id,t_depthstencilstate));

		return t_depthstencilstate_id;
	}


	/** CreateSamplerState
	*/
	s32 D3d11_Impl::CreateSamplerState(const D3d11_Sampler& a_sampler)
	{
		//ＩＤ。
		s32 t_samplerstate_id = this->id_maker.MakeID();

		sharedptr<D3d11_Impl_SamplerState> t_samplerstate = new D3d11_Impl_SamplerState();
		{
			t_samplerstate->sampler = a_sampler;
		}

		//レンダーコマンド。
		sharedptr<NBsys::NActionBatching::ActionBatching_ActionList> t_actionlist = new NBsys::NActionBatching::ActionBatching_ActionList();
		{
			t_actionlist->Add(new D3d11_Impl_ActionBatching_SamplerState_Create(*this,t_samplerstate));
		}
		this->StartBatching(t_actionlist);

		//管理リスト。
		this->samplerstate_list.insert(STLMap<s32,sharedptr<D3d11_Impl_SamplerState>>::value_type(t_samplerstate_id,t_samplerstate));

		return t_samplerstate_id;
	}


	/** Render_CreateVertexShader
	*/
	void D3d11_Impl::Render_CreateVertexShader(sharedptr<D3d11_Impl_VertexShader>& a_vertexshader)
	{
		char* t_data = reinterpret_cast<char*>(a_vertexshader->fileobject->GetLoadData().get());
		s32 t_size = static_cast<s32>(a_vertexshader->fileobject->GetLoadSize());

		if(a_vertexshader->fileobject->GetAddAllocateSize() > 0){
			if(t_data){
				t_data[t_size] = 0x00;
			}
		}else{
			ASSERT(0);
		}

		/** t_blob
		*/
		sharedptr<ID3DBlob> t_blob;
		if(t_data){
			sharedptr<ID3DBlob> t_blob_error;
			ID3DBlob* t_raw = nullptr;
			ID3DBlob* t_raw_error = nullptr;
			HRESULT t_result = ::D3DCompile(t_data,static_cast<size_t>(t_size),nullptr,nullptr,nullptr,"VS","vs_4_0",D3DCOMPILE_ENABLE_STRICTNESS|D3DCOMPILE_DEBUG,0,&t_raw,&t_raw_error);
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
				TAGLOG(L"compile vertex","FAILED");
				TAGLOG(L"compile vertex",t_errorstring.c_str());
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
			u32 t_layout_size = static_cast<u32>(a_vertexshader->layout->size());
			D3D11_INPUT_ELEMENT_DESC* t_layout_data = new D3D11_INPUT_ELEMENT_DESC[t_layout_size];
			sharedptr<D3D11_INPUT_ELEMENT_DESC> t_layout(t_layout_data,default_delete<D3D11_INPUT_ELEMENT_DESC[]>());
			{
				 for(u32 ii=0;ii<t_layout_size;ii++){
					t_layout_data[ii].SemanticName			= a_vertexshader->layout->at(ii).semantic_name.c_str();
					t_layout_data[ii].SemanticIndex			= static_cast<UINT>(a_vertexshader->layout->at(ii).semantic_index);
					t_layout_data[ii].InputSlot				= static_cast<UINT>(a_vertexshader->layout->at(ii).input_slot);
					t_layout_data[ii].AlignedByteOffset		= static_cast<UINT>(a_vertexshader->layout->at(ii).offset);
					t_layout_data[ii].InputSlotClass		= D3D11_INPUT_PER_VERTEX_DATA;
					t_layout_data[ii].InstanceDataStepRate	= 0;

					switch(a_vertexshader->layout->at(ii).format){
					case D3d11_LayoutFormatType::R32G32B32_FLOAT:		t_layout_data[ii].Format = DXGI_FORMAT_R32G32B32_FLOAT;		break;
					case D3d11_LayoutFormatType::R32G32B32A32_FLOAT:	t_layout_data[ii].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;	break;
					case D3d11_LayoutFormatType::R32G32_FLOAT:			t_layout_data[ii].Format = DXGI_FORMAT_R32G32_FLOAT;		break;
					case D3d11_LayoutFormatType::R8G8B8A8_UINT:			t_layout_data[ii].Format = DXGI_FORMAT_R8G8B8A8_UINT;		break;
					case D3d11_LayoutFormatType::R8_UINT:				t_layout_data[ii].Format = DXGI_FORMAT_R8_UINT;				break;
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
			HRESULT t_result = ::D3DCompile(t_data,static_cast<size_t>(t_size),nullptr,nullptr,nullptr,"PS","ps_4_0",D3DCOMPILE_ENABLE_STRICTNESS|D3DCOMPILE_DEBUG,0,&t_raw,&t_raw_error);
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
				TAGLOG(L"compile vertex","FAILED");
				TAGLOG(L"compile vertex",t_errorstring.c_str());
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
		D3D11_BUFFER_DESC t_desc = {0};
		{
			t_desc.Usage = D3D11_USAGE_DEFAULT;
			t_desc.ByteWidth = static_cast<UINT>(a_vertexbuffer->countofvertex * a_vertexbuffer->stridebyte);
			t_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			t_desc.CPUAccessFlags = 0;

			if(a_vertexbuffer->write_flag){
				t_desc.CPUAccessFlags |= D3D11_CPU_ACCESS_WRITE;
				t_desc.Usage = D3D11_USAGE_DYNAMIC;
			}
		}

		D3D11_SUBRESOURCE_DATA t_subresource_data = {0};
		{
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
		D3D11_BUFFER_DESC t_desc = {0};
		{
			t_desc.Usage = D3D11_USAGE_DEFAULT;
			t_desc.ByteWidth = static_cast<UINT>(a_constantbuffer->size);
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
	void D3d11_Impl::Render_CreateTexture(sharedptr<D3d11_Impl_Texture>& a_texture,bool a_write_flag)
	{
		{
			D3D11_TEXTURE2D_DESC t_desc = {0};
			{
				t_desc.Width = static_cast<UINT>(a_texture->texture->GetWidth());
				t_desc.Height = static_cast<UINT>(a_texture->texture->GetHeight());
				t_desc.MipLevels = 1;
				t_desc.ArraySize = 1;
				t_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
				t_desc.SampleDesc.Count = 1;
				t_desc.SampleDesc.Quality = 0;
				if(a_write_flag){
					//GPU (読み取りのみ) と CPU (書き込みのみ) によるアクセスが可能なリソース。
					t_desc.Usage = D3D11_USAGE_DYNAMIC;
				}else{
					t_desc.Usage = D3D11_USAGE_DEFAULT;
				}
				t_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
				if(a_write_flag){
					//リソースをマップ可能にし、CPU がそのリソースの内容を変更できるようにします。
					t_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
				}else{
					t_desc.CPUAccessFlags = 0;
				}
				t_desc.MiscFlags = 0;
			}

			D3D11_SUBRESOURCE_DATA t_data = {0};
			{
				t_data.pSysMem = a_texture->texture->GetPixel().get();
				t_data.SysMemPitch = static_cast<UINT>(a_texture->texture->GetPitch());
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
				Memory::ZeroClear(t_desc);
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
		D3D11_BLEND_DESC t_desc = {0};
		{
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
			Memory::ZeroClear(t_desc);
			t_desc.FillMode = D3D11_FILL_SOLID;
			t_desc.DepthClipEnable = FALSE;
			t_desc.MultisampleEnable = FALSE;
			t_desc.DepthBiasClamp = 0;
			t_desc.SlopeScaledDepthBias = 0;

			switch(a_rasterizerstate->culltype){
			case D3d11_CullType::None:		t_desc.CullMode = D3D11_CULL_NONE;		break;
			case D3d11_CullType::Front:		t_desc.CullMode = D3D11_CULL_FRONT;		break;
			case D3d11_CullType::Back:		t_desc.CullMode = D3D11_CULL_BACK;		break;
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


	/** Render_CreateDepthStencilState
	*/
	void D3d11_Impl::Render_CreateDepthStencilState(sharedptr<D3d11_Impl_DepthStencilState>& a_depthstencilstate)
	{
		D3D11_DEPTH_STENCIL_DESC t_desc = {0};
		{
			if(a_depthstencilstate->depthtest_flag){
				//深度テストを使用する。
				t_desc.DepthEnable = TRUE;
			}else{
				//深度テストを使用しない。
				t_desc.DepthEnable = FALSE;
			}

			if(a_depthstencilstate->depthwrie_flag){
				//深度ステンシル バッファーへの書き込みをオンにします。
				t_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
			}else{
				//深度ステンシル バッファーへの書き込みをオフにします。
				t_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
			}

			//ソース データが対象データよりも小さい場合、比較に合格します。
			t_desc.DepthFunc = D3D11_COMPARISON_LESS;
		}

		ID3D11DepthStencilState* t_raw = nullptr;
		HRESULT t_result = this->device->CreateDepthStencilState(&t_desc,&t_raw);
		if(t_raw != nullptr){
			a_depthstencilstate->depthstencilstate.reset(t_raw,release_delete<ID3D11DepthStencilState>());
		}
		if(FAILED(t_result)){
			a_depthstencilstate->depthstencilstate.reset();
		}
	}


	/** Render_CreateSamplerState
	*/
	void D3d11_Impl::Render_CreateSamplerState(sharedptr<D3d11_Impl_SamplerState>& a_samplerstate)
	{
		D3D11_SAMPLER_DESC t_desc;
		{
			Memory::ZeroClear(t_desc);
			t_desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
			t_desc.MinLOD = 0;
			t_desc.MaxLOD = D3D11_FLOAT32_MAX;

			switch(a_samplerstate->sampler.textureaddrestype_u){
			case D3d11_TextureAddressType::Wrap:			t_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;			break;
			case D3d11_TextureAddressType::Mirror:			t_desc.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR;			break;
			case D3d11_TextureAddressType::Clamp:			t_desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;			break;
			case D3d11_TextureAddressType::Border:			t_desc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;			break;
			case D3d11_TextureAddressType::Mirror_Once:		t_desc.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR_ONCE;	break;
			default:ASSERT(0);break;
			}

			switch(a_samplerstate->sampler.textureaddrestype_v){
			case D3d11_TextureAddressType::Wrap:			t_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;			break;
			case D3d11_TextureAddressType::Mirror:			t_desc.AddressV = D3D11_TEXTURE_ADDRESS_MIRROR;			break;
			case D3d11_TextureAddressType::Clamp:			t_desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;			break;
			case D3d11_TextureAddressType::Border:			t_desc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;			break;
			case D3d11_TextureAddressType::Mirror_Once:		t_desc.AddressV = D3D11_TEXTURE_ADDRESS_MIRROR_ONCE;	break;
			default:ASSERT(0);break;
			}

			switch(a_samplerstate->sampler.textureaddrestype_w){
			case D3d11_TextureAddressType::Wrap:			t_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;			break;
			case D3d11_TextureAddressType::Mirror:			t_desc.AddressW = D3D11_TEXTURE_ADDRESS_MIRROR;			break;
			case D3d11_TextureAddressType::Clamp:			t_desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;			break;
			case D3d11_TextureAddressType::Border:			t_desc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;			break;
			case D3d11_TextureAddressType::Mirror_Once:		t_desc.AddressW = D3D11_TEXTURE_ADDRESS_MIRROR_ONCE;	break;
			default:ASSERT(0);break;
			}

			switch(a_samplerstate->sampler.filtertype){
			case D3d11_FilterType::MIN_MAG_MIP_POINT:		t_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;			break;
			case D3d11_FilterType::MIN_MAG_MIP_LINEAR:		t_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;		break;
			default:ASSERT(0);break;
			}
		}

		ID3D11SamplerState* t_raw = nullptr;
		HRESULT t_result = this->device->CreateSamplerState(&t_desc,&t_raw);
		if(t_raw != nullptr){
			a_samplerstate->samplerstate.reset(t_raw,release_delete<ID3D11SamplerState>());
		}
		if(FAILED(t_result)){
			a_samplerstate->samplerstate.reset();
		}
	}


	/** Render_SetFont
	*/
	#if(BSYS_FONT_ENABLE)
	void D3d11_Impl::Render_SetFont(D3d11_FontTextureType::Id a_fonttexture_type,sharedptr<NBsys::NFont::Font>& a_font,s32 a_texture_width,const STLWString& a_name)
	{
		this->font_list[a_fonttexture_type].reset(new D3d11_Impl_Font(*this,a_font,a_texture_width,a_name,a_fonttexture_type));
	}
	#endif


	/** Render_DrawFont_ClearLockFlag
	*/
	#if(BSYS_FONT_ENABLE)
	void D3d11_Impl::Render_DrawFont_ClearLockFlag(D3d11_FontTextureType::Id a_fonttexture_type)
	{
		if(this->font_list[a_fonttexture_type] != nullptr){
			this->font_list[a_fonttexture_type]->ResetLock();
		}
	}
	#endif


	/** Render_PreUpdateFontTexture
	*/
	#if(BSYS_FONT_ENABLE)
	bool D3d11_Impl::Render_PreUpdateFontTexture(D3d11_FontTextureType::Id a_fonttexture_type,const STLWString& a_string)
	{
		if(this->font_list[a_fonttexture_type] != nullptr){
			return this->font_list[a_fonttexture_type]->PreUpdateFontTexture(a_string);
		}

		return false;
	}
	#endif


	/** Render_WriteFontTexture
	*/
	#if(BSYS_FONT_ENABLE)
	void D3d11_Impl::Render_WriteFontTexture(D3d11_FontTextureType::Id a_fonttexture_type)
	{
		if(this->font_list[a_fonttexture_type] != nullptr){
			this->font_list[a_fonttexture_type]->WriteFontTexture();
		}
	}
	#endif


	/** Render_MakeFontVertex
	*/
	#if(BSYS_FONT_ENABLE)
	void D3d11_Impl::Render_MakeFontVertex(D3d11_FontTextureType::Id a_fonttexture_type,const STLWString& a_string,sharedptr<NBsys::NVertex::Vertex<NBsys::NVertex::Vertex_Data_Pos3Uv2Color4TextureIndex4>>& a_vertex,f32 a_x,f32 a_y,f32 a_w,f32 a_h,s32 a_alignment_x,s32 a_alignment_y,f32 a_z,f32 a_view_size_w,f32 a_view_size_h,const NBsys::NColor::Color_F& a_color)
	{
		if(this->font_list[a_fonttexture_type] != nullptr){
			this->font_list[a_fonttexture_type]->MakeFontVertex(a_string,a_vertex,a_x,a_y,a_w,a_h,a_alignment_x,a_alignment_y,a_z,a_view_size_w,a_view_size_h,a_color);
		}
	}
	#endif


	/** Render_GetFontTexture
	*/
	#if(BSYS_FONT_ENABLE)
	s32 D3d11_Impl::Render_GetFontTexture(D3d11_FontTextureType::Id a_fonttexture_type)
	{
		if(this->font_list[a_fonttexture_type] != nullptr){
			return this->font_list[a_fonttexture_type]->GetTexture();
		}
		return -1;
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

	/** スクリーンショット。
	*/
	sharedptr<NBsys::NTexture::Texture> D3d11_Impl::Render_ScreenShot()
	{
		sharedptr<NBsys::NTexture::Texture> t_screenshot;
		if(this->backbuffer){
			D3D11_TEXTURE2D_DESC t_desc_backbuffer = {0};
			{
				this->backbuffer->GetDesc(&t_desc_backbuffer);
			}

			D3D11_TEXTURE2D_DESC t_desc_dest = {0};
			{
				t_desc_dest.ArraySize = 1;
				t_desc_dest.BindFlags = 0;
				t_desc_dest.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
				t_desc_dest.Format = t_desc_backbuffer.Format;
				t_desc_dest.Height = t_desc_backbuffer.Height;
				t_desc_dest.Width = t_desc_backbuffer.Width;
				t_desc_dest.MipLevels = 1;
				t_desc_dest.MiscFlags = 0;
				t_desc_dest.SampleDesc.Count = 1;
				t_desc_dest.SampleDesc.Quality = 0;
				t_desc_dest.Usage = D3D11_USAGE_STAGING;
			}

			sharedptr<ID3D11Texture2D> t_texture;
			sharedptr<ID3D11Resource> t_backbuffer_resource;

			//テクスチャー作成。
			if(this->device){
				ID3D11Texture2D* t_texture_raw = nullptr;
				HRESULT t_result = this->device.get()->CreateTexture2D(&t_desc_dest,0,&t_texture_raw);
				if(t_texture_raw != nullptr){
					t_texture.reset(t_texture_raw,release_delete<ID3D11Texture2D>());
				}
				if(FAILED(t_result)){
					t_texture.reset();
				}
			}

			if(t_texture){
				//リソース取得。
				if(this->backbuffer_rendertargetview){
					ID3D11Resource* t_backbuffer_resource_raw = nullptr;
					this->backbuffer_rendertargetview.get()->GetResource(&t_backbuffer_resource_raw);
					if(t_backbuffer_resource_raw != nullptr){
						t_backbuffer_resource.reset(t_backbuffer_resource_raw,release_delete<ID3D11Resource>());
					}
				}

				//コピー。
				if(t_backbuffer_resource){
					if(this->devicecontext){
						this->devicecontext.get()->CopyResource(t_texture.get(),t_backbuffer_resource.get());
					}
					t_backbuffer_resource.reset();
				}

				//コピー。
				D3D11_MAPPED_SUBRESOURCE t_mapped_resource;
				if(this->devicecontext){
					HRESULT t_result = this->devicecontext.get()->Map(t_texture.get(),0,D3D11_MAP_READ,0,&t_mapped_resource);
					if(SUCCEEDED(t_result)){
						u32 t_size = t_mapped_resource.RowPitch * t_desc_backbuffer.Height;
			
						t_screenshot.reset(
							new NBsys::NTexture::Texture(
								new u8[t_size],
								static_cast<s32>(t_desc_backbuffer.Width),
								static_cast<s32>(t_desc_backbuffer.Height),
								static_cast<s32>(t_mapped_resource.RowPitch),
								NBsys::NTexture::TextureType::R8G8B8A8,
								L"screenshot"
							)
						);

						Memory::Copy(t_screenshot->GetPixel().get(),static_cast<s32>(t_size),t_mapped_resource.pData,static_cast<s32>(t_size));
						this->devicecontext.get()->Unmap(t_texture.get(),0);
					}
				}
			}
		}
		return t_screenshot;
	}


	/** リクエスト登録。
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
	void D3d11_Impl::Render_ClearRenderTargetView(const NBsys::NColor::Color_F& a_color)
	{
		if(this->devicecontext){

			this->devicecontext->ClearRenderTargetView(this->backbuffer_rendertargetview.get(),a_color.raw.color);

			return;
		}

		ASSERT(0);
	}


	/** Render_ClearDepthStencilView
	*/
	void D3d11_Impl::Render_ClearDepthStencilView()
	{
		if(this->devicecontext){
			if(this->depthbuffer_depthstencilview){
				this->devicecontext->ClearDepthStencilView(this->depthbuffer_depthstencilview.get(),D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,1.0f,0);
				return;
			}
		}

		ASSERT(0);
	}


	/** Render_Present
	*/
	bool D3d11_Impl::Render_Present(s32 a_sync_interval)
	{
		if(this->testpresent_mode == false){
			if(this->swapchain){
				HRESULT t_result = this->swapchain->Present(static_cast<UINT>(a_sync_interval),0);

				if(t_result == DXGI_STATUS_OCCLUDED){

					/*
					ターゲット ウィンドウ (または IDXGIOutput) が、z オーダーに基づいて別のウィンドウによってオクルードされています。
					このステータスを受け取った場合、アプリケーションはレンダリングを停止し、
					DXGI_PRESENT_TESTを使用してレンダリングを再開する時期を決定する必要があります。
					*/

					this->testpresent_mode = true;
					TAGLOG(L"NBsys::ND3d11","DXGI_STATUS_OCCLUDED = true");

					return false;
				}else if(t_result == S_OK){
					return true;
				}
			}
		}else{
			if(this->swapchain){
				HRESULT t_result = this->swapchain->Present(0,DXGI_PRESENT_TEST);

				if(t_result == DXGI_STATUS_OCCLUDED){
				}else if(t_result == S_OK){
					this->testpresent_mode = false;
					TAGLOG(L"NBsys::ND3d11","DXGI_STAS_OKTUS_OCCLUDED = false");
					return true;
				}
			}
		}

		return false;
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
		if(a_vertexshader_id >= 0){
			sharedptr<D3d11_Impl_VertexShader>& t_vertexshader = this->GetVertexShader(a_vertexshader_id);
			if(t_vertexshader){
				if(this->devicecontext){
					this->devicecontext->IASetInputLayout(t_vertexshader->inputlayout.get());
					this->devicecontext->VSSetShader(t_vertexshader->vertexshader.get(),nullptr,0);

					return;
				}
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
				if(this->devicecontext){
					this->devicecontext->PSSetShader(t_pixelshader->pixelshader.get(),nullptr,0);

					return;
				}
			}
		}

		ASSERT(0);
	}


	/** Render_Draw
	*/
	void D3d11_Impl::Render_Draw(s32 a_count_of_vertex,s32 a_start_of_vertex)
	{
		if(this->devicecontext){
			if(this->devicecontext){
				this->devicecontext->Draw(static_cast<UINT>(a_count_of_vertex),static_cast<UINT>(a_start_of_vertex));
			
				return;
			}
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
				if(this->devicecontext){

					ID3D11Buffer* t_list[] = 
					{
						t_constantbuffer->buffer.get()
					};

					this->devicecontext->VSSetConstantBuffers(static_cast<UINT>(t_constantbuffer->register_b_index),COUNTOF(t_list),t_list);

					return;
				}
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
				if(this->devicecontext){
					ID3D11Buffer* t_list[] = 
					{
						t_constantbuffer->buffer.get()
					};

					this->devicecontext->PSSetConstantBuffers(static_cast<UINT>(t_constantbuffer->register_b_index),COUNTOF(t_list),t_list);

					return;
				}
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
				if(this->devicecontext){
					ID3D11Buffer* t_list[] = {
						t_vertexbuffer->buffer.get(),
					};
					
					UINT t_stride = static_cast<UINT>(t_vertexbuffer->stridebyte);
					
					UINT t_offset = static_cast<UINT>(t_vertexbuffer->offset);

					this->devicecontext->IASetVertexBuffers(0,COUNTOF(t_list),t_list,&t_stride,&t_offset);

					return;
				}
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
				if(this->devicecontext){
					D3D11_MAPPED_SUBRESOURCE t_mapped_resource;

					HRESULT t_result = this->devicecontext->Map(t_vertexbuffer->buffer.get(),0,D3D11_MAP_WRITE_DISCARD,0,&t_mapped_resource);
					if(SUCCEEDED(t_result)){

						s32 t_size = t_vertexbuffer->stridebyte * t_vertexbuffer->countofvertex;
						Memory::Copy(t_mapped_resource.pData,t_size,a_data,a_size);
						this->devicecontext->Unmap(t_vertexbuffer->buffer.get(),0);

					}
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
				if(this->devicecontext){
					ID3D11ShaderResourceView* t_resourceview_list[] = {
						t_texture->resourceview.get()
					};

					this->devicecontext->PSSetShaderResources(static_cast<UINT>(a_register_t_index),COUNTOF(t_resourceview_list),t_resourceview_list);

					return;
				}
			}
		}else{

			ID3D11ShaderResourceView* t_resourceview_list[] = {
				nullptr
			};

			this->devicecontext->PSSetShaderResources(static_cast<UINT>(a_register_t_index),COUNTOF(t_resourceview_list),t_resourceview_list);

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
				if(this->devicecontext){
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
				if(this->devicecontext){
					this->devicecontext->RSSetState(t_rasterizerstate->rasterizerstate.get());

					return;
				}
			}
		}

		ASSERT(0);
	}


	/** Render_SetDepthStencilState
	*/
	void D3d11_Impl::Render_SetDepthStencilState(s32 a_depthstencilstate_id)
	{
		if(a_depthstencilstate_id >= 0){
			sharedptr<D3d11_Impl_DepthStencilState>& t_depthstencilstate = this->GetDepthStencilState(a_depthstencilstate_id);
			if(t_depthstencilstate){
				if(this->devicecontext){
					this->devicecontext->OMSetDepthStencilState(t_depthstencilstate->depthstencilstate.get(),0);

					return;
				}
			}
		}

		ASSERT(0);
	}


	/** Render_SetSamplerState
	*/
	void D3d11_Impl::Render_SetSamplerState(s32 a_register_t_index,s32 a_samplerstate_id)
	{
		if(a_samplerstate_id >= 0){
			sharedptr<D3d11_Impl_SamplerState>& t_samplerstate = this->GetSamplerState(a_samplerstate_id);
			if(t_samplerstate){
				if(this->devicecontext){
					ID3D11SamplerState* t_samplerstate_list[] = {
						t_samplerstate->samplerstate.get()
					};

					this->devicecontext->PSSetSamplers(static_cast<UINT>(a_register_t_index),1,t_samplerstate_list);

					return;
				}
			}
		}

		ASSERT(0);
	}


}}
#endif

