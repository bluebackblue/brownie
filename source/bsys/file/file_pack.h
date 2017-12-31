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


/** include
*/
#include "./file_pack_workitem.h"


/** NBsys::NFile
*/
#if((BSYS_FILE_ENABLE)&&(BSYS_FILE_PACK_ENABLE))
namespace NBsys{namespace NFile
{
	/** File_Pack
	*/
	class File_Pack
	{
	private:

		/** パックリスト。
		*/
		STLMap<STLWString,sharedptr<File_Pack_WorkItem>>::Type pack_list;

	private:

		/** copy constructor禁止。
		*/
		File_Pack(const File_Pack& a_this) = delete;

		/** コピー禁止。
		*/
		void operator =(const File_Pack& a_this) = delete;

	public:

		/** constructor
		*/
		File_Pack();

		/** destructor
		*/
		nonvirtual ~File_Pack();

		/** 登録。
		*/
		void Regist(const STLWString& a_pack_filename_short,const sharedptr<File_Pack_WorkItem>& a_workitem);

		/** 解除。
		*/
		void UnRegist(const STLWString& a_pack_filename_short);

		/** 読み込み済みパックのチェック。
		*/
		bool IsExist(const STLWString& a_pack_filename_short);

		/** パックからファイルを開く。
		*/
		sharedptr<File_Pack_FileState>& TryCreatePackFileState(const STLWString& a_filename);

		/** 読み込み。
		*/
		bool ReadFromFileState(const sharedptr<File_Pack_FileState>& a_filestate,u8* a_buffer,s64 a_size,s64 a_offset);

	};


}}
#endif

