#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ファイル。
*/


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./file_allocator.h"
#include "./file_thread_decl.h"
#include "./file_pack_filehandle.h"
#include "./file_convertlock_returntype.h"


/** NBsys::NFile
*/
#if(BSYS_FILE_ENABLE)
namespace NBsys{namespace NFile
{
	/** File_WorkItem
	*/
	class File_WorkItem
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

		/** Mode
		*/
		struct Mode
		{
			enum Id
			{
				None = 0,
				Normal,
				Pack,
			};
		};

		LockObject& lockobject;

		/** メインステップ。
		*/
		MainStep::Id mainstep;

		/** mode
		*/
		Mode::Id mode;

		/** ファイルハンドル。
		*/
		#if(BSYS_FILE_PACK_ENABLE)
		sharedptr<File_Pack_FileHandle> pack_filehandle;
		#endif

		/** ファイルハンドル。
		*/
		FileHandle normal_filehandle;

		/** ファイル名。
		*/
		STLWString filename_short;

		/** データ。
		*/
		sharedptr<u8> data;

		/** コンバートフラグ。
		*/
		s32 convertflag;

		/** データサイズ。
		*/
		s64 data_size;

		/** オフセット。
		*/
		s64 data_offset;
		
		/** エラーコード。
		*/
		ErrorCode::Id errorcode;

		/** 処理中。
		*/
		bool isbusy;

		/** メモリ確保。
		*/
		sharedptr<File_Allocator> allocator;

		/** メモリ確保時に余分に確保するサイズ。
		*/
		s32 add_allocatesize;

	public:

		/** constructor
		*/
		File_WorkItem(LockObject& a_lockobject,const STLWString& a_filename_short,sharedptr<File_Allocator>& a_allocator,s32 a_add_allocatesize);

		/** destructor
		*/
		nonvirtual ~File_WorkItem();

	public:

		/** GetData
		*/
		sharedptr<u8>& GetData();

		/** GetSize
		*/
		s64 GetSize() const;

		/** GetAddAllocateSize
		*/
		s32 GetAddAllocateSize() const;

		/** IsBusy
		*/
		bool IsBusy() const;

		/** GetFilenameShort
		*/
		const STLWString& GetFileNameShort() const;

		/** コンバートロック。
		*/
		File_ConvertLock_ReturnType::Id ConvertLock();

		/** コンバートアンロック。
		*/
		void ConvertUnlock();

	public:

		/** 更新。
		*/
		bool Update(File_Thread& a_thread,const STLWString& a_rootpath_full,bool a_cancel);

		/** エラーコード。
		*/
		ErrorCode::Id GetErrorCode() const;

	};


}}
#endif

