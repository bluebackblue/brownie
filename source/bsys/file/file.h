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
#include "./file_thread.h"
#include "./file_pack_makethread.h"
#include "./file_object.h"
#include "./file_pack_object.h"


/** NBsys::NFile
*/
#if(BSYS_FILE_ENABLE)
namespace NBsys{namespace NFile
{
	/** システムの開始。
	*/
	void StartSystem(s32 a_device_max);


	/** ルート設定。
	*/
	void SetRoot(s32 a_device_index,const STLWString& a_rootpath_full);


	/** システムのインスタンス取得。
	*/
	sharedptr<ThreadTemplate<File_Thread>>& GetSystemInstance(s32 a_device_index);


	/** リークチェック。
	*/
	void LeakCheck();


	/** キャッシュクリア。
	*/
	void CacheClear(s32 a_device_index,s32 a_cachegroup_id);


	/** システムの終了リクエスト。
	*/
	void EndSystemRequest();


	/** システムの終了待ち。
	*/
	void EndWaitSystem();


	/** [パック]作成。
	*/
	#if(BSYS_FILE_PACK_ENABLE)
	sharedptr<ThreadTemplate<NBsys::NFile::File_Pack_MakeThread>> Pack_Create(const STLWString& a_rootpath_full,const STLWString& a_pack_filename_full,const sharedptr<File_Allocator>& a_allocator);
	#endif


	/** [パック]アンロードリクエスト。
	*/
	#if(BSYS_FILE_PACK_ENABLE)
	void Pack_UnLoad(s32 a_device_index,const STLWString& a_pack_filename_short);
	#endif

	/** [パック]読み込み済みチェック。
	*/
	#if(BSYS_FILE_PACK_ENABLE)
	bool Pack_IsExist(s32 a_device_index,const STLWString& a_pack_filename_short);
	#endif


}}
#endif

