

/**
* Copyright (c) 2017 blueback
* Released under the MIT License
* https://github.com/bluebackblue/brownie/blob/master/LICENSE
* http://bbbproject.sakura.ne.jp/wordpress/mitlicense
* @brief ＭＭＤ。ＰＭＸ。
*/


/** include
*/
#include <bsys_pch.h>


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./mmd_pmx.h"


/** NBsys::NMmd
*/
#if(BSYS_MMD_PMX_ENABLE)
namespace NBsys{namespace NMmd
{

	/** Load_Header
	*/
	bool Mmd_Pmx::Load_Header(u8*& a_raw)
	{
		//Mmd_Pmx_Header
		this->header = Memory::Copy<Mmd_Pmx_Header>(a_raw);

		//t_header_ex_size
		u8 t_header_ex_size = Memory::Copy<u8>(a_raw,0);

		//Mmd_Pmx_Header_Ex
		this->header_ex = Memory::Copy<Mmd_Pmx_Header_Ex>(a_raw,t_header_ex_size + 1);

		//model_name
		STLWString model_name_jp;
		STLWString model_name_en;

		//comment
		STLWString comment_jp;
		STLWString comment_en;

		//model name jp
		{
			u32 t_length = Memory::Copy<u32>(a_raw);
			if(t_length > 0){
				if(this->header_ex.is_utf8){
					STLString t_buffer(reinterpret_cast<char*>(a_raw),t_length);
					CharToWchar(t_buffer,this->model_name_jp);
				}else{
					this->model_name_jp = STLWString(reinterpret_cast<wchar*>(a_raw),t_length/2);
				}
				a_raw += t_length;
			}
		}

		//model name en
		{
			u32 t_length = Memory::Copy<u32>(a_raw);
			if(t_length > 0){
				if(this->header_ex.is_utf8){
					STLString t_buffer(reinterpret_cast<char*>(a_raw),t_length);
					CharToWchar(t_buffer,this->model_name_en);
				}else{
					this->model_name_en = STLWString(reinterpret_cast<wchar*>(a_raw),t_length/2);
				}
				a_raw += t_length;
			}
		}

		//comment jp
		{
			u32 t_length = Memory::Copy<u32>(a_raw);
			if(t_length > 0){
				if(this->header_ex.is_utf8){
					STLString t_buffer(reinterpret_cast<char*>(a_raw),t_length);
					CharToWchar(t_buffer,this->comment_jp);
				}else{
					this->comment_jp = STLWString(reinterpret_cast<wchar*>(a_raw),t_length/2);
				}
				a_raw += t_length;
			}
		}

		//comment en
		{
			u32 t_length = Memory::Copy<u32>(a_raw);
			if(t_length > 0){
				if(this->header_ex.is_utf8){
					STLString t_buffer(reinterpret_cast<char*>(a_raw),t_length);
					CharToWchar(t_buffer,this->comment_en);
				}else{
					this->comment_en = STLWString(reinterpret_cast<wchar*>(a_raw),t_length/2);
				}
				a_raw += t_length;
			}
		}

		return true;
	}

