

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �t�@�C���B
*/


/** include
*/
#include <bsys_pch.h>


/** include
*/
#include "../types/types.h"


/** NBsys
*/
#include "./file_object.h"
#include "./file.h"
#include "./file_convertlock_returntype.h"


/** NBsys::NFile
*/
#if(BSYS_FILE_ENABLE)
namespace NBsys{namespace NFile
{

	/** constructor
	*/
	File_Object::File_Object(s32 a_device_index,const STLWString& a_filename_short,s32 a_cachegroup_id,sharedptr< File_Allocator >& a_allocator,s32 a_add_allocatesize)
	{
		//���[�h�J�n�B
		sharedptr< ThreadTemplate< File_Thread > >& t_instance = GetSystemInstance(a_device_index);
		this->workitem = (*t_instance)->LoadRequest(Path::Name(a_filename_short),a_cachegroup_id,a_allocator,a_add_allocatesize);
	}

	/** destructor
	*/
	File_Object::~File_Object()
	{
		this->workitem.reset();
	}

	/** �f�[�^�擾�B
	*/
	sharedptr< u8 >& File_Object::GetLoadData()
	{
		return this->workitem->GetData();
	}

	/** ���[�h�T�C�Y�擾�B
	*/
	s64 File_Object::GetLoadSize() const
	{
		return this->workitem->GetSize();
	}

	/** GetFileNameShort
	*/
	const STLWString& File_Object::GetFileNameShort() const
	{
		return this->workitem->GetFileNameShort();
	}

	/** GetAddAllocateSize
	*/
	s32 File_Object::GetAddAllocateSize() const
	{
		return this->workitem->GetAddAllocateSize();
	}

	/** �R���o�[�g���b�N�B
	*/
	File_ConvertLock_ReturnType::Id File_Object::ConvertLock()
	{
		return this->workitem->ConvertLock();
	}

	/** �R���o�[�g�A�����b�N�B
	*/
	void File_Object::ConvertUnlock()
	{
		this->workitem->ConvertUnlock();
	}

	/** �������B
	*/
	bool File_Object::IsBusy() const
	{
		return this->workitem->IsBusy();
	}

	/** �G���[�R�[�h�擾�B
	*/
	ErrorCode::Id File_Object::GetErrorCode() const
	{
		return this->workitem->GetErrorCode();
	}
}}
#endif

