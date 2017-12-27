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

		/** ロックオブジェクト。
		*/
		LockObject& lockobject;

		/** パックリスト。
		*/
		STLList<sharedptr<File_Pack_WorkItem>>::Type list;

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
		File_Pack(LockObject& a_lockobject);

		/** destructor
		*/
		nonvirtual ~File_Pack();

		/** 登録。
		*/
		void Resist(const sharedptr<File_Pack_WorkItem>& a_workitem);

		/** 読み込み済みパックのチェック。
		*/
		bool IsExist(const STLWString& a_pack_filename_short);

		/** パックからファイルを開く。
		*/
		sharedptr<File_Pack_FileHandle>& CreatePackFileHandle(const STLWString& a_filename);

	};


}}
#endif