	/** Load_Vertex
	*/
	bool Mmd_Pmx::Load_Vertex(u8*& a_raw)
	{
		this->vertex_list_size = Memory::Copy<u32>(a_raw);
		this->vertex_list.reset(new Mmd_Pmx_VertexData[this->vertex_list_size],default_delete<Mmd_Pmx_VertexData[]>());

		for(u32 ii=0;ii<this->vertex_list_size;ii++){
			Mmd_Pmx_VertexData& t_vertex_data = this->vertex_list.get()[ii];

			//position
			t_vertex_data.position = Memory::Copy<NBsys::NGeometry::Geometry_Vector3>(a_raw);

			//normal
			t_vertex_data.normal = Memory::Copy<NBsys::NGeometry::Geometry_Vector3>(a_raw);

			//uv
			t_vertex_data.uv = Memory::Copy<NBsys::NGeometry::Geometry_Vector2>(a_raw);

			//uv_ex
			for(s32 jj=0;jj<this->header_ex.uv_ex_size;jj++){
				t_vertex_data.uv_ex[jj] = Memory::Copy<NBsys::NGeometry::Geometry_Vector4>(a_raw);
			}

			//weight_type
			t_vertex_data.weight_type = Memory::Copy<u8>(a_raw);

			//bone
			switch (t_vertex_data.weight_type){
			case 0:
				{
					if(this->header_ex.bone_index_size == 1){
						t_vertex_data.bone_index[0] = Memory::Copy<s8>(a_raw);
					}else if(this->header_ex.bone_index_size == 2){
						t_vertex_data.bone_index[0] = Memory::Copy<s16>(a_raw);
					}else{
						t_vertex_data.bone_index[0] = Memory::Copy<s32>(a_raw);
					}
				}break;
			case 1:
				{
					for(s32 jj=0;jj<2;jj++){
						if(this->header_ex.bone_index_size == 1){
							t_vertex_data.bone_index[jj] = Memory::Copy<s8>(a_raw);
						}else if(this->header_ex.bone_index_size == 2){
							t_vertex_data.bone_index[jj] = Memory::Copy<s16>(a_raw);
						}else{
							t_vertex_data.bone_index[jj] = Memory::Copy<s32>(a_raw);
						}
					}

					t_vertex_data.bone_weight[0] = Memory::Copy<f32>(a_raw);
				}break;
			case 2:
				{
					for(s32 jj=0;jj<4;jj++){
						if(this->header_ex.bone_index_size == 1){
							t_vertex_data.bone_index[jj] = Memory::Copy<s8>(a_raw);
						}else if(this->header_ex.bone_index_size == 2){
							t_vertex_data.bone_index[jj] = Memory::Copy<s16>(a_raw);
						}else{
							t_vertex_data.bone_index[jj] = Memory::Copy<s32>(a_raw);
						}
					}

					for(s32 jj=0;jj<4;jj++){
						t_vertex_data.bone_weight[jj] = Memory::Copy<f32>(a_raw);
					}
				}break;
			case 3:
				{
					for(s32 jj=0;jj<2;jj++){
						if(this->header_ex.bone_index_size == 1){
							t_vertex_data.bone_index[jj] = Memory::Copy<s8>(a_raw);
						}else if(this->header_ex.bone_index_size == 2){
							t_vertex_data.bone_index[jj] = Memory::Copy<s16>(a_raw);
						}else{
							t_vertex_data.bone_index[jj] = Memory::Copy<s32>(a_raw);
						}
					}

					t_vertex_data.bone_weight[0] = Memory::Copy<f32>(a_raw);

					t_vertex_data.sdef_c = Memory::Copy<NBsys::NGeometry::Geometry_Vector3>(a_raw);
					t_vertex_data.sdef_r0 = Memory::Copy<NBsys::NGeometry::Geometry_Vector3>(a_raw);
					t_vertex_data.sdef_r1 = Memory::Copy<NBsys::NGeometry::Geometry_Vector3>(a_raw);
				}break;
			case 4:
				{
					for(s32 jj=0;jj<4;jj++){
						if(this->header_ex.bone_index_size == 1){
							t_vertex_data.bone_index[jj] = Memory::Copy<s8>(a_raw);
						}else if(this->header_ex.bone_index_size == 2){
							t_vertex_data.bone_index[jj] = Memory::Copy<s16>(a_raw);
						}else{
							t_vertex_data.bone_index[jj] = Memory::Copy<s32>(a_raw);
						}
					}

					for(s32 jj=0;jj<4;jj++){
						t_vertex_data.bone_weight[jj] = Memory::Copy<f32>(a_raw);
					}
				}break;
			default:
				{
					ASSERT(0);
				}break;
			}

			//edge_mag
			t_vertex_data.edge_mag = Memory::Copy<f32>(a_raw);
		}

		return true;
	}

