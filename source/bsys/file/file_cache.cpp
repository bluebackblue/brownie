

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ファイル。
*/


/** include
*/
#include <bsys_pch.h>


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** include
*/
#include "./file_cache.h"
#include "./file_cachegroupid.h"


/** NBsys::NFile
*/
#if(BSYS_FILE_ENABLE)
namespace NBsys{namespace NFile
{
	/** constructor
	*/
	File_Cache::File_Cache()
	{
	}


	/** destructor
	*/
	File_Cache::~File_Cache()
	{
	}


	/** キャッシュへ登録。
	*/
	void File_Cache::SetCache(const sharedptr<File_WorkItem>& a_workitem,s32 a_cachegroup_id)
	{
		MemoryContainer t_memorycontainer(BSYS_FILE_MEMORYCONTAINER);

		auto t_it_item = this->map.find(a_workitem->GetFileNameShort());
		if(t_it_item == this->map.cend()){
			//新規。
			sharedptr<File_Cache_Item> t_newitem(new File_Cache_Item(a_workitem));

			//ＩＤ追加。
			t_newitem->AddID(a_cachegroup_id);

			//ワークアイテムをキャッシュに追加。
			this->map.insert(STLMap<STLWString,sharedptr<File_Cache_Item>>::value_type(a_workitem->GetFileNameShort(),t_newitem));
		}else{
			//既存。ＩＤのみ追加。
			t_it_item->second->AddID(a_cachegroup_id);
		}
	}


	/** 名前からキャッシュを検索。
	*/
	const sharedptr<File_WorkItem>& File_Cache::GetCacheFromFileNameShort(const STLWString& a_filename_short) const
	{
		auto t_it_item = this->map.find(a_filename_short);
		if(t_it_item != this->map.cend()){
			return t_it_item->second->workitem;
		}

		return sharedptr<File_WorkItem>::null();
	}


	/** キャッシュクリア。
	*/
	void File_Cache::CacheClear(s32 a_cachegroup_id)
	{
		if(a_cachegroup_id <= File_CacheGroupID::NoCache){
			//全部。削除。
			STLMap<STLWString,sharedptr<File_Cache_Item>>::Type().swap(this->map);
		}else{
			auto t_it = this->map.begin();
			while(t_it != this->map.end()){
				t_it->second->KillID(a_cachegroup_id);

				if(t_it->second->IsEmpty()){
					//中身が空のものはキャッシュマップから削除。
					auto t_it_erase = t_it;
					t_it++;
					this->map.erase(t_it_erase);
					continue;
				}else{
					t_it++;
				}
			}
		}
	}


	/** リークチェック。
	*/
	void File_Cache::LeakCheck() const
	{
		auto t_it = this->map.cbegin();
		while(t_it != this->map.cend()){
			if(t_it->second.use_count() > 1){
				//誰かから参照されている。
				ASSERT(0);
			}
			t_it++;
		}
	}


}}
#endif

