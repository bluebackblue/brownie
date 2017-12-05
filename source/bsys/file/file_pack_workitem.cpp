

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
		//��[����]����B
		{
			this->filehandle.Close();
		}
	}

	/** �G���[�R�[�h�擾�B
	*/
	ErrorCode::Id File_Pack_WorkItem::GetErrorCode() const
	{
		return this->errorcode;
	}

	/** �p�b�N�t�@�C�����擾�B
	*/
	const STLWString& File_Pack_WorkItem::GetPackFileNameShort()
	{
		return this->pack_filename_short;
	}

	/** �t�@�C�������B
	*/
	sharedptr<File_Pack_FileHandle>& File_Pack_WorkItem::FindFromFileNameShort(const STLWString& a_filename_short)
	{
		STLMap<STLWString,sharedptr<File_Pack_FileHandle>>::iterator t_it = this->filelist.find(a_filename_short);
		if(t_it != this->filelist.end()){
			return t_it->second;
		}
		return sharedptr<File_Pack_FileHandle>::null();
	}

	/** [�X���b�h����]�X�V�B

		@return : true = ���� / false = ��ƒ�

	*/
	bool File_Pack_WorkItem::Update(const STLWString& a_rootpath_full)
	{
		switch(this->mainstep){
		case MainStep::Open:
			{
				//�J���B

				STLWString t_pack_filename_full = Path::DirAndName(a_rootpath_full,this->pack_filename_short);

				bool t_ret_open = false;
				{
					//��[����]�J���B
					t_ret_open = this->filehandle.ReadOpen(t_pack_filename_full);
				}

				if(t_ret_open){

					//��[����]�t�@�C���T�C�Y�B
					{
						this->data_size = this->filehandle.GetSize();
					}

					{
						if(this->data_size > 0LL){
							this->mainstep = MainStep::Read;
							break;
						}else{
							//�t�@�C���T�C�Y�擾�Ɏ��s�B
							this->errorcode = ErrorCode::Load_OpenError;
							this->mainstep = MainStep::Error;
						}
					}
				}else{
					//�t�@�C�����J���̂Ɏ��s�B
					this->errorcode = ErrorCode::Load_OpenError;
					this->mainstep = MainStep::Error;
					break;
				}
			}break;
		case MainStep::Read:
			{
				//�ǂݍ��ށB

				s64 t_offset = 0;

				//�w�b�_�[�T�C�Y�B
				u32 t_header_size = 0;
				this->filehandle.Read(reinterpret_cast<u8*>(&t_header_size),sizeof(u32),0);
				t_offset += sizeof(u32);

				//�w�b�_�[�f�[�^�B
				sharedptr<u8> t_header(new u8[t_header_size],default_delete<u8[]>());
				this->filehandle.Read(t_header.get(),t_header_size,0);

				//�����B
				u32 t_all_count = 0;
				Memory::memcpy(&t_all_count,sizeof(u32),&t_header.get()[t_offset],sizeof(u32));
				t_offset += sizeof(u32);

				//�e�t�@�C���T�C�Y�B
				sharedptr<u32> t_file_size(new u32[t_all_count]);
				Memory::memcpy(t_file_size.get(),sizeof(u32) * t_all_count,&t_header.get()[t_offset],sizeof(u32) * t_all_count);
				t_offset += sizeof(u32) * t_all_count;

				//�e�t�@�C���������T�C�Y�B
				sharedptr<u16> t_filename_length(new u16[t_all_count]);
				Memory::memcpy(t_filename_length.get(),sizeof(u16) * t_all_count,&t_header.get()[t_offset],sizeof(u16) * t_all_count);
				t_offset += sizeof(u16) * t_all_count;

				//�e�t�@�C�������܂Ƃ߂����́B
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
					//�����B
					return true;
				}
			}break;
		case MainStep::Error:
			{
				//��[����]����B
				{
					this->filehandle.Close();
				}

				{
					//�G���[�����B
					return true;
				}
			}break;
		}

		ThreadSleep(0);

		return false;
	}

}}
#endif

