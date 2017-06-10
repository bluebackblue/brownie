

/**
* Copyright (c) 2017 blueback
* Released under the MIT License
* https://github.com/bluebackblue/brownie/blob/master/LICENSE
* http://bbbproject.sakura.ne.jp/wordpress/mitlicense
* @brief �l�l�c�B�o�l�w�B
*/


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./mmdpmx.h"


/** NBsys::NMmdPmx
*/
#if(BSYS_MMDPMX_ENABLE)
namespace NBsys{namespace NMmdPmx
{

	/** Load_Header
	*/
	bool MmdPmx::Load_Header(u8*& a_raw)
	{
		//MmdPmx_Header
		this->header = Memory::Copy< MmdPmx_Header >(a_raw);

		//t_header_ex_size
		u8 t_header_ex_size = Memory::Copy< u8 >(a_raw,0);

		//MmdPmx_Header_Ex
		this->header_ex = Memory::Copy< MmdPmx_Header_Ex >(a_raw,t_header_ex_size + 1);

		//model_name
		STLWString model_name_jp;
		STLWString model_name_en;

		//comment
		STLWString comment_jp;
		STLWString comment_en;

		//model name jp
		{
			u32 t_length = Memory::Copy< u32 >(a_raw);
			if(t_length > 0){
				if(this->header_ex.is_utf8){
					STLString t_buffer(reinterpret_cast< char* >(a_raw),t_length);
					CharToWchar(t_buffer,this->model_name_jp);
				}else{
					this->model_name_jp = STLWString(reinterpret_cast< wchar* >(a_raw),t_length/2);
				}
				a_raw += t_length;
			}
		}

		//model name en
		{
			u32 t_length = Memory::Copy< u32 >(a_raw);
			if(t_length > 0){
				if(this->header_ex.is_utf8){
					STLString t_buffer(reinterpret_cast< char* >(a_raw),t_length);
					CharToWchar(t_buffer,this->model_name_en);
				}else{
					this->model_name_en = STLWString(reinterpret_cast< wchar* >(a_raw),t_length/2);
				}
				a_raw += t_length;
			}
		}

		//comment jp
		{
			u32 t_length = Memory::Copy< u32 >(a_raw);
			if(t_length > 0){
				if(this->header_ex.is_utf8){
					STLString t_buffer(reinterpret_cast< char* >(a_raw),t_length);
					CharToWchar(t_buffer,this->comment_jp);
				}else{
					this->comment_jp = STLWString(reinterpret_cast< wchar* >(a_raw),t_length/2);
				}
				a_raw += t_length;
			}
		}

		//comment en
		{
			u32 t_length = Memory::Copy< u32 >(a_raw);
			if(t_length > 0){
				if(this->header_ex.is_utf8){
					STLString t_buffer(reinterpret_cast< char* >(a_raw),t_length);
					CharToWchar(t_buffer,this->comment_en);
				}else{
					this->comment_en = STLWString(reinterpret_cast< wchar* >(a_raw),t_length/2);
				}
				a_raw += t_length;
			}
		}

		return true;
	}

