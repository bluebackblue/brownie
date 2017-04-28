#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ファイル。
*/


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./file_workitem.h"


/** NBsys::NFile
*/
#if(BSYS_FILE_ENABLE)
namespace NBsys{namespace NFile
{

	/** File_Cache_Item
	*/
	struct File_Cache_Item
	{
		/** キャッシュしているワークアイテム。
		*/
		sharedptr< File_WorkItem > workitem;

		/** 参照ＩＤを列挙。
		*/
		typedef STLMap< s32 , bool >::Type IDListType;
		IDListType cachegroup_id_list;

		/** constructor
		*/
		explicit File_Cache_Item(const sharedptr< File_WorkItem >& a_workitem);

		/** destructor
		*/
		nonvirtual ~File_Cache_Item();

		/** ＩＤ追加。
		*/
		void AddID(s32 a_id);

		/** ＩＤ削除。
		*/
		void KillID(s32 a_id);

		/** 検索。
		*/
		bool Find(s32 a_id);

		/** 空かどうか。
		*/
		bool IsEmpty();

	};

}}
#endif

