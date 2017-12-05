

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

	/** �X���b�h���C���B
	*/
	void File_Thread::ThreadMain(ThreadArgument& a_threadargument)
	{
		bool t_request = false;

		MemoryContainer t_memorycontainer(BSYS_FILE_MEMORYCONTAINER);

		while(1){

			{
				//���N�G�X�g�҂��B
				if(t_request == false){
					this->request_event.Wait();
				}

				//���N�G�X�g��t�J�n�B
				this->request_event.Clear();
			}

			//�p�b�N�B
			#if(BSYS_FILE_PACK_ENABLE)
			while(1){
				//�������K�v�Ȃ��̂������B
				sharedptr<File_Pack_WorkItem> t_workitem_pack;
				{
					//���r���B
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

				//�����B
				if(t_workitem_pack){
					while(1){
						if(t_workitem_pack->Update(Path::Dir(a_threadargument.rootpath_full))){
							if(t_workitem_pack->GetErrorCode() == ErrorCode::Success){
								//�p�b�N�t�@�C���B�w�b�_�[�ǂݍ��݊����B
								this->pack.Resist(t_workitem_pack);
							}else{
								//�p�b�N�t�@�C���B�ǂݍ��ݎ��s�B
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

			//�ǂݍ��݁B
			{
				//�������K�v�Ȃ��̂������B
				sharedptr<File_WorkItem> t_workitem;
				{
					//���r���B
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

				//�����B
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

			//�I���`�F�b�N�B
			if(this->endrequest.Load()){
				return;
			}
		}
	}

	/** [���C���X���b�h]EndRequest
	*/
	void File_Thread::EndRequest()
	{
		//���r���B
		AutoLock t_autolock(this->lockobject);

		this->endrequest.Store(true);
		this->request_event.Signal();
	}

	/** [���C���X���b�h]���b�N�I�u�W�F�N�g�̎擾�B
	*/
	LockObject& File_Thread::GetLockObject()
	{
		return this->lockobject;
	}
	
	/** [���C���X���b�h][�p�b�N]���[�h���N�G�X�g�B
	*/
	#if(BSYS_FILE_PACK_ENABLE)
	void File_Thread::Pack_LoadRequest(const STLWString& a_pack_filename_short,const STLWString& a_pack_rootpath_short)
	{
		//���r���B
		AutoLock t_autolock(this->lockobject);
		{
			MemoryContainer t_memorycontainer(BSYS_FILE_MEMORYCONTAINER);

			sharedptr<File_Pack_WorkItem> t_workitem_pack(new File_Pack_WorkItem(Path::Name(a_pack_filename_short),Path::Dir(a_pack_rootpath_short)));

			//��ƃ��X�g�ɓo�^�B
			for(s32 ii=0;ii<COUNTOF(this->worklist_pack);ii++){
				if(this->worklist_pack[ii] == nullptr){
					//��ƃ��X�g�ɋ󂫂���B

					this->worklist_pack[ii] = t_workitem_pack;
					this->request_event.Signal();

					return;
				}
			}

			ASSERT(0);
		}
	}
	#endif

	/** [���C���X���b�h]�ǂݍ��ݍς݃`�F�b�N�B
	*/
	#if(BSYS_FILE_PACK_ENABLE)
	bool File_Thread::Pack_IsExist(const STLWString& a_pack_filename_short)
	{
		//���r���B
		AutoLock t_autolock(this->lockobject);
		{
			return this->pack.IsExist(Path::Name(a_pack_filename_short));

			ASSERT(0);
		}
	}
	#endif

	/** [���C���X���b�h]���[�h���N�G�X�g�B
	*/
	const sharedptr<File_WorkItem> File_Thread::LoadRequest(const STLWString& a_filename_short,s32 a_cachegroup_id,sharedptr<File_Allocator>& a_allocator,s32 a_add_allocatesize)
	{
		//���r���B
		AutoLock t_autolock(this->lockobject);
		{
			MemoryContainer t_memorycontainer(BSYS_FILE_MEMORYCONTAINER);

			sharedptr<File_WorkItem> t_workitem;
			
			if(a_cachegroup_id > 0){
				const sharedptr<File_WorkItem>& t_workitem_ref = this->cache.GetCacheFromFileNameShort(Path::Name(a_filename_short));
				if(t_workitem_ref != nullptr){
					//���L���b�V���ɂ���B

					//�L���b�V���O���[�v�h�c�ǉ��B
					this->cache.SetCache(t_workitem_ref,a_cachegroup_id);

					return t_workitem_ref;
				}else{
					//���L���b�V���ɂȂ��B
					t_workitem.reset(new File_WorkItem(this->lockobject,Path::Name(a_filename_short),a_allocator,a_add_allocatesize));

					//�L���b�V���O���[�v�h�c�ǉ��B
					this->cache.SetCache(t_workitem,a_cachegroup_id);
				}
			}else{
				ASSERT(a_cachegroup_id == -1);

				//���L���b�V�����g��Ȃ��B
				t_workitem.reset(new File_WorkItem(this->lockobject,Path::Name(a_filename_short),a_allocator,a_add_allocatesize));
			}

			//��ƃ��X�g�ɓo�^�B
			if(t_workitem != nullptr){
				for(s32 ii=0;ii<COUNTOF(this->worklist);ii++){
					if(this->worklist[ii] == nullptr){
						//��ƃ��X�g�ɋ󂫂���B

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

	/** [���C���X���b�h]�L���b�V���N���A�B
	*/
	void File_Thread::CacheClear(s32 a_cachegroup_id)
	{
		//���r���B
		AutoLock t_autolock(this->lockobject);
		{
			this->cache.CacheClear(a_cachegroup_id);
		}
	}

	/** [���C���X���b�h]���[�N�`�F�b�N�B
	*/
	void File_Thread::LeakCheck()
	{
		//���r���B
		AutoLock t_autolock(this->lockobject);
		{
			this->cache.LeakCheck();
		}
	}

	/** [�t�@�C���X���b�h]Pack_GetInstance

	�r���Ȃ��B

	*/
	#if(BSYS_FILE_PACK_ENABLE)
	File_Pack& File_Thread::Pack_GetInstance()
	{
		return this->pack;
	}
	#endif

}}
#endif