	/** Load_Vertex
	*/
	bool MmdPmx::Load_Vertex(u8*& a_raw)
	{
		this->vertex_list_size = Memory::Copy< u32 >(a_raw);
		this->vertex_list.reset(new MmdPmx_VertexData[this->vertex_list_size],default_delete< MmdPmx_VertexData[] >());

		for(u32 ii=0;ii<this->vertex_list_size;ii++){
			MmdPmx_VertexData& t_vertex_data = this->vertex_list.get()[ii];

			//position
			t_vertex_data.position = Memory::Copy< NBsys::NGeometry::Geometry_Vector3 >(a_raw);

			//normal
			t_vertex_data.normal = Memory::Copy< NBsys::NGeometry::Geometry_Vector3 >(a_raw);

			//uv
			t_vertex_data.uv = Memory::Copy< NBsys::NGeometry::Geometry_Vector2 >(a_raw);

			//uv_ex
			for(s32 jj=0;jj<this->header_ex.uv_ex_size;jj++){
				t_vertex_data.uv_ex[jj] = Memory::Copy< NBsys::NGeometry::Geometry_Vector4 >(a_raw);
			}

			//weight_type
			t_vertex_data.weight_type = Memory::Copy< u8 >(a_raw);

			//bone
			switch (t_vertex_data.weight_type){
			case 0:
				{
					if(this->header_ex.bone_index_size == 1){
						t_vertex_data.bone_index[0] = Memory::Copy< s8 >(a_raw);
					}else if(this->header_ex.bone_index_size == 2){
						t_vertex_data.bone_index[0] = Memory::Copy< s16 >(a_raw);
					}else{
						t_vertex_data.bone_index[0] = Memory::Copy< s32 >(a_raw);
					}
				}break;
			case 1:
				{
					for(s32 jj=0;jj<2;jj++){
						if(this->header_ex.bone_index_size == 1){
							t_vertex_data.bone_index[jj] = Memory::Copy< s8 >(a_raw);
						}else if(this->header_ex.bone_index_size == 2){
							t_vertex_data.bone_index[jj] = Memory::Copy< s16 >(a_raw);
						}else{
							t_vertex_data.bone_index[jj] = Memory::Copy< s32 >(a_raw);
						}
					}

					t_vertex_data.bone_weight[0] = Memory::Copy< f32 >(a_raw);
				}break;
			case 2:
				{
					for(s32 jj=0;jj<4;jj++){
						if(this->header_ex.bone_index_size == 1){
							t_vertex_data.bone_index[jj] = Memory::Copy< s8 >(a_raw);
						}else if(this->header_ex.bone_index_size == 2){
							t_vertex_data.bone_index[jj] = Memory::Copy< s16 >(a_raw);
						}else{
							t_vertex_data.bone_index[jj] = Memory::Copy< s32 >(a_raw);
						}
					}

					for(s32 jj=0;jj<4;jj++){
						t_vertex_data.bone_weight[jj] = Memory::Copy< f32 >(a_raw);
					}
				}break;
			case 3:
				{
					for(s32 jj=0;jj<2;jj++){
						if(this->header_ex.bone_index_size == 1){
							t_vertex_data.bone_index[jj] = Memory::Copy< s8 >(a_raw);
						}else if(this->header_ex.bone_index_size == 2){
							t_vertex_data.bone_index[jj] = Memory::Copy< s16 >(a_raw);
						}else{
							t_vertex_data.bone_index[jj] = Memory::Copy< s32 >(a_raw);
						}
					}

					t_vertex_data.bone_weight[0] = Memory::Copy< f32 >(a_raw);

					t_vertex_data.sdef_c = Memory::Copy< NBsys::NGeometry::Geometry_Vector3 >(a_raw);
					t_vertex_data.sdef_r0 = Memory::Copy< NBsys::NGeometry::Geometry_Vector3 >(a_raw);
					t_vertex_data.sdef_r1 = Memory::Copy< NBsys::NGeometry::Geometry_Vector3 >(a_raw);
				}break;
			case 4:
				{
					for(s32 jj=0;jj<4;jj++){
						if(this->header_ex.bone_index_size == 1){
							t_vertex_data.bone_index[jj] = Memory::Copy< s8 >(a_raw);
						}else if(this->header_ex.bone_index_size == 2){
							t_vertex_data.bone_index[jj] = Memory::Copy< s16 >(a_raw);
						}else{
							t_vertex_data.bone_index[jj] = Memory::Copy< s32 >(a_raw);
						}
					}

					for(s32 jj=0;jj<4;jj++){
						t_vertex_data.bone_weight[jj] = Memory::Copy< f32 >(a_raw);
					}
				}break;
			default:
				{
					ASSERT(0);
				}break;
			}

			//edge_mag
			t_vertex_data.edge_mag = Memory::Copy< f32 >(a_raw);
		}

		return true;
	}

	/** Load_Index
	*/
	bool MmdPmx::Load_Index(u8*& a_raw)
	{
		this->index_list_size = Memory::Copy< u32 >(a_raw);
		this->index_list.reset(new u32[this->index_list_size],default_delete< u32[] >());

		if(this->header_ex.vertex_index_size == 1){
			for(u32 ii=0;ii<this->index_list_size;ii++){
				this->index_list.get()[ii] = Memory::Copy< u8 >(a_raw);
			}
		}else if(this->header_ex.vertex_index_size == 2){
			for(u32 ii=0;ii<this->index_list_size;ii++){
				this->index_list.get()[ii] = Memory::Copy< u16 >(a_raw);
			}
		}else{
			for(u32 ii=0;ii<this->index_list_size;ii++){
				this->index_list.get()[ii] = Memory::Copy< u32 >(a_raw);
			}
		}

		return true;
	}

