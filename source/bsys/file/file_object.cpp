

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


/** NBsys
*/
#include "./file_object.h"
#include "./file.h"
#include "./file_convertlock_returntype.h"


/** NBsys::NFile
*/
#if(BSYS_FILE_ENABLE)
namespace NBsys{namespace NFile
{
	/** constructor
	*/
	File_Object::File_Object(s32 a_device_index,const STLWString& a_filename_short,s32 a_cachegroup_id,const sharedptr<File_Allocator>& a_allocator,s32 a_add_allocatesize)
	{
		//ロード開始。
		sharedptr<ThreadTemplate<File_Thread>>& t_instance = GetSystemInstance(a_device_index);
		if(t_instance){
			this->workitem = (*t_instance)->LoadRequest(Path::Name(a_filename_short),a_cachegroup_id,a_allocator,a_add_allocatesize);
		}else{
			ASSERT(0);
		}
	}


	/** destructor
	*/
	File_Object::~File_Object()
	{
		this->workitem.reset();
	}


	/** データ取得。
	*/
	sharedptr<u8>& File_Object::GetLoadData()
	{
		return this->workitem->GetData();
	}


	/** ロードサイズ取得。
	*/
	s64 File_Object::GetLoadSize() const
	{
		return this->workitem->GetSize();
	}


	/** GetFileNameShort
	*/
	const STLWString& File_Object::GetFileNameShort() const
	{
		return this->workitem->GetFileNameShort();
	}


	/** GetAddAllocateSize
	*/
	s32 File_Object::GetAddAllocateSize() const
	{
		return this->workitem->GetAddAllocateSize();
	}


	/** コンバートロック。
	*/
	File_ConvertLock_ReturnType::Id File_Object::ConvertLock()
	{
		return this->workitem->ConvertLock();
	}


	/** コンバートアンロック。
	*/
	void File_Object::ConvertUnlock()
	{
		this->workitem->ConvertUnlock();
	}


	/** 処理中。
	*/
	bool File_Object::IsBusy() const
	{
		return this->workitem->IsBusy();
	}


	/** エラーコード取得。
	*/
	ErrorCode::Id File_Object::GetErrorCode() const
	{
		return this->workitem->GetErrorCode();
	}


}}
#endif

