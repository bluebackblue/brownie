#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ファイルハンドル。
*/


/** include
*/
#include "./types.h"
#include "./platform.h"


/** include
*/
#include "./sharedptr.h"
#include "./stlstring.h"


/** NBlib
*/
namespace NBlib
{
	/** FileHandle_Impl
	*/
	class FileHandle_Impl;

	/** FileHandle
	*/
	class FileHandle
	{
	private:
		/** impl
		*/
		sharedptr< FileHandle_Impl > impl;

	public:
		/** GetImpl
		*/
		sharedptr< FileHandle_Impl >& GetImpl();

	public:
		/** constructor
		*/
		FileHandle();

		/** destructor
		*/
		nonvirtual ~FileHandle();

	public:
		
		/** 読み込みモードで開く。
		*/
		bool ReadOpen(const STLWString& a_filename);

		/** 書き込みモードで開く。
		*/
		bool WriteOpen(const STLWString& a_filename);

		/** 閉じる。
		*/
		void Close();

		/** 読み込み。
		*/
		bool Read(u8* a_buffer,s64 a_size,s64 a_offset);

		/** 書き込み。
		*/
		bool Write(const u8* a_buffer,s64 a_size,s64 a_offset);

		/** ファイルサイズ取得。
		*/
		s64 GetSize() const;

		/** ファイルオープンチェック。
		*/
		bool IsOpen() const;

		/** ＥＯＦ設定。
		*/
		void SetEOF(s64 a_offset);

	};
}

