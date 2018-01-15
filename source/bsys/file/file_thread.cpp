

/**
 * Copyright (c) 2016-2018 blueback
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
#include "./file_thread.h"
#include "./file_object.h"
#include "./file_allocator.h"


/** warning

4710 : この関数はインライン展開のために選択されましたが、コンパイラはインライン展開を実行しませんでした。

*/
#pragma warning(disable:4710)


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
		pack(),
		#endif

		cache()
	{
		this->endrequest.Store(false);
		for(s32 ii=0;ii<COUNTOF(this->worklist);ii++){
			this->worklist[ii].reset();
		}

		#if(BSYS_FILE_PACK_ENABLE)
		this->pack.reset(new File_Pack());
		#endif
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

			//リクエスト待ち。
			if(t_request == false){
				this->request_event.Wait();
			}else{
				t_request = false;
			}

			//リクエスト受付開始。
			this->request_event.Clear();

			{
				//パック。
				#if(BSYS_FILE_PACK_ENABLE)
				while(1){
					//処理が必要なものを検索。
					sharedptr<File_Pack_WorkItem> t_workitem_pack;
					{
						//■排他。(this->packworklist[])にアクセス。
						AutoLock  t_autolock_workitem_pack(this->lockobject_packworklist);

						for(s32 ii=0;ii<COUNTOF(this->packworklist);ii++){
							if(this->packworklist[ii] != nullptr){
								t_request = true;
								t_workitem_pack = this->packworklist[ii];
								this->packworklist[ii].reset();
								break;
							}
						}
					}

					//処理。
					if(t_workitem_pack){
						//■排他。(this->pack)にアクセス。
						AutoLock t_autolock_pack(this->lockobject_pack);

						while(1){
							if(t_workitem_pack->Update(*this,a_threadargument.rootpath_full)){
								if(t_workitem_pack->GetErrorCode() == ErrorCode::Success){
									//パックファイル。ヘッダー読み込み完了。
									this->pack->Regist(t_workitem_pack->GetPackFileNameShort(),t_workitem_pack);
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
						//■排他。(this->worklist[])にアクセス。

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

							if(t_workitem->Update(*this,a_threadargument.rootpath_full,t_cancel)){
								break;
							}
						}
						t_workitem.reset();
					}
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
		//AutoLock t_autolock(this->lockobject_thread);

		{
			this->endrequest.Store(true);
			this->request_event.Signal();
		}
	}


	/** [メインスレッド][パック]ロードリクエスト。
	*/
	#if(BSYS_FILE_PACK_ENABLE)
	sharedptr<File_Pack_WorkItem> File_Thread::Pack_LoadRequest(const STLWString& a_pack_filename_short,const STLWString& a_pack_connectto_rootpath_short)
	{
		{
			MemoryContainer t_memorycontainer(BSYS_FILE_MEMORYCONTAINER);

			sharedptr<File_Pack_WorkItem> t_workitem_pack(new File_Pack_WorkItem(Path::Name(a_pack_filename_short),Path::Dir(a_pack_connectto_rootpath_short)));

			//作業リストに登録。
			while(1){
				//■排他。(this->packworklist[])にアクセス。
				//■この排他処理から抜けた瞬間にworklistからworkitemが消費されるので参照カウント数が０にならないように注意。
				AutoLock t_autolock(this->lockobject_packworklist);

				for(s32 ii=0;ii<COUNTOF(this->packworklist);ii++){
					if(this->packworklist[ii] == nullptr){
						//作業リストに空きあり。

						this->packworklist[ii] = t_workitem_pack;
						this->request_event.Signal();

						return t_workitem_pack;
					}
				}

				ASSERT(0);
			}
		}

		return sharedptr<File_Pack_WorkItem>::null();
	}
	#endif


	/** [メインスレッド][パック]アンロード。
	*/
	#if(BSYS_FILE_PACK_ENABLE)
	void File_Thread::Pack_UnLoad(const STLWString& a_pack_filename_short)
	{
		//■排他。(this->pack)にアクセス。
		AutoLock t_autolock(this->lockobject_pack);

		{
			this->pack->UnRegist(a_pack_filename_short);
		}
	}
	#endif


	/** [メインスレッド]読み込み済みチェック。
	*/
	#if(BSYS_FILE_PACK_ENABLE)
	bool File_Thread::Pack_IsExist(const STLWString& a_pack_filename_short)
	{
		//■排他。(this->pack)にアクセス。
		AutoLock t_autolock(this->lockobject_pack);

		{
			return this->pack->IsExist(Path::Name(a_pack_filename_short));
		}
	}
	#endif


	/** [メインスレッド]ロードリクエスト。
	*/
	const sharedptr<File_WorkItem> File_Thread::LoadRequest(const STLWString& a_filename_short,s32 a_cachegroup_id,const sharedptr<File_Allocator>& a_allocator,s32 a_add_allocatesize)
	{
		{
			MemoryContainer t_memorycontainer(BSYS_FILE_MEMORYCONTAINER);

			sharedptr<File_WorkItem> t_workitem;
			
			//キャッシュ操作。
			{
				//■排他。(this->cache)にアクセス。
				AutoLock t_autolock_cache(this->lockobject_cache);

				if(a_cachegroup_id > 0){
					const sharedptr<File_WorkItem>& t_workitem_ref = this->cache.GetCacheFromFileNameShort(Path::Name(a_filename_short));
					if(t_workitem_ref != nullptr){
						//■キャッシュにあり。

						//キャッシュグループＩＤ追加。
						this->cache.SetCache(t_workitem_ref,a_cachegroup_id);

						return t_workitem_ref;
					}else{
						//■キャッシュになし。
						t_workitem.reset(new File_WorkItem(Path::Name(a_filename_short),a_allocator,a_add_allocatesize));

						//キャッシュグループＩＤ追加。
						this->cache.SetCache(t_workitem,a_cachegroup_id);
					}
				}else{
					ASSERT(a_cachegroup_id == -1);

					//■キャッシュを使わない。
					t_workitem.reset(new File_WorkItem(Path::Name(a_filename_short),a_allocator,a_add_allocatesize));
				}
			}

			//作業リストに登録。
			if(t_workitem != nullptr){

				while(1){

					//■排他。(this->worklist[])にアクセス。
					//■この排他処理から抜けた瞬間にworklistからworkitemが消費されるので参照カウント数が０にならないように注意。
					AutoLock t_autolock(this->lockobject_worklist);

					for(s32 ii=0;ii<COUNTOF(this->worklist);ii++){
						if(this->worklist[ii] == nullptr){
							//作業リストに空きあり。

							this->worklist[ii] = t_workitem;
							this->request_event.Signal();

							return t_workitem;
						}
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
		//■排他。(this->cache)にアクセス。
		AutoLock t_autolock(this->lockobject_cache);

		{
			this->cache.CacheClear(a_cachegroup_id);
		}
	}


	/** [メインスレッド]リークチェック。
	*/
	void File_Thread::LeakCheck() const
	{
		//■排他。(this->cache)にアクセス。
		AutoLock t_autolock(this->lockobject_cache);

		{
			this->cache.LeakCheck();
		}
	}


	/** [ファイルスレッド]Pack_TryCreateFileState。
	*/
	#if(BSYS_FILE_PACK_ENABLE)
	sharedptr<File_Pack_FileState>& File_Thread::Pack_TryCreateFileState(const STLWString& a_filename)
	{
		//■排他。(this->pack)にアクセス。
		AutoLock t_autolock(this->lockobject_pack);

		return this->pack->TryCreatePackFileState(a_filename);
	}
	#endif


	/** [ファイルスレッド]Pack_Read。
	*/
	#if(BSYS_FILE_PACK_ENABLE)
	bool File_Thread::Pack_Read(const sharedptr<File_Pack_FileState>& a_filestate,u8* a_buffer,s64 a_size,s64 a_offset)
	{
		//■排他。(this->pack)にアクセス。
		AutoLock t_autolock(this->lockobject_pack);

		return this->pack->ReadFromFileState(a_filestate,a_buffer,a_size,a_offset);
	}
	#endif

}}
#endif