	/** Load_Index
	*/
	bool Mmd_Pmx::Load_Index(u8*& a_raw)
	{
		this->index_list_size = Memory::Copy<u32>(a_raw);
		this->index_list.reset(new u32[this->index_list_size],default_delete<u32[]>());

		if(this->header_ex.vertex_index_size == 1){
			for(u32 ii=0;ii<this->index_list_size;ii++){
				this->index_list.get()[ii] = Memory::Copy<u8>(a_raw);
			}
		}else if(this->header_ex.vertex_index_size == 2){
			for(u32 ii=0;ii<this->index_list_size;ii++){
				this->index_list.get()[ii] = Memory::Copy<u16>(a_raw);
			}
		}else{
			for(u32 ii=0;ii<this->index_list_size;ii++){
				this->index_list.get()[ii] = Memory::Copy<u32>(a_raw);
			}
		}

		return true;
	}

	/** Load_TextureName
	*/
	bool Mmd_Pmx::Load_TextureName(u8*& a_raw)
	{
		this->texturename_list_size = Memory::Copy<u32>(a_raw);

		for(u32 ii=0;ii<this->texturename_list_size;ii++){

			STLWString t_texturename;
					
			u32 t_length = Memory::Copy<u32>(a_raw);
			if(t_length > 0){
				if(this->header_ex.is_utf8){
					STLString t_buffer(reinterpret_cast<char*>(a_raw),t_length);
					CharToWchar(reinterpret_cast<char*>(a_raw),t_texturename);
				}else{
					t_texturename = STLWString(reinterpret_cast<wchar*>(a_raw),t_length/2);
				}
				a_raw += t_length;
			}

			this->texturename_list.push_back(t_texturename);
		}

		return true;
	}

