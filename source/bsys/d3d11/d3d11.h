#pragma once

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief Ｄ３Ｄ１１。
*/


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
#include "../window/window.h"
#include "../color/color.h"
#include "../file/file.h"
#include "../texture/texture.h"
#include "../font/font.h"
#include "../vertex/vertex.h"
#pragma warning(pop)


/** include
*/
#include "./d3d11_layout.h"
#include "./d3d11_sampler.h"


/** NBsys::ND3d11
*/
#if(BSYS_D3D11_ENABLE)
namespace NBsys{namespace ND3d11
{
	/** D3d11_Impl
	*/
	class D3d11_Impl;

	/** D3d11
	*/
	class D3d11
	{
	private:

		/** impl
		*/
		sharedptr<D3d11_Impl> impl;

	public:

		/** GetImpl
		*/
		sharedptr<D3d11_Impl>& GetImpl();

	public:

		/** constructor
		*/
		D3d11();

		/** destructor
		*/
		nonvirtual ~D3d11();

	public:

		/** GetSize
		*/
		const Size2DType<f32>& GetSize();

		/** IsExistTexture
		*/
		bool IsExistTexture(s32 a_texture_id);

		/** テクスチャーＩＤを列挙したリストを作成する。
		*/
		void CreateTextureIdList(STLVector<s32>::Type& a_list);

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
		s32 CreateBlendState(bool a_blend_state);

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

		/** 作成。
		*/
		void Render_Create(sharedptr<NWindow::Window>& a_window,const Size2DType<f32>& a_size);

		/** 削除。
		*/
		void Render_Delete();

		/** リクエスト処理。
		*/
		void Render_Main();

		/** スクリーンショット。
		*/
		sharedptr<NBsys::NTexture::Texture> Render_ScreenShot();

	public:

		/** Render_ViewPort
		*/
		void Render_ViewPort(const Rect2DType_R<f32>& a_rect);

		/** Render_ClearRenderTargetView
		*/
		void Render_ClearRenderTargetView(const NBsys::NColor::Color_F& a_color);

		/** Render_ClearDepthStencilView
		*/
		void Render_ClearDepthStencilView();

		/** Render_Present
		*/
		bool Render_Present(s32 a_sync_interval = 1);

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

		/** Render_SetRasterizerState
		*/
		void Render_SetRasterizerState(s32 a_rasterizerstate_id);

		/** Render_SetDepthStencilState
		*/
		void Render_SetDepthStencilState(s32 a_depthstencilstate_id);

		/** Render_SetSamplerState
		*/
		void Render_SetSamplerState(s32 a_register_index,s32 a_samplerstate_id);

	};


}}
#endif

