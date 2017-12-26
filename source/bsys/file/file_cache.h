#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ファイル。
*/


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./file_workitem.h"
#include "./file_cache_item.h"


/** NBsys::NFile
*/
#if(BSYS_FILE_ENABLE)
namespace NBsys{namespace NFile
{
	/** File_Cache
	*/
	class File_Cache
	{
	private:

		/** キャッシュマップ。
		*/
		STLMap<STLWString,sharedptr<File_Cache_Item>>::Type map;
	
	public:

		/** constructor
		*/
		File_Cache();

		/** destructor
		*/
		nonvirtual ~File_Cache();

		/** キャッシュへ登録。
		*/
		void SetCache(const sharedptr<File_WorkItem>& a_workitem,s32 a_cachegroup_id);

		/** 名前からキャッシュを検索。
		*/
		const sharedptr<File_WorkItem>& GetCacheFromFileNameShort(const STLWString& a_filename_short) const;

		/** キャッシュクリア。
		*/
		void CacheClear(s32 a_cachegroup_id);

		/** リークチェック。
		*/
		void LeakCheck() const;

	};


}}
#endif

