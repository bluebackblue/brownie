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
#include "./file_object.h"
#include "./file_allocator.h"
#include "./file_cache.h"
#include "./file_pack.h"
#include "./file_pack_filehandle.h"


/** NBsys::NFile
*/
#if(BSYS_FILE_ENABLE)
namespace NBsys{namespace NFile
{

	/** File_Thread
	*/
	class File_Thread
	{
	private:
		/** endrequest
		*/
		AtomicValue<bool> endrequest;

		/** ���b�N�I�u�W�F�N�g�B
		*/
		LockObject lockobject;

		/** ��ƃ��X�g�B
		*/
		sharedptr<File_WorkItem> worklist[BSYS_FILE_LISTSIZE];

		/** �p�b�N��ƃ��X�g�B
		*/
		#if(BSYS_FILE_PACK_ENABLE)
		sharedptr<File_Pack_WorkItem> worklist_pack[1];
		#endif

		/** [���N�G�X�g]�C�x���g�B
		*/
		SimpleEvent request_event;

		/** �p�b�N�B
		*/
		#if(BSYS_FILE_PACK_ENABLE)
		File_Pack pack;
		#endif

		/** �L���b�V���B
		*/
		File_Cache cache;

	public:
		/** constructor
		*/
		File_Thread();

		/** destructor
		*/
		nonvirtual ~File_Thread();

	public:
		/** �����B
		*/
		struct ThreadArgument
		{
			/** threadname
			*/
			STLString threadname;

			/** stacksize
			*/
			size_t stacksize;

			/** priority
			*/
			s32 priority;

			/** rootpath_full
			*/
			STLWString rootpath_full;

			/** constructor
			*/
			ThreadArgument()
				:
				threadname("file_thread"),
				stacksize(64 * 1024),
				priority(0),
				rootpath_full(L"./")
			{
			}

			/** destructor
			*/
			nonvirtual ~ThreadArgument()
			{
			}
		};

		/** �X���b�h���C���B
		*/
		void ThreadMain(ThreadArgument& a_threadargument);

		/** [���C���X���b�h]�I�����N�G�X�g�B
		*/
		void EndRequest();

		/** [���C���X���b�h]���b�N�I�u�W�F�N�g�̎擾�B
		*/
		LockObject& GetLockObject();

		/** [���C���X���b�h][�p�b�N]���[�h���N�G�X�g�B
		*/
		#if(BSYS_FILE_PACK_ENABLE)
		void Pack_LoadRequest(const STLWString& a_pack_filename_short,const STLWString& a_pack_rootpath_short);
		#endif

		/** [���C���X���b�h][�p�b�N]�ǂݍ��ݍς݃`�F�b�N�B
		*/
		#if(BSYS_FILE_PACK_ENABLE)
		bool Pack_IsExist(const STLWString& a_pack_filename_short);
		#endif

		/** [���C���X���b�h]���[�h���N�G�X�g�B
		*/
		const sharedptr<File_WorkItem> LoadRequest(const STLWString& a_filename_short,s32 a_cachegroup_id,sharedptr<File_Allocator>& a_allocator,s32 a_add_allocatesize);

		/** [���C���X���b�h]�L���b�V���N���A�B
		*/
		void CacheClear(s32 a_cachegroup_id);

		/** [���C���X���b�h]���[�N�`�F�b�N�B
		*/
		void LeakCheck();

		/** [�t�@�C���X���b�h]Pack_GetInstance�B

		�r���Ȃ��B��������̌Ăяo���B

		*/
		#if(BSYS_FILE_PACK_ENABLE)
		File_Pack& Pack_GetInstance();
		#endif

	};

}}
#endif
