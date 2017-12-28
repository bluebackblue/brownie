

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
#include "./file_cache_item.h"


/** NBsys::NFile
*/
#if(BSYS_FILE_ENABLE)
namespace NBsys{namespace NFile
{
	/** constructor
	*/
	File_Cache_Item::File_Cache_Item(const sharedptr<File_WorkItem>& a_workitem)
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
		auto t_it = this->cachegroup_id_list.find(a_cachegroup_id);
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
		auto t_it = this->cachegroup_id_list.find(a_cachegroup_id);
		if(t_it == this->cachegroup_id_list.end()){
		}else{
			t_it->second = false;
		}
	}


	/** 検索。
	*/
	bool File_Cache_Item::Find(s32 a_cachegroup_id)
	{
		auto t_it = this->cachegroup_id_list.find(a_cachegroup_id);
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
		for(auto t_it = this->cachegroup_id_list.cbegin();t_it != this->cachegroup_id_list.cend();t_it++){
			if(t_it->second == true){
				return false;
			}
		}
		return true;
	}


}}
#endif

