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
#include "../window/window.h"
#include "../color/color.h"
#include "../file/file.h"
#include "../texture/texture.h"


/** include
*/
#include "./d3d11_layout.h"


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
		sharedptr< D3d11_Impl > impl;

	public:
		/** GetImpl
		*/
		sharedptr< D3d11_Impl >& GetImpl();

	public:
		/** constructor
		*/
		D3d11();

		/** destructor
		*/
		nonvirtual ~D3d11();

	public:

		/** CreateVertexShader
		*/
		s32 CreateVertexShader(AsyncResult< bool >& a_asyncresult,sharedptr< NBsys::NFile::File_Object >& a_fileobject,sharedptr< STLVector< NBsys::ND3d11::D3d11_Layout >::Type >& a_layout);

		/** CreatePixelShader
		*/
		s32 CreatePixelShader(AsyncResult< bool >& a_asyncresult,sharedptr< NBsys::NFile::File_Object >& a_fileobject);

		/** CreateVertexBuffer
		*/
		s32 CreateVertexBuffer(const void* a_data,s32 a_stridebyte,s32 a_offset,s32 a_countofvertex,bool a_write_flag);

		/** CreateConstantBuffer
		*/
		s32 CreateConstantBuffer(s32 a_register_b_index,s32 a_size);

		/** CreateTexture
		*/
		s32 CreateTexture(sharedptr< NBsys::NTexture::Texture >& a_texture);

		/** CreateBlendState
		*/
		s32 CreateBlendState(bool a_blend_state);

		/** CreateRasterizerState
		*/
		s32 CreateRasterizerState(D3d11_CullType::Id a_culltype);

	public:
		/** çÏê¨ÅB
		*/
		void Render_Create(sharedptr< NWindow::Window >& a_window,s32 a_width,s32 a_height);

		/** çÌèúÅB
		*/
		void Render_Delete();

		/** Render_Main
		*/
		void Render_Main();

	public:
		/** Render_ViewPort
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

		/** Render_DrawLine
		*/
		void Render_DrawLine();
	};

}}
#endif

