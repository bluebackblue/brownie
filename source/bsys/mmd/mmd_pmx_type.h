#pragma once

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

		/** ���ʕ`��B
		*/
		bool drawmode_cullfull;

		/** �e�����B
		*/
		bool drawmode_shadow;

		/** �Z���t�V���h�E�}�b�v�ւ̕`��B
		*/
		bool drawmode_selfshadowmap;

		/** �Z���t�V���h�E�̕`��B
		*/
		bool drawmode_selfshadow;

		/** �G�b�W�̕`��B
		*/
		bool drawmode_edge;

		/** ���_�J���[�B
		*/
		bool drawmode_vertexcolor;

		/** �|�C���g�`��B
		*/
		bool drawmode_point;

		/** ���C���`��B
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
		bool boneflag_target_showmode;		//�ڑ���(PMD�q�{�[���w��)�\�����@ -> 0:���W�I�t�Z�b�g�Ŏw�� 1:�{�[���Ŏw��B
		bool boneflag_allow_rotate;			//��]�\
		bool boneflag_allow_translate;		//�ړ��\
		bool boneflag_visible;				//�\��
		bool boneflag_allow_control;		//�����
		bool boneflag_ik;					//IK
		bool boneflag_dummy;				//dummy
		bool boneflag_append_local;			//���[�J���t�^ | �t�^�Ώ� 0:���[�U�[�ό`�l�^IK�����N�^���d�t�^ 1:�e�̃��[�J���ό`�ʁB
		bool boneflag_append_rotate;		//��]�t�^
		bool boneflag_append_translate;		//�ړ��t�^
		bool boneflag_fixed_axis;			//���Œ�
		bool boneflag_local_axis;			//���[�J����
		bool boneflag_deform_after_physics;	//������ό`
		bool boneflag_deform_outer_parent;	//�O���e�ό`

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

