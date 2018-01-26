

/**
 * Copyright (c) blueback
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
#include "./file_pack_makethread.h"
#include "./file_object.h"
#include "./file_allocator.h"


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
	File_Pack_MakeThread::File_Pack_MakeThread()
		:
		errorcode(ErrorCode::Success)
	{
	}


	/** destructor
	*/
	File_Pack_MakeThread::~File_Pack_MakeThread()
	{
	}


	/** 再起探査。
	*/
	bool File_Pack_MakeThread::SearchDirectory(STLVector<SearchItem>::Type& a_result_list,const SearchItem& a_request)
	{
		//クリア。
		a_result_list.clear();

		STLVector<SearchItem>::Type t_worklist;
		t_worklist.push_back(a_request);


		while(t_worklist.size() > 0){
			SearchItem t_workitem = t_worklist[t_worklist.size() - 1];
			{
				t_worklist.pop_back();
			}

			DirectoryHandle t_directoryhandle;
			if(t_directoryhandle.Open(t_workitem.filename_fullpath)){
				s32 ii_max = t_directoryhandle.GetSize();
				for(s32 ii=0;ii<ii_max;ii++){
					DirectoryHandle::DirectoryItem& t_item = t_directoryhandle.GetItem(ii);
					if(t_item.is_directory == true){
						//ワークリストに追加。
						t_worklist.push_back(SearchItem(Path::DirAndDir(t_workitem.filename_short,t_item.name),Path::DirAndDir(t_directoryhandle.GetFullPath(),t_item.name)));
					}else{
						//結果リストに追加。
						SearchItem t_request(Path::DirAndName(t_workitem.filename_short,t_item.name),Path::DirAndName(t_directoryhandle.GetFullPath(),t_item.name));
						a_result_list.push_back(t_request);
					}
				}
			}else{
				this->errorcode = ErrorCode::File_Error;
				DEEPDEBUG_TAGLOG(BSYS_FILE_DEBUG_ENABLE,L"file_pack_makethread","error : %08x",this->errorcode);
				return false;
			}
		}

		return true;
	}

	
	/** WritePack
	*/
	bool File_Pack_MakeThread::WritePack(const STLWString& a_pack_filename_full,const STLVector<SearchItem>::Type& a_search_list)
	{
		FileHandle t_filehandle_write;

		if(t_filehandle_write.WriteOpen(Path::Name(a_pack_filename_full)) == false){
			this->errorcode = ErrorCode::File_OpenError;
			DEEPDEBUG_TAGLOG(BSYS_FILE_DEBUG_ENABLE,L"file_pack_makethread","error : %08x",this->errorcode);
			return false;
		}else{

			/*
			------------------------------------------------------------------
			4 Byte                                    : ＩＤ
			4 Byte                                    : バージョン
			4 Byte                                    : ヘッダーサイズ
			4 Byte                                    : ファイル総数
			ファイル総数 * 4 Byte                     : 各ファイルサイズ
			ファイル総数 * 2 Byte                     : 各ファイルパス文字数（対象フォルダからの相対パス）
			(各ファイルパス文字数(合計) + 1) * 2 Byte : wchar型、0x0000区切り
			各ファイルサイズ(合計) Byte               : データ
			------------------------------------------------------------------ 
			*/

			s64 t_offset = 0;

			//ＩＤ。
			s64 t_id_offset = t_offset;
			u8 t_id[4] = {'B','P','A','C'};
			t_offset += sizeof(t_id);

			//バージョン。
			s64 t_version_offset = t_offset;
			u32 t_version = BSYS_FILE_PACK_VERSION;
			t_offset += sizeof(t_version);

			//ヘッダーサイズ。
			s64 t_header_size_offset = t_offset;
			u32 t_header_size = 0;
			t_offset += sizeof(t_header_size);

			//ファイル総数。
			s64 t_all_count_offset = t_offset;
			u32 t_all_count = static_cast<u32>(a_search_list.size());
			t_offset += sizeof(t_all_count);

			//各ファイルサイズ。
			s64 t_file_size_offset = t_offset;
			sharedptr<u32> t_file_size(new u32[t_all_count],default_delete<u32[]>());
			t_offset += sizeof(u32) * t_all_count;

			//各ファイル名文字数。
			s64 t_filename_length_offset = t_offset;
			sharedptr<u16> t_filename_length(new u16[t_all_count],default_delete<u16[]>());
			for(u32 ii=0;ii<a_search_list.size();ii++){
				t_filename_length.get()[ii] = static_cast<u16>(a_search_list.at(ii).filename_short.length());
			}
			t_offset += sizeof(u16) * t_all_count;

			//各ファイル名をまとめたもの。
			s64 t_all_filename_offset = t_offset;
			STLVector<wchar>::Type t_all_filename;
			for(u32 ii=0;ii<a_search_list.size();ii++){
				for(u32 jj=0;jj<a_search_list.at(ii).filename_short.length();jj++){
					t_all_filename.push_back(a_search_list.at(ii).filename_short.at(jj));
				}
				t_all_filename.push_back(0x0000);
			}
			t_offset += sizeof(wchar) * t_all_filename.size();

			//ヘッダーサイズ。
			t_header_size = static_cast<u32>(t_offset);

			//ＩＤ。
			if(t_filehandle_write.Write(reinterpret_cast<u8*>(&t_id),sizeof(t_id),t_id_offset) == false){
				this->errorcode = ErrorCode::File_WriteError;
				DEEPDEBUG_TAGLOG(BSYS_FILE_DEBUG_ENABLE,L"file_pack_makethread","error : %08x",this->errorcode);
				return false;
			}

			//バージョン。
			if(t_filehandle_write.Write(reinterpret_cast<u8*>(&t_version),sizeof(t_version),t_version_offset) == false){
				this->errorcode = ErrorCode::File_WriteError;
				DEEPDEBUG_TAGLOG(BSYS_FILE_DEBUG_ENABLE,L"file_pack_makethread","error : %08x",this->errorcode);
				return false;
			}

			//ヘッダーサイズ。
			if(t_filehandle_write.Write(reinterpret_cast<u8*>(&t_header_size),sizeof(t_header_size),t_header_size_offset) == false){
				this->errorcode = ErrorCode::File_WriteError;
				DEEPDEBUG_TAGLOG(BSYS_FILE_DEBUG_ENABLE,L"file_pack_makethread","error : %08x",this->errorcode);
				return false;
			}

			//総数。
			if(t_filehandle_write.Write(reinterpret_cast<u8*>(&t_all_count),sizeof(t_all_count),t_all_count_offset) == false){
				this->errorcode = ErrorCode::File_WriteError;
				DEEPDEBUG_TAGLOG(BSYS_FILE_DEBUG_ENABLE,L"file_pack_makethread","error : %08x",this->errorcode);
				return false;
			}

			//各ファイル名文字サイズ。
			if(t_filehandle_write.Write(reinterpret_cast<u8*>(t_filename_length.get()),static_cast<s64>(sizeof(u16) * t_all_count),t_filename_length_offset) == false){
				this->errorcode = ErrorCode::File_WriteError;
				DEEPDEBUG_TAGLOG(BSYS_FILE_DEBUG_ENABLE,L"file_pack_makethread","error : %08x",this->errorcode);
				return false;
			}

			//各ファイル名をひとまとめにしたもの。
			if(sizeof(wchar) * t_all_filename.size() > 0){
				if(t_filehandle_write.Write(reinterpret_cast<u8*>(&t_all_filename[0]),static_cast<s64>(sizeof(wchar) * t_all_filename.size()),t_all_filename_offset) == false){
					this->errorcode = ErrorCode::File_WriteError;
					DEEPDEBUG_TAGLOG(BSYS_FILE_DEBUG_ENABLE,L"file_pack_makethread","error : %08x",this->errorcode);
					return false;
				}
			}

			{
				for(u32 ii=0;ii<a_search_list.size();ii++){
					FileHandle t_filehandle_read;
					if(t_filehandle_read.ReadOpen(Path::Name(a_search_list.at(ii).filename_fullpath))){

						s64 t_filesize_read = t_filehandle_read.GetSize();
							
						//ファイルサイズ。設定。
						t_file_size.get()[ii] = static_cast<u32>(t_filesize_read);

						//読み込み。
						sharedptr<u8> t_filedata(new u8[static_cast<u32>(t_filesize_read)],default_delete<u8[]>());
						if(t_filehandle_read.Read(t_filedata.get(),t_filesize_read,0) == false){
							this->errorcode = ErrorCode::File_ReadError;
							DEEPDEBUG_TAGLOG(BSYS_FILE_DEBUG_ENABLE,L"file_pack_makethread","error : %08x",this->errorcode);
							return false;
						}
						t_filehandle_read.Close();

						//各データ。書き込み。
						if(t_filehandle_write.Write(reinterpret_cast<u8*>(t_filedata.get()),t_filesize_read,t_offset) == false){
							this->errorcode = ErrorCode::File_WriteError;
							DEEPDEBUG_TAGLOG(BSYS_FILE_DEBUG_ENABLE,L"file_pack_makethread","error : %08x",this->errorcode);
							return false;
						}

						t_offset += t_filesize_read;
					}else{
						//ファイルサイズ。設定。
						t_file_size.get()[ii] = 0;

						this->errorcode = ErrorCode::File_OpenError;
						DEEPDEBUG_TAGLOG(BSYS_FILE_DEBUG_ENABLE,L"file_pack_makethread","error : %08x",this->errorcode);
						return false;
					}
				}

				//各ファイルサイズ。
				if(t_filehandle_write.Write(reinterpret_cast<u8*>(t_file_size.get()),static_cast<s32>(sizeof(u32) * t_all_count),t_file_size_offset) == false){
					this->errorcode = ErrorCode::File_WriteError;
					DEEPDEBUG_TAGLOG(BSYS_FILE_DEBUG_ENABLE,L"file_pack_makethread","error : %08x",this->errorcode);
					return false;
				}
			}
		}
	
		t_filehandle_write.Close();
		return true;
	}


	/** スレッドメイン。
	*/
	void File_Pack_MakeThread::ThreadMain(ThreadArgument& a_threadargument)
	{
		MemoryContainer t_memorycontainer(BSYS_FILE_MEMORYCONTAINER);

		{
			AutoLock t_autolock(this->lockobject);

			STLVector<SearchItem>::Type t_search_list;
			if(this->SearchDirectory(t_search_list,SearchItem(L"",a_threadargument.rootpath_full)) == true){
				if(this->WritePack(a_threadargument.pack_filename_full,t_search_list) == true){
				}
			}
		}
	}


}}
#endif

