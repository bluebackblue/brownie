#pragma once

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ＭＭＤ。ＰＭＸ。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../file/file.h"
#include "../geometry/geometry.h"
#include "../color/color.h"
#pragma warning(pop)


/** include
*/
#include "./mmd_pmx_type.h"


/** NBsys::NMmd
*/
#if(BSYS_MMD_ENABLE)
#pragma warning(push)
#pragma warning(disable:4514)
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

		/** padding
		*/
		padding64(0,7);
		padding32(0,3);

		/** model_name
		*/
		STLWString model_name_jp;
		STLWString model_name_en;

		/** comment
		*/
		STLWString comment_jp;
		STLWString comment_en;

		/** padding
		*/
		padding64(1,4);

		/** vertex_list
		*/
		u32 vertex_list_size;
		sharedptr<Mmd_Pmx_VertexData> vertex_list;

		/** padding
		*/
		padding64(2,4);

		/** index_list
		*/
		u32 index_list_size;
		sharedptr<u32> index_list;

		/** padding
		*/
		padding64(3,4);

		/** texturename_list
		*/
		u32 texturename_list_size;
		STLVector<STLWString>::Type texturename_list;

		/** padding
		*/
		padding64(4,4);

		/** parts_list
		*/
		u32 parts_list_size;
		STLVector<Mmd_Pmx_Parts>::Type parts_list;

		/** padding
		*/
		padding64(5,4);

		/** bone_list
		*/
		u32 bone_list_size;
		STLVector<Mmd_Pmx_Bone>::Type bone_list;

	public:

		/** constructor
		*/
		Mmd_Pmx()
			:
			vertex_list_size(0),
			index_list_size(0),
			texturename_list_size(0),
			parts_list_size(0),
			bone_list_size(0)
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
		bool Load(sharedptr<NFile::File_Object>& a_file);

	};


}}
#pragma warning(pop)
#endif

