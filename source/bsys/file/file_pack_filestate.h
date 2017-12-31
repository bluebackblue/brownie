#pragma once

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ファイル。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** include
*/
#include "./file_pack_workitem_decl.h"


/** NBsys::NFile
*/
#if((BSYS_FILE_ENABLE)&&(BSYS_FILE_PACK_ENABLE))
#pragma warning(push)
#pragma warning(disable:4710)
namespace NBsys{namespace NFile
{
	/** File_Pack_FileState
	*/
	struct File_Pack_FileState
	{
		/** parent
		*/
		File_Pack_WorkItem* parent;

		/** データサイズ。
		*/
		s64 data_size;

		/** データオフセット。
		*/
		s64 data_offset;

		/** constructor
		*/
		File_Pack_FileState(File_Pack_WorkItem* a_parent,s64 a_data_size,s64 a_data_offset)
			:
			parent(a_parent),
			data_size(a_data_size),
			data_offset(a_data_offset)
		{
		}

		/** destructor
		*/
		nonvirtual ~File_Pack_FileState()
		{
		}

	};


}}
#pragma warning(pop)
#endif

