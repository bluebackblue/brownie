#pragma once

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ファイル。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


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
#if((BSYS_FILE_ENABLE)&&(BSYS_FILE_PACK_ENABLE))
#pragma warning(push)
#pragma warning(disable:4710 4514 4820)
namespace NBsys{namespace NFile
{
	/** File_Pack_MakeThread
	*/
	class File_Pack_MakeThread
	{
	private:

		/** ロックオブジェクト。
		*/
		LockObject lockobject;

	public:

		/** constructor
		*/
		File_Pack_MakeThread();

		/** destructor
		*/
		nonvirtual ~File_Pack_MakeThread();

	private:

		/** copy constructor禁止。
		*/
		File_Pack_MakeThread(const File_Pack_MakeThread& a_this) = delete;

		/** コピー禁止。
		*/
		void operator =(const File_Pack_MakeThread& a_this) = delete;

	public:

		/** 引数。
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

		/** スレッドメイン。
		*/
		void ThreadMain(ThreadArgument& a_threadargument);

	};


}}
#pragma warning(pop)
#endif

