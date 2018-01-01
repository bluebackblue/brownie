

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
#include "./file_pack_workitem.h"
#include "./file_thread.h"


/** warning

4710 : この関数はインライン展開のために選択されましたが、コンパイラはインライン展開を実行しませんでした。

*/
#pragma warning(disable:4710)


/** NBsys::NFile
*/
#if((BSYS_FILE_ENABLE)&&(BSYS_FILE_PACK_ENABLE))
namespace NBsys{namespace NFile
{
	/** constructor
	*/
	File_Pack_WorkItem::File_Pack_WorkItem(const STLWString& a_pack_filename_short,const STLWString& a_pack_rootpath_short)
		:
		lockobject(),
		mainstep(MainStep::Open),
		filehandle(),
		pack_filename_short(a_pack_filename_short),
		pack_rootpath_short(a_pack_rootpath_short),
		data_size(0LL),
		errorcode(ErrorCode::Success),
		isbusy(true),
		filestate_list()
	{
	}


	/** destructor
	*/
	File_Pack_WorkItem::~File_Pack_WorkItem()
	{
		//■排他。
		AutoLock t_autolock(this->lockobject);

		this->filestate_list.clear();

		this->filehandle.Close();
	}


	/** エラーコード取得。
	*/
	ErrorCode::Id File_Pack_WorkItem::GetErrorCode() const
	{
		//■排他。
		AutoLock t_autolock(this->lockobject);

		return this->errorcode;
	}


	/** IsBusy
	*/
	bool File_Pack_WorkItem::IsBusy() const
	{
		return this->isbusy.Load();
	}


	/** パックファイル名取得。
	*/
	const STLWString& File_Pack_WorkItem::GetPackFileNameShort() const
	{
		//■排他。
		AutoLock t_autolock(this->lockobject);

		return this->pack_filename_short;
	}


	/** ファイル検索。
	*/
	sharedptr<File_Pack_FileState>& File_Pack_WorkItem::FindFromFileNameShort(const STLWString& a_filename_short)
	{
		//■排他。
		AutoLock t_autolock(this->lockobject);

		auto t_it = this->filestate_list.find(a_filename_short);
		if(t_it != this->filestate_list.cend()){
			return t_it->second;
		}
		return sharedptr<File_Pack_FileState>::null();
	}


	/** 読み込み。
	*/
	bool File_Pack_WorkItem::Read(const sharedptr<File_Pack_FileState>& a_filestate,u8* a_buffer,s64 a_size,s64 a_offset)
	{
		//■排他。
		AutoLock t_autolock(this->lockobject);

		return this->filehandle.Read(a_buffer,a_size,a_filestate->data_offset + a_offset);
	}


