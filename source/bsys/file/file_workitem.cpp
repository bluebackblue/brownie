

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
#include "./file_workitem.h"
#include "./file_allocator.h"
#include "./file_pack_filehandle.h"
#include "./file_thread.h"


/** NBsys::NFile
*/
#if(BSYS_FILE_ENABLE)
namespace NBsys{namespace NFile
{

	/** constructor
	*/
	File_WorkItem::File_WorkItem(LockObject& a_lockobject,const STLWString& a_filename_short,sharedptr< File_Allocator >& a_allocator,s32 a_add_allocatesize)
		:
		lockobject(a_lockobject),
		mainstep(MainStep::Open),
		mode(Mode::None),

		#if(BSYS_FILE_PACK_ENABLE)
		pack_filehandle(),
		#endif

		normal_filehandle(),
		filename_short(a_filename_short),
		convertflag(-1),
		data_size(0LL),
		data_offset(0LL),
		errorcode(ErrorCode::Success),
		isbusy(true),
		allocator(a_allocator),
		add_allocatesize(a_add_allocatesize)
	{
		this->data.reset();
	}

	/** destructor
	*/
	File_WorkItem::~File_WorkItem()
	{
	}

	/** �G���[�R�[�h�擾�B
	*/
	ErrorCode::Id File_WorkItem::GetErrorCode() const
	{
		AutoLock t_autolock(this->lockobject);

		return this->errorcode;
	}

	/** GetData�B
	*/
	sharedptr< u8 >& File_WorkItem::GetData()
	{
		AutoLock t_autolock(this->lockobject);

		if(this->mainstep == MainStep::End){
			if(this->errorcode == ErrorCode::Success){
				return this->data;
			}
		}
		return sharedptr< u8 >::null();
	}

	/** GetSize
	*/
	s64 File_WorkItem::GetSize() const
	{
		AutoLock t_autolock(this->lockobject);

		return this->data_size;
	}

	/** GetAddAllocateSize
	*/
	s32 File_WorkItem::GetAddAllocateSize() const
	{
		AutoLock t_autolock(this->lockobject);

		return this->add_allocatesize;
	}

	/** IsBusy
	*/
	bool File_WorkItem::IsBusy() const
	{
		AutoLock t_autolock(this->lockobject);

		if((this->mainstep == MainStep::End)||(this->mainstep == MainStep::Error)){
			return false;
		}
		return true;
	}

	/** GetFileNameShort
	*/
	const STLWString& File_WorkItem::GetFileNameShort() const
	{
		AutoLock t_autolock(this->lockobject);

		return this->filename_short;
	}

	/** �R���o�[�g���b�N�B
	*/
	File_ConvertLock_ReturnType::Id File_WorkItem::ConvertLock()
	{
		AutoLock t_autolock(this->lockobject);

		if(this->convertflag < 0){

			//���R���o�[�g => �R���o�[�g���B

			this->convertflag = 0;
			return File_ConvertLock_ReturnType::Locked;

		}else if(this->convertflag == 0){
		
			//�R���o�[�g���B
		
			return File_ConvertLock_ReturnType::ConvertNow;
		}
		
		//�R���o�[�g�ς݁B
		return File_ConvertLock_ReturnType::AlreadyConverted;
	}

	/** �R���o�[�g�A�����b�N�B
	*/
	void File_WorkItem::ConvertUnlock()
	{
		AutoLock t_autolock(this->lockobject);

		if(this->convertflag < 0){

			//���R���o�[�g�B

			ASSERT(0);
		}else if(this->convertflag == 0){

			//�R���o�[�g�� => �R���o�[�g�ς݁B

			this->convertflag = 1;
		}

		//�R���o�[�g�ς݁B
		ASSERT(0);
	}