	/** Load_Parts
	*/
	bool Mmd_Pmx::Load_Parts(u8*& a_raw)
	{
		this->parts_list_size = Memory::Copy<u32>(a_raw);
		this->parts_list.resize(this->parts_list_size);

		s32 t_start_index = 0;

		for(u32 ii=0;ii<this->parts_list_size;ii++){
			Mmd_Pmx_Parts& t_parts = this->parts_list.at(ii);

			//parts_name_jp
			{
				u32 t_length = Memory::Copy<u32>(a_raw);
				if(t_length > 0){
					if(this->header_ex.is_utf8){
						STLString t_buffer(reinterpret_cast<char*>(a_raw),t_length);
						CharToWchar(t_buffer,t_parts.parts_name_jp);
					}else{
						t_parts.parts_name_jp = STLWString(reinterpret_cast<wchar*>(a_raw),t_length/2);
					}
					a_raw += t_length;
				}
			}

			//parts_name_en
			{
				u32 t_length = Memory::Copy<u32>(a_raw);
				if(t_length > 0){
					if(this->header_ex.is_utf8){
						STLString t_buffer(reinterpret_cast<char*>(a_raw),t_length);
						CharToWchar(t_buffer,t_parts.parts_name_en);
					}else{
						t_parts.parts_name_en = STLWString(reinterpret_cast<wchar*>(a_raw),t_length/2);
					}
					a_raw += t_length;
				}
			}

			//diffuse
			{
				t_parts.diffuse = Memory::Copy<NBsys::NColor::Color_F>(a_raw);
			}

			//specular : TODO : COLOR3
			{
				t_parts.specular = Memory::Copy<NBsys::NGeometry::Geometry_Vector3>(a_raw);
			}

			//specular_power
			{
				t_parts.specular_power = Memory::Copy<f32>(a_raw);
			}

			//ambient
			{
				t_parts.ambient = Memory::Copy<NBsys::NGeometry::Geometry_Vector3>(a_raw);
			}

			//mode
			{
				//00000001 : 両面描画。
				//00000010 : 地面影。
				//00000100 : セルフシャドウマップへの描画。
				//00001000 : セルフシャドウの描画。
				//00010000 : エッジ描画。
				//00100000 : 頂点カラー。
				//01000000 : Point描画。
				//10000000 : Line描画。

				u8 t_drawmode = Memory::Copy<u8>(a_raw);

				/** 両面描画。
				*/
				t_parts.drawmode_cullfull = (t_drawmode & (0x01)) > 0;

				/** 影発生。
				*/
				t_parts.drawmode_shadow = (t_drawmode & (0x01<<1)) > 0;

				/** セルフシャドウマップへの描画。
				*/
				t_parts.drawmode_selfshadowmap = (t_drawmode & (0x01<<2)) > 0;

				/** セルフシャドウの描画。
				*/
				t_parts.drawmode_selfshadow = (t_drawmode & (0x01<<3)) > 0;

				/** エッジの描画。
				*/
				t_parts.drawmode_edge = (t_drawmode & (0x01<<4)) > 0;

				/** 頂点カラー。
				*/
				t_parts.drawmode_vertexcolor = (t_drawmode & (0x01<<5)) > 0;

				/** ポイント描画。
				*/
				t_parts.drawmode_point = (t_drawmode & (0x01<<6)) > 0;

				/** ライン描画。
				*/
				t_parts.drawmode_line = (t_drawmode & (0x01<<7)) > 0;
			}

			//edge
			{
				t_parts.edge_color = Memory::Copy<NBsys::NColor::Color_F>(a_raw);
				t_parts.edge_size = Memory::Copy<f32>(a_raw);
			}

			//textureindex
			{
				if(this->header_ex.texture_index_size == 1){
					t_parts.textureindex = Memory::Copy<s8>(a_raw);
				}else if(this->header_ex.texture_index_size == 2){
					t_parts.textureindex = Memory::Copy<s16>(a_raw);
				}else{
					t_parts.textureindex = Memory::Copy<s32>(a_raw);
				}

				if(this->header_ex.texture_index_size == 1){
					t_parts.textureindex_sphere = Memory::Copy<s8>(a_raw);
				}else if(this->header_ex.texture_index_size == 2){
					t_parts.textureindex_sphere = Memory::Copy<s16>(a_raw);
				}else{
					t_parts.textureindex_sphere = Memory::Copy<s32>(a_raw);
				}

				t_parts.textureindex_sphere_mode = Memory::Copy<s8>(a_raw);
			}

			//toon
			{
				t_parts.toon_mode = Memory::Copy<u8>(a_raw);

				if(t_parts.toon_mode == 0){
					//個別。

					if(this->header_ex.texture_index_size == 1){
						t_parts.toon_textureindex = Memory::Copy<s8>(a_raw);
					}else if(this->header_ex.texture_index_size == 2){
						t_parts.toon_textureindex = Memory::Copy<s16>(a_raw);
					}else{
						t_parts.toon_textureindex = Memory::Copy<s32>(a_raw);
					}

				}else if(t_parts.toon_mode == 1){
					//共通。

					t_parts.toon_textureindex = Memory::Copy<s8>(a_raw);
				}else{
					ASSERT(0);
				}
			}

			//comment
			{
				u32 t_length = Memory::Copy<u32>(a_raw);
				if(t_length > 0){
					if(this->header_ex.is_utf8){
						STLString t_buffer(reinterpret_cast<char*>(a_raw),t_length);
						CharToWchar(t_buffer,t_parts.comment);
					}else{
						t_parts.comment = STLWString(reinterpret_cast<wchar*>(a_raw),t_length/2);
					}
					a_raw += t_length;
				}
			}

			//index_size
			{
				t_parts.start_index = t_start_index;
				t_parts.count_of_index = Memory::Copy<u32>(a_raw);
				t_start_index += t_parts.count_of_index;
			}
		}

		return true;
	}

