

/**
 * Copyright (c) blueback
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
	File_Pack::File_Pack()
	{
	}


	/** destructor
	*/
	File_Pack::~File_Pack()
	{
	}


	/** 登録。
	*/
	void File_Pack::Regist(const STLWString& a_pack_filename_short,const sharedptr<File_Pack_WorkItem>& a_workitem)
	{
		this->pack_list.insert(std::make_pair(a_pack_filename_short,a_workitem));
	}


	/** 解除。
	*/
	void File_Pack::UnRegist(const STLWString& a_pack_filename_short)
	{
		auto t_it = std::as_const(this->pack_list).find(a_pack_filename_short);
		if(t_it != this->pack_list.cend()){
			this->pack_list.erase(t_it);
		}
	}


	/** 読み込み済みチェック。
	*/
	bool File_Pack::IsExist(const STLWString& a_pack_filename_short)
	{
		auto t_it = std::as_const(this->pack_list).find(a_pack_filename_short);
		if(t_it != this->pack_list.cend()){
			return true;
		}
		return false;
	}


	/** パックからファイルを開く。
	*/
	sharedptr<File_Pack_FileState>& File_Pack::TryCreatePackFileState(const STLWString& a_filename_short)
	{
		auto t_it_end = this->pack_list.end();
		for(auto t_it = this->pack_list.begin();t_it != t_it_end;++t_it){
			sharedptr<File_Pack_FileState>& t_pack_filehandle = t_it->second->FindFromFileNameShort(a_filename_short);
			if(t_pack_filehandle != nullptr){
				return t_pack_filehandle;
			}
		}

		return sharedptr<File_Pack_FileState>::null();
	}

	/** 読み込み。
	*/
	bool File_Pack::ReadFromFileState(const sharedptr<File_Pack_FileState>& a_filestate,u8* a_buffer,s64 a_size,s64 a_offset)
	{
		return a_filestate->parent->Read(a_filestate,a_buffer,a_size,a_offset);
	}

}}
#endif

