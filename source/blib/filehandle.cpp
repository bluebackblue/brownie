

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ファイルハンドル。
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
#include "./filehandle.h"
#include "./filehandle_impl.h"
#include "./stlstring.h"


/** NBlib
*/
namespace NBlib
{
	/** constructor
	*/
	FileHandle::FileHandle()
	{
		this->impl.reset(new FileHandle_Impl());
	}


	/** GetImpl
	*/
	sharedptr<FileHandle_Impl>& FileHandle::GetImpl()
	{
		return this->impl;
	}


	/** destructor
	*/
	FileHandle::~FileHandle()
	{
		this->impl.reset();
	}
	

	/** 読み込みモードで開く。
	*/
	bool FileHandle::ReadOpen(const STLWString& a_filename)
	{
		return this->impl->ReadOpen(a_filename);
	}


	/** 書き込みモードで開く。
	*/
	bool FileHandle::WriteOpen(const STLWString& a_filename)
	{
		return this->impl->WriteOpen(a_filename);
	}


	/** 閉じる。
	*/
	void FileHandle::Close()
	{
		return this->impl->Close();
	}


	/** 読み込み。
	*/
	bool FileHandle::Read(u8* a_buffer,s64 a_size,s64 a_offset)
	{
		return this->impl->Read(a_buffer,a_size,a_offset);
	}


	/** 書き込み。
	*/
	bool FileHandle::Write(const u8* a_buffer,s64 a_size,s64 a_offset)
	{
		return this->impl->Write(a_buffer,a_size,a_offset);
	}


	/** ファイルサイズ取得。
	*/
	s64 FileHandle::GetSize() const
	{
		return this->impl->GetSize();
	}


	/** ファイルオープンチェック。
	*/
	bool FileHandle::IsOpen() const
	{
		return this->impl->IsOpen();
	}


	/** ＥＯＦ設定。
	*/
	void FileHandle::SetEOF(s64 a_offset)
	{
		this->impl->SetEOF(a_offset);
	}


}

