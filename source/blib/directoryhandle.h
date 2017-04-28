#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �f�B���N�g���n���h���B
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
		sharedptr< DirectoryHandle_Impl > impl;

	public:
		/** GetImpl
		*/
		const sharedptr< DirectoryHandle_Impl >& GetImpl() const;

	public:
		/** DirectoryItem
		*/
		struct DirectoryItem
		{
			/** ���O�B
			*/
			STLWString name;

			/** �f�B���N�g���t���O�B
			*/
			bool is_directory;
		};

	public:
		/** constructor
		*/
		DirectoryHandle();

		/** destructor
		*/
		nonvirtual ~DirectoryHandle();

	public:
		
		/** �J���B
		*/
		bool Open(const STLWString& a_directoryname);

		/** ����B
		*/
		void Close();

		/** �T�C�Y�B
		*/
		s32 GetSize();

		/** �擾�B
		*/
		DirectoryHandle::DirectoryItem& GetItem(s32 a_index);

		/** �t���p�X�擾�B
		*/
		STLWString& GetFullPath();

	};
}

