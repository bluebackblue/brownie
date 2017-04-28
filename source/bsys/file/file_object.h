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
#include "./file_workitem.h"
#include "./file_convertlock_returntype.h"


/** NBsys::NFile
*/
#if(BSYS_FILE_ENABLE)
namespace NBsys{namespace NFile
{

	/** File_Object
	*/
	class File_Object
	{
	private:
		sharedptr< File_WorkItem > workitem;

	public:
		/** constructor
		*/
		File_Object(s32 a_device_index,const STLWString& a_filename_short,s32 a_cachegroup_id,sharedptr< File_Allocator >& a_allocator,s32 a_add_allocatesize);

		/** destructor
		*/
		virtual ~File_Object();

	public:
		/** ���[�h�f�[�^�擾�B
		*/
		sharedptr< u8 >& GetLoadData();

		/** ���[�h�T�C�Y�擾�B
		*/
		s64 GetLoadSize() const;

		/** GetFileNameShort
		*/
		const STLWString& GetFileNameShort() const;

		/** GetAddAllocateSize
		*/
		s32 GetAddAllocateSize() const;

		/** �R���o�[�g���b�N�B
		*/
		File_ConvertLock_ReturnType::Id ConvertLock();

		/** �R���o�[�g�A�����b�N�B
		*/
		void ConvertUnlock();

		/** �������B
		*/
		bool IsBusy() const;

		/** �G���[�R�[�h�擾�B
		*/
		ErrorCode::Id GetErrorCode() const;

	};
}}
#endif

