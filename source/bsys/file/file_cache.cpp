

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �t�@�C���B
*/


/** include
*/
#include <bsys_pch.h>


/** include
*/
#include "../types/types.h"


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

	/** �L���b�V���֓o�^�B
	*/
	void File_Cache::SetCache(const sharedptr<File_WorkItem>& a_workitem,s32 a_cachegroup_id)
	{
		MemoryContainer t_memorycontainer(BSYS_FILE_MEMORYCONTAINER);

		STLMap<STLWString,sharedptr<File_Cache_Item>>::iterator t_it_item = this->map.find(a_workitem->GetFileNameShort());
		if(t_it_item == this->map.end()){
			//�V�K�B
			sharedptr<File_Cache_Item> t_newitem(new File_Cache_Item(a_workitem));

			//�h�c�ǉ��B
			t_newitem->AddID(a_cachegroup_id);

			//���[�N�A�C�e�����L���b�V���ɒǉ��B
			this->map.insert(STLMap<STLWString,sharedptr<File_Cache_Item>>::value_type(a_workitem->GetFileNameShort(),t_newitem));
		}else{
			//�����B�h�c�̂ݒǉ��B
			t_it_item->second->AddID(a_cachegroup_id);
		}
	}

	/** ���O����L���b�V���������B
	*/
	const sharedptr<File_WorkItem>& File_Cache::GetCacheFromFileNameShort(const STLWString& a_filename_short) const
	{
		STLMap<STLWString,sharedptr<File_Cache_Item>>::const_iterator t_it_item = this->map.find(a_filename_short);
		if(t_it_item != this->map.end()){
			return t_it_item->second->workitem;
		}

		return sharedptr<File_WorkItem>::null();
	}

	/** �L���b�V���N���A�B
	*/
	void File_Cache::CacheClear(s32 a_cachegroup_id)
	{
		if(a_cachegroup_id <= File_CacheGroupID::NoCache){
			//�S���B�폜�B
			STLMap<STLWString,sharedptr<File_Cache_Item>>::Type().swap(this->map);
		}else{
			STLMap<STLWString,sharedptr<File_Cache_Item>>::iterator t_it = this->map.begin();
			while(t_it != this->map.end()){
				t_it->second->KillID(a_cachegroup_id);

				if(t_it->second->IsEmpty()){
					//���g����̂��̂̓L���b�V���}�b�v����폜�B
					STLMap<STLWString,sharedptr<File_Cache_Item>>::iterator t_it_erase = t_it;
					t_it++;
					this->map.erase(t_it_erase);
					continue;
				}else{
					t_it++;
				}
			}
		}
	}

	/** ���[�N�`�F�b�N�B
	*/
	void File_Cache::LeakCheck() const
	{
		STLMap<STLWString,sharedptr<File_Cache_Item>>::const_iterator t_it = this->map.begin();
		while(t_it != this->map.end()){
			if(t_it->second.use_count() > 1){
				//�N������Q�Ƃ���Ă���B
				ASSERT(0);
			}
			t_it++;
		}
	}

}}
#endif