	/** Load_TextureName
	*/
	bool MmdPmx::Load_TextureName(u8*& a_raw)
	{
		this->texturename_list_size = Memory::Copy< u32 >(a_raw);

		for(u32 ii=0;ii<this->texturename_list_size;ii++){

			STLWString t_texturename;
					
			u32 t_length = Memory::Copy< u32 >(a_raw);
			if(t_length > 0){
				if(this->header_ex.is_utf8){
					STLString t_buffer(reinterpret_cast< char* >(a_raw),t_length);
					CharToWchar(reinterpret_cast< char* >(a_raw),t_texturename);
				}else{
					t_texturename = STLWString(reinterpret_cast< wchar* >(a_raw),t_length/2);
				}
				a_raw += t_length;
			}

			this->texturename_list.push_back(t_texturename);
		}

		return true;
	}

	/** Load_Parts
	*/
	bool MmdPmx::Load_Parts(u8*& a_raw)
	{
		this->parts_list_size = Memory::Copy< u32 >(a_raw);
		this->parts_list.resize(this->parts_list_size);

		s32 t_start_index = 0;

		for(u32 ii=0;ii<this->parts_list_size;ii++){
			MmdPmx_Parts& t_parts = this->parts_list.at(ii);

			//parts_name_jp
			{
				u32 t_length = Memory::Copy< u32 >(a_raw);
				if(t_length > 0){
					if(this->header_ex.is_utf8){
						STLString t_buffer(reinterpret_cast< char* >(a_raw),t_length);
						CharToWchar(t_buffer,t_parts.parts_name_jp);
					}else{
						t_parts.parts_name_jp = STLWString(reinterpret_cast< wchar* >(a_raw),t_length/2);
					}
					a_raw += t_length;
				}
			}

			//parts_name_en
			{
				u32 t_length = Memory::Copy< u32 >(a_raw);
				if(t_length > 0){
					if(this->header_ex.is_utf8){
						STLString t_buffer(reinterpret_cast< char* >(a_raw),t_length);
						CharToWchar(t_buffer,t_parts.parts_name_en);
					}else{
						t_parts.parts_name_en = STLWString(reinterpret_cast< wchar* >(a_raw),t_length/2);
					}
					a_raw += t_length;
				}
			}

			//diffuse
			{
				t_parts.diffuse = Memory::Copy< NBsys::NColor::Color_F >(a_raw);
			}

			//specular : TODO : COLOR3
			{
				t_parts.specular = Memory::Copy< NBsys::NGeometry::Geometry_Vector3 >(a_raw);
			}

			//specular_power
			{
				t_parts.specular_power = Memory::Copy< f32 >(a_raw);
			}

			//ambient
			{
				t_parts.ambient = Memory::Copy< NBsys::NGeometry::Geometry_Vector3 >(a_raw);
			}

			//mode
			{
				//00000001 : ���ʕ`��B
				//00000010 : �n�ʉe�B
				//00000100 : �Z���t�V���h�E�}�b�v�ւ̕`��B
				//00001000 : �Z���t�V���h�E�̕`��B
				//00010000 : �G�b�W�`��B
				//00100000 : ���_�J���[�B
				//01000000 : Point�`��B
				//10000000 : Line�`��B

				u8 t_drawmode = Memory::Copy< u8 >(a_raw);

				/** ���ʕ`��B
				*/
				t_parts.drawmode_cullfull = (t_drawmode & (0x01)) > 0;

				/** �e�����B
				*/
				t_parts.drawmode_shadow = (t_drawmode & (0x01<<1)) > 0;

				/** �Z���t�V���h�E�}�b�v�ւ̕`��B
				*/
				t_parts.drawmode_selfshadowmap = (t_drawmode & (0x01<<2)) > 0;

				/** �Z���t�V���h�E�̕`��B
				*/
				t_parts.drawmode_selfshadow = (t_drawmode & (0x01<<3)) > 0;

				/** �G�b�W�̕`��B
				*/
				t_parts.drawmode_edge = (t_drawmode & (0x01<<4)) > 0;

				/** ���_�J���[�B
				*/
				t_parts.drawmode_vertexcolor = (t_drawmode & (0x01<<5)) > 0;

				/** �|�C���g�`��B
				*/
				t_parts.drawmode_point = (t_drawmode & (0x01<<6)) > 0;

				/** ���C���`��B
				*/
				t_parts.drawmode_line = (t_drawmode & (0x01<<7)) > 0;
			}

			//edge
			{
				t_parts.edge_color = Memory::Copy< NBsys::NColor::Color_F >(a_raw);
				t_parts.edge_size = Memory::Copy< f32 >(a_raw);
			}

			//textureindex
			{
				if(this->header_ex.texture_index_size == 1){
					t_parts.textureindex = Memory::Copy< s8 >(a_raw);
				}else if(this->header_ex.texture_index_size == 2){
					t_parts.textureindex = Memory::Copy< s16 >(a_raw);
				}else{
					t_parts.textureindex = Memory::Copy< s32 >(a_raw);
				}

				if(this->header_ex.texture_index_size == 1){
					t_parts.textureindex_sphere = Memory::Copy< s8 >(a_raw);
				}else if(this->header_ex.texture_index_size == 2){
					t_parts.textureindex_sphere = Memory::Copy< s16 >(a_raw);
				}else{
					t_parts.textureindex_sphere = Memory::Copy< s32 >(a_raw);
				}

				t_parts.textureindex_sphere_mode = Memory::Copy< s8 >(a_raw);
			}

			//toon
			{
				t_parts.toon_mode = Memory::Copy< u8 >(a_raw);

				if(t_parts.toon_mode == 0){
					//�ʁB

					if(this->header_ex.texture_index_size == 1){
						t_parts.toon_textureindex = Memory::Copy< s8 >(a_raw);
					}else if(this->header_ex.texture_index_size == 2){
						t_parts.toon_textureindex = Memory::Copy< s16 >(a_raw);
					}else{
						t_parts.toon_textureindex = Memory::Copy< s32 >(a_raw);
					}

				}else if(t_parts.toon_mode == 1){
					//���ʁB

					t_parts.toon_textureindex = Memory::Copy< s8 >(a_raw);
				}else{
					ASSERT(0);
				}
			}

			//comment
			{
				u32 t_length = Memory::Copy< u32 >(a_raw);
				if(t_length > 0){
					if(this->header_ex.is_utf8){
						STLString t_buffer(reinterpret_cast< char* >(a_raw),t_length);
						CharToWchar(t_buffer,t_parts.comment);
					}else{
						t_parts.comment = STLWString(reinterpret_cast< wchar* >(a_raw),t_length/2);
					}
					a_raw += t_length;
				}
			}

			//index_size
			{
				t_parts.start_index = t_start_index;
				t_parts.count_of_index = Memory::Copy< u32 >(a_raw);
				t_start_index += t_parts.count_of_index;
			}
		}

		return true;
	}

