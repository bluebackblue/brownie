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


/** NBsys::NFile
*/
#if(BSYS_FILE_ENABLE)
namespace NBsys{namespace NFile
{

	/** File_Cache_Item
	*/
	struct File_Cache_Item
	{
		/** �L���b�V�����Ă��郏�[�N�A�C�e���B
		*/
		sharedptr< File_WorkItem > workitem;

		/** �Q�Ƃh�c��񋓁B
		*/
		typedef STLMap< s32 , bool >::Type IDListType;
		IDListType cachegroup_id_list;

		/** constructor
		*/
		explicit File_Cache_Item(const sharedptr< File_WorkItem >& a_workitem);

		/** destructor
		*/
		nonvirtual ~File_Cache_Item();

		/** �h�c�ǉ��B
		*/
		void AddID(s32 a_id);

		/** �h�c�폜�B
		*/
		void KillID(s32 a_id);

		/** �����B
		*/
		bool Find(s32 a_id);

		/** �󂩂ǂ����B
		*/
		bool IsEmpty();

	};

}}
#endif

