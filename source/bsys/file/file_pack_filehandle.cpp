

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
#include "./file_pack_filehandle.h"


/** warning

4710 : The given function was selected for inline expansion, but the compiler did not perform the inlining.

*/
#pragma warning(disable:4710)


/** NBsys::NFile
*/
#if((BSYS_FILE_ENABLE)&&(BSYS_FILE_PACK_ENABLE))
namespace NBsys{namespace NFile
{
	/** constructor
	*/
	File_Pack_FileHandle::File_Pack_FileHandle(FileHandle& a_filehandle,s64 a_data_size,s64 a_data_offset)
		:
		filehandle(a_filehandle),
		data_size(a_data_size),
		data_offset(a_data_offset)
	{
	}


	/** destructor
	*/
	File_Pack_FileHandle::~File_Pack_FileHandle()
	{
	}


	/** ファイルサイズ取得。
	*/
	s64 File_Pack_FileHandle::GetSize()
	{
		return this->data_size;
	}


	/** 読み込み。
	*/
	bool File_Pack_FileHandle::Read(u8* a_buffer,s64 a_size,s64 a_offset)
	{
		return this->filehandle.Read(a_buffer,a_size,this->data_offset + a_offset);
	}


}}
#endif

