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
#if(BSYS_FILE_PACK_ENABLE)
namespace NBsys{namespace NFile
{

	/** File_Pack_MakeThread
	*/
	class File_Pack_MakeThread
	{
	private:
		/** ���b�N�I�u�W�F�N�g�B
		*/
		LockObject lockobject;

	public:
		/** constructor
		*/
		File_Pack_MakeThread();

		/** destructor
		*/
		nonvirtual ~File_Pack_MakeThread();

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

			/** pack_filename_full
			*/
			STLWString pack_filename_full;

			/** allocator
			*/
			sharedptr<File_Allocator> allocator;

			/** constructor
			*/
			ThreadArgument()
				:
				threadname("file_pack_makethread"),
				stacksize(64 * 1024),
				priority(0),
				rootpath_full(L"./"),
				pack_filename_full(L""),
				allocator(nullptr)
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

	};

}}
#endif

