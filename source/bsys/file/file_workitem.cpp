

/**
 * Copyright (c) 2016-2017 blueback
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
#include "./file_workitem.h"
#include "./file_allocator.h"
#include "./file_pack_filestate.h"
#include "./file_thread.h"


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
	File_WorkItem::File_WorkItem(const STLWString& a_filename_short,const sharedptr<File_Allocator>& a_allocator,s32 a_add_allocatesize)
		:
		lockobject(),
		mainstep(MainStep::Open),
		mode(Mode::None),

		#if(BSYS_FILE_PACK_ENABLE)
		pack_filehstate(),
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
		//■排他。
		AutoLock t_autolock(this->lockobject);

		this->normal_filehandle.Close();
	}


	/** エラーコード取得。
	*/
	ErrorCode::Id File_WorkItem::GetErrorCode() const
	{
		//■排他。
		AutoLock t_autolock(this->lockobject);

		return this->errorcode;
	}


	/** GetData。
	*/
	sharedptr<u8>& File_WorkItem::GetData()
	{
		//■排他。
		AutoLock t_autolock(this->lockobject);

		if(this->mainstep == MainStep::End){
			if(this->errorcode == ErrorCode::Success){
				return this->data;
			}
		}
		return sharedptr<u8>::null();
	}


	/** GetSize
	*/
	s64 File_WorkItem::GetSize() const
	{
		//■排他。
		AutoLock t_autolock(this->lockobject);

		return this->data_size;
	}


	/** GetAddAllocateSize
	*/
	s32 File_WorkItem::GetAddAllocateSize() const
	{
		//■排他。
		AutoLock t_autolock(this->lockobject);

		return this->add_allocatesize;
	}


	/** IsBusy
	*/
	bool File_WorkItem::IsBusy() const
	{
		return this->isbusy.Load();
	}


	/** GetFileNameShort
	*/
	const STLWString& File_WorkItem::GetFileNameShort() const
	{
		//■排他。
		AutoLock t_autolock(this->lockobject);

		return this->filename_short;
	}


	/** コンバートロック。
	*/
	File_ConvertLock_ReturnType::Id File_WorkItem::ConvertLock()
	{
		//■排他。
		AutoLock t_autolock(this->lockobject);

		if(this->convertflag < 0){

			//未コンバート => コンバート中。

			this->convertflag = 0;
			return File_ConvertLock_ReturnType::Locked;

		}else if(this->convertflag == 0){
		
			//コンバート中。
		
			return File_ConvertLock_ReturnType::ConvertNow;
		}
		
		//コンバート済み。
		return File_ConvertLock_ReturnType::AlreadyConverted;
	}


	/** コンバートアンロック。
	*/
	void File_WorkItem::ConvertUnlock()
	{
		//■排他。
		AutoLock t_autolock(this->lockobject);

		if(this->convertflag < 0){

			//未コンバート。

			ASSERT(0);
			return;
		}else if(this->convertflag == 0){

			//コンバート中 => コンバート済み。

			this->convertflag = 1;
			return;
		}

		//コンバート済み。
		ASSERT(0);
		return;
	}


	/** [スレッドから]更新。

		@return : true = 完了 / false = 作業中

		filehandleは複数スレッドからアクセスされないので、排他しない。

	*/
	bool File_WorkItem::Update(File_Thread& a_thread,const STLWString& a_rootpath_full,bool a_cancel)
	{
		//■排他。
		AutoLock t_autolock(this->lockobject);

		switch(this->mainstep){
		case MainStep::Open:
			{
				//開く。

				STLWString t_filename_full;
				STLWString t_filename_short;
				{

					t_filename_full = Path::DirAndName(a_rootpath_full,this->filename_short);
					t_filename_short = Path::Name(this->filename_short);
				}

				this->mode = Mode::None;

				//■[処理]パックからファイルを開く。
				#if(BSYS_FILE_PACK_ENABLE)
				if(this->mode == Mode::None){
					this->pack_filehstate = a_thread.Pack_TryCreateFileState(t_filename_short);
					if(this->pack_filehstate != nullptr){
						this->mode = Mode::Pack;
					}
				}
				#else
				UNUSED(a_thread);
				#endif

				//■[処理]開く。
				if(this->mode == Mode::None){
					bool t_ret_open = this->normal_filehandle.ReadOpen(t_filename_full);
					if(t_ret_open == true){
						this->mode = Mode::Normal;
					}
				}

				if(this->mode != Mode::None){
					//■[処理]ファイルサイズ。

					s64 t_data_size = 0;

					if(this->mode == Mode::Pack){
						#if(BSYS_FILE_PACK_ENABLE)
						t_data_size = this->pack_filehstate->data_size;
						#endif
					}else if(this->mode == Mode::Normal){
						t_data_size = this->normal_filehandle.GetSize();
					}

					{
						this->data_size = t_data_size;

						if(this->data_size > 0LL){
							this->data_offset = 0LL;

							if(this->allocator){
								//アロケータ使用。
								this->data.reset(reinterpret_cast<u8*>(this->allocator->Alloc(static_cast<u32>(this->data_size + this->add_allocatesize))),File_Alloc_Deleter(this->allocator));
							}else{
								//通常アロケート。
								MemoryContainer t_memorycontainer(BSYS_FILE_MEMORYCONTAINER);

								this->data.reset(new u8[static_cast<u32>(this->data_size + this->add_allocatesize)],default_delete<u8[]>());
							}
							this->mainstep = MainStep::Read;
							break;
						}else{
							//ファイルサイズ取得に失敗。
							this->errorcode = ErrorCode::Load_OpenError;
							this->mainstep = MainStep::Error;
						}
					}
				}else{
					//ファイルを開くのに失敗。
					this->errorcode = ErrorCode::Load_OpenError;
					this->mainstep = MainStep::Error;
					break;
				}
			}break;
		case MainStep::Read:
			{
				//読み込む。
				s64 t_readsize = 0LL;
				u8* t_readdata = nullptr;
				s64 t_readoffset = 0LL;
				{
					t_readsize = this->data_size - this->data_offset;
					if(t_readsize >= (512*1024)){
						t_readsize = (512*1024);
					}

					t_readdata = &(this->data.get()[this->data_offset]);

					t_readoffset = this->data_offset;
				}

				bool t_ret_read = false;
				if(this->mode == Mode::Pack){
					//■[処理]読み込み。
					#if(BSYS_FILE_PACK_ENABLE)
					t_ret_read = a_thread.Pack_Read(this->pack_filehstate,t_readdata,t_readsize,t_readoffset);
					#endif
				}else if(this->mode == Mode::Normal){
					//■[処理]読み込み。
					t_ret_read = this->normal_filehandle.Read(t_readdata,t_readsize,t_readoffset);
				}

				{
					if(a_cancel){
						//キャンセル。
						this->errorcode = ErrorCode::Load_CancelError;
						this->mainstep = MainStep::Error;
						break;
					}else if(t_ret_read){
						//読み込み中。
						this->data_offset += t_readsize;
						if(this->data_offset >= this->data_size){
							//読み込み完了。
							this->mainstep = MainStep::End;
						}else{
							//読み込み中。
						}
					}else{
						//読み込みに失敗。
						this->errorcode = ErrorCode::Load_ReadError;
						this->mainstep = MainStep::Error;
						break;
					}
				}
			}break;
		case MainStep::End:
			{
				//■[処理]閉じる。
				if(this->mode == Mode::Normal){
					this->normal_filehandle.Close();
				}

				{
					//完了。
					this->isbusy.Store(false);
					return true;
				}
			}break;
		case MainStep::Error:
			{
				//■[処理]閉じる。
				if(this->mode == Mode::Normal){
					this->normal_filehandle.Close();
				}

				{
					//エラー完了。
					this->isbusy.Store(false);
					return true;
				}
			}break;
		default:
		case MainStep::None:
			{
				ASSERT(0);
			}break;
		}

		ThreadSleep(0);

		return false;
	}


}}
#endif

