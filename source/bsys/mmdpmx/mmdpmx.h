#pragma once

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
#include "../file/file.h"
#include "../geometry/geometry.h"


/** NBsys::NMmdPmx
*/
#if(BSYS_MODEL_ENABLE)
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
		u8 material_index_size;
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

	/** ÉçÅ[ÉhÅB
	*/
	sharedptr< MmdPmx > Load(sharedptr< NFile::File_Object >& a_file);

}}
#endif

