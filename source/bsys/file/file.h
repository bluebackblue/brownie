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
#include "./file_thread.h"
#include "./file_pack_makethread.h"


/** NBsys::NFile
*/
#if(BSYS_FILE_ENABLE)
namespace NBsys{namespace NFile
{
	/** �V�X�e���̊J�n�B
	*/
	void StartSystem(s32 a_device_max);

	/** ���[�g�ݒ�B
	*/
	void SetRoot(s32 a_device_index,const STLWString& a_rootpath_full);

	/** �V�X�e���̃C���X�^���X�擾�B
	*/
	sharedptr<ThreadTemplate<File_Thread>>& GetSystemInstance(s32 a_device_index);

	/** ���[�N�`�F�b�N�B
	*/
	void LeakCheck();

	/** �L���b�V���N���A�B
	*/
	void CacheClear(s32 a_device_index,s32 a_cachegroup_id);

	/** �V�X�e���̏I�����N�G�X�g�B
	*/
	void EndSystemRequest();

	/** �V�X�e���̏I���҂��B
	*/
	void EndWaitSystem();

	/** [�p�b�N]�쐬�B
	*/
	#if(BSYS_FILE_PACK_ENABLE)
	sharedptr<ThreadTemplate<File_Pack_MakeThread>> Pack_Create(const STLWString& a_rootpath_full,const STLWString& a_pack_filename_full,const sharedptr<File_Allocator>& a_allocator);
	#endif

	/** [�p�b�N]���[�h���N�G�X�g�B
	*/
	#if(BSYS_FILE_PACK_ENABLE)
	void Pack_LoadRequest(s32 a_device_index,const STLWString& a_pack_filename_short,const STLWString& a_pack_rootpath_short);
	#endif

	/** [�p�b�N]�ǂݍ��ݍς݃`�F�b�N�B
	*/
	#if(BSYS_FILE_PACK_ENABLE)
	bool Pack_IsExist(s32 a_device_index,const STLWString& a_pack_filename_short);
	#endif

}}
#endif
