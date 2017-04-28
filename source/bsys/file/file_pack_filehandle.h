#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �t�@�C���B
*/


/** include
*/
#include "../types/types.h"


/** NBsys::NFile
*/
#if(BSYS_FILE_PACK_ENABLE)
namespace NBsys{namespace NFile
{

	/** File_Pack_FileHandle
	*/
	class File_Pack_FileHandle
	{
	private:

		/** �t�@�C���n���h���B
		*/
		FileHandle filehandle;

		/** �f�[�^�T�C�Y�B
		*/
		s64 data_size;

		/** �f�[�^�I�t�Z�b�g�B
		*/
		s64 data_offset;

	public:
		/** constructor
		*/
		explicit File_Pack_FileHandle(FileHandle& a_filehandle,s64 a_data_size,s64 a_data_offset);

		/** destructor
		*/
		nonvirtual ~File_Pack_FileHandle();

	public:

		/** �t�@�C���T�C�Y�擾�B
		*/
		s64 GetSize();

		/** �ǂݍ��݁B
		*/
		bool Read(u8* a_buffer,s64 a_size,s64 a_offset);

	};

}}
#endif

