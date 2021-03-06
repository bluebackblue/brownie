﻿#pragma once

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief OpenGL。
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
//#include "../texture/texture.h"
#include "../actionbatching/actionbatching.h"
//#include "../geometry/geometry.h"
#include "../color/color.h"
//#include "../font/font.h"
#pragma warning(pop)


/** include
*/
#include "./opengl_shaderlayout.h"


/** include
*/
#include "./opengl_impl_include.h"
#include "./opengl_impl_vertexbuffer.h"
#include "./opengl_impl_shaderstate.h"
//#include "./opengl_impl_rawid.h"
//#include "./opengl_impl_texture.h"
//#include "./opengl_impl_framebuffer.h"
//#include "./opengl_impl_font_decl.h"


/** NBsys::NOpengl
*/
#if(BSYS_OPENGL_ENABLE)
#pragma warning(push)
#pragma warning(disable:4710 4820)
namespace NBsys{namespace NOpengl
{
	/** Opengl_Impl
	*/
	class Opengl_Impl
	{
	private:

		/** ロックオブジェクト。
		*/
		LockObject lockobject;

		/** window
		*/
		GLFWwindow* window;

		/** performance_counter_update
		*/
		u64 performance_counter_update;

		/** update_proc
		*/
		bool (*update_proc)(f32 a_delta,bool a_endrequest);

		/** draw_proc
		*/
		void (*draw_proc)();

		/** mouse_l
		*/
		bool mouse_l;

		/** mouse_r
		*/
		bool mouse_r;

		/** mouse_x
		*/
		s32 mouse_x;

		/** mouse_y
		*/
		s32 mouse_y;

		/** id_maker
		*/
		IDMaker id_maker;

		/** アクションバッチング。ロックオブジェクト。
		*/
		LockObject actionbatching_lockobject;

		/** アクションバッチング。
		*/
		NBsys::NActionBatching::ActionBatching actionbatching;

		/** バーテックスバッファリスト。
		*/
		STLMap<s32,sharedptr<Opengl_Impl_VertexBuffer>>::Type vertexbuffer_list;

		/** shaderstate_list
		*/
		STLVector<sharedptr<Opengl_Impl_ShaderState>>::Type shaderstate_list;

		/** current_shaderprogram_rawid
		*/
		RawID current_shaderprogram_rawid;

		/** current_vertexarray_rawid
		*/
		RawID current_vertexarray_rawid;

		#if(0)

		/** rawtexture_list
		*/
		STLMap<s32,sharedptr<Opengl_Impl_Texture>>::Type texture_list;

		/** framebuffer_list
		*/
		STLMap<s32,sharedptr<Opengl_Impl_FrameBuffer>>::Type framebuffer_list;




		/** current_framebuffer_rawid
		*/
		RawID current_framebuffer_rawid;


		/** current_texture_rawid
		*/
		RawID current_texture_rawid;

		/** font
		*/
		sharedptr<Opengl_Impl_Font> font;

		#endif

	public:
		/** constructor
		*/
		Opengl_Impl() noexcept;

		/** destructor
		*/
		nonvirtual ~Opengl_Impl() noexcept;

	private:

		/** copy constructor禁止。
		*/
		Opengl_Impl(const Opengl_Impl& a_this) = delete;

		/** コピー禁止。
		*/
		void operator =(const Opengl_Impl& a_this) = delete;

	public:

		/** Init。
		*/
		void Init(bool (*a_update_proc)(f32 a_delta,bool a_endrequest),void (*a_draw_proc)());

		/** Main。
		*/
		void Main();

		/** StartBatching
		*/
		void StartBatching(sharedptr<NBsys::NActionBatching::ActionBatching_ActionList>& a_actionlist);

		/** バーテックスバッファ作成。
		*/
		s32 CreateVertexBuffer(const sharedptr<u8>& a_data_byte,s32 a_size_byte,s32 a_stride_byte);

		/** バーテックスバッファ削除。
		*/
		void DeleteVertexBuffer(s32 a_vertexbufferid);

		/** シェーダーロード開始。
		*/
		void LoadShaderRequest(const sharedptr<Opengl_ShaderLayout>& a_shaderlayout,AsyncResult<bool>& a_asyncresult);

		/** シェーダー削除。
		*/
		void DeleteShader(s32 a_shaderid);


		#if(0)
		/** SetShadeModel
		*/
		void SetShadeModel(Opengl_ShadeModelType::Id a_shademodeltype);

		/** [メインスレッド]テクスチャ―作成。
		*/
		s32 CreateTexture(const sharedptr<NBsys::NTexture::Texture>& a_texture);

		/** [メインスレッド]テクスチャー削除。
		*/
		void DeleteTexture(s32 a_textureid);

		/** [メインスレッド]フレームバッファ作成。
		*/
		s32 CreateFrameBuffer(s32 a_textureid_depth,s32 a_textureid_color0);

		/** [メインスレッド]フレームバッファ削除。
		*/
		//void DeleteFrameBuffer(s32 a_framebufferid);

		/** GetMouse
		*/
		void GetMouse(s32& a_x,s32& a_y,bool& a_left,bool& a_right);
		
