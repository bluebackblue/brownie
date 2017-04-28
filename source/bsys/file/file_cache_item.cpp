

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ファイル。
*/


/** include
*/
#include <bsys_pch.h>


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./file_cache_item.h"


/** NBsys::NFile
*/
#if(BSYS_FILE_ENABLE)
namespace NBsys{namespace NFile
{
	/** constructor
	*/
	File_Cache_Item::File_Cache_Item(const sharedptr< File_WorkItem >& a_workitem)
		:
		workitem(a_workitem)
	{
	}

	/** destructor
	*/
	File_Cache_Item::~File_Cache_Item()
	{
	}

	/** ＩＤ追加。
	*/
	void File_Cache_Item::AddID(s32 a_cachegroup_id)
	{
		IDListType::iterator t_it = this->cachegroup_id_list.find(a_cachegroup_id);
		if(t_it == this->cachegroup_id_list.end()){
			this->cachegroup_id_list.insert(IDListType::value_type(a_cachegroup_id,true));
		}else{
			t_it->second = true;
		}
	}

	/** ＩＤ削除。
	*/
	void File_Cache_Item::KillID(s32 a_cachegroup_id)
	{
		IDListType::iterator t_it = this->cachegroup_id_list.find(a_cachegroup_id);
		if(t_it == this->cachegroup_id_list.end()){
		}else{
			t_it->second = false;
		}
	}

	/** 検索。
	*/
	bool File_Cache_Item::Find(s32 a_cachegroup_id)
	{
		IDListType::iterator t_it = this->cachegroup_id_list.find(a_cachegroup_id);
		if(t_it != this->cachegroup_id_list.end()){
			if(t_it->second == true){
				return true;
			}
		}
		return false;
	}

	/** 空かどうか。
	*/
	bool File_Cache_Item::IsEmpty()
	{
		for(IDListType::iterator t_it = this->cachegroup_id_list.begin();t_it != this->cachegroup_id_list.end();t_it++){
			if(t_it->second == true){
				return false;
			}
		}
		return true;
	}

}}
#endif

