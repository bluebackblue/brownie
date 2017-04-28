

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

	/** �X���b�h���C���B
	*/
	void File_Pack_MakeThread::ThreadMain(ThreadArgument& a_threadargument)
	{
		bool t_request = false;

		MemoryContainer t_memorycontainer(BSYS_FILE_MEMORYCONTAINER);

		{
			/** ���[�N�A�C�e���B
			*/
			struct WorkItem
			{
				/** �p�b�N����̒Z�k�p�X�B
				*/
				STLWString path_pack_short;

				/** ��΃p�X�B
				*/
				STLWString path_full;

				WorkItem(const STLWString& a_path_short,const STLWString& a_path_full)
					:
					path_pack_short(Path::Dir(a_path_short)),
					path_full(Path::Dir(a_path_full))
				{
				}
			};

			STLVector< WorkItem >::Type t_worklist;
			{
				t_worklist.push_back(WorkItem(L"",a_threadargument.rootpath_full));
			}

			/** �t�@�C�����B�p�b�N����̒Z�k�p�X�B
			*/
			STLVector< STLWString >::Type t_filename_pack_short_list;

			/** �t�@�C�����B��΃p�X�B
			*/
			STLVector< STLWString >::Type t_filename_fullpath_list;

			while(t_worklist.size() > 0){
				WorkItem t_workitem = t_worklist[t_worklist.size() - 1];
				t_worklist.pop_back();

				DirectoryHandle t_directoryhandle;
				t_directoryhandle.Open(t_workitem.path_full);

				s32 ii_max = t_directoryhandle.GetSize();
				for(s32 ii=0;ii<ii_max;ii++){
					DirectoryHandle::DirectoryItem& t_item = t_directoryhandle.GetItem(ii);
					if(t_item.is_directory == true){
						//�f�B���N�g���B
						t_worklist.push_back(WorkItem(Path::DirAndDir(t_workitem.path_pack_short,t_item.name),Path::DirAndDir(t_directoryhandle.GetFullPath(),t_item.name)));
					}else{
						//�t�@�C���B
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
					4 Byte                                    : �w�b�_�[�T�C�Y
					4 Byte                                    : �t�@�C������
					�t�@�C������ * 4 Byte                     : �e�t�@�C���T�C�Y
					�t�@�C������ * 2 Byte                     : �e�t�@�C���p�X�������i�Ώۃt�H���_����̑��΃p�X�j
					(�e�t�@�C���p�X������(���v) + 1) * 2 Byte : wchar�^�A0x0000��؂�
					�e�t�@�C���T�C�Y(���v) Byte               : �f�[�^
					------------------------------------------------------------------ 
					*/

					s64 t_offset = 0;

					//�w�b�_�[�T�C�Y�B
					s64 t_header_size_offset = t_offset;
					u32 t_header_size = 0;
					t_offset += sizeof(u32);

					//�t�@�C�������B
					s64 t_all_count_offset = t_offset;
					u32 t_all_count = static_cast< u32 >(t_filename_pack_short_list.size());
					t_offset += sizeof(u32);

					//�e�t�@�C���T�C�Y�B
					s64 t_file_size_offset = t_offset;
					sharedptr< u32 > t_file_size(new u32[t_all_count],default_delete< u32[] >());
					t_offset += sizeof(u32) * t_all_count;

					//�e�t�@�C�����������B
					s64 t_filename_length_offset = t_offset;
					sharedptr< u16 > t_filename_length(new u16[t_all_count],default_delete< u16[] >());
					for(int ii=0;ii<static_cast< s32 >(t_filename_pack_short_list.size());ii++){
						t_filename_length.get()[ii] = static_cast< u16 >(t_filename_pack_short_list[ii].length());
					}
					t_offset += sizeof(u16) * t_all_count;

					//�e�t�@�C�������܂Ƃ߂����́B
					s64 t_all_filename_offset = t_offset;
					STLVector< wchar >::Type t_all_filename;
					for(s32 ii=0;ii<static_cast< s32 >(t_filename_pack_short_list.size());ii++){
						for(s32 jj=0;jj<static_cast< s32 >(t_filename_pack_short_list[ii].length());jj++){
							t_all_filename.push_back(t_filename_pack_short_list[ii][jj]);
						}
						t_all_filename.push_back(0x0000);
					}
					t_offset += sizeof(wchar) * t_all_filename.size();

					//�w�b�_�[�T�C�Y�B
					t_header_size = static_cast< s32 >(t_offset);

					{
						//�w�b�_�[�T�C�Y�B
						if(t_filehandle_write.Write(reinterpret_cast< u8* >(&t_header_size),sizeof(t_header_size),t_header_size_offset) == false){
							ASSERT(0);
						}

						//�����B
						if(t_filehandle_write.Write(reinterpret_cast< u8* >(&t_all_count),sizeof(t_all_count),t_all_count_offset) == false){
							ASSERT(0);
						}

						//�e�t�@�C���������T�C�Y�B
						if(t_filehandle_write.Write(reinterpret_cast< u8* >(t_filename_length.get()),sizeof(u16) * t_all_count,t_filename_length_offset) == false){
							ASSERT(0);
						}

						//�e�t�@�C�������ЂƂ܂Ƃ߂ɂ������́B
						if(t_filehandle_write.Write(reinterpret_cast< u8* >(&t_all_filename[0]),sizeof(wchar) * t_all_filename.size(),t_all_filename_offset) == false){
							ASSERT(0);
						}
					}

					{
						for(int ii=0;ii<static_cast< s32 >(t_filename_fullpath_list.size());ii++){
							FileHandle t_filehandle_read;
							t_filehandle_read.ReadOpen(Path::Name(t_filename_fullpath_list[ii]));

							s64 t_filesize_read = t_filehandle_read.GetSize();
							
							//�t�@�C���T�C�Y�B
							t_file_size.get()[ii] = static_cast<u32>(t_filesize_read);

							sharedptr< u8 > t_filedata(new u8[static_cast<s32>(t_filesize_read)],default_delete< u8[] >());

							//�ǂݍ��݁B
							if(t_filehandle_read.Read(t_filedata.get(),t_filesize_read,0) == false){
								ASSERT(0);
							}

							t_filehandle_read.Close();

							//�e�f�[�^�B
							if(t_filehandle_write.Write(reinterpret_cast< u8* >(t_filedata.get()),t_filesize_read,t_offset) == false){
								ASSERT(0);
							}

							t_offset += t_filesize_read;
						}
					}

					{
						//�e�t�@�C���T�C�Y�B
						if(t_filehandle_write.Write(reinterpret_cast< u8* >(t_file_size.get()),sizeof(u32) * t_all_count,t_file_size_offset) == false){
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

