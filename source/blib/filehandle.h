#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �t�@�C���n���h���B
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
		
		/** �ǂݍ��݃��[�h�ŊJ���B
		*/
		bool ReadOpen(const STLWString& a_filename);

		/** �������݃��[�h�ŊJ���B
		*/
		bool WriteOpen(const STLWString& a_filename);

		/** ����B
		*/
		void Close();

		/** �ǂݍ��݁B
		*/
		bool Read(u8* a_buffer,s64 a_size,s64 a_offset);

		/** �������݁B
		*/
		bool Write(const u8* a_buffer,s64 a_size,s64 a_offset);

		/** �t�@�C���T�C�Y�擾�B
		*/
		s64 GetSize() const;

		/** �t�@�C���I�[�v���`�F�b�N�B
		*/
		bool IsOpen() const;

		/** �d�n�e�ݒ�B
		*/
		void SetEOF(s64 a_offset);

	};
}

