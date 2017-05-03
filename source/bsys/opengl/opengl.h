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
#include "./opengl_shaderlayout.h"


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

		/** �e�N�X�`���\�쐬�B
		*/
		s32 CreateTexture(const sharedptr< NBsys::NTexture::Texture >& a_texture);

		/** �e�N�X�`���[�폜�B
		*/
		void DeleteTexture(s32 a_textureid);

		/** �t���[���o�b�t�@�쐬�B
		*/
		s32 CreateFrameBuffer(s32 a_textureid_depth,s32 a_textureid_color0);

		/** �t���[���o�b�t�@�폜�B
		*/
		//void DeleteFrameBuffer(s32 a_framebufferid);

		/** �}�E�X�擾�B
		*/
		void GetMouse(s32& a_x,s32& a_y,bool& a_left,bool& a_right);

		/** SetFont
		*/
		void SetFont(sharedptr< NBsys::NFont::Font >& a_font,s32 a_texture_width,const STLString& a_name);

		#endif

	public:

		#if(0)

		#if !defined(ROM_MASTER)

		/** �q�`�v�e�N�X�`���[�h�c�擾�B
		*/
		u32 Debug_GetRawTextureID(s32 a_textureid);

		#endif

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

		/** [�`�施��]�V�F�[�_�[�ݒ�B
		*/
		void Render_SetShader(s32 a_shaderid);

		/** [�`�施��]�o�b�e�b�N�X�o�b�t�@�ݒ�B
		*/
		void Render_SetVertexBuffer(s32 a_vertexbufferid);

		/** Render_SetAttributeParameter�B

		return : �g�p�o�C�g���B

		*/
		s32 Render_SetAttributeParameter(s32 a_shaderid,const STLString& a_name,s32 a_stride_byte,s32 a_offset_byte);

		/** Render_DrawArray_Triangle�B
		*/
		void Render_DrawArray_Triangle(s32 a_vertex_offset,s32 a_vertex_countof);

		#if(0)
		/** �A�N�V�����o�b�`���O�X�V�B
		*/
		void Render_UpdateActionBatching();

		/** Render_SetColorMask�B
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

		/** Render_ViewPort�B
		*/
		void Render_ViewPort(f32 a_x,f32 a_y,f32 a_width,f32 a_height);

		/** Render_SetDepthTest�B
		*/
		void Render_SetDepthTest(bool a_flag);

		/** Render_SetAlphaBlend�B
		*/
		void Render_SetAlphaBlend(bool a_flag);

		/** Render_SetUniformParameter�B
		*/
		void Render_SetUniformParameter(s32 a_shaderid,const STLString& a_name,const void* a_data_byte,s32 a_countof);

		/** Render_SetUniformTexture�B
		*/
		void Render_SetUniformTexture(s32 a_shaderid,const STLString& a_name,s32 a_textureid);

		/** Render_DrawArray_Quads�B
		*/
		void Render_DrawArray_Quads(s32 a_vertex_offset,s32 a_vertex_countof);

		/** Render_DrawFont_StartClear�B
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

