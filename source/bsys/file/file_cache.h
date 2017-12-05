#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �t�@�C���B
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
		/** �L���b�V���}�b�v�B
		*/
		STLMap<STLWString,sharedptr<File_Cache_Item>>::Type map;
	
	public:
		/** constructor
		*/
		File_Cache();

		/** destructor
		*/
		nonvirtual ~File_Cache();

		/** �L���b�V���֓o�^�B
		*/
		void SetCache(const sharedptr<File_WorkItem>& a_workitem,s32 a_cachegroup_id);

		/** ���O����L���b�V���������B
		*/
		const sharedptr<File_WorkItem>& GetCacheFromFileNameShort(const STLWString& a_filename_short) const;

		/** �L���b�V���N���A�B
		*/
		void CacheClear(s32 a_cachegroup_id);

		/** ���[�N�`�F�b�N�B
		*/
		void LeakCheck() const;

	};

}}
#endif

