

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ディレクトリハンドル。
*/


/** include
*/
#include <blib_pch.h>


/** include
*/
#include "./types.h"
#include "./platform.h"


/** include
*/
#include "./sharedptr.h"
#include "./directoryhandle.h"
#include "./directoryhandle_impl.h"
#include "./stlstring.h"


/** NBlib
*/
namespace NBlib
{
	/** constructor
	*/
	DirectoryHandle::DirectoryHandle()
	{
		this->impl.reset(new DirectoryHandle_Impl());
	}


	/** GetImpl
	*/
	sharedptr<DirectoryHandle_Impl>& DirectoryHandle::GetImpl()
	{
		return this->impl;
	}


	/** destructor
	*/
	DirectoryHandle::~DirectoryHandle()
	{
		this->impl.reset();
	}

	
	/** 開く。
	*/
	bool DirectoryHandle::Open(const STLWString& a_directoryname)
	{
		return this->impl->Open(a_directoryname);
	}


	/** 閉じる。
	*/
	void DirectoryHandle::Close()
	{
		return this->impl->Close();
	}


	/** サイズ。
	*/
	s32 DirectoryHandle::GetSize()
	{
		return this->impl->GetSize();
	}


	/** 取得。
	*/
	DirectoryHandle::DirectoryItem& DirectoryHandle::GetItem(s32 a_index)
	{
		return this->impl->GetItem(a_index);
	}


	/** フルパス取得。
	*/
	STLWString& DirectoryHandle::GetFullPath()
	{
		return this->impl->GetFullPath();
	}


}