	/** [スレッドから]更新。

		@return : true = 完了 / false = 作業中

	*/
	bool File_Pack_WorkItem::Update(File_Thread& /*a_thread*/,const STLWString& a_rootpath_full)
	{
		//■排他。
		AutoLock t_autolock(this->lockobject);

		switch(this->mainstep){
		case MainStep::Open:
			{
				//開く。

				STLWString t_pack_filename_full;
				{
					t_pack_filename_full = Path::DirAndName(a_rootpath_full,this->pack_filename_short);
				}

				bool t_ret_open = false;

				{
					//■[処理]開く。
					t_ret_open = this->filehandle.ReadOpen(t_pack_filename_full);
				}

				if(t_ret_open){

					//■[処理]ファイルサイズ。

					s64 t_data_size = 0;

					{
						t_data_size = this->filehandle.GetSize();
					}

					{
						this->data_size = t_data_size;

						if(this->data_size > 0LL){
							this->mainstep = MainStep::Read;
							break;
						}else{
							//ファイルサイズ取得に失敗。
							this->errorcode = ErrorCode::File_OpenError;
							this->mainstep = MainStep::Error;
							DEEPDEBUG_TAGLOG(BSYS_FILE_DEBUG_ENABLE,L"file_pack_workitem","error : %08x",this->errorcode);
							return false;
						}
					}
				}else{
					//ファイルを開くのに失敗。
					this->errorcode = ErrorCode::File_OpenError;
					this->mainstep = MainStep::Error;
					return false;
				}
			}break;
		case MainStep::Read:
			{
				//読み込む。

				//ＩＤ。
				u8 t_id[4] = {0};
				this->filehandle.Read(reinterpret_cast<u8*>(&t_id),sizeof(t_id),0);
				if(NMemory::Compare(t_id,"BPAC",sizeof(t_id)) != 0){
					//ＩＤが違う。
					this->errorcode = ErrorCode::File_IdError;
					this->mainstep = MainStep::Error;
					DEEPDEBUG_TAGLOG(BSYS_FILE_DEBUG_ENABLE,L"file_pack_workitem","error : %08x",this->errorcode);
					return false;
				}

				//バージョン。
				u32 t_version = 0;
				this->filehandle.Read(reinterpret_cast<u8*>(&t_version),sizeof(u32),4);
				if(t_version != BSYS_FILE_PACK_VERSION){
					//バージョンが違う。
					this->errorcode = ErrorCode::File_VersionError;
					this->mainstep = MainStep::Error;
					DEEPDEBUG_TAGLOG(BSYS_FILE_DEBUG_ENABLE,L"file_pack_workitem","error : %08x",this->errorcode);
					return false;
				}

				s64 t_offset = 0;

				//ヘッダーサイズ。
				u32 t_header_size = 0;
				this->filehandle.Read(reinterpret_cast<u8*>(&t_header_size),sizeof(u32),8);
				t_offset += sizeof(u32);
				//TODO:error

				//ヘッダーデータ。
				sharedptr<u8> t_header(new u8[t_header_size],default_delete<u8[]>());
				this->filehandle.Read(t_header.get(),t_header_size,8);

				{
					//総数。
					u32 t_all_count = 0;
					NMemory::Copy(&t_all_count,sizeof(u32),&t_header.get()[t_offset],sizeof(t_all_count));
					t_offset += sizeof(t_all_count);

					//各ファイルサイズ。
					sharedptr<u32> t_file_size(new u32[t_all_count]);
					NMemory::Copy(t_file_size.get(),(sizeof(u32) * t_all_count),&t_header.get()[t_offset],(sizeof(u32) * t_all_count));
					t_offset += sizeof(u32) * t_all_count;

					//各ファイル名文字サイズ。
					sharedptr<u16> t_filename_length(new u16[t_all_count]);
					NMemory::Copy(t_filename_length.get(),(sizeof(u16) * t_all_count),&t_header.get()[t_offset],(sizeof(u16) * t_all_count));
					t_offset += sizeof(u16) * t_all_count;

					//各ファイル名をまとめたもの。
					{
						s64 t_offset_path = t_offset;
						s64 t_offset_data = t_header_size;

						for(u32 ii=0;ii<t_all_count;ii++){
							wchar t_buffer[300] = {0};
							s32 t_length = static_cast<s32>(sizeof(u16) * (t_filename_length.get()[ii]+1));
							if(t_length >= COUNTOF(t_buffer)){
								//ファイル名が長い。
								this->errorcode = ErrorCode::File_NameError;
								this->mainstep = MainStep::Error;
								DEEPDEBUG_TAGLOG(BSYS_FILE_DEBUG_ENABLE,L"file_pack_workitem","error : %08x",this->errorcode);
								return false;
							}

							NMemory::Copy(&t_buffer[0],sizeof(t_buffer),&t_header.get()[t_offset_path],t_length);
							t_offset_path += sizeof(u16) * (t_filename_length.get()[ii] + 1);
						
							STLWString t_filename_short = Path::DirAndName(this->pack_rootpath_short,t_buffer);

							this->filestate_list.insert(std::make_pair(t_filename_short,new File_Pack_FileState(this,t_file_size.get()[ii],t_offset_data)));

							t_offset_data += t_file_size.get()[ii];
						}
					}
				}

				this->mainstep = MainStep::End;

			}break;
		case MainStep::End:
			{
				{
					//完了。
					this->isbusy.Store(false);
					return true;
				}
			}break;
		case MainStep::Error:
			{
				//■[処理]閉じる。
				{
					this->filehandle.Close();
				}

				{
					//エラー完了。
					this->isbusy.Store(false);
					return true;
				}
			}break;
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

