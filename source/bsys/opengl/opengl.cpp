

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief OpenGL。
*/


/** include
*/
#include <bsys_pch.h>


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./opengl.h"
#include "./opengl_impl.h"


/** NBsys::NOpengl
*/
#if(BSYS_OPENGL_ENABLE)
namespace NBsys{namespace NOpengl
{

	/** constructor
	*/
	Opengl::Opengl()
	{
		this->impl.reset(new Opengl_Impl());
	}

	/** destructor
	*/
	Opengl::~Opengl()
	{
		this->impl.reset();
	}

	/** GetImpl
	*/
	const sharedptr< Opengl_Impl >& Opengl::GetImpl() const
	{
		return this->impl;
	}


	/** Init
	*/
	void Opengl::Init(bool (*a_update_proc)(f32 a_delta,bool a_endrequest),void (*a_draw_proc)())
	{
		this->impl->Init(a_update_proc,a_draw_proc);
	}

	/** Main
	*/
	void Opengl::Main()
	{
		this->impl->Main();
	}

	#if(0)

	/** SetShadeModel
	*/
	void Opengl::SetShadeModel(Opengl_ShadeModelType::Id a_shademodeltype)
	{
		this->impl->SetShadeModel(a_shademodeltype);
	}

	/** テクスチャ―登録。
	*/
	s32 Opengl::CreateTexture(const sharedptr< NBsys::NTexture::Texture >& a_texture)
	{
		return this->impl->CreateTexture(a_texture);
	}

	/** テクスチャ―解除。
	*/
	void Opengl::DeleteTexture(s32 a_textureid)
	{
		this->impl->DeleteTexture(a_textureid);
	}

	/** フレームバッファ作成。
	*/
	s32 Opengl::CreateFrameBuffer(s32 a_textureid_depth,s32 a_textureid_color0)
	{
		return this->impl->CreateFrameBuffer(a_textureid_depth,a_textureid_color0);
	}

	/** フレームバッファ削除。
	*/
	/*
	void Opengl::DeleteFrameBuffer(s32 a_framebufferid)
	{
		this->impl->DeleteFrameBuffer();
	}
	*/

	/** バーテックスバッファ作成。
	*/
	s32 Opengl::CreateVertexBuffer(const sharedptr< u8 >& a_data_byte,s32 a_size_byte,s32 a_stride_byte)
	{
		return this->impl->CreateVertexBuffer(a_data_byte,a_size_byte,a_stride_byte);
	}

	/** バーテックスバッファ削除。
	*/
	/*
	void Opengl::DeleteVertexBuffer(s32 a_vertexbufferid)
	{
		this->impl->DeleteVertexBuffer(a_vertexbufferid);
	}
	*/

	/** マウス取得。
	*/
	void Opengl::GetMouse(s32& a_x,s32& a_y,bool& a_left,bool& a_right)
	{
		this->impl->GetMouse(a_x,a_y,a_left,a_right);
	}

	/** SetFont
	*/
	void Opengl::SetFont(sharedptr< NBsys::NFont::Font >& a_font,s32 a_texture_width,const STLString& a_name)
	{
		this->impl->SetFont(a_font,a_texture_width,a_name);
	}

	#if !defined(ROM_MASTER)

	/** ＲＡＷテクスチャーＩＤ取得。
	*/
	u32 Opengl::Debug_GetRawTextureID(s32 a_textureid)
	{
		return this->impl->GetTexture_RawID(a_textureid).rawid;
	}

	#endif

	#endif

	/** [描画命令]クリアカラー設定。
	*/
	void Opengl::Render_SetClearColor(const NBsys::NColor::Color_F& a_color)
	{
		this->impl->Render_SetClearColor(a_color);
	}

	/** [描画命令]クリアバッファ。
	*/
	void Opengl::Render_ClearBuffer(bool a_depth,bool a_color)
	{
		this->impl->Render_ClearBuffer(a_depth,a_color);
	}

	#if(0)

	/** アクションバッチング更新。
	*/
	void Opengl::Render_UpdateActionBatching()
	{
		this->impl->Render_UpdateActionBatching();
	}

	/** Render_SetVertexBuffer。
	*/
	void Opengl::Render_SetVertexBuffer(s32 a_vertexbufferid)
	{
		this->impl->Render_SetVertexBuffer(a_vertexbufferid);
	}

	/** [レンダースレッドRender_SetColorMask。
	*/
	void Opengl::Render_SetColorMask(bool a_r,bool a_g,bool a_b,bool a_a)
	{
		this->impl->Render_SetColorMask(a_r,a_g,a_b,a_a);
	}