	/** Load_Bone
	*/
	bool Mmd_Pmx::Load_Bone(u8*& a_raw)
	{
		this->bone_list_size = Memory::Copy<u32>(a_raw);
		this->bone_list.resize(this->bone_list_size);

		for(u32 ii=0;ii<this->bone_list_size;ii++){
			Mmd_Pmx_Bone& t_bone = this->bone_list.at(ii);

			//bonename_jp
			{
				u32 t_length = Memory::Copy<u32>(a_raw);
				if(t_length > 0){
					if(this->header_ex.is_utf8){
						STLString t_buffer(reinterpret_cast<char*>(a_raw),t_length);
						CharToWchar(t_buffer,t_bone.bone_name_jp);
					}else{
						t_bone.bone_name_jp = STLWString(reinterpret_cast<wchar*>(a_raw),t_length/2);
					}
					a_raw += t_length;
				}
			}

			//bonename_en
			{
				u32 t_length = Memory::Copy<u32>(a_raw);
				if(t_length > 0){
					if(this->header_ex.is_utf8){
						STLString t_buffer(reinterpret_cast<char*>(a_raw),t_length);
						CharToWchar(t_buffer,t_bone.bone_name_en);
					}else{
						t_bone.bone_name_en = STLWString(reinterpret_cast<wchar*>(a_raw),t_length/2);
					}
					a_raw += t_length;
				}
			}

			t_bone.bone_position = Memory::Copy<NBsys::NGeometry::Geometry_Vector3>(a_raw);

			//boneindex_parent
			{
				if(this->header_ex.bone_index_size == 1){
					t_bone.boneindex_parent = Memory::Copy<s8>(a_raw);
				}else if(this->header_ex.bone_index_size == 2){
					t_bone.boneindex_parent = Memory::Copy<s16>(a_raw);
				}else{
					t_bone.boneindex_parent = Memory::Copy<s32>(a_raw);
				}
			}

			t_bone.deform_depth = Memory::Copy<s32>(a_raw);

			u16 t_boneflag = Memory::Copy<u16>(a_raw);
			t_bone.boneflag_target_showmode			= (0x0001 & t_boneflag) > 0;
			t_bone.boneflag_allow_rotate			= (0x0002 & t_boneflag) > 0;
			t_bone.boneflag_allow_translate			= (0x0004 & t_boneflag) > 0;
			t_bone.boneflag_visible					= (0x0008 & t_boneflag) > 0;
			t_bone.boneflag_allow_control			= (0x0010 & t_boneflag) > 0;
			t_bone.boneflag_ik						= (0x0020 & t_boneflag) > 0;
			t_bone.boneflag_dummy					= (0x0040 & t_boneflag) > 0;
			t_bone.boneflag_append_local			= (0x0080 & t_boneflag) > 0;
			t_bone.boneflag_append_rotate			= (0x0100 & t_boneflag) > 0;
			t_bone.boneflag_append_translate		= (0x0200 & t_boneflag) > 0;
			t_bone.boneflag_fixed_axis				= (0x0400 & t_boneflag) > 0;
			t_bone.boneflag_local_axis				= (0x0800 & t_boneflag) > 0;
			t_bone.boneflag_deform_after_physics	= (0x1000 & t_boneflag) > 0;
			t_bone.boneflag_deform_outer_parent		= (0x2000 & t_boneflag) > 0;



			if (t_bone.boneflag_target_showmode == false){
				t_bone.bone_position_offset = Memory::Copy<NBsys::NGeometry::Geometry_Vector3>(a_raw);
			}else{
				//boneindex_link
				{
					if(this->header_ex.bone_index_size == 1){
						t_bone.boneindex_link = Memory::Copy<s8>(a_raw);
					}else if(this->header_ex.bone_index_size == 2){
						t_bone.boneindex_link = Memory::Copy<s16>(a_raw);
					}else{
						t_bone.boneindex_link = Memory::Copy<s32>(a_raw);
					}
				}
			}

			if(t_bone.boneflag_append_rotate || t_bone.boneflag_append_translate){

				//boneindex_append
				{
					if(this->header_ex.bone_index_size == 1){
						t_bone.boneindex_append = Memory::Copy<s8>(a_raw);
					}else if(this->header_ex.bone_index_size == 2){
						t_bone.boneindex_append = Memory::Copy<s16>(a_raw);
					}else{
						t_bone.boneindex_append = Memory::Copy<s32>(a_raw);
					}
				}

				t_bone.boneindex_append_weight = Memory::Copy<f32>(a_raw);
			}

			if(t_bone.boneflag_fixed_axis){
				t_bone.bone_fixed_axis = Memory::Copy<NBsys::NGeometry::Geometry_Vector3>(a_raw);
			}

			if(t_bone.boneflag_local_axis){
				t_bone.bone_local_axis_x = Memory::Copy<NBsys::NGeometry::Geometry_Vector3>(a_raw);
				t_bone.bone_local_axis_z = Memory::Copy<NBsys::NGeometry::Geometry_Vector3>(a_raw);
			}

			if(t_bone.boneflag_deform_outer_parent){
				t_bone.bone_key_value = Memory::Copy<s32>(a_raw);
			}

			if(t_bone.boneflag_ik){

				//ik_target_boneindex
				{
					if(this->header_ex.bone_index_size == 1){
						t_bone.bone_ik_target_boneindex = Memory::Copy<s8>(a_raw);
					}else if(this->header_ex.bone_index_size == 2){
						t_bone.bone_ik_target_boneindex = Memory::Copy<s16>(a_raw);
					}else{
						t_bone.bone_ik_target_boneindex = Memory::Copy<s32>(a_raw);
					}
				}

				t_bone.bone_ik_iteration_count = Memory::Copy<s32>(a_raw);
				t_bone.bone_ik_limit_rad = Memory::Copy<f32>(a_raw);

				{
					t_bone.bone_ik_list_size = Memory::Copy<s32>(a_raw);
					if(t_bone.bone_ik_list_size > 0){
						t_bone.bone_ik_list.resize(t_bone.bone_ik_list_size);

						for(s32 jj=0;jj<static_cast<s32>(t_bone.bone_ik_list_size);jj++){
							Mmd_Pmx_Bone_Ik& t_bone_ik = t_bone.bone_ik_list[jj];

							//ik_link_boneindex
							{
								if(this->header_ex.bone_index_size == 1){
									t_bone_ik.ik_link_boneindex = Memory::Copy<s8>(a_raw);
								}else if(this->header_ex.bone_index_size == 2){
									t_bone_ik.ik_link_boneindex = Memory::Copy<s16>(a_raw);
								}else{
									t_bone_ik.ik_link_boneindex = Memory::Copy<s32>(a_raw);
								}
							}

							//ik_link_limit
							t_bone_ik.ik_link_limit_enable = Memory::Copy<u8>(a_raw);
							if(t_bone_ik.ik_link_limit_enable > 0){
								t_bone_ik.ik_link_limit_min = Memory::Copy<NBsys::NGeometry::Geometry_Vector3>(a_raw);
								t_bone_ik.ik_link_limit_max = Memory::Copy<NBsys::NGeometry::Geometry_Vector3>(a_raw);
							}else{
								t_bone_ik.ik_link_limit_min = NBsys::NGeometry::Geometry_Identity();
								t_bone_ik.ik_link_limit_max = NBsys::NGeometry::Geometry_Identity();
							}
						}
					}
				}
			}
		}

		return true;
	}

	/** Load
	*/
	bool Mmd_Pmx::Load(sharedptr<NFile::File_Object>& a_file)
	{
		if(a_file->IsBusy() == true){
			return false;
		}

		sharedptr<u8>& t_data = a_file->GetLoadData();
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

}}
#endif

