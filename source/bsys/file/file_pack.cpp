

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


/** include
*/
#include "./file_pack.h"


/** warning

4710 : The given function was selected for inline expansion, but the compiler did not perform the inlining.

*/
#pragma warning(disable:4710)


/** NBsys::NFile
*/
#if((BSYS_FILE_ENABLE)&&(BSYS_FILE_PACK_ENABLE))
namespace NBsys{namespace NFile
{
	/** constructor
	*/
	File_Pack::File_Pack(LockObject& a_lockobject)
		:
		lockobject(a_lockobject)
	{
	}


	/** destructor
	*/
	File_Pack::~File_Pack()
	{
	}


	/** 登録。
	*/
	void File_Pack::Resist(const sharedptr<File_Pack_WorkItem>& a_workitem)
	{
		//■排他。
		AutoLock t_autolock(this->lockobject);

		this->list.push_back(a_workitem);
	}


	/** 読み込み済みチェック。
	*/
	bool File_Pack::IsExist(const STLWString& a_pack_filename_short)
	{
		//■排他。
		AutoLock t_autolock(this->lockobject);

		auto t_it_end = this->list.cend();
		for(auto t_it = this->list.cbegin();t_it != t_it_end;++t_it){
			if((*t_it)->GetPackFileNameShort() == a_pack_filename_short){
				return true;
			}
		}

		return false;
	}


	/** パックからファイルを開く。
	*/
	sharedptr<File_Pack_FileHandle>& File_Pack::CreatePackFileHandle(const STLWString& a_filename_short)
	{
		//■排他。
		AutoLock t_autolock(this->lockobject);

		auto t_it_end = this->list.end();
		for(auto t_it = this->list.begin();t_it != t_it_end;++t_it){
			sharedptr<File_Pack_FileHandle>& t_pack_filehandle = (*t_it)->FindFromFileNameShort(a_filename_short);
			if(t_pack_filehandle != nullptr){
				return t_pack_filehandle;
			}
		}

		return sharedptr<File_Pack_FileHandle>::null();
	}


}}
#endif

