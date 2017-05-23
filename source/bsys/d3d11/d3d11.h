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
		s32 CreateVertexBuffer(AsyncResult< bool >& a_asyncresult,const void* a_data,s32 a_stridebyte,s32 a_offset,s32 a_countofvertex);

		/** CreateConstantBuffer
		*/
		s32 CreateConstantBuffer(AsyncResult< bool >& a_asyncresult,s32 a_size);

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
		void Render_VSSetConstantBuffers(s32 a_startslot,s32 a_constantbuffer_id);

		/** Render_IASetInputLayout
		*/
		void Render_IASetInputLayout(s32 a_vertexshader_id);

		/** Render_IASetVertexBuffers
		*/
		void Render_IASetVertexBuffers(s32 a_vertexbuffer_id);

		/** Render_IASetPrimitiveTopology_TriangleList
		*/
		void Render_IASetPrimitiveTopology_TriangleList();

	};

}}
#endif