	/** Render_SetPolygonOffset。
	*/
	void Opengl::Render_SetPolygonOffset(bool a_flag,f32 a_factor,f32 a_unit)
	{
		this->impl->Render_SetPolygonOffset(a_flag,a_factor,a_unit);
	}

	#endif


	#if(0)

	/** Render_SetTextureDirect
	*/
	void Opengl::Render_SetTextureDirect(s32 a_textureunitid,s32 a_textureid)
	{
		this->impl->Render_SetTextureDirect(a_textureunitid,a_textureid);
	}

	/** Render_SetFrameBuffer。
	*/
	void Opengl::Render_SetFrameBuffer(s32 a_framebufferid)
	{
		this->impl->Render_SetFrameBuffer(a_framebufferid);
	}

	/** Render_DrawWorldLine。
	*/
	void Opengl::Render_DrawWorldLine()
	{
		this->impl->Render_DrawWorldLine();
	}

	/** Render_SetProjectionMatrix。
	*/
	void Opengl::Render_SetProjectionMatrix(const NBsys::NGeometry::Geometry_Matrix_44& a_projection)
	{
		this->impl->Render_SetProjectionMatrix(a_projection);
	}

	/** Render_SetViewMatrix。
	*/
	void Opengl::Render_SetViewMatrix(const NBsys::NGeometry::Geometry_Matrix_44& a_view)
	{
		this->impl->Render_SetViewMatrix(a_view);
	}

	/** Render_ViewPort。
	*/
	void Opengl::Render_ViewPort(f32 a_x,f32 a_y,f32 a_width,f32 a_height)
	{
		this->impl->Render_ViewPort(a_x,a_y,a_width,a_height);
	}



	/** Render_SetDepthTest
	*/
	void Opengl::Render_SetDepthTest(bool a_flag)
	{
		this->impl->Render_SetDepthTest(a_flag);
	}

	/** Render_SetAlphaBlend。
	*/
	void Opengl::Render_SetAlphaBlend(bool a_flag)
	{
		this->impl->Render_SetAlphaBlend(a_flag);
	}

	/** Render_SetShader。
	*/
	void Opengl::Render_SetShader(s32 a_vertex_shader_index)
	{
		this->impl->Render_SetShader(a_vertex_shader_index);
	}

	/** Render_SetVertexAttribute。

	return : 使用バイト数。

	*/
	s32 Opengl::Render_SetAttributeParameter(s32 a_shaderid,const STLString& a_name,const void* a_data_byte,s32 a_stride_byte,s32 a_offset_byte)
	{
		return this->impl->Render_SetAttributeParameter(a_shaderid,a_name,a_data_byte,a_stride_byte,a_offset_byte);
	}

	/** Render_SetUniformParameter
	*/
	void Opengl::Render_SetUniformParameter(s32 a_shaderid,const STLString& a_name,const void* a_data_byte,s32 a_countof)
	{
		this->impl->Render_SetUniformParameter(a_shaderid,a_name,a_data_byte,a_countof);
	}

	/** Render_SetUniformTexture
	*/
	void Opengl::Render_SetUniformTexture(s32 a_shaderid,const STLString& a_name,s32 a_textureid)
	{
		this->impl->Render_SetUniformTexture(a_shaderid,a_name,a_textureid);
	}

	/** Render_DrawArray_Triangle
	*/
	void Opengl::Render_DrawArray_Triangle(s32 a_vertex_offset,s32 a_vertex_countof)
	{
		this->impl->Render_DrawArray_Triangle(a_vertex_offset,a_vertex_countof);
	}

	/** Render_DrawArray_Quads
	*/
	void Opengl::Render_DrawArray_Quads(s32 a_vertex_offset,s32 a_vertex_countof)
	{
		this->impl->Render_DrawArray_Quads(a_vertex_offset,a_vertex_countof);
	}

	/** Render_DrawFont_StartClear
	*/
	void Opengl::Render_DrawFont_StartClear()
	{
		this->impl->Render_DrawFont_StartClear();
	}

	/** Render_DrawFont
	*/
	void Opengl::Render_DrawFont(const STLWString& a_string,f32 a_font_size,f32 a_x,f32 a_y,const NBsys::NColor::Color_F& a_color)
	{
		this->impl->Render_DrawFont(a_string,a_font_size,a_x,a_y,a_color);
	}

	/** Render_DrawRect。
	*/
	void Opengl::Render_DrawRect(f32 a_x,f32 a_y,f32 a_w,f32 a_h,s32 a_textureid,const NBsys::NColor::Color_F& a_color)
	{
		this->impl->Render_DrawRect(a_x,a_y,a_w,a_h,a_textureid,a_color);
	}

	#endif

}}
#endif

