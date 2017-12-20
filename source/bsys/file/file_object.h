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
#include "./file_workitem.h"
#include "./file_convertlock_returntype.h"


/** NBsys::NFile
*/
#if(BSYS_FILE_ENABLE)
namespace NBsys{namespace NFile
{
	/** File_Object
	*/
	class File_Object
	{
	private:

		/** workitem
		*/
		sharedptr<File_WorkItem> workitem;

	public:

		/** constructor
		*/
		File_Object(s32 a_device_index,const STLWString& a_filename_short,s32 a_cachegroup_id,sharedptr<File_Allocator>& a_allocator,s32 a_add_allocatesize);

		/** destructor
		*/
		virtual ~File_Object();

	public:

		/** ロードデータ取得。
		*/
		sharedptr<u8>& GetLoadData();

		/** ロードサイズ取得。
		*/
		s64 GetLoadSize() const;

		/** GetFileNameShort
		*/
		const STLWString& GetFileNameShort() const;

		/** GetAddAllocateSize
		*/
		s32 GetAddAllocateSize() const;

		/** コンバートロック。
		*/
		File_ConvertLock_ReturnType::Id ConvertLock();

		/** コンバートアンロック。
		*/
		void ConvertUnlock();

		/** 処理中。
		*/
		bool IsBusy() const;

		/** エラーコード取得。
		*/
		ErrorCode::Id GetErrorCode() const;

	};


}}
#endif

