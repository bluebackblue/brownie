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
#include "../file/file.h"
#include "../geometry/geometry.h"
#include "../color/color.h"


/** NBsys::NMmdPmx
*/
#if(BSYS_MMDPMX_ENABLE)
namespace NBsys{namespace NMmdPmx
{
	/** MmdPmx_Header
	*/
	struct MmdPmx_Header
	{
		/** PMX
		*/
		char tag[4];

		/** version
		*/
		f32 version;
	};

	/** MmdPmx_Header_Ex
	*/
	struct MmdPmx_Header_Ex
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

	/** MmdPmx_VertexData
	*/
	struct MmdPmx_VertexData
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

	/** MmdPmx_Parts
	*/
	struct MmdPmx_Parts
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

	/** MmdPmx
	*/
	class MmdPmx
	{
	public:
		/** header
		*/
		MmdPmx_Header header;

		/** header_ex
		*/
		MmdPmx_Header_Ex header_ex;

		/** model_name
		*/
		STLWString model_name_jp;
		STLWString model_name_en;

		/** comment
		*/
		STLWString comment_jp;
		STLWString comment_en;

		/** vertex_list
		*/
		u32 vertex_list_size;
		sharedptr< MmdPmx_VertexData > vertex_list;

		/** index_list
		*/
		u32 index_list_size;
		sharedptr< u32 > index_list;

		/** texturename_list
		*/
		u32 texturename_list_size;
		STLVector< STLWString >::Type texturename_list;

		/** parts_list
		*/
		u32 parts_list_size;
		STLVector< MmdPmx_Parts >::Type parts_list;

	public:
		/** constructor
		*/
		MmdPmx()
		{
		}

		/** destructor
		*/
		~MmdPmx()
		{
		}

	};

	/** ロード。
	*/
	sharedptr< MmdPmx > Load(sharedptr< NFile::File_Object >& a_file);

}}
#endif

