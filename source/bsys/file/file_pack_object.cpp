

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
#include "./file_pack_object.h"
#include "./file.h"


/** warning

4710 : この関数はインライン展開のために選択されましたが、コンパイラはインライン展開を実行しませんでした。

*/
#pragma warning(disable:4710)


/** NBsys::NFile
*/
#if((BSYS_FILE_ENABLE)&&(BSYS_FILE_PACK_ENABLE))
namespace NBsys{namespace NFile
{
	/** constructor
	*/
	File_Pack_Object::File_Pack_Object(s32 a_device_index,const STLWString& a_pack_filename_short,const STLWString& a_pack_connectto_rootpath_short)
	{
		//ロード開始。
		sharedptr<ThreadTemplate<File_Thread>>& t_instance = GetSystemInstance(a_device_index);
		if(t_instance){
			this->workitem = (*t_instance)->Pack_LoadRequest(Path::Name(a_pack_filename_short),Path::Dir(a_pack_connectto_rootpath_short));
		}else{
			ASSERT(0);
		}
	}


	/** destructor
	*/
	File_Pack_Object::~File_Pack_Object()
	{
		this->workitem.reset();
	}


	/** 処理中。
	*/
	bool File_Pack_Object::IsBusy() const
	{
		return this->workitem->IsBusy();
	}


	/** エラーコード取得。
	*/
	ErrorCode::Id File_Pack_Object::GetErrorCode() const
	{
		return this->workitem->GetErrorCode();
	}


}}
#endif

