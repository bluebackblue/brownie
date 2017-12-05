#pragma once

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
#include "../geometry/geometry.h"
#include "../color/color.h"


/** NBsys::NMmd
*/
#if(BSYS_MMD_PMX_ENABLE)
namespace NBsys{namespace NMmd
{
	/** Mmd_Pmx_Header
	*/
	struct Mmd_Pmx_Header
	{
		/** PMX
		*/
		char tag[4];

		/** version
		*/
		f32 version;
	};

	/** Mmd_Pmx_Header_Ex
	*/
	struct Mmd_Pmx_Header_Ex
	{
		u8 size;

		u8 is_utf8;
		u8 uv_ex_size;
		u8 vertex_index_size;
		u8 texture_index_size;
		u8 parts_index_size;
		u8 bone_index_size;
		u8 morph_index_size;
		u8 rigid_body_index_size;
	};

	/** Mmd_Pmx_VertexData
	*/
	struct Mmd_Pmx_VertexData
	{
		NBsys::NGeometry::Geometry_Vector3	position;
		NBsys::NGeometry::Geometry_Vector3	normal;
		NBsys::NGeometry::Geometry_Vector2	uv;

		NBsys::NGeometry::Geometry_Vector4	uv_ex[4];

		u8									weight_type;

		s32									bone_index[4];
		f32									bone_weight[4];

		NBsys::NGeometry::Geometry_Vector3	sdef_c;
		NBsys::NGeometry::Geometry_Vector3	sdef_r0;
		NBsys::NGeometry::Geometry_Vector3	sdef_r1;

		f32									edge_mag;
	};

	/** Mmd_Pmx_Parts
	*/
	struct Mmd_Pmx_Parts
	{
		/** parts_name
		*/
		STLWString parts_name_jp;

		/** parts_name_en
		*/
		STLWString parts_name_en;

		/** diffuse
		*/
		NBsys::NColor::Color_F diffuse;

		/** specular
		*/
		NBsys::NGeometry::Geometry_Vector3 specular;

		/** specular_power
		*/
		f32 specular_power;

		/** ambient
		*/
		NBsys::NGeometry::Geometry_Vector3 ambient;

		/** 両面描画。
		*/
		bool drawmode_cullfull;

		/** 影発生。
		*/
		bool drawmode_shadow;

		/** セルフシャドウマップへの描画。
		*/
		bool drawmode_selfshadowmap;

		/** セルフシャドウの描画。
		*/
		bool drawmode_selfshadow;

		/** エッジの描画。
		*/
		bool drawmode_edge;

		/** 頂点カラー。
		*/
		bool drawmode_vertexcolor;

		/** ポイント描画。
		*/
		bool drawmode_point;

		/** ライン描画。
		*/
		bool drawmode_line;

		/** edge
		*/
		NBsys::NColor::Color_F edge_color;
		f32 edge_size;

		/** textureindex
		*/
		s32 textureindex;
		s32 textureindex_sphere;
		u8 textureindex_sphere_mode;

		/** toon
		*/
		u8 toon_mode;
		s32 toon_textureindex;

		/** comment
		*/
		STLWString comment;
		
		/** count_of_index
		*/
		u32 start_index;
		u32 count_of_index;
	};

	/** Mmd_Pmx_Bone_Ik
	*/
	struct Mmd_Pmx_Bone_Ik
	{
		/** ik_link_boneindex
		*/
		s32 ik_link_boneindex;

		/** ik_link_limit_enable
		*/
		u8 ik_link_limit_enable;
		NBsys::NGeometry::Geometry_Vector3 ik_link_limit_min;
		NBsys::NGeometry::Geometry_Vector3 ik_link_limit_max;
	};

	/** Mmd_Pmx_Bone
	*/
	struct Mmd_Pmx_Bone
	{
		/** bone_name
		*/
		STLWString bone_name_jp;
		STLWString bone_name_en;

		/** bone_position
		*/
		NBsys::NGeometry::Geometry_Vector3 bone_position;

		/** boneindex_parent
		*/
		s32 boneindex_parent;

		/** deform_depth
		*/
		s32 deform_depth;

		/** boneflag
		*/
		bool boneflag_target_showmode;		//接続先(PMD子ボーン指定)表示方法 -> 0:座標オフセットで指定 1:ボーンで指定。
		bool boneflag_allow_rotate;			//回転可能
		bool boneflag_allow_translate;		//移動可能
		bool boneflag_visible;				//表示
		bool boneflag_allow_control;		//操作可
		bool boneflag_ik;					//IK
		bool boneflag_dummy;				//dummy
		bool boneflag_append_local;			//ローカル付与 | 付与対象 0:ユーザー変形値／IKリンク／多重付与 1:親のローカル変形量。
		bool boneflag_append_rotate;		//回転付与
		bool boneflag_append_translate;		//移動付与
		bool boneflag_fixed_axis;			//軸固定
		bool boneflag_local_axis;			//ローカル軸
		bool boneflag_deform_after_physics;	//物理後変形
		bool boneflag_deform_outer_parent;	//外部親変形

		/** bone_position_offset
		*/
		NBsys::NGeometry::Geometry_Vector3 bone_position_offset;

		/** boneindex_link
		*/
		s32 boneindex_link;

		/** boneindex
		*/
		s32 boneindex_append;
		f32 boneindex_append_weight;

		/** bone_fixed_axis
		*/
		NBsys::NGeometry::Geometry_Vector3 bone_fixed_axis;

		/** bone_local_axis
		*/
		NBsys::NGeometry::Geometry_Vector3 bone_local_axis_x;
		NBsys::NGeometry::Geometry_Vector3 bone_local_axis_z;

		/** bone_key_value
		*/
		s32 bone_key_value;

		/** bone_ik
		*/
		s32 bone_ik_target_boneindex;
		s32 bone_ik_iteration_count;
		f32	bone_ik_limit_rad;

		/** bone_ik_list
		*/
		u32 bone_ik_list_size;
		STLVector<Mmd_Pmx_Bone_Ik>::Type bone_ik_list;
	};

}}
#endif

