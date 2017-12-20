

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
#include "./file_pack_workitem.h"


/** NBsys::NFile
*/
#if(BSYS_FILE_PACK_ENABLE)
namespace NBsys{namespace NFile
{
	/** constructor
	*/
	File_Pack_WorkItem::File_Pack_WorkItem(const STLWString& a_pack_filename_short,const STLWString& a_pack_rootpath_short)
		:
		mainstep(MainStep::Open),
		filehandle(),
		pack_filename_short(a_pack_filename_short),
		pack_rootpath_short(a_pack_rootpath_short),
		data_size(0LL),
		errorcode(ErrorCode::Success)
	{
	}


	/** destructor
	*/
	File_Pack_WorkItem::~File_Pack_WorkItem()
	{
		//■[処理]閉じる。
		{
			this->filehandle.Close();
		}
	}


	/** エラーコード取得。
	*/
	ErrorCode::Id File_Pack_WorkItem::GetErrorCode() const
	{
		return this->errorcode;
	}


	/** パックファイル名取得。
	*/
	const STLWString& File_Pack_WorkItem::GetPackFileNameShort()
	{
		return this->pack_filename_short;
	}


	/** ファイル検索。
	*/
	sharedptr<File_Pack_FileHandle>& File_Pack_WorkItem::FindFromFileNameShort(const STLWString& a_filename_short)
	{
		STLMap<STLWString,sharedptr<File_Pack_FileHandle>>::iterator t_it = this->filelist.find(a_filename_short);
		if(t_it != this->filelist.end()){
			return t_it->second;
		}
		return sharedptr<File_Pack_FileHandle>::null();
	}


	/** [スレッドから]更新。

		@return : true = 完了 / false = 作業中

	*/
	bool File_Pack_WorkItem::Update(const STLWString& a_rootpath_full)
	{
		switch(this->mainstep){
		case MainStep::Open:
			{
				//開く。

				STLWString t_pack_filename_full = Path::DirAndName(a_rootpath_full,this->pack_filename_short);

				bool t_ret_open = false;
				{
					//■[処理]開く。
					t_ret_open = this->filehandle.ReadOpen(t_pack_filename_full);
				}

				if(t_ret_open){

					//■[処理]ファイルサイズ。
					{
						this->data_size = this->filehandle.GetSize();
					}

					{
						if(this->data_size > 0LL){
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

				s64 t_offset = 0;

				//ヘッダーサイズ。
				u32 t_header_size = 0;
				this->filehandle.Read(reinterpret_cast<u8*>(&t_header_size),sizeof(u32),0);
				t_offset += sizeof(u32);

				//ヘッダーデータ。
				sharedptr<u8> t_header(new u8[t_header_size],default_delete<u8[]>());
				this->filehandle.Read(t_header.get(),t_header_size,0);

				//総数。
				u32 t_all_count = 0;
				Memory::memcpy(&t_all_count,sizeof(u32),&t_header.get()[t_offset],sizeof(u32));
				t_offset += sizeof(u32);

				//各ファイルサイズ。
				sharedptr<u32> t_file_size(new u32[t_all_count]);
				Memory::memcpy(t_file_size.get(),sizeof(u32) * t_all_count,&t_header.get()[t_offset],sizeof(u32) * t_all_count);
				t_offset += sizeof(u32) * t_all_count;

				//各ファイル名文字サイズ。
				sharedptr<u16> t_filename_length(new u16[t_all_count]);
				Memory::memcpy(t_filename_length.get(),sizeof(u16) * t_all_count,&t_header.get()[t_offset],sizeof(u16) * t_all_count);
				t_offset += sizeof(u16) * t_all_count;

				//各ファイル名をまとめたもの。
				{
					s64 t_offset_path = t_offset;
					s64 t_offset_data = t_header_size;

					for(s32 ii=0;ii<static_cast<s32>(t_all_count);ii++){
						wchar t_buffer[300] = {0};
						s32 t_length = sizeof(u16)*(t_filename_length.get()[ii]+1);
						ASSERT(t_length < COUNTOF(t_buffer));

						Memory::memcpy(&t_buffer[0],sizeof(t_buffer),&t_header.get()[t_offset_path],t_length);
						t_offset_path += sizeof(u16) * (t_filename_length.get()[ii] + 1);
						
						STLWString t_filename_short = Path::DirAndName(this->pack_rootpath_short,t_buffer);

						this->filelist.insert(STLMap<STLWString,sharedptr<File_Pack_FileHandle>>::value_type(t_filename_short,new File_Pack_FileHandle(this->filehandle,t_file_size.get()[ii],t_offset_data)));

						t_offset_data += t_file_size.get()[ii];
					}
				}

				this->mainstep = MainStep::End;

			}break;
		case MainStep::End:
			{
				{
					//完了。
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
					return true;
				}
			}break;
		}

		ThreadSleep(0);

		return false;
	}


}}
#endif

