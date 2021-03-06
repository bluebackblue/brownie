﻿#pragma once

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ディレクトリハンドル。
*/


/** include
*/
#include "./types.h"
#include "./platform.h"


/** include
*/
#include "./sharedptr.h"
#include "./stlstring.h"
#include "./errorcode.h"


/** NBlib
*/
namespace NBlib
{
	/** DirectoryHandle_Impl
	*/
	class DirectoryHandle_Impl;


	/** DirectoryHandle
	*/
	class DirectoryHandle
	{
	private:

		/** impl
		*/
		sharedptr<DirectoryHandle_Impl> impl;

	public:

		/** GetImpl
		*/
		sharedptr<DirectoryHandle_Impl>& GetImpl();

	public:

		/** DirectoryItem
		*/
		struct DirectoryItem
		{
			/** 名前。
			*/
			STLWString name;

			/** ディレクトリフラグ。
			*/
			bool is_directory;

			/** padding
			*/
			padding64(0,7);
			padding32(0,3);
		};

	public:

		/** constructor
		*/
		DirectoryHandle();

		/** destructor
		*/
		nonvirtual ~DirectoryHandle();

	public:
		
		/** 開く。
		*/
		bool Open(const STLWString& a_directoryname);

		/** 閉じる。
		*/
		void Close();

		/** サイズ。
		*/
		s32 GetSize();

		/** 取得。
		*/
		DirectoryHandle::DirectoryItem& GetItem(s32 a_index);

		/** フルパス取得。
		*/
		STLWString& GetFullPath();

		/** ディレクトリ作成。
		*/
		ErrorCode::Id MakeDirectory(const STLWString& a_directoryname);

	};


}