	/** [�X���b�h����]�X�V�B

		@return : true = ���� / false = ��ƒ�

		filehandle�͕����X���b�h����A�N�Z�X����Ȃ��̂ŁA�r�����Ȃ��B

	*/
	bool File_WorkItem::Update(File_Thread& a_thread,const STLWString& a_rootpath_full,bool a_cancel)
	{
		switch(this->mainstep){
		case MainStep::Open:
			{
				//�J���B

				STLWString t_filename_full;
				STLWString t_filename_short;
				{
					//���r���B
					AutoLock t_autolock(this->lockobject);

					t_filename_full = Path::DirAndName(a_rootpath_full,this->filename_short);
					t_filename_short = Path::Name(this->filename_short);
				}

				this->mode = Mode::None;

				//��[����]�p�b�N����t�@�C�����J���B
				#if(BSYS_FILE_PACK_ENABLE)
				if(this->mode == Mode::None){
					File_Pack& t_pack = a_thread.Pack_GetInstance();
					this->pack_filehandle = t_pack.CreatePackFileHandle(t_filename_short);
					if(this->pack_filehandle != nullptr){
						this->mode = Mode::Pack;
					}
				}
				#else
				UNUSED(a_thread);
				#endif

				//��[����]�J���B
				if(this->mode == Mode::None){
					bool t_ret_open = this->normal_filehandle.ReadOpen(t_filename_full);
					if(t_ret_open == true){
						this->mode = Mode::Normal;
					}
				}

				if(this->mode != Mode::None){
					//��[����]�t�@�C���T�C�Y�B

					if(this->mode == Mode::Pack){
						#if(BSYS_FILE_PACK_ENABLE)
						this->data_size = this->pack_filehandle->GetSize();
						#endif
					}else if(Mode::Normal){
						this->data_size = this->normal_filehandle.GetSize();
					}

					{
						//���r���B
						AutoLock t_autolock(this->lockobject);

						if(this->data_size > 0LL){
							this->data_offset = 0LL;

							if(this->allocator){
								//�A���P�[�^�g�p�B
								this->data.reset(reinterpret_cast< u8* >(this->allocator->Alloc(static_cast< u32 >(this->data_size + this->add_allocatesize))),File_Alloc_Deleter(this->allocator));
							}else{
								//�ʏ�A���P�[�g�B
								MemoryContainer t_memorycontainer(BSYS_FILE_MEMORYCONTAINER);

								this->data.reset(new u8[static_cast< u32 >(this->data_size + this->add_allocatesize)],default_delete< u8[] >());
							}
							this->mainstep = MainStep::Read;
							break;
						}else{
							//�t�@�C���T�C�Y�擾�Ɏ��s�B
							this->errorcode = ErrorCode::Load_OpenError;
							this->mainstep = MainStep::Error;
						}
					}
				}else{
					//���r���B
					AutoLock t_autolock(this->lockobject);

					//�t�@�C�����J���̂Ɏ��s�B
					this->errorcode = ErrorCode::Load_OpenError;
					this->mainstep = MainStep::Error;
					break;
				}
			}break;
		case MainStep::Read:
			{
				//�ǂݍ��ށB
				s64 t_readsize = 0LL;
				u8* t_readdata = nullptr;
				s64 t_readoffset = 0LL;
				{
					//���r���B
					AutoLock t_autolock(this->lockobject);

					t_readsize = this->data_size - this->data_offset;
					if(t_readsize >= (512*1024)){
						t_readsize = (512*1024);
					}

					t_readdata = &(this->data.get()[this->data_offset]);

					t_readoffset = this->data_offset;
				}

				bool t_ret_read = false;
				if(this->mode == Mode::Pack){
					//��[����]�ǂݍ��݁B
					#if(BSYS_FILE_PACK_ENABLE)
					t_ret_read = this->pack_filehandle->Read(t_readdata,t_readsize,t_readoffset);
					#endif
				}else if(this->mode == Mode::Normal){
					//��[����]�ǂݍ��݁B
					t_ret_read = this->normal_filehandle.Read(t_readdata,t_readsize,t_readoffset);
				}

				{
					//���r���B
					AutoLock t_autolock(this->lockobject);

					if(a_cancel){
						//�L�����Z���B
						this->errorcode = ErrorCode::Load_CancelError;
						this->mainstep = MainStep::Error;
						break;
					}else if(t_ret_read){
						//�ǂݍ��ݒ��B
						this->data_offset += t_readsize;
						if(this->data_offset >= this->data_size){
							//�ǂݍ��݊����B
							this->mainstep = MainStep::End;
						}else{
							//�ǂݍ��ݒ��B
						}
					}else{
						//�ǂݍ��݂Ɏ��s�B
						this->errorcode = ErrorCode::Load_ReadError;
						this->mainstep = MainStep::Error;
						break;
					}
				}
			}break;
		case MainStep::End:
			{
				//��[����]����B
				if(this->mode == Mode::Normal){
					this->normal_filehandle.Close();
				}

				{
					AutoLock t_autolock(this->lockobject);

					//�����B
					this->isbusy = false;
					return true;
				}
			}break;
		case MainStep::Error:
			{
				//��[����]����B
				if(this->mode == Mode::Normal){
					this->normal_filehandle.Close();
				}

				{
					AutoLock t_autolock(this->lockobject);

					//�G���[�����B
					this->isbusy = false;
					return true;
				}
			}break;
		}

		ThreadSleep(0);

		return false;
	}

}}
#endif

