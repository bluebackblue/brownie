

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ファイル。
*/


/** include
*/
#include <bsys_pch.h>


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./file_pack.h"


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

		STLList<sharedptr<File_Pack_WorkItem>>::iterator t_it_end = this->list.end();
		for(STLList<sharedptr<File_Pack_WorkItem>>::iterator t_it = this->list.begin();t_it != t_it_end;++t_it){
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

		STLList<sharedptr<File_Pack_WorkItem>>::iterator t_it_end = this->list.end();
		for(STLList<sharedptr<File_Pack_WorkItem>>::iterator t_it = this->list.begin();t_it != t_it_end;++t_it){
			sharedptr<File_Pack_FileHandle>& t_pack_filehandle = (*t_it)->FindFromFileNameShort(a_filename_short);
			if(t_pack_filehandle != nullptr){
				return t_pack_filehandle;
			}
		}

		return sharedptr<File_Pack_FileHandle>::null();
	}


}}
#endif

