

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �f�B���N�g���n���h���B
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
	sharedptr< DirectoryHandle_Impl >& DirectoryHandle::GetImpl()
	{
		return this->impl;
	}

	/** destructor
	*/
	DirectoryHandle::~DirectoryHandle()
	{
		this->impl.reset();
	}
	
	/** �J���B
	*/
	bool DirectoryHandle::Open(const STLWString& a_directoryname)
	{
		return this->impl->Open(a_directoryname);
	}

	/** ����B
	*/
	void DirectoryHandle::Close()
	{
		return this->impl->Close();
	}

	/** �T�C�Y�B
	*/
	s32 DirectoryHandle::GetSize()
	{
		return this->impl->GetSize();
	}

	/** �擾�B
	*/
	DirectoryHandle::DirectoryItem& DirectoryHandle::GetItem(s32 a_index)
	{
		return this->impl->GetItem(a_index);
	}

	/** �t���p�X�擾�B
	*/
	STLWString& DirectoryHandle::GetFullPath()
	{
		return this->impl->GetFullPath();
	}

}

