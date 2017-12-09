

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
#include "./file_pack_makethread.h"
#include "./file_object.h"
#include "./file_allocator.h"


/** NBsys::NFile
*/
#if(BSYS_FILE_PACK_ENABLE)
namespace NBsys{namespace NFile
{
	/** constructor
	*/
	File_Pack_MakeThread::File_Pack_MakeThread()
	{
	}

	/** destructor
	*/
	File_Pack_MakeThread::~File_Pack_MakeThread()
	{
	}

	/** スレッドメイン。
	*/
	void File_Pack_MakeThread::ThreadMain(ThreadArgument& a_threadargument)
	{
		bool t_request = false;

		MemoryContainer t_memorycontainer(BSYS_FILE_MEMORYCONTAINER);

		{
			/** ワークアイテム。
			*/
			struct WorkItem
			{
				/** パックからの短縮パス。
				*/
				STLWString path_pack_short;

				/** 絶対パス。
				*/
				STLWString path_full;

				WorkItem(const STLWString& a_path_short,const STLWString& a_path_full)
					:
					path_pack_short(Path::Dir(a_path_short)),
					path_full(Path::Dir(a_path_full))
				{
				}
			};

			STLVector<WorkItem>::Type t_worklist;
			{
				t_worklist.push_back(WorkItem(L"",a_threadargument.rootpath_full));
			}

			/** ファイル名。パックからの短縮パス。
			*/
			STLVector<STLWString>::Type t_filename_pack_short_list;

			/** ファイル名。絶対パス。
			*/
			STLVector<STLWString>::Type t_filename_fullpath_list;

			while(t_worklist.size() > 0){
				WorkItem t_workitem = t_worklist[t_worklist.size() - 1];
				t_worklist.pop_back();

				DirectoryHandle t_directoryhandle;
				t_directoryhandle.Open(t_workitem.path_full);

				s32 ii_max = t_directoryhandle.GetSize();
				for(s32 ii=0;ii<ii_max;ii++){
					DirectoryHandle::DirectoryItem& t_item = t_directoryhandle.GetItem(ii);
					if(t_item.is_directory == true){
						//ディレクトリ。
						t_worklist.push_back(WorkItem(Path::DirAndDir(t_workitem.path_pack_short,t_item.name),Path::DirAndDir(t_directoryhandle.GetFullPath(),t_item.name)));
					}else{
						//ファイル。
						t_filename_pack_short_list.push_back(Path::DirAndName(t_workitem.path_pack_short,t_item.name));
						t_filename_fullpath_list.push_back(Path::DirAndName(t_directoryhandle.GetFullPath(),t_item.name));
					}
				}
			}

			{
				FileHandle t_filehandle_write;

				if(t_filehandle_write.WriteOpen(Path::Name(a_threadargument.pack_filename_full)) == false){
					ASSERT(0);
				}else{

					/*
					------------------------------------------------------------------
					4 Byte                                    : ヘッダーサイズ
					4 Byte                                    : ファイル総数
					ファイル総数 * 4 Byte                     : 各ファイルサイズ
					ファイル総数 * 2 Byte                     : 各ファイルパス文字数（対象フォルダからの相対パス）
					(各ファイルパス文字数(合計) + 1) * 2 Byte : wchar型、0x0000区切り
					各ファイルサイズ(合計) Byte               : データ
					------------------------------------------------------------------ 
					*/

					s64 t_offset = 0;

					//ヘッダーサイズ。
					s64 t_header_size_offset = t_offset;
					u32 t_header_size = 0;
					t_offset += sizeof(u32);

					//ファイル総数。
					s64 t_all_count_offset = t_offset;
					u32 t_all_count = static_cast<u32>(t_filename_pack_short_list.size());
					t_offset += sizeof(u32);

					//各ファイルサイズ。
					s64 t_file_size_offset = t_offset;
					sharedptr<u32> t_file_size(new u32[t_all_count],default_delete<u32[]>());
					t_offset += sizeof(u32) * t_all_count;

					//各ファイル名文字数。
					s64 t_filename_length_offset = t_offset;
					sharedptr<u16> t_filename_length(new u16[t_all_count],default_delete<u16[]>());
					for(s32 ii=0;ii<static_cast<s32>(t_filename_pack_short_list.size());ii++){
						t_filename_length.get()[ii] = static_cast<u16>(t_filename_pack_short_list[ii].length());
					}
					t_offset += sizeof(u16) * t_all_count;

					//各ファイル名をまとめたもの。
					s64 t_all_filename_offset = t_offset;
					STLVector<wchar>::Type t_all_filename;
					for(s32 ii=0;ii<static_cast<s32>(t_filename_pack_short_list.size());ii++){
						for(s32 jj=0;jj<static_cast<s32>(t_filename_pack_short_list[ii].length());jj++){
							t_all_filename.push_back(t_filename_pack_short_list[ii][jj]);
						}
						t_all_filename.push_back(0x0000);
					}
					t_offset += sizeof(wchar) * t_all_filename.size();

					//ヘッダーサイズ。
					t_header_size = static_cast<s32>(t_offset);

					{
						//ヘッダーサイズ。
						if(t_filehandle_write.Write(reinterpret_cast<u8*>(&t_header_size),sizeof(t_header_size),t_header_size_offset) == false){
							ASSERT(0);
						}

						//総数。
						if(t_filehandle_write.Write(reinterpret_cast<u8*>(&t_all_count),sizeof(t_all_count),t_all_count_offset) == false){
							ASSERT(0);
						}

						//各ファイル名文字サイズ。
						if(t_filehandle_write.Write(reinterpret_cast<u8*>(t_filename_length.get()),sizeof(u16) * t_all_count,t_filename_length_offset) == false){
							ASSERT(0);
						}

						//各ファイル名をひとまとめにしたもの。
						if(t_filehandle_write.Write(reinterpret_cast<u8*>(&t_all_filename[0]),sizeof(wchar) * t_all_filename.size(),t_all_filename_offset) == false){
							ASSERT(0);
						}
					}

					{
						for(s32 ii=0;ii<static_cast<s32>(t_filename_fullpath_list.size());ii++){
							FileHandle t_filehandle_read;
							t_filehandle_read.ReadOpen(Path::Name(t_filename_fullpath_list[ii]));

							s64 t_filesize_read = t_filehandle_read.GetSize();
							
							//ファイルサイズ。
							t_file_size.get()[ii] = static_cast<u32>(t_filesize_read);

							sharedptr<u8> t_filedata(new u8[static_cast<s32>(t_filesize_read)],default_delete<u8[]>());

							//読み込み。
							if(t_filehandle_read.Read(t_filedata.get(),t_filesize_read,0) == false){
								ASSERT(0);
							}

							t_filehandle_read.Close();

							//各データ。
							if(t_filehandle_write.Write(reinterpret_cast<u8*>(t_filedata.get()),t_filesize_read,t_offset) == false){
								ASSERT(0);
							}

							t_offset += t_filesize_read;
						}
					}

					{
						//各ファイルサイズ。
						if(t_filehandle_write.Write(reinterpret_cast<u8*>(t_file_size.get()),sizeof(u32) * t_all_count,t_file_size_offset) == false){
							ASSERT(0);
						}
					}

					t_filehandle_write.Close();
				}
			}
		}
	}

}}
#endif

