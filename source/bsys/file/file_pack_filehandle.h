#pragma once

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ファイル。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** NBsys::NFile
*/
#if((BSYS_FILE_ENABLE)&&(BSYS_FILE_PACK_ENABLE))
namespace NBsys{namespace NFile
{
	/** File_Pack_FileHandle
	*/
	class File_Pack_FileHandle
	{
	private:

		/** ファイルハンドル。
		*/
		FileHandle filehandle;

		/** データサイズ。
		*/
		s64 data_size;

		/** データオフセット。
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

		/** ファイルサイズ取得。
		*/
		s64 GetSize();

		/** 読み込み。
		*/
		bool Read(u8* a_buffer,s64 a_size,s64 a_offset);

	};


}}
#endif

