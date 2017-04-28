#pragma once

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief OpenGL。
*/


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./opengl_shaderinitializelist.h"


/** include
*/
//#include "../texture/texture_decl.h"
//#include "../geometry/geometry.h"
#include "../color/color.h"
//#include "../font/font.h"


/** NBsys::NOpengl
*/
#if(BSYS_OPENGL_ENABLE)
namespace NBsys{namespace NOpengl
{
	/** Opengl_Impl
	*/
	class Opengl_Impl;

	/** Opengl
	*/
	class Opengl
	{
	private:
		/** impl
		*/
		sharedptr< Opengl_Impl > impl;

	public:
		/** GetImpl
		*/
		const sharedptr< Opengl_Impl >& GetImpl() const;

	public:
		/** constructor
		*/
		Opengl();

		/** destructor
		*/
		nonvirtual ~Opengl();

	public:

		/** Init
		*/
		void Init(bool (*a_update_proc)(f32 a_delta,bool a_endrequest),void (*a_draw_proc)());

		/** Main
		*/
		void Main();

		#if(0)

		/** SetShadeModel
		*/
		void SetShadeModel(Opengl_ShadeModelType::Id a_shademodeltype);

		/** テクスチャ―作成。
		*/
		s32 CreateTexture(const sharedptr< NBsys::NTexture::Texture >& a_texture);

		/** テクスチャー削除。
		*/
		void DeleteTexture(s32 a_textureid);

		/** フレームバッファ作成。
		*/
		s32 CreateFrameBuffer(s32 a_textureid_depth,s32 a_textureid_color0);

		/** フレームバッファ削除。
		*/
		//void DeleteFrameBuffer(s32 a_framebufferid);

		/** バーテックスバッファ作成。
		*/
		s32 CreateVertexBuffer(const sharedptr< u8 >& a_data_byte,s32 a_size_byte,s32 a_stride_byte);

		/** バーテックスバッファ削除。
		*/
		//void DeleteVertexBuffer(s32 a_vertexbufferid);

		/** マウス取得。
		*/
		void GetMouse(s32& a_x,s32& a_y,bool& a_left,bool& a_right);

		/** SetFont
		*/
		void SetFont(sharedptr< NBsys::NFont::Font >& a_font,s32 a_texture_width,const STLString& a_name);

		#endif

	public:

		#if(0)

		#if !defined(ROM_MASTER)

		/** ＲＡＷテクスチャーＩＤ取得。
		*/
		u32 Debug_GetRawTextureID(s32 a_textureid);

		#endif

		#endif

	public:

		/** [描画命令]クリアカラー設定。
		*/
		void Render_SetClearColor(const NBsys::NColor::Color_F& a_color);

		/** [描画命令]クリアバッファ。
		*/
		void Render_ClearBuffer(bool a_depth,bool a_color);

		#if(0)
		/** アクションバッチング更新。
		*/
		void Render_UpdateActionBatching();

		/** Render_SetVertexBuffer。
		*/
		void Render_SetVertexBuffer(s32 a_vertexbufferid);

		/** Render_SetColorMask。
		*/
		void Render_SetColorMask(bool a_r,bool a_g,bool a_b,bool a_a);

		/** Render_SetPolygonOffset。
		*/
		void Render_SetPolygonOffset(bool a_flag,f32 a_factor,f32 a_unit);

		#endif


		#if(0)

		/** Render_SetTextureDirect。
		*/
		void Render_SetTextureDirect(s32 a_textureunitid,s32 a_textureid);

		/** Render_SetFrameBuffer。
		*/
		void Render_SetFrameBuffer(s32 a_framebufferid);

		/** Render_DrawWorldLine。
		*/
		void Render_DrawWorldLine();

		/** Render_SetProjectionMatrix。
		*/
		void Render_SetProjectionMatrix(const NBsys::NGeometry::Geometry_Matrix_44& a_projection);

		/** Render_SetViewMatrix。
		*/
		void Render_SetViewMatrix(const NBsys::NGeometry::Geometry_Matrix_44& a_view);

		/** Render_ViewPort。
		*/
		void Render_ViewPort(f32 a_x,f32 a_y,f32 a_width,f32 a_height);


		/** Render_SetDepthTest。
		*/
		void Render_SetDepthTest(bool a_flag);

		/** Render_SetAlphaBlend。
		*/
		void Render_SetAlphaBlend(bool a_flag);

		/** Render_SetShader。
		*/
		void Render_SetShader(s32 a_vertex_shader_index);

		/** Render_SetAttributeParameter。

		return : 使用バイト数。

		*/
		s32 Render_SetAttributeParameter(s32 a_shaderid,const STLString& a_name,const void* a_data_byte,s32 a_stride_byte,s32 a_offset_byte);

		/** Render_SetUniformParameter。
		*/
		void Render_SetUniformParameter(s32 a_shaderid,const STLString& a_name,const void* a_data_byte,s32 a_countof);

		/** Render_SetUniformTexture。
		*/
		void Render_SetUniformTexture(s32 a_shaderid,const STLString& a_name,s32 a_textureid);

		/** Render_DrawArray_Triangle。
		*/
		void Render_DrawArray_Triangle(s32 a_vertex_offset,s32 a_vertex_countof);

		/** Render_DrawArray_Quads。
		*/
		void Render_DrawArray_Quads(s32 a_vertex_offset,s32 a_vertex_countof);

		/** Render_DrawFont_StartClear。
		*/
		void Render_DrawFont_StartClear();

		/** Render_DrawFont。
		*/
		void Render_DrawFont(const STLWString& a_string,f32 a_font_size,f32 a_x,f32 a_y,const NBsys::NColor::Color_F& a_color);

		/** Render_DrawRect。
		*/
		void Render_DrawRect(f32 a_x,f32 a_y,f32 a_w,f32 a_h,s32 a_textureid,const NBsys::NColor::Color_F& a_color);

		#endif
	};

}}
#endif

