

/**
* Copyright (c) 2017 blueback
* Released under the MIT License
* https://github.com/bluebackblue/brownie/blob/master/LICENSE
* http://bbbproject.sakura.ne.jp/wordpress/mitlicense
* @brief ＭＭＤ。ＰＭＸ。
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
	/** Load
	*/
	sharedptr< MmdPmx > Load(sharedptr< NFile::File_Object >& a_file)
	{
		if(a_file->IsBusy() == true){
			return nullptr;
		}

		sharedptr< MmdPmx > t_mmdpmx(new MmdPmx());
		sharedptr< u8 >& t_data = a_file->GetLoadData();
		u8* t_raw = t_data.get();

		{
			//MmdPmx_Header
			t_mmdpmx->header = Memory::Copy< MmdPmx_Header >(t_raw);

			//t_header_ex_size
			u8 t_header_ex_size = Memory::Copy< u8 >(t_raw,0);

			//MmdPmx_Header_Ex
			t_mmdpmx->header_ex = Memory::Copy< MmdPmx_Header_Ex >(t_raw,t_header_ex_size + 1);

			//model_name
			STLWString model_name_jp;
			STLWString model_name_en;

			//comment
			STLWString comment_jp;
			STLWString comment_en;

			//model name jp
			{
				u32 t_length = Memory::Copy< u32 >(t_raw);
				if(t_length > 0){
					if(t_mmdpmx->header_ex.is_utf8){
						STLString t_buffer(reinterpret_cast< char* >(t_raw),t_length);
						CharToWchar(t_buffer,t_mmdpmx->model_name_jp);
					}else{
						t_mmdpmx->model_name_jp = STLWString(reinterpret_cast< wchar* >(t_raw),t_length/2);
					}
					t_raw += t_length;
				}
			}

			//model name en
			{
				u32 t_length = Memory::Copy< u32 >(t_raw);
				if(t_length > 0){
					if(t_mmdpmx->header_ex.is_utf8){
						STLString t_buffer(reinterpret_cast< char* >(t_raw),t_length);
						CharToWchar(t_buffer,t_mmdpmx->model_name_en);
					}else{
						t_mmdpmx->model_name_en = STLWString(reinterpret_cast< wchar* >(t_raw),t_length/2);
					}
					t_raw += t_length;
				}
			}

			//comment jp
			{
				u32 t_length = Memory::Copy< u32 >(t_raw);
				if(t_length > 0){
					if(t_mmdpmx->header_ex.is_utf8){
						STLString t_buffer(reinterpret_cast< char* >(t_raw),t_length);
						CharToWchar(t_buffer,t_mmdpmx->comment_jp);
					}else{
						t_mmdpmx->comment_jp = STLWString(reinterpret_cast< wchar* >(t_raw),t_length/2);
					}
					t_raw += t_length;
				}
			}

			//comment en
			{
				u32 t_length = Memory::Copy< u32 >(t_raw);
				if(t_length > 0){
					if(t_mmdpmx->header_ex.is_utf8){
						STLString t_buffer(reinterpret_cast< char* >(t_raw),t_length);
						CharToWchar(t_buffer,t_mmdpmx->comment_en);
					}else{
						t_mmdpmx->comment_en = STLWString(reinterpret_cast< wchar* >(t_raw),t_length/2);
					}
					t_raw += t_length;
				}
			}

			//vertex
			{
				t_mmdpmx->vertex_list_size = Memory::Copy< u32 >(t_raw);
				t_mmdpmx->vertex_list.reset(new MmdPmx_VertexData[t_mmdpmx->vertex_list_size],default_delete< MmdPmx_VertexData[] >());

				for(u32 ii=0;ii<t_mmdpmx->vertex_list_size;ii++){
					MmdPmx_VertexData& t_vertex_data = t_mmdpmx->vertex_list.get()[ii];

					//position
					t_vertex_data.position = Memory::Copy< NBsys::NGeometry::Geometry_Vector3 >(t_raw);

					//normal
					t_vertex_data.normal = Memory::Copy< NBsys::NGeometry::Geometry_Vector3 >(t_raw);

					//uv
					t_vertex_data.uv = Memory::Copy< NBsys::NGeometry::Geometry_Vector2 >(t_raw);

					//uv_ex
					for(s32 jj=0;jj<t_mmdpmx->header_ex.uv_ex_size;jj++){
						t_vertex_data.uv_ex[jj] = Memory::Copy< NBsys::NGeometry::Geometry_Vector4 >(t_raw);
					}

					//weight_type
					t_vertex_data.weight_type = Memory::Copy< u8 >(t_raw);

					//bone
					switch (t_vertex_data.weight_type){
					case 0:
						{
							if(t_mmdpmx->header_ex.bone_index_size == 1){
								t_vertex_data.bone_index[0] = Memory::Copy< s8 >(t_raw);
							}else if(t_mmdpmx->header_ex.bone_index_size == 2){
								t_vertex_data.bone_index[0] = Memory::Copy< s16 >(t_raw);
							}else{
								t_vertex_data.bone_index[0] = Memory::Copy< s32 >(t_raw);
							}
						}break;
					case 1:
						{
							for(s32 jj=0;jj<2;jj++){
								if(t_mmdpmx->header_ex.bone_index_size == 1){
									t_vertex_data.bone_index[jj] = Memory::Copy< s8 >(t_raw);
								}else if(t_mmdpmx->header_ex.bone_index_size == 2){
									t_vertex_data.bone_index[jj] = Memory::Copy< s16 >(t_raw);
								}else{
									t_vertex_data.bone_index[jj] = Memory::Copy< s32 >(t_raw);
								}
							}

							t_vertex_data.bone_weight[0] = Memory::Copy< f32 >(t_raw);
						}break;
					case 2:
						{
							for(s32 jj=0;jj<4;jj++){
								if(t_mmdpmx->header_ex.bone_index_size == 1){
									t_vertex_data.bone_index[jj] = Memory::Copy< s8 >(t_raw);
								}else if(t_mmdpmx->header_ex.bone_index_size == 2){
									t_vertex_data.bone_index[jj] = Memory::Copy< s16 >(t_raw);
								}else{
									t_vertex_data.bone_index[jj] = Memory::Copy< s32 >(t_raw);
								}
							}

							for(s32 jj=0;jj<4;jj++){
								t_vertex_data.bone_weight[jj] = Memory::Copy< f32 >(t_raw);
							}
						}break;
					case 3:
						{
							for(s32 jj=0;jj<2;jj++){
								if(t_mmdpmx->header_ex.bone_index_size == 1){
									t_vertex_data.bone_index[jj] = Memory::Copy< s8 >(t_raw);
								}else if(t_mmdpmx->header_ex.bone_index_size == 2){
									t_vertex_data.bone_index[jj] = Memory::Copy< s16 >(t_raw);
								}else{
									t_vertex_data.bone_index[jj] = Memory::Copy< s32 >(t_raw);
								}
							}

							t_vertex_data.bone_weight[0] = Memory::Copy< f32 >(t_raw);

							t_vertex_data.sdef_c = Memory::Copy< NBsys::NGeometry::Geometry_Vector3 >(t_raw);
							t_vertex_data.sdef_r0 = Memory::Copy< NBsys::NGeometry::Geometry_Vector3 >(t_raw);
							t_vertex_data.sdef_r1 = Memory::Copy< NBsys::NGeometry::Geometry_Vector3 >(t_raw);
						}break;
					case 4:
						{
							for(s32 jj=0;jj<4;jj++){
								if(t_mmdpmx->header_ex.bone_index_size == 1){
									t_vertex_data.bone_index[jj] = Memory::Copy< s8 >(t_raw);
								}else if(t_mmdpmx->header_ex.bone_index_size == 2){
									t_vertex_data.bone_index[jj] = Memory::Copy< s16 >(t_raw);
								}else{
									t_vertex_data.bone_index[jj] = Memory::Copy< s32 >(t_raw);
								}
							}

							for(s32 jj=0;jj<4;jj++){
								t_vertex_data.bone_weight[jj] = Memory::Copy< f32 >(t_raw);
							}
						}break;
					default:
						{
							ASSERT(0);
						}break;
					}

					//edge_mag
					t_vertex_data.edge_mag = Memory::Copy< f32 >(t_raw);
				}
			}

			//index
			{
				t_mmdpmx->index_list_size = Memory::Copy< u32 >(t_raw);
				t_mmdpmx->index_list.reset(new u32[t_mmdpmx->index_list_size],default_delete< u32[] >());

				if(t_mmdpmx->header_ex.vertex_index_size == 1){
					for(u32 ii=0;ii<t_mmdpmx->index_list_size;ii++){
						t_mmdpmx->index_list.get()[ii] = Memory::Copy< u8 >(t_raw);
					}
				}else if(t_mmdpmx->header_ex.vertex_index_size == 2){
					for(u32 ii=0;ii<t_mmdpmx->index_list_size;ii++){
						t_mmdpmx->index_list.get()[ii] = Memory::Copy< u16 >(t_raw);
					}
				}else{
					for(u32 ii=0;ii<t_mmdpmx->index_list_size;ii++){
						t_mmdpmx->index_list.get()[ii] = Memory::Copy< u32 >(t_raw);
					}
				}
			}

			//texturename
			{
				t_mmdpmx->texturename_list_size = Memory::Copy< u32 >(t_raw);

				for(u32 ii=0;ii<t_mmdpmx->texturename_list_size;ii++){

					STLWString t_texturename;
					
					u32 t_length = Memory::Copy< u32 >(t_raw);
					if(t_length > 0){
						if(t_mmdpmx->header_ex.is_utf8){
							STLString t_buffer(reinterpret_cast< char* >(t_raw),t_length);
							CharToWchar(reinterpret_cast< char* >(t_raw),t_texturename);
						}else{
							t_texturename = STLWString(reinterpret_cast< wchar* >(t_raw),t_length/2);
						}
						t_raw += t_length;
					}

					t_mmdpmx->texturename_list.push_back(t_texturename);
				}
			}

			//parts
			{
				t_mmdpmx->parts_list_size = Memory::Copy< u32 >(t_raw);
				t_mmdpmx->parts_list.resize(t_mmdpmx->parts_list_size);

				s32 t_start_index = 0;

				for(u32 ii=0;ii<t_mmdpmx->parts_list_size;ii++){
					MmdPmx_Parts& t_parts = t_mmdpmx->parts_list.at(ii);

					//parts_name_jp
					{
						u32 t_length = Memory::Copy< u32 >(t_raw);
						if(t_length > 0){
							if(t_mmdpmx->header_ex.is_utf8){
								STLString t_buffer(reinterpret_cast< char* >(t_raw),t_length);
								CharToWchar(t_buffer,t_parts.parts_name_jp);
							}else{
								t_parts.parts_name_jp = STLWString(reinterpret_cast< wchar* >(t_raw),t_length/2);
							}
							t_raw += t_length;
						}
					}

					//parts_name_en
					{
						u32 t_length = Memory::Copy< u32 >(t_raw);
						if(t_length > 0){
							if(t_mmdpmx->header_ex.is_utf8){
								STLString t_buffer(reinterpret_cast< char* >(t_raw),t_length);
								CharToWchar(t_buffer,t_parts.parts_name_en);
							}else{
								t_parts.parts_name_en = STLWString(reinterpret_cast< wchar* >(t_raw),t_length/2);
							}
							t_raw += t_length;
						}
					}

					//diffuse
					{
						t_parts.diffuse = Memory::Copy< NBsys::NColor::Color_F >(t_raw);
					}

					//specular : TODO : COLOR3
					{
						t_parts.specular = Memory::Copy< NBsys::NGeometry::Geometry_Vector3 >(t_raw);
					}

					//specular_power
					{
						t_parts.specular_power = Memory::Copy< f32 >(t_raw);
					}

					//ambient
					{
						t_parts.ambient = Memory::Copy< NBsys::NGeometry::Geometry_Vector3 >(t_raw);
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

						u8 t_drawmode = Memory::Copy< u8 >(t_raw);

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
						t_parts.edge_color = Memory::Copy< NBsys::NColor::Color_F >(t_raw);
						t_parts.edge_size = Memory::Copy< f32 >(t_raw);
					}

					//textureindex
					{
						if(t_mmdpmx->header_ex.texture_index_size == 1){
							t_parts.textureindex = Memory::Copy< s8 >(t_raw);
						}else if(t_mmdpmx->header_ex.texture_index_size == 2){
							t_parts.textureindex = Memory::Copy< s16 >(t_raw);
						}else{
							t_parts.textureindex = Memory::Copy< s32 >(t_raw);
						}

						if(t_mmdpmx->header_ex.texture_index_size == 1){
							t_parts.textureindex_sphere = Memory::Copy< s8 >(t_raw);
						}else if(t_mmdpmx->header_ex.texture_index_size == 2){
							t_parts.textureindex_sphere = Memory::Copy< s16 >(t_raw);
						}else{
							t_parts.textureindex_sphere = Memory::Copy< s32 >(t_raw);
						}

						t_parts.textureindex_sphere_mode = Memory::Copy< s8 >(t_raw);
					}

					//toon
					{
						t_parts.toon_mode = Memory::Copy< u8 >(t_raw);

						if(t_parts.toon_mode == 0){
							//個別。

							if(t_mmdpmx->header_ex.texture_index_size == 1){
								t_parts.toon_textureindex = Memory::Copy< s8 >(t_raw);
							}else if(t_mmdpmx->header_ex.texture_index_size == 2){
								t_parts.toon_textureindex = Memory::Copy< s16 >(t_raw);
							}else{
								t_parts.toon_textureindex = Memory::Copy< s32 >(t_raw);
							}

						}else if(t_parts.toon_mode == 1){
							//共通。

							t_parts.toon_textureindex = Memory::Copy< s8 >(t_raw);
						}else{
							ASSERT(0);
						}
					}

					//comment
					{
						u32 t_length = Memory::Copy< u32 >(t_raw);
						if(t_length > 0){
							if(t_mmdpmx->header_ex.is_utf8){
								STLString t_buffer(reinterpret_cast< char* >(t_raw),t_length);
								CharToWchar(t_buffer,t_parts.comment);
							}else{
								t_parts.comment = STLWString(reinterpret_cast< wchar* >(t_raw),t_length/2);
							}
							t_raw += t_length;
						}
					}

					//index_size
					{
						t_parts.start_index = t_start_index;
						t_parts.count_of_index = Memory::Copy< u32 >(t_raw);
						t_start_index += t_parts.count_of_index;
					}
				}
			}

			//bone
			{
				u32 t_bone_count = Memory::Copy< u32 >(t_raw);

				for(u32 ii=0;ii<t_bone_count;ii++){

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




					//bonename_jp
					{
						u32 t_length = Memory::Copy< u32 >(t_raw);
						if(t_length > 0){
							if(t_mmdpmx->header_ex.is_utf8){
								STLString t_buffer(reinterpret_cast< char* >(t_raw),t_length);
								CharToWchar(t_buffer,t_bone_name_jp);
							}else{
								t_bone_name_jp = STLWString(reinterpret_cast< wchar* >(t_raw),t_length/2);
							}
							t_raw += t_length;
						}
					}

					//bonename_en
					{
						u32 t_length = Memory::Copy< u32 >(t_raw);
						if(t_length > 0){
							if(t_mmdpmx->header_ex.is_utf8){
								STLString t_buffer(reinterpret_cast< char* >(t_raw),t_length);
								CharToWchar(t_buffer,t_bone_name_en);
							}else{
								t_bone_name_en = STLWString(reinterpret_cast< wchar* >(t_raw),t_length/2);
							}
							t_raw += t_length;
						}
					}

					t_bone_position = Memory::Copy< NBsys::NGeometry::Geometry_Vector3 >(t_raw);

					//boneindex_parent
					{
						if(t_mmdpmx->header_ex.bone_index_size == 1){
							t_boneindex_parent = Memory::Copy< s8 >(t_raw);
						}else if(t_mmdpmx->header_ex.bone_index_size == 2){
							t_boneindex_parent = Memory::Copy< s16 >(t_raw);
						}else{
							t_boneindex_parent = Memory::Copy< s32 >(t_raw);
						}
					}

					t_deform_depth = Memory::Copy< s32 >(t_raw);

					t_boneflag = Memory::Copy< u16 >(t_raw);

					/*
					0x0001  : 接続先(PMD子ボーン指定)表示方法 -> 0:座標オフセットで指定 1:ボーンで指定。
					0x0002  : 回転可能
					0x0004  : 移動可能
					0x0008  : 表示
					0x0010  : 操作可
					0x0020  : IK
					0x0040	: dummy
					0x0080  : ローカル付与 | 付与対象 0:ユーザー変形値／IKリンク／多重付与 1:親のローカル変形量。
					0x0100  : 回転付与
					0x0200  : 移動付与
					0x0400  : 軸固定
					0x0800  : ローカル軸
					0x1000  : 物理後変形
					0x2000  : 外部親変形
					*/
					bool t_boneflag_target_showmode			= (t_boneflag & (0x01    )) > 0;
					bool t_boneflag_allow_rotate			= (t_boneflag & (0x01<<2 )) > 0;
					bool t_boneflag_allow_translate			= (t_boneflag & (0x01<<3 )) > 0;
					bool t_boneflag_visible					= (t_boneflag & (0x01<<4 )) > 0;
					bool t_boneflag_allow_control			= (t_boneflag & (0x01<<5 )) > 0;
					bool t_boneflag_ik						= (t_boneflag & (0x01<<6 )) > 0;
					bool t_boneflag_dummy					= (t_boneflag & (0x01<<7 )) > 0;
					bool t_boneflag_append_local			= (t_boneflag & (0x01<<8 )) > 0;
					bool t_boneflag_append_rotate			= (t_boneflag & (0x01<<9 )) > 0;
					bool t_boneflag_append_translate		= (t_boneflag & (0x01<<10)) > 0;
					bool t_boneflag_fixed_axis				= (t_boneflag & (0x01<<11)) > 0;
					bool t_boneflag_local_axis				= (t_boneflag & (0x01<<12)) > 0;
					bool t_boneflag_deform_after_physics	= (t_boneflag & (0x01<<13)) > 0;
					bool t_boneflag_deform_outer_parent		= (t_boneflag & (0x01<<14)) > 0;

					if (t_boneflag_target_showmode == false){
						t_bone_position_offset = Memory::Copy< NBsys::NGeometry::Geometry_Vector3 >(t_raw);
					}else{
						//boneindex_link
						{
							if(t_mmdpmx->header_ex.bone_index_size == 1){
								t_boneindex_link = Memory::Copy< s8 >(t_raw);
							}else if(t_mmdpmx->header_ex.bone_index_size == 2){
								t_boneindex_link = Memory::Copy< s16 >(t_raw);
							}else{
								t_boneindex_link = Memory::Copy< s32 >(t_raw);
							}
						}
					}

					if(t_boneflag_append_rotate || t_boneflag_append_translate){

						//boneindex_append
						{
							if(t_mmdpmx->header_ex.bone_index_size == 1){
								t_boneindex_append = Memory::Copy< s8 >(t_raw);
							}else if(t_mmdpmx->header_ex.bone_index_size == 2){
								t_boneindex_append = Memory::Copy< s16 >(t_raw);
							}else{
								t_boneindex_append = Memory::Copy< s32 >(t_raw);
							}
						}

						t_boneindex_append_weight = Memory::Copy< f32 >(t_raw);
					}

					if(t_boneflag_fixed_axis){
						t_bone_fixed_axis = Memory::Copy< NBsys::NGeometry::Geometry_Vector3 >(t_raw);
					}

					if(t_boneflag_local_axis){
						t_bone_local_axix_x = Memory::Copy< NBsys::NGeometry::Geometry_Vector3 >(t_raw);
						t_bone_local_axix_z = Memory::Copy< NBsys::NGeometry::Geometry_Vector3 >(t_raw);
					}

					if(t_boneflag_deform_outer_parent){
						t_bone_key_value = Memory::Copy< s32 >(t_raw);
					}

					if(t_boneflag_ik){

						//ik_target_boneindex
						{
							if(t_mmdpmx->header_ex.bone_index_size == 1){
								t_bone_ik_target_boneindex = Memory::Copy< s8 >(t_raw);
							}else if(t_mmdpmx->header_ex.bone_index_size == 2){
								t_bone_ik_target_boneindex = Memory::Copy< s16 >(t_raw);
							}else{
								t_bone_ik_target_boneindex = Memory::Copy< s32 >(t_raw);
							}
						}

						t_bone_ik_iteration_count = Memory::Copy< s32 >(t_raw);
						t_bone_ik_limit_rad = Memory::Copy< f32 >(t_raw);


						{
							s32 t_ik_link_count = 0;


							t_ik_link_count = Memory::Copy< s32 >(t_raw);

							for(int jj=0;jj<t_ik_link_count;jj++){

								s32 t_ik_link_boneindex = -1;
								u8 t_ik_link_enable_limit = 0x00;

								NBsys::NGeometry::Geometry_Vector3 t_ik_link_limit_min = NBsys::NGeometry::Geometry_Identity();
								NBsys::NGeometry::Geometry_Vector3 t_ik_link_limit_max = NBsys::NGeometry::Geometry_Identity();

								//t_ik_link_boneindex
								{
									if(t_mmdpmx->header_ex.bone_index_size == 1){
										t_ik_link_boneindex = Memory::Copy< s8 >(t_raw);
									}else if(t_mmdpmx->header_ex.bone_index_size == 2){
										t_ik_link_boneindex = Memory::Copy< s16 >(t_raw);
									}else{
										t_ik_link_boneindex = Memory::Copy< s32 >(t_raw);
									}
								}

								t_ik_link_enable_limit = Memory::Copy< u8 >(t_raw);

								if(t_ik_link_enable_limit > 0){
									t_ik_link_limit_min = Memory::Copy< NBsys::NGeometry::Geometry_Vector3 >(t_raw);
									t_ik_link_limit_max = Memory::Copy< NBsys::NGeometry::Geometry_Vector3 >(t_raw);
								}
							}
						}
					}
				}
			}



		}

		return t_mmdpmx;
	}

}}
#endif

