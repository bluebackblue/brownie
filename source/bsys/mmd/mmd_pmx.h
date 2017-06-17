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
#include "../color/color.h"


/** include
*/
#include "./mmd_pmx_type.h"


/** NBsys::NMmd
*/
#if(BSYS_MMD_PMX_ENABLE)
namespace NBsys{namespace NMmd
{
	/** Mmd_Pmx
	*/
	class Mmd_Pmx
	{
	public:
		/** header
		*/
		Mmd_Pmx_Header header;

		/** header_ex
		*/
		Mmd_Pmx_Header_Ex header_ex;

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
		sharedptr< Mmd_Pmx_VertexData > vertex_list;

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
		STLVector< Mmd_Pmx_Parts >::Type parts_list;

		/** bone_list
		*/
		u32 bone_list_size;
		STLVector< Mmd_Pmx_Bone >::Type bone_list;

	public:
		/** constructor
		*/
		Mmd_Pmx()
		{
		}

		/** destructor
		*/
		~Mmd_Pmx()
		{
		}

	private:

		/** Load_Header
		*/
		bool Load_Header(u8*& a_raw);

		/** Load_Vertex
		*/
		bool Load_Vertex(u8*& a_raw);

		/** Load_Index
		*/
		bool Load_Index(u8*& a_raw);

		/** Load_TextureName
		*/
		bool Load_TextureName(u8*& a_raw);

		/** Load_Parts
		*/
		bool Load_Parts(u8*& a_raw);

		/** Load_Bone
		*/
		bool Load_Bone(u8*& a_raw);

	public:

		/** Load
		*/
		bool Load(sharedptr< NFile::File_Object >& a_file);

	};

}}
#endif

