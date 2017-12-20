﻿#pragma once

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
#if defined(PLATFORM_VCWIN)
	#include <brownie_config/windows_include.h>
#endif


/** include
*/
#include "../window/window.h"
#include "../color/color.h"
#include "../actionbatching/actionbatching.h"
#include "../file/file.h"
#include "../texture/texture.h"
#include "../font/font.h"
#include "../vertex/vertex.h"


/** include
*/
#include "./d3d11_layout.h"
#include "./d3d11_sampler.h"


/** include
*/
#include "./d3d11_impl_font_decl.h"


/** include
*/
#if(BSYS_D3D11_ENABLE)
	#include <brownie_config/d3d11_include.h>
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
		sharedptr<ID3D11VertexShader> vertexshader;
		
		/** inputlayout
		*/
		sharedptr<ID3D11InputLayout> inputlayout;

		/** fileobject
		*/
		sharedptr<NBsys::NFile::File_Object> fileobject; 

		/** layout
		*/
		sharedptr<STLVector<NBsys::ND3d11::D3d11_Layout>::Type> layout;
	};

	/** D3d11_Impl_PixelShader
	*/
	struct D3d11_Impl_PixelShader
	{
		/** pixelshader
		*/
		sharedptr<ID3D11PixelShader> pixelshader;

		/** fileobject
		*/
		sharedptr<NBsys::NFile::File_Object> fileobject; 
	};

	/** D3d11_Impl_VertexBuffer
	*/
	struct D3d11_Impl_VertexBuffer
	{
		/** buffer
		*/
		sharedptr<ID3D11Buffer> buffer;

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

		/** write_flag
		*/
		bool write_flag;
	};

	/** D3d11_Impl_ConstantBuffer
	*/
	struct D3d11_Impl_ConstantBuffer
	{
		/** buffer
		*/
		sharedptr<ID3D11Buffer> buffer;

		/** size
		*/
		s32 size;

		/** register_b_index
		*/
		s32 register_b_index;
	};

	/** D3d11_Impl_Texture
	*/
	struct D3d11_Impl_Texture
	{
		/** texture2d
		*/
		sharedptr<ID3D11Texture2D> texture2d;

		/** texture
		*/
		sharedptr<NBsys::NTexture::Texture> texture;

		/** resourceview
		*/
		sharedptr<ID3D11ShaderResourceView> resourceview;
	};

	/** D3d11_Impl_BlendState
	*/
	struct D3d11_Impl_BlendState
	{
		/** blendstate
		*/
		sharedptr<ID3D11BlendState> blendstate;

		/** alpha_blend
		*/
		bool alpha_blend;
	};

	/** D3d11_Impl_RasterizerState
	*/
	struct D3d11_Impl_RasterizerState
	{
		/** rasterizerstate
		*/
		sharedptr<ID3D11RasterizerState> rasterizerstate;

		/** culltype
		*/
		D3d11_CullType::Id culltype;
	};

	/** D3d11_Impl_DepthStencilState
	*/
	struct D3d11_Impl_DepthStencilState
	{
		/** rasterizerstate
		*/
		sharedptr<ID3D11DepthStencilState> depthstencilstate;

		/** depthtest_flag
		*/
		bool depthtest_flag;
		
		/** depthwrie_flag
		*/
		bool depthwrie_flag;
	};

	/** D3d11_Impl_SamplerState
	*/
	struct D3d11_Impl_SamplerState
	{
		/** rasterizerstate
		*/
		sharedptr<ID3D11SamplerState> samplerstate;

		/** sampler
		*/
		D3d11_Sampler sampler;
	};

	/** D3d11_Impl

	デバイスへのアクセスを行う関数は「Render_」で始まります。

	*/
	class D3d11_Impl
	{
	private:
		/** width
		*/
		s32 width;

		/** height
		*/
		s32 height;

		/** testpresent_mode
		*/
		bool testpresent_mode;

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
		sharedptr<ID3D11Device> device;

		/** devicecontext
		*/
		sharedptr<ID3D11DeviceContext> devicecontext;
		
		/** swapchain
		*/
		sharedptr<IDXGISwapChain> swapchain;

		/** backbuffer
		*/
		sharedptr<ID3D11Texture2D> backbuffer;

		/** backbuffer_rendertargetview
		*/
		sharedptr<ID3D11RenderTargetView> backbuffer_rendertargetview;

		/** backbuffer_shaderresourceview
		*/
		sharedptr<ID3D11ShaderResourceView> backbuffer_shaderresourceview;

		/** depthbuffer
		*/
		sharedptr<ID3D11Texture2D> depthbuffer;

		/** depthbuffer_depthstencilview
		*/
		sharedptr<ID3D11DepthStencilView> depthbuffer_depthstencilview;

		/** depthbuffer_shaderresourceview
		*/
		sharedptr<ID3D11ShaderResourceView> depthbuffer_shaderresourceview;

		/** depthbuffer_depthstencilstate
		*/
		sharedptr<ID3D11DepthStencilState> depthbuffer_depthstencilstate;

		/** font
		*/
		#if(BSYS_FONT_ENABLE)
		sharedptr<D3d11_Impl_Font> font_list[D3d11_FontTextureType::Id::Max];
		#endif

	private:

		/** vertexshader_list
		*/
		STLMap<s32,sharedptr<D3d11_Impl_VertexShader>>::Type vertexshader_list;

		/** pixelshader_list
		*/
		STLMap<s32,sharedptr<D3d11_Impl_PixelShader>>::Type pixelshader_list;

		/** vertexbuffer_list
		*/
		STLMap<s32,sharedptr<D3d11_Impl_VertexBuffer>>::Type vertexbuffer_list;

		/** constantbuffer_list
		*/
		STLMap<s32,sharedptr<D3d11_Impl_ConstantBuffer>>::Type constantbuffer_list;

		/** texture_list
		*/
		STLMap<s32,sharedptr<D3d11_Impl_Texture>>::Type texture_list;

		/** blendstate_list
		*/
		STLMap<s32,sharedptr<D3d11_Impl_BlendState>>::Type blendstate_list;

		/** rasterizerstate_list
		*/
		STLMap<s32,sharedptr<D3d11_Impl_RasterizerState>>::Type rasterizerstate_list;

		/** depthstencilstate_list
		*/
		STLMap<s32,sharedptr<D3d11_Impl_DepthStencilState>>::Type depthstencilstate_list;

		/** samplerstate_list
		*/
		STLMap<s32,sharedptr<D3d11_Impl_SamplerState>>::Type samplerstate_list;

	public:
		/** constructor
		*/
		D3d11_Impl();

		/** destructor
		*/
		nonvirtual ~D3d11_Impl();

	public:
		/** GetWidth
		*/
		s32 GetWidth();

		/** GetHeight
		*/
		s32 GetHeight();

		/** IsExistTexture
		*/
		bool IsExistTexture(s32 a_texture_id);

		/** CreateTextureIdList
		*/
		void CreateTextureIdList(STLVector<s32>::Type& a_list);

		/** Render_Create
		*/
		void Render_Create(sharedptr<NWindow::Window>& a_window,s32 a_width,s32 a_height);

		/** Render_Delete
		*/
		void Render_Delete();

		/** Render_GetDevice
		*/
		sharedptr<ID3D11Device>& GetDevice();

		/** Render_GetDeviceContext
		*/
		sharedptr<ID3D11DeviceContext>& GetDeviceContext();

		/** Render_GetSwapChain
		*/
		sharedptr<IDXGISwapChain>& GetSwapChain();

		/** Render_GetBackBuffer
		*/
		sharedptr<ID3D11Texture2D>& GetBackBuffer();

		/** Render_GetRenderTargetView
		*/
		sharedptr<ID3D11RenderTargetView>& GetRenderTargetView();

		/** Render_GetDepthBuffer
		*/
		sharedptr<ID3D11Texture2D>& GetDepthBuffer();

		/** Render_GetDepthStencilState
		*/
		sharedptr<ID3D11DepthStencilState>& GetDepthStencilState();

		/** Render_GetSamplerState
		*/
		sharedptr<ID3D11SamplerState>& GetSamplerState();

		/** Render_GetDepthStencilView
		*/
		sharedptr<ID3D11DepthStencilView>& GetDepthStencilView();

	public:

		/** GetVertexshader
		*/
		sharedptr<D3d11_Impl_VertexShader>& GetVertexShader(s32 a_vertexshader_id);

		/** GetPixelshader
		*/
		sharedptr<D3d11_Impl_PixelShader>& GetPixelShader(s32 a_pixelshader_id);

		/** GetVertexbuffer
		*/
		sharedptr<D3d11_Impl_VertexBuffer>& GetVertexBuffer(s32 a_vertexbuffer_id);

		/** GetConstantBuffer
		*/
		sharedptr<D3d11_Impl_ConstantBuffer>& GetConstantBuffer(s32 a_constantbuffer_id);

		/** GetTexture
		*/
		sharedptr<D3d11_Impl_Texture>& GetTexture(s32 a_texture_id);

		/** GetBlendState
		*/
		sharedptr<D3d11_Impl_BlendState>& GetBlendState(s32 a_blendstate_id);

		/** GetRasterizerState
		*/
		sharedptr<D3d11_Impl_RasterizerState>& GetRasterizerState(s32 a_rasterizerstate_id);

		/** GetDepthStencilState
		*/
		sharedptr<D3d11_Impl_DepthStencilState>& GetDepthStencilState(s32 a_depthstencilstate_id);

		/** GetSamplerState
		*/
		sharedptr<D3d11_Impl_SamplerState>& GetSamplerState(s32 a_samplerstate_id);

	public:

		/** CreateVertexShader
		*/
		s32 CreateVertexShader(AsyncResult<bool>& a_asyncresult,sharedptr<NBsys::NFile::File_Object>& a_fileobject,sharedptr<STLVector<NBsys::ND3d11::D3d11_Layout>::Type>& a_layout);

		/** CreatePixelShader
		*/
		s32 CreatePixelShader(AsyncResult<bool>& a_asyncresult,sharedptr<NBsys::NFile::File_Object>& a_fileobject);

		/** CreateVertexBuffer
		*/
		s32 CreateVertexBuffer(const void* a_data,s32 a_stridebyte,s32 a_offset,s32 a_countofvertex,bool a_write_flag);

		/** CreateConstantBuffer
		*/
		s32 CreateConstantBuffer(s32 a_register_b_index,s32 a_size);

		/** CreateTexture
		*/
		s32 CreateTexture(sharedptr<NBsys::NTexture::Texture>& a_texture,bool a_write_flag);

		/** CreateBlendState
		*/
		s32 CreateBlendState(bool a_alpha_blend);

		/** CreateRasterizerState
		*/
		s32 CreateRasterizerState(D3d11_CullType::Id a_culltype);

		/** CreateDepthStencilState
		*/
		s32 CreateDepthStencilState(bool a_depthtest_flag,bool a_depthwrie_flag);

		/** CreateSamplerState
		*/
		s32 CreateSamplerState(const D3d11_Sampler& a_sampler);
	public:

		/** Render_CreateVertexShader
		*/
		void Render_CreateVertexShader(sharedptr<D3d11_Impl_VertexShader>& a_vertexshader);

		/** Render_CreatePixelShader
		*/
		void Render_CreatePixelShader(sharedptr<D3d11_Impl_PixelShader>& a_pixelshader);

		/** Render_CreateVertexBuffer
		*/
		void Render_CreateVertexBuffer(sharedptr<D3d11_Impl_VertexBuffer>& a_pixelshader);

		/** Render_CreateConstantBuffer
		*/
		void Render_CreateConstantBuffer(sharedptr<D3d11_Impl_ConstantBuffer>& a_constantbuffer);

		/** Render_CreateTexture
		*/
		void Render_CreateTexture(sharedptr<D3d11_Impl_Texture>& a_texture,bool a_write_flag);

		/** Render_CreateBlendState
		*/
		void Render_CreateBlendState(sharedptr<D3d11_Impl_BlendState>& a_blendstate);

		/** Render_CreateRasterizerState
		*/
		void Render_CreateRasterizerState(sharedptr<D3d11_Impl_RasterizerState>& a_rasterizerstate);

		/** Render_CreateDepthStencilState
		*/
		void Render_CreateDepthStencilState(sharedptr<D3d11_Impl_DepthStencilState>& a_depthstencilstate);

		/** Render_CreateSamplerState
		*/
		void Render_CreateSamplerState(sharedptr<D3d11_Impl_SamplerState>& a_samplerstate);
	public:

		/** Render_SetFont
		*/
		#if(BSYS_FONT_ENABLE)
		void Render_SetFont(D3d11_FontTextureType::Id a_fonttexture_type,sharedptr<NBsys::NFont::Font>& a_font,s32 a_texture_width,const STLWString& a_name);
		#endif

		/** Render_DrawFont_ClearLockFlag
		*/
		#if(BSYS_FONT_ENABLE)
		void Render_DrawFont_ClearLockFlag(D3d11_FontTextureType::Id a_fonttexture_type);
		#endif

		/** Render_PreUpdateFontTexture
		*/
		#if(BSYS_FONT_ENABLE)
		bool Render_PreUpdateFontTexture(D3d11_FontTextureType::Id a_fonttexture_type,const STLWString& a_string);
		#endif

		/** Render_WriteFontTexture
		*/
		#if(BSYS_FONT_ENABLE)
		void Render_WriteFontTexture(D3d11_FontTextureType::Id a_fonttexture_type);
		#endif

		/** Render_MakeFontVertex
		*/
		#if(BSYS_FONT_ENABLE)
		void Render_MakeFontVertex(D3d11_FontTextureType::Id a_fonttexture_type,const STLWString& a_string,sharedptr<NBsys::NVertex::Vertex<NBsys::NVertex::Vertex_Data_Pos3Uv2Color4TextureIndex4>>& a_vertex,f32 a_x,f32 a_y,f32 a_w,f32 a_h,s32 a_alignment_x,s32 a_alignment_y,f32 a_z,f32 a_view_size_w,f32 a_view_size_h,const NBsys::NColor::Color_F& a_color);
		#endif

		/** Render_GetFontTexture
		*/
		#if(BSYS_FONT_ENABLE)
		s32 Render_GetFontTexture(D3d11_FontTextureType::Id a_fonttexture_type);
		#endif

	public:

		/** リクエスト処理。
		*/
		void Render_Main();

		/** リクエスト登録。
		*/
		void StartBatching(sharedptr<NBsys::NActionBatching::ActionBatching_ActionList>& a_actionlist);

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
		bool Render_Present(s32 a_sync_interval);

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
		void Render_VSSetConstantBuffers(s32 a_constantbuffer_id);

		/** Render_PSSetConstantBuffers
		*/
		void Render_PSSetConstantBuffers(s32 a_constantbuffer_id);
		
		/** Render_SetVertexBuffer
		*/
		void Render_SetVertexBuffer(s32 a_vertexbuffer_id);

		/** Render_ReMapVertexBuffer
		*/
		void Render_ReMapVertexBuffer(s32 a_vertexbuffer_id,const void* a_data,s32 a_size);

		/** Render_SetPrimitiveTopology
		*/
		void Render_SetPrimitiveTopology(D3d11_TopologyType::Id a_topology_type);

		/** Render_SetTexture
		*/
		void Render_SetTexture(s32 a_register_t_index,s32 a_texture_id);

		/** Render_SetBlendState
		*/
		void Render_SetBlendState(s32 a_blendstate_id);

		/** Render_SetRasterizerState();
		*/
		void Render_SetRasterizerState(s32 a_rasterizerstate_id);

		/** Render_SetDepthStencilState
		*/
		void Render_SetDepthStencilState(s32 a_depthstencilstate_id);

		/** Render_SetSamplerState
		*/
		void Render_SetSamplerState(s32 a_register_t_index,s32 a_samplerstate_id);

	};

}}
#endif

