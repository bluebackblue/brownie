

/**
* Copyright (c) 2017 blueback
* Released under the MIT License
* https://github.com/bluebackblue/brownie/blob/master/LICENSE
* http://bbbproject.sakura.ne.jp/wordpress/mitlicense
* @brief ÇlÇlÇcÅBÇoÇlÇwÅB
*/


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./mmdpmx.h"


/** NBsys::NMmdPmx
*/
#if(BSYS_MODEL_ENABLE)
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
						CharToWchar(reinterpret_cast< char* >(t_raw),t_mmdpmx->model_name_jp);
					}else{
						t_mmdpmx->model_name_jp = reinterpret_cast< wchar* >(t_raw);
					}
					t_raw += t_length;
				}
			}

			//model name en
			{
				u32 t_length = Memory::Copy< u32 >(t_raw);
				if(t_length > 0){
					if(t_mmdpmx->header_ex.is_utf8){
						CharToWchar(reinterpret_cast< char* >(t_raw),t_mmdpmx->model_name_en);
					}else{
						t_mmdpmx->model_name_en = reinterpret_cast< wchar* >(t_raw);
					}
					t_raw += t_length;
				}
			}

			//comment jp
			{
				u32 t_length = Memory::Copy< u32 >(t_raw);
				if(t_length > 0){
					if(t_mmdpmx->header_ex.is_utf8){
						CharToWchar(reinterpret_cast< char* >(t_raw),t_mmdpmx->comment_jp);
					}else{
						t_mmdpmx->comment_jp = reinterpret_cast< wchar* >(t_raw);
					}
					t_raw += t_length;
				}
			}

			//comment en
			{
				u32 t_length = Memory::Copy< u32 >(t_raw);
				if(t_length > 0){
					if(t_mmdpmx->header_ex.is_utf8){
						CharToWchar(reinterpret_cast< char* >(t_raw),t_mmdpmx->comment_en);
					}else{
						t_mmdpmx->comment_en = reinterpret_cast< wchar* >(t_raw);
					}
					t_raw += t_length;
				}
			}

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
		}

		return t_mmdpmx;
	}

}}
#endif

