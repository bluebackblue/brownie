

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
#include "./file_thread.h"
#include "./file_object.h"
#include "./file_allocator.h"


/** NBsys::NFile
*/
#if(BSYS_FILE_ENABLE)
namespace NBsys{namespace NFile
{
	/** constructor
	*/
	File_Thread::File_Thread()
		:
		request_event(true),

		#if(BSYS_FILE_PACK_ENABLE)
		pack(this->lockobject),
		#endif

		cache()
	{
		this->endrequest.Store(false);
		for(s32 ii=0;ii<COUNTOF(this->worklist);ii++){
			this->worklist[ii].reset();
		}
	}

	/** destructor
	*/
	File_Thread::~File_Thread()
	{
	}

	/** スレッドメイン。
	*/
	void File_Thread::ThreadMain(ThreadArgument& a_threadargument)
	{
		bool t_request = false;

		MemoryContainer t_memorycontainer(BSYS_FILE_MEMORYCONTAINER);

		while(1){

			{
				//リクエスト待ち。
				if(t_request == false){
					this->request_event.Wait();
				}

				//リクエスト受付開始。
				this->request_event.Clear();
			}

			//パック。
			#if(BSYS_FILE_PACK_ENABLE)
			while(1){
				//処理が必要なものを検索。
				sharedptr<File_Pack_WorkItem> t_workitem_pack;
				{
					//■排他。
					AutoLock t_autolock(this->lockobject);

					t_request = false;
					for(s32 ii=0;ii<COUNTOF(this->worklist_pack);ii++){
						if(this->worklist_pack[ii] != nullptr){
							t_request = true;
							t_workitem_pack = this->worklist_pack[ii];
							this->worklist_pack[ii].reset();
							break;
						}
					}
				}

				//処理。
				if(t_workitem_pack){
					while(1){
						if(t_workitem_pack->Update(Path::Dir(a_threadargument.rootpath_full))){
							if(t_workitem_pack->GetErrorCode() == ErrorCode::Success){
								//パックファイル。ヘッダー読み込み完了。
								this->pack.Resist(t_workitem_pack);
							}else{
								//パックファイル。読み込み失敗。
								ASSERT(0);
							}
							break;
						}
					}
					t_workitem_pack.reset();
				}else{
					break;
				}
			}
			#endif

			//読み込み。
			{
				//処理が必要なものを検索。
				sharedptr<File_WorkItem> t_workitem;
				{
					//■排他。
					AutoLock t_autolock(this->lockobject);

					t_request = false;
					for(s32 ii=0;ii<COUNTOF(this->worklist);ii++){
						if(this->worklist[ii] != nullptr){
							t_request = true;
							t_workitem = this->worklist[ii];
							this->worklist[ii].reset();
							break;
						}
					}
				}

				//処理。
				if(t_workitem){
					while(1){
						bool t_cancel = false;

						if(t_workitem.use_count() <= 1){
							t_cancel = true;
						}

						if(t_workitem->Update(*this,Path::Dir(a_threadargument.rootpath_full),t_cancel)){
							break;
						}
					}
					t_workitem.reset();
				}
			}

			//終了チェック。
			if(this->endrequest.Load()){
				return;
			}
		}
	}

	/** [メインスレッド]EndRequest
	*/
	void File_Thread::EndRequest()
	{
		//■排他。
		AutoLock t_autolock(this->lockobject);

		this->endrequest.Store(true);
		this->request_event.Signal();
	}

	/** [メインスレッド]ロックオブジェクトの取得。
	*/
	LockObject& File_Thread::GetLockObject()
	{
		return this->lockobject;
	}
	
