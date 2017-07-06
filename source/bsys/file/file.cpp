

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
#include "./file.h"
#include "./file_thread.h"


/** NBsys::NFile
*/
#if(BSYS_FILE_ENABLE)
namespace NBsys{namespace NFile
{
	/** s_thread
	*/
	sharedptr< STLVector< sharedptr< ThreadTemplate< File_Thread > > >::Type > s_thread_list;

	/** システムの開始。
	*/
	void StartSystem(s32 a_device_max)
	{
		MemoryContainer t_memorycontainer(BSYS_FILE_MEMORYCONTAINER);

		if(s_thread_list == nullptr){
			s_thread_list.reset(new STLVector< sharedptr< ThreadTemplate< File_Thread > > >::Type());

			for(s32 ii=0;ii<a_device_max;ii++){
				s_thread_list->push_back(nullptr);
			}

		}else{
			ASSERT(0);
		}
	}

	/** ルートの設定。
	*/
	void SetRoot(s32 a_device_index,const STLWString& a_rootpath_full)
	{
		MemoryContainer t_memorycontainer(BSYS_FILE_MEMORYCONTAINER);

		if(s_thread_list != nullptr){
			if(s_thread_list->at(a_device_index) == nullptr){
				File_Thread::ThreadArgument t_threadargument;
				{
					t_threadargument.rootpath_full = Path::Dir(a_rootpath_full);
				}

				s_thread_list->at(a_device_index).reset(new ThreadTemplate< File_Thread >());
				s_thread_list->at(a_device_index)->Start(t_threadargument);
			}else{
				ASSERT(0);
			}
		}else{
			ASSERT(0);
		}
	}

	/** システムのインスタンス取得。
	*/
	sharedptr< ThreadTemplate< File_Thread > >& GetSystemInstance(s32 a_device_index)
	{
		ASSERT((0 <= a_device_index)&&(a_device_index < s_thread_list->size()));

		return s_thread_list->at(a_device_index);
	}

	/** リークチェック。
	*/
	void LeakCheck()
	{
		if(s_thread_list != nullptr){
			STLVector< sharedptr< ThreadTemplate< File_Thread > > >::iterator t_it = s_thread_list->begin();
			STLVector< sharedptr< ThreadTemplate< File_Thread > > >::iterator t_it_end = s_thread_list->end();

			for(;t_it!=t_it_end;++t_it){
				if(t_it->get() != nullptr){
					if(t_it->get()->get() != nullptr){
						t_it->get()->get()->LeakCheck();
					}
				}
			}
		}else{
			ASSERT(0);
		}
	}

	/** キャッシュクリア。
	*/
	void CacheClear(s32 a_device_index,s32 a_cachegroup_id)
	{
		if(s_thread_list != nullptr){
			s_thread_list->at(a_device_index)->get()->CacheClear(a_cachegroup_id);
		}else{
			ASSERT(0);
		}
	}

	/** システムの終了リクエスト。
	*/
	void EndSystemRequest()
	{
		if(s_thread_list != nullptr){
			STLVector< sharedptr< ThreadTemplate< File_Thread > > >::iterator t_it = s_thread_list->begin();
			STLVector< sharedptr< ThreadTemplate< File_Thread > > >::iterator t_it_end = s_thread_list->end();

			for(;t_it!=t_it_end;++t_it){
				if(t_it->get() != nullptr){
					if(t_it->get()->get() != nullptr){
						t_it->get()->get()->EndRequest();
					}
				}
			}
		}else{
			ASSERT(0);
		}
	}

	/** システムの終了待ち。
	*/
	void EndWaitSystem()
	{
		s_thread_list.reset();
	}

	/** [パック]作成。
	*/
	#if(BSYS_FILE_PACK_ENABLE)
	sharedptr< ThreadTemplate< File_Pack_MakeThread > > Pack_Create(const STLWString& a_rootpath_full,const STLWString& a_pack_filename_full,const sharedptr< File_Allocator >& a_allocator)
	{
		File_Pack_MakeThread::ThreadArgument t_threadargument;
		{
			t_threadargument.rootpath_full = Path::Dir(a_rootpath_full);
			t_threadargument.pack_filename_full = Path::Name(a_pack_filename_full);
			t_threadargument.allocator = a_allocator;
		}

		sharedptr< ThreadTemplate< File_Pack_MakeThread > > t_pack_makethread(new ThreadTemplate< File_Pack_MakeThread >());
		t_pack_makethread->Start(t_threadargument);

		return t_pack_makethread;
	}
	#endif

	/** [パック]ロードリクエスト。
	*/
	#if(BSYS_FILE_PACK_ENABLE)
	void Pack_LoadRequest(s32 a_device_index,const STLWString& a_pack_filename_short,const STLWString& a_pack_rootpath_short)
	{
		NBsys::NFile::GetSystemInstance(a_device_index)->get()->Pack_LoadRequest(a_pack_filename_short,a_pack_rootpath_short);
	}
	#endif

	/** [パック]読み込み済みチェック。
	*/
	#if(BSYS_FILE_PACK_ENABLE)
	bool Pack_IsExist(s32 a_device_index,const STLWString& a_pack_filename_short)
	{
		return NBsys::NFile::GetSystemInstance(a_device_index)->get()->Pack_IsExist(a_pack_filename_short);
	}
	#endif

}}
#endif
