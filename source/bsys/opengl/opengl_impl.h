#pragma once

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief OpenGL�B
*/


/** include
*/
#include "../types/types.h"


/** include
*/
//#include "../texture/texture.h"
#include "../actionbatching/actionbatching.h"
//#include "../geometry/geometry.h"
#include "../color/color.h"
//#include "../font/font.h"


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
namespace NBsys{namespace NOpengl
{
	/** Opengl_Impl
	*/
	class Opengl_Impl
	{
	private:

		/** ���b�N�I�u�W�F�N�g�B
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

		/** �A�N�V�����o�b�`���O�B���b�N�I�u�W�F�N�g�B
		*/
		LockObject actionbatching_lockobject;

		/** �A�N�V�����o�b�`���O�B
		*/
		NBsys::NActionBatching::ActionBatching actionbatching;

		/** �o�[�e�b�N�X�o�b�t�@���X�g�B
		*/
		STLMap< s32 , sharedptr< Opengl_Impl_VertexBuffer > >::Type vertexbuffer_list;

		/** shaderstate_list
		*/
		STLVector< sharedptr< Opengl_Impl_ShaderState > >::Type shaderstate_list;

		/** current_shaderprogram_rawid
		*/
		RawID current_shaderprogram_rawid;

		/** current_vertexarray_rawid
		*/
		RawID current_vertexarray_rawid;



		#if(0)

		/** rawtexture_list
		*/
		STLMap< s32 , sharedptr< Opengl_Impl_Texture > >::Type texture_list;

		/** framebuffer_list
		*/
		STLMap< s32 , sharedptr< Opengl_Impl_FrameBuffer > >::Type framebuffer_list;




		/** current_framebuffer_rawid
		*/
		RawID current_framebuffer_rawid;


		/** current_texture_rawid
		*/
		RawID current_texture_rawid;

		/** font
		*/
		sharedptr< Opengl_Impl_Font > font;

		#endif

	public:
		/** constructor
		*/
		Opengl_Impl() noexcept;

		/** destructor
		*/
		nonvirtual ~Opengl_Impl() noexcept;

	public:

		/** Init�B
		*/
		void Init(bool (*a_update_proc)(f32 a_delta,bool a_endrequest),void (*a_draw_proc)());

		/** Main�B
		*/
		void Main();

		/** StartBatching
		*/
		void StartBatching(sharedptr< NBsys::NActionBatching::ActionBatching_ActionList >& a_actionlist);

		/** �o�[�e�b�N�X�o�b�t�@�쐬�B
		*/
		s32 CreateVertexBuffer(const sharedptr< u8 >& a_data_byte,s32 a_size_byte,s32 a_stride_byte);

		/** �o�[�e�b�N�X�o�b�t�@�폜�B
		*/
		void DeleteVertexBuffer(s32 a_vertexbufferid);

		/** �V�F�[�_�[���[�h�J�n�B
		*/
		void LoadShaderRequest(const sharedptr< Opengl_ShaderLayout >& a_shaderlayout,AsyncResult< bool >& a_asyncresult);

		/** �V�F�[�_�[�폜�B
		*/
		void DeleteShader(s32 a_shaderid);


		#if(0)
		/** SetShadeModel
		*/
		void SetShadeModel(Opengl_ShadeModelType::Id a_shademodeltype);

		/** [���C���X���b�h]�e�N�X�`���\�쐬�B
		*/
		s32 CreateTexture(const sharedptr< NBsys::NTexture::Texture>& a_texture);

		/** [���C���X���b�h]�e�N�X�`���[�폜�B
		*/
		void DeleteTexture(s32 a_textureid);

		/** [���C���X���b�h]�t���[���o�b�t�@�쐬�B
		*/
		s32 CreateFrameBuffer(s32 a_textureid_depth,s32 a_textureid_color0);

		/** [���C���X���b�h]�t���[���o�b�t�@�폜�B
		*/
		//void DeleteFrameBuffer(s32 a_framebufferid);

		/** GetMouse
		*/
		void GetMouse(s32& a_x,s32& a_y,bool& a_left,bool& a_right);
		
		/** SetFont
		*/
		void SetFont(sharedptr< NBsys::NFont::Font >& a_font,s32 a_texture_width,const STLString& a_name);

		#endif

	public:

		#if(0)

		/** �q�`�v�e�N�X�`���[�h�c�擾�B
		*/
		RawID GetTexture_RawID(s32 a_textureid);

		#endif

	public:

		#if(0)

		/** �A�N�V�����o�b�`���O�X�V�B
		*/
		void Render_UpdateActionBatching();
	
		/** Render_CreateFrameBuffer�B
		*/
		void Render_CreateFrameBuffer(sharedptr< Opengl_Impl_FrameBuffer >& a_framebuffer);