	/** [メインスレッド][パック]ロードリクエスト。
	*/
	#if(BSYS_FILE_PACK_ENABLE)
	void File_Thread::Pack_LoadRequest(const STLWString& a_pack_filename_short,const STLWString& a_pack_rootpath_short)
	{
		//■排他。
		AutoLock t_autolock(this->lockobject);
		{
			MemoryContainer t_memorycontainer(BSYS_FILE_MEMORYCONTAINER);

			sharedptr<File_Pack_WorkItem> t_workitem_pack(new File_Pack_WorkItem(Path::Name(a_pack_filename_short),Path::Dir(a_pack_rootpath_short)));

			//作業リストに登録。
			for(s32 ii=0;ii<COUNTOF(this->worklist_pack);ii++){
				if(this->worklist_pack[ii] == nullptr){
					//作業リストに空きあり。

					this->worklist_pack[ii] = t_workitem_pack;
					this->request_event.Signal();

					return;
				}
			}

			ASSERT(0);
		}
	}
	#endif

	/** [メインスレッド]読み込み済みチェック。
	*/
	#if(BSYS_FILE_PACK_ENABLE)
	bool File_Thread::Pack_IsExist(const STLWString& a_pack_filename_short)
	{
		//■排他。
		AutoLock t_autolock(this->lockobject);
		{
			return this->pack.IsExist(Path::Name(a_pack_filename_short));

			ASSERT(0);
		}
	}
	#endif

	/** [メインスレッド]ロードリクエスト。
	*/
	const sharedptr<File_WorkItem> File_Thread::LoadRequest(const STLWString& a_filename_short,s32 a_cachegroup_id,sharedptr<File_Allocator>& a_allocator,s32 a_add_allocatesize)
	{
		//■排他。
		AutoLock t_autolock(this->lockobject);
		{
			MemoryContainer t_memorycontainer(BSYS_FILE_MEMORYCONTAINER);

			sharedptr<File_WorkItem> t_workitem;
			
			if(a_cachegroup_id > 0){
				const sharedptr<File_WorkItem>& t_workitem_ref = this->cache.GetCacheFromFileNameShort(Path::Name(a_filename_short));
				if(t_workitem_ref != nullptr){
					//■キャッシュにあり。

					//キャッシュグループＩＤ追加。
					this->cache.SetCache(t_workitem_ref,a_cachegroup_id);

					return t_workitem_ref;
				}else{
					//■キャッシュになし。
					t_workitem.reset(new File_WorkItem(this->lockobject,Path::Name(a_filename_short),a_allocator,a_add_allocatesize));

					//キャッシュグループＩＤ追加。
					this->cache.SetCache(t_workitem,a_cachegroup_id);
				}
			}else{
				ASSERT(a_cachegroup_id == -1);

				//■キャッシュを使わない。
				t_workitem.reset(new File_WorkItem(this->lockobject,Path::Name(a_filename_short),a_allocator,a_add_allocatesize));
			}

			//作業リストに登録。
			if(t_workitem != nullptr){
				for(s32 ii=0;ii<COUNTOF(this->worklist);ii++){
					if(this->worklist[ii] == nullptr){
						//作業リストに空きあり。

						this->worklist[ii] = t_workitem;
						this->request_event.Signal();

						return this->worklist[ii];
					}
				}
			}

			ASSERT(0);
			return sharedptr<File_WorkItem>::null();
		}
	}

	/** [メインスレッド]キャッシュクリア。
	*/
	void File_Thread::CacheClear(s32 a_cachegroup_id)
	{
		//■排他。
		AutoLock t_autolock(this->lockobject);
		{
			this->cache.CacheClear(a_cachegroup_id);
		}
	}

	/** [メインスレッド]リークチェック。
	*/
	void File_Thread::LeakCheck()
	{
		//■排他。
		AutoLock t_autolock(this->lockobject);
		{
			this->cache.LeakCheck();
		}
	}

	/** [ファイルスレッド]Pack_GetInstance

	排他なし。

	*/
	#if(BSYS_FILE_PACK_ENABLE)
	File_Pack& File_Thread::Pack_GetInstance()
	{
		return this->pack;
	}
	#endif

}}
#endif
