#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �t�@�C���B
*/


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./file_allocator.h"
#include "./file_thread_decl.h"
#include "./file_pack_filehandle.h"
#include "./file_convertlock_returntype.h"


/** NBsys::NFile
*/
#if(BSYS_FILE_ENABLE)
namespace NBsys{namespace NFile
{
	/** File_WorkItem
	*/
	class File_WorkItem
	{
	private:

		/** MainStep
		*/
		struct MainStep
		{
			enum Id
			{
				None = 0,
				Open,
				Read,
				End,
				Error,
			};
		};

		/** Mode
		*/
		struct Mode
		{
			enum Id
			{
				None = 0,
				Normal,
				Pack,
			};
		};

		LockObject& lockobject;

		/** ���C���X�e�b�v�B
		*/
		MainStep::Id mainstep;

		/** mode
		*/
		Mode::Id mode;

		/** �t�@�C���n���h���B
		*/
		#if(BSYS_FILE_PACK_ENABLE)
		sharedptr< File_Pack_FileHandle > pack_filehandle;
		#endif

		/** �t�@�C���n���h���B
		*/
		FileHandle normal_filehandle;

		/** �t�@�C�����B
		*/
		STLWString filename_short;

		/** �f�[�^�B
		*/
		sharedptr< u8 > data;

		/** �R���o�[�g�t���O�B
		*/
		s32 convertflag;

		/** �f�[�^�T�C�Y�B
		*/
		s64 data_size;

		/** �I�t�Z�b�g�B
		*/
		s64 data_offset;
		
		/** �G���[�R�[�h�B
		*/
		ErrorCode::Id errorcode;

		/** �������B
		*/
		bool isbusy;

		/** �������m�ہB
		*/
		sharedptr< File_Allocator > allocator;

		/** �������m�ێ��ɗ]���Ɋm�ۂ���T�C�Y�B
		*/
		s32 add_allocatesize;

	public:
		/** constructor
		*/
		File_WorkItem(LockObject& a_lockobject,const STLWString& a_filename_short,sharedptr< File_Allocator >& a_allocator,s32 a_add_allocatesize);

		/** destructor
		*/
		nonvirtual ~File_WorkItem();

	public:
		/** GetData
		*/
		sharedptr< u8 >& GetData();

		/** GetSize
		*/
		s64 GetSize() const;

		/** GetAddAllocateSize
		*/
		s32 GetAddAllocateSize() const;

		/** IsBusy
		*/
		bool IsBusy() const;

		/** GetFilenameShort
		*/
		const STLWString& GetFileNameShort() const;

		/** �R���o�[�g���b�N�B
		*/
		File_ConvertLock_ReturnType::Id ConvertLock();

		/** �R���o�[�g�A�����b�N�B
		*/
		void ConvertUnlock();

	public:
		/** �X�V�B
		*/
		bool Update(File_Thread& a_thread,const STLWString& a_rootpath_full,bool a_cancel);

		/** �G���[�R�[�h�B
		*/
		ErrorCode::Id GetErrorCode() const;

	};

}}
#endif
