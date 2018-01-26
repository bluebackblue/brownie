#pragma once

/**
 * Copyright (c) blueback
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
#include "./file_allocator.h"


/** NBsys::NFile
*/
#if(BSYS_FILE_ENABLE)
namespace NBsys{namespace NFile
{
	/** File_Pack_Object
	*/
	class File_Pack_Object
	{
	private:

		/** workitem
		*/
		sharedptr<File_Pack_WorkItem> workitem;

	public:

		/** constructor

		a_device_index						: デバイスインデックス。
		a_pack_filename_short				: ルートパスからの相対パスでパックファイルを指定。
		a_pack_connectto_rootpath_short		: ルートパスからの相対パスで接続先を指定。

		*/
		File_Pack_Object(s32 a_device_index,const STLWString& a_pack_filename_short,const STLWString& a_pack_connectto_rootpath_short);

		/** destructor
		*/
		virtual ~File_Pack_Object();

	public:

		/** 処理中。
		*/
		bool IsBusy() const;

		/** エラーコード取得。
		*/
		ErrorCode::Id GetErrorCode() const;

	};


}}
#endif

