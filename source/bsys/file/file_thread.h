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
#include "./file_allocator.h"
#include "./file_cache.h"
#include "./file_pack.h"
#include "./file_pack_filestate.h"


/** NBsys::NFile
*/
#if(BSYS_FILE_ENABLE)
#pragma warning(push)
#pragma warning(disable:4514 4820)
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

		/** ロックオブジェクト。
		*/
		mutable LockObject lockobject_thread;

		/** ロックオブジェクト。(this->cache)にアクセス。
		*/
		mutable LockObject lockobject_cache;

		/** ロックオブジェクト。(this->worklist[])にアクセス。
		*/
		mutable LockObject lockobject_worklist;

		/** ロックオブジェクト。(this->packworklist[])にアクセス。
		*/
		mutable LockObject lockobject_packworklist;

		/** ロックオブジェクト。(this->pack)にアクセス。
		*/
		mutable LockObject lockobject_pack;

		/** 作業リスト。
		*/
		sharedptr<File_WorkItem> worklist[BSYS_FILE_LISTSIZE];

		/** パック作業リスト。
		*/
		#if(BSYS_FILE_PACK_ENABLE)
		sharedptr<File_Pack_WorkItem> packworklist[1];
		#endif

		/** [リクエスト]イベント。
		*/
		SimpleEvent request_event;

		/** パック。
		*/
		#if(BSYS_FILE_PACK_ENABLE)
		sharedptr<File_Pack> pack;
		#endif

		/** キャッシュ。
		*/
		File_Cache cache;

	public:

		/** constructor
		*/
		File_Thread();

		/** destructor
		*/
		nonvirtual ~File_Thread();

	private:

		/** copy constructor禁止。
		*/
		File_Thread(const File_Thread& a_this) = delete;

		/** コピー禁止。
		*/
		void operator =(const File_Thread& a_this) = delete;

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

		/** スレッドメイン。
		*/
		void ThreadMain(ThreadArgument& a_threadargument);

		/** [メインスレッド]終了リクエスト。
		*/
		void EndRequest();

		/** [メインスレッド][パック]ロードリクエスト。
		*/
		#if(BSYS_FILE_PACK_ENABLE)
		sharedptr<File_Pack_WorkItem> Pack_LoadRequest(const STLWString& a_pack_filename_short,const STLWString& a_pack_connectto_rootpath_short);
		#endif

		/** [メインスレッド][パック]アンロード。
		*/
		#if(BSYS_FILE_PACK_ENABLE)
		void Pack_UnLoad(const STLWString& a_pack_filename_short);
		#endif

		/** [メインスレッド][パック]読み込み済みチェック。
		*/
		#if(BSYS_FILE_PACK_ENABLE)
		bool Pack_IsExist(const STLWString& a_pack_filename_short);
		#endif

		/** [メインスレッド]ロードリクエスト。
		*/
		const sharedptr<File_WorkItem> LoadRequest(const STLWString& a_filename_short,s32 a_cachegroup_id,const sharedptr<File_Allocator>& a_allocator,s32 a_add_allocatesize);

		/** [メインスレッド]キャッシュクリア。
		*/
		void CacheClear(s32 a_cachegroup_id);

		/** [メインスレッド]リークチェック。
		*/
		void LeakCheck() const;

		/** [ファイルスレッド]Pack_TryCreateFileState。
		*/
		#if(BSYS_FILE_PACK_ENABLE)
		sharedptr<File_Pack_FileState>& Pack_TryCreateFileState(const STLWString& a_filename);
		#endif

		/** [ファイルスレッド]Pack_CreateFileState。
		*/
		bool Pack_Read(const sharedptr<File_Pack_FileState>& a_filestate,u8* a_buffer,s64 a_size,s64 a_offset);

	};


}}
#pragma warning(pop)
#endif

