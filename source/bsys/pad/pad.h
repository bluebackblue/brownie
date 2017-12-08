#pragma once

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �p�b�h�B
*/


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./pad_list.h"
#include "./pad_device_base.h"
#include "./pad_virtual.h"


/** NBsys::NPad
*/
namespace NBsys{namespace NPad
{
	/** �V�X�e���̊J�n�B
	*/
	void StartSystem(s32 a_virtualpad_max);

	/** �V�X�e���̃C���X�^���X�擾�B
	*/
	sharedptr<Pad_List>& GetSystemInstance();

	/** �f�o�C�X�ǉ��B
	*/
	void AddDevice(sharedptr<Pad_Device_Base>& a_device_instance);

	/** ���z�p�b�h�擾�B
	*/
	sharedptr<Pad_Virtual>& GetVirtualPad(s32 a_virtualpad_index);

	/** �X�V�B
	*/
	void Update(bool a_device_update);

	/** �V�X�e���̏I���B
	*/
	void EndSystem();
}}

