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
#include "./file_pack_filestate.h"
#include "./file_thread_decl.h"


/** NBsys::NFile
*/
#if((BSYS_FILE_ENABLE)&&(BSYS_FILE_PACK_ENABLE))
#pragma warning(push)
#pragma warning(disable:4820)
namespace NBsys{namespace NFile
{
	/** File_Pack_WorkItem
	*/
	class File_Pack_WorkItem
	{
	private:

		/** MainStep
		*/
		struct MainStep
		{
			enum Id
			{
				None = 0,
				Open,
				Read,
				End,
				Error,
			};
		};

		/** lockobject
		*/
		mutable LockObject lockobject;

		/** メインステップ。
		*/
		MainStep::Id mainstep;

		/** ファイルハンドル。
		*/
		FileHandle filehandle;

		/** パックファイル名。
		*/
		STLWString pack_filename_short;

		/** パックルートパス。
		*/
		STLWString pack_rootpath_short;

		/** データサイズ。
		*/
		s64 data_size;

		/** エラーコード。
		*/
		ErrorCode::Id errorcode;

		/** 処理中。
		*/
		AtomicValue<bool> isbusy;

		/** filestate_list
		*/
		STLMap<STLWString,sharedptr<File_Pack_FileState>>::Type filestate_list;

	public:

		/** constructor
		*/
		explicit File_Pack_WorkItem(const STLWString& a_pack_filename_short,const STLWString& a_pack_rootpath_short);

		/** destructor
		*/
		nonvirtual ~File_Pack_WorkItem();

	private:

		/** copy constructor禁止。
		*/
		File_Pack_WorkItem(const File_Pack_WorkItem& a_this) = delete;

		/** コピー禁止。
		*/
		void operator =(const File_Pack_WorkItem& a_this) = delete;

	public:

		/** エラーコード取得。
		*/
		ErrorCode::Id GetErrorCode() const;

		/** IsBusy
		*/
		bool IsBusy() const;

		/** パックファイル名取得。
		*/
		const STLWString& GetPackFileNameShort() const;

		/** ファイル検索。
		*/
		sharedptr<File_Pack_FileState>& FindFromFileNameShort(const STLWString& a_filename_short);

		/** 読み込み。
		*/
		bool Read(const sharedptr<File_Pack_FileState>& a_filestate,u8* a_buffer,s64 a_size,s64 a_offset);

		/** 更新。
		*/
		bool Update(File_Thread& a_thread,const STLWString& a_rootpath_full);

	};


}}
#pragma warning(pop)
#endif