		/** SetFont
		*/
		void SetFont(sharedptr<NBsys::NFont::Font>& a_font,s32 a_texture_width,const STLString& a_name);

		#endif

	public:

		#if(0)

		/** ＲＡＷテクスチャーＩＤ取得。
		*/
		RawID GetTexture_RawID(s32 a_textureid);

		#endif

	public:

		#if(0)

		/** アクションバッチング更新。
		*/
		void Render_UpdateActionBatching();
	
		/** Render_CreateFrameBuffer。
		*/
		void Render_CreateFrameBuffer(sharedptr<Opengl_Impl_FrameBuffer>& a_framebuffer);

		/** Render_CreateTexture。
		*/
		void Render_CreateTexture(sharedptr<Opengl_Impl_Texture>& a_texture);

		/** Render_DeleteTexture。
		*/
		void Render_DeleteTexture(sharedptr<Opengl_Impl_Texture>& a_texture);

		#endif

	public:

		/** [描画命令]クリアカラー設定。
		*/
		void Render_SetClearColor(const NBsys::NColor::Color_F& a_color);

		/** [描画命令]クリアバッファ。
		*/
		void Render_ClearBuffer(bool a_depth,bool a_color);

		/** [描画命令]ワールドライン描画。
		*/
		#if defined(ROM_DEVELOP)
		void Render_DrawWorldLine();
		#endif

		/** [描画命令]バーテックスバッファ作成。
		*/
		void Render_CreateVertexBuffer(sharedptr<Opengl_Impl_VertexBuffer>& a_vertexbuffer);

		/** [描画命令]バーテックスバッファ削除。
		*/
		void Render_DeleteVertexBuffer(sharedptr<Opengl_Impl_VertexBuffer>& a_vertexbuffer);

		/** [描画命令]シェーダーロード。
		*/
		void Render_LoadShader(sharedptr<Opengl_ShaderLayout>& a_shaderlayout);

		/** [描画命令]シェーダー削除。
		*/
		void Render_DeleteShader(sharedptr<Opengl_Impl_ShaderState>& a_shaderstate);

		/** [描画命令]シェーダー設定。
		*/
		void Render_SetShader(s32 a_shaderid);
	
		/** [描画命令]バーテックスバッファ設定。
		*/
		void Render_SetVertexBuffer(s32 a_vertexbufferid);

		/** Render_SetAttributeParameter。

		return : 使用バイト数。

		*/
		s32 Render_SetAttributeParameter(s32 a_shaderid,const STLString& a_name,s32 a_stride_byte,s32 a_offset_byte);

		/** Render_DrawArray_Triangle。
		*/
		void Render_DrawArray_Triangle(s32 a_vertex_offset,s32 a_vertex_countof);

		/** Render_ViewPort。
		*/
		void Render_ViewPort(const Rect2DType_R<f32>& a_rect);

		/** Render_SetVertexUniform。
		*/
		void Render_SetUniformParameter(s32 a_shaderid,const STLString& a_name,const void* a_data_byte,s32 a_countof);

		/** Render_SetDepthTest。
		*/
		void Render_SetDepthTest(bool a_flag);

		#if(0)

		/** [レンダースレッドRender_SetColorMask。
		*/
		void Render_SetColorMask(bool a_r,bool a_g,bool a_b,bool a_a);

		/** Render_SetPolygonOffset。
		*/
		void Render_SetPolygonOffset(bool a_flag,f32 a_factor,f32 a_unit);

		/** Render_SetTextureDirect。
		*/
		void Render_SetTextureDirect(s32 a_textureunitid,s32 a_textureid);

		/** Render_SetFrameBuffer。
		*/
		void Render_SetFrameBuffer(s32 a_framebufferid);

		/** Render_SetProjectionMatrix。
		*/
		void Render_SetProjectionMatrix(const NBsys::NGeometry::Geometry_Matrix_44& a_projection);

		/** Render_SetViewMatrix。
		*/
		void Render_SetViewMatrix(const NBsys::NGeometry::Geometry_Matrix_44& a_view);




		/** Render_SetAlphaBlend。
		*/
		void Render_SetAlphaBlend(bool a_flag);

		/** Render_SetShader。
		*/
		void Render_SetShader(s32 a_vertex_shader_index);


		/** Render_SetUniformTexture。
		*/
		void Render_SetUniformTexture(s32 a_shaderid,const STLString& a_name,s32 a_textureid);

		/** Render_DrawArray_Quads。
		*/
		void Render_DrawArray_Quads(s32 a_vertex_offset,s32 a_vertex_countof);

		/** Render_DrawFont_ClearLockFlag
		*/
		void Render_DrawFont_ClearLockFlag();

		/** Render_DrawFont。
		*/
		void Render_DrawFont(const STLWString& a_string,f32 a_font_size,f32 a_x,f32 a_y,const NBsys::NColor::Color_F& a_color);

		/** Render_DrawRect。
		*/
		void Render_DrawRect(f32 a_x,f32 a_y,f32 a_w,f32 a_h,s32 a_textureid,const NBsys::NColor::Color_F& a_color);

		#endif
	};

}}
#pragma warning(pop)
#endif