	/** Load_Bone
	*/
	bool MmdPmx::Load_Bone(u8*& a_raw)
	{
		STLWString t_bone_name_jp = L"";
		STLWString t_bone_name_en = L"";

		NBsys::NGeometry::Geometry_Vector3 t_bone_position = NBsys::NGeometry::Geometry_Identity();

		s32 t_boneindex_parent = -1;

		s32 t_deform_depth = -1;

		u16 t_boneflag = 0x0000;

		NBsys::NGeometry::Geometry_Vector3 t_bone_position_offset(NBsys::NGeometry::Geometry_Identity());

		s32 t_boneindex_link = -1;

		s32 t_boneindex_append = -1;
		f32 t_boneindex_append_weight = 0.0f;

		NBsys::NGeometry::Geometry_Vector3 t_bone_fixed_axis(NBsys::NGeometry::Geometry_Identity());

		NBsys::NGeometry::Geometry_Vector3 t_bone_local_axix_x = NBsys::NGeometry::Geometry_Identity();
		NBsys::NGeometry::Geometry_Vector3 t_bone_local_axix_z = NBsys::NGeometry::Geometry_Identity();

		s32 t_bone_key_value = 0;

		s32 t_bone_ik_target_boneindex = -1;
		s32 t_bone_ik_iteration_count = 0;
		f32	t_bone_ik_limit_rad = 0.0f;

		u32 t_bone_count = Memory::Copy< u32 >(a_raw);

		for(u32 ii=0;ii<t_bone_count;ii++){

			//bonename_jp
			{
				u32 t_length = Memory::Copy< u32 >(a_raw);
				if(t_length > 0){
					if(this->header_ex.is_utf8){
						STLString t_buffer(reinterpret_cast< char* >(a_raw),t_length);
						CharToWchar(t_buffer,t_bone_name_jp);
					}else{
						t_bone_name_jp = STLWString(reinterpret_cast< wchar* >(a_raw),t_length/2);
					}
					a_raw += t_length;
				}
			}

			//bonename_en
			{
				u32 t_length = Memory::Copy< u32 >(a_raw);
				if(t_length > 0){
					if(this->header_ex.is_utf8){
						STLString t_buffer(reinterpret_cast< char* >(a_raw),t_length);
						CharToWchar(t_buffer,t_bone_name_en);
					}else{
						t_bone_name_en = STLWString(reinterpret_cast< wchar* >(a_raw),t_length/2);
					}
					a_raw += t_length;
				}
			}

			t_bone_position = Memory::Copy< NBsys::NGeometry::Geometry_Vector3 >(a_raw);

			//boneindex_parent
			{
				if(this->header_ex.bone_index_size == 1){
					t_boneindex_parent = Memory::Copy< s8 >(a_raw);
				}else if(this->header_ex.bone_index_size == 2){
					t_boneindex_parent = Memory::Copy< s16 >(a_raw);
				}else{
					t_boneindex_parent = Memory::Copy< s32 >(a_raw);
				}
			}

			t_deform_depth = Memory::Copy< s32 >(a_raw);

			t_boneflag = Memory::Copy< u16 >(a_raw);

			/*
			0x0001  : �ڑ���(PMD�q�{�[���w��)�\�����@ -> 0:���W�I�t�Z�b�g�Ŏw�� 1:�{�[���Ŏw��B
			0x0002  : ��]�\
			0x0004  : �ړ��\
			0x0008  : �\��
			0x0010  : �����
			0x0020  : IK
			0x0040	: dummy
			0x0080  : ���[�J���t�^ | �t�^�Ώ� 0:���[�U�[�ό`�l�^IK�����N�^���d�t�^ 1:�e�̃��[�J���ό`�ʁB
			0x0100  : ��]�t�^
			0x0200  : �ړ��t�^
			0x0400  : ���Œ�
			0x0800  : ���[�J����
			0x1000  : ������ό`
			0x2000  : �O���e�ό`
			*/
			bool t_boneflag_target_showmode			= (0x0001 & t_boneflag) > 0;
			bool t_boneflag_allow_rotate			= (0x0002 & t_boneflag) > 0;
			bool t_boneflag_allow_translate			= (0x0004 & t_boneflag) > 0;
			bool t_boneflag_visible					= (0x0008 & t_boneflag) > 0;
			bool t_boneflag_allow_control			= (0x0010 & t_boneflag) > 0;
			bool t_boneflag_ik						= (0x0020 & t_boneflag) > 0;
			bool t_boneflag_dummy					= (0x0040 & t_boneflag) > 0;
			bool t_boneflag_append_local			= (0x0080 & t_boneflag) > 0;
			bool t_boneflag_append_rotate			= (0x0100 & t_boneflag) > 0;
			bool t_boneflag_append_translate		= (0x0200 & t_boneflag) > 0;
			bool t_boneflag_fixed_axis				= (0x0400 & t_boneflag) > 0;
			bool t_boneflag_local_axis				= (0x0800 & t_boneflag) > 0;
			bool t_boneflag_deform_after_physics	= (0x1000 & t_boneflag) > 0;
			bool t_boneflag_deform_outer_parent		= (0x2000 & t_boneflag) > 0;



			if (t_boneflag_target_showmode == false){
				t_bone_position_offset = Memory::Copy< NBsys::NGeometry::Geometry_Vector3 >(a_raw);
			}else{
				//boneindex_link
				{
					if(this->header_ex.bone_index_size == 1){
						t_boneindex_link = Memory::Copy< s8 >(a_raw);
					}else if(this->header_ex.bone_index_size == 2){
						t_boneindex_link = Memory::Copy< s16 >(a_raw);
					}else{
						t_boneindex_link = Memory::Copy< s32 >(a_raw);
					}
				}
			}

			if(t_boneflag_append_rotate || t_boneflag_append_translate){

				//boneindex_append
				{
					if(this->header_ex.bone_index_size == 1){
						t_boneindex_append = Memory::Copy< s8 >(a_raw);
					}else if(this->header_ex.bone_index_size == 2){
						t_boneindex_append = Memory::Copy< s16 >(a_raw);
					}else{
						t_boneindex_append = Memory::Copy< s32 >(a_raw);
					}
				}

				t_boneindex_append_weight = Memory::Copy< f32 >(a_raw);
			}

			if(t_boneflag_fixed_axis){
				t_bone_fixed_axis = Memory::Copy< NBsys::NGeometry::Geometry_Vector3 >(a_raw);
			}

			if(t_boneflag_local_axis){
				t_bone_local_axix_x = Memory::Copy< NBsys::NGeometry::Geometry_Vector3 >(a_raw);
				t_bone_local_axix_z = Memory::Copy< NBsys::NGeometry::Geometry_Vector3 >(a_raw);
			}

			if(t_boneflag_deform_outer_parent){
				t_bone_key_value = Memory::Copy< s32 >(a_raw);
			}

			if(t_boneflag_ik){

				//ik_target_boneindex
				{
					if(this->header_ex.bone_index_size == 1){
						t_bone_ik_target_boneindex = Memory::Copy< s8 >(a_raw);
					}else if(this->header_ex.bone_index_size == 2){
						t_bone_ik_target_boneindex = Memory::Copy< s16 >(a_raw);
					}else{
						t_bone_ik_target_boneindex = Memory::Copy< s32 >(a_raw);
					}
				}

				t_bone_ik_iteration_count = Memory::Copy< s32 >(a_raw);
				t_bone_ik_limit_rad = Memory::Copy< f32 >(a_raw);


				{
					s32 t_ik_link_count = 0;


					t_ik_link_count = Memory::Copy< s32 >(a_raw);

					for(int jj=0;jj<t_ik_link_count;jj++){

						s32 t_ik_link_boneindex = -1;
						u8 t_ik_link_enable_limit = 0x00;

						NBsys::NGeometry::Geometry_Vector3 t_ik_link_limit_min = NBsys::NGeometry::Geometry_Identity();
						NBsys::NGeometry::Geometry_Vector3 t_ik_link_limit_max = NBsys::NGeometry::Geometry_Identity();

						//t_ik_link_boneindex
						{
							if(this->header_ex.bone_index_size == 1){
								t_ik_link_boneindex = Memory::Copy< s8 >(a_raw);
							}else if(this->header_ex.bone_index_size == 2){
								t_ik_link_boneindex = Memory::Copy< s16 >(a_raw);
							}else{
								t_ik_link_boneindex = Memory::Copy< s32 >(a_raw);
							}
						}

						t_ik_link_enable_limit = Memory::Copy< u8 >(a_raw);

						if(t_ik_link_enable_limit > 0){
							t_ik_link_limit_min = Memory::Copy< NBsys::NGeometry::Geometry_Vector3 >(a_raw);
							t_ik_link_limit_max = Memory::Copy< NBsys::NGeometry::Geometry_Vector3 >(a_raw);
						}
					}
				}
			}
		}

		return true;
	}

	/** Load
	*/
	bool MmdPmx::Load(sharedptr< NFile::File_Object >& a_file)
	{
		sharedptr< u8 >& t_data = a_file->GetLoadData();
		u8* t_raw = t_data.get();
		
		{
			if(this->Load_Header(t_raw) == false){
				return false;
			}

			if(this->Load_Vertex(t_raw) == false){
				return false;
			}

			if(this->Load_Index(t_raw) == false){
				return false;
			}

			if(this->Load_TextureName(t_raw) == false){
				return false;
			}

			if(this->Load_Parts(t_raw) == false){
				return false;
			}

			if(this->Load_Bone(t_raw) == false){
				return false;
			}
		}

		return true;
	}

	/** Load
	*/
	sharedptr< MmdPmx > Load(sharedptr< NFile::File_Object >& a_file)
	{
		if(a_file->IsBusy() == true){
			return nullptr;
		}

		sharedptr< MmdPmx > t_mmdpmx(new MmdPmx());
		if(t_mmdpmx->Load(a_file) == true){
			return t_mmdpmx;
		}

		return nullptr;
	}

}}
#endif