		/** Render_CreateTexture�B
		*/
		void Render_CreateTexture(sharedptr< Opengl_Impl_Texture >& a_texture);

		/** Render_DeleteTexture�B
		*/
		void Render_DeleteTexture(sharedptr< Opengl_Impl_Texture >& a_texture);

		#endif

	public:

		/** [�`�施��]�N���A�J���[�ݒ�B
		*/
		void Render_SetClearColor(const NBsys::NColor::Color_F& a_color);

		/** [�`�施��]�N���A�o�b�t�@�B
		*/
		void Render_ClearBuffer(bool a_depth,bool a_color);

		/** [�`�施��]���[���h���C���`��B
		*/
		#if(ROM_DEVELOP)
		void Render_DrawWorldLine();
		#endif

		/** [�`�施��]�o�[�e�b�N�X�o�b�t�@�쐬�B
		*/
		void Render_CreateVertexBuffer(sharedptr< Opengl_Impl_VertexBuffer >& a_vertexbuffer);

		/** [�`�施��]�o�[�e�b�N�X�o�b�t�@�폜�B
		*/
		void Render_DeleteVertexBuffer(sharedptr< Opengl_Impl_VertexBuffer >& a_vertexbuffer);

		/** [�`�施��]�V�F�[�_�[���[�h�B
		*/
		void Render_LoadShader(sharedptr< Opengl_ShaderLayout >& a_shaderlayout);

		/** [�`�施��]�V�F�[�_�[�폜�B
		*/
		void Render_DeleteShader(sharedptr< Opengl_Impl_ShaderState >& a_shaderstate);

		/** [�`�施��]�V�F�[�_�[�ݒ�B
		*/
		void Render_SetShader(s32 a_shaderid);
	
		/** [�`�施��]�o�[�e�b�N�X�o�b�t�@�ݒ�B
		*/
		void Render_SetVertexBuffer(s32 a_vertexbufferid);

		/** Render_SetAttributeParameter�B

		return : �g�p�o�C�g���B

		*/
		s32 Render_SetAttributeParameter(s32 a_shaderid,const STLString& a_name,s32 a_stride_byte,s32 a_offset_byte);

		/** Render_DrawArray_Triangle�B
		*/
		void Render_DrawArray_Triangle(s32 a_vertex_offset,s32 a_vertex_countof);

		/** Render_ViewPort�B
		*/
		void Render_ViewPort(f32 a_x,f32 a_y,f32 a_width,f32 a_height);

		/** Render_SetVertexUniform�B
		*/
		void Render_SetUniformParameter(s32 a_shaderid,const STLString& a_name,const void* a_data_byte,s32 a_countof);

		/** Render_SetDepthTest�B
		*/
		void Render_SetDepthTest(bool a_flag);

		#if(0)

		/** [�����_�[�X���b�hRender_SetColorMask�B
		*/
		void Render_SetColorMask(bool a_r,bool a_g,bool a_b,bool a_a);

		/** Render_SetPolygonOffset�B
		*/
		void Render_SetPolygonOffset(bool a_flag,f32 a_factor,f32 a_unit);

		/** Render_SetTextureDirect�B
		*/
		void Render_SetTextureDirect(s32 a_textureunitid,s32 a_textureid);

		/** Render_SetFrameBuffer�B
		*/
		void Render_SetFrameBuffer(s32 a_framebufferid);

		/** Render_SetProjectionMatrix�B
		*/
		void Render_SetProjectionMatrix(const NBsys::NGeometry::Geometry_Matrix_44& a_projection);

		/** Render_SetViewMatrix�B
		*/
		void Render_SetViewMatrix(const NBsys::NGeometry::Geometry_Matrix_44& a_view);




		/** Render_SetAlphaBlend�B
		*/
		void Render_SetAlphaBlend(bool a_flag);

		/** Render_SetShader�B
		*/
		void Render_SetShader(s32 a_vertex_shader_index);


		/** Render_SetUniformTexture�B
		*/
		void Render_SetUniformTexture(s32 a_shaderid,const STLString& a_name,s32 a_textureid);

		/** Render_DrawArray_Quads�B
		*/
		void Render_DrawArray_Quads(s32 a_vertex_offset,s32 a_vertex_countof);

		/** Render_DrawFont_StartClear
		*/
		void Render_DrawFont_StartClear();

		/** Render_DrawFont�B
		*/
		void Render_DrawFont(const STLWString& a_string,f32 a_font_size,f32 a_x,f32 a_y,const NBsys::NColor::Color_F& a_color);

		/** Render_DrawRect�B
		*/
		void Render_DrawRect(f32 a_x,f32 a_y,f32 a_w,f32 a_h,s32 a_textureid,const NBsys::NColor::Color_F& a_color);

		#endif
	};

}}
#endif

