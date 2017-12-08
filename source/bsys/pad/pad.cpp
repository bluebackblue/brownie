

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �p�b�h�B
*/


/** include
*/
#include <bsys_pch.h>


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./pad.h"
#include "./pad_list.h"


/** NBsys::NPad
*/
namespace NBsys{namespace NPad
{
	/** s_thread
	*/
	sharedptr<Pad_List> s_instance;

	/** �V�X�e���̊J�n�B
	*/
	void StartSystem(s32 a_virtualpad_max)
	{
		if(s_instance == nullptr){
			s_instance.reset(new Pad_List(a_virtualpad_max));
		}else{
			ASSERT(0);
		}
	}

	/** �V�X�e���̃C���X�^���X�擾�B
	*/
	sharedptr<Pad_List>& GetSystemInstance()
	{
		return s_instance;
	}

	/** �f�o�C�X�ǉ��B
	*/
	void AddDevice(sharedptr<Pad_Device_Base>& a_device_instance)
	{
		if(s_instance != nullptr){
			s_instance->AddDevice(a_device_instance);
		}else{
			ASSERT(0);
		}
	}

	/** ���z�p�b�h�擾�B
	*/
	sharedptr<Pad_Virtual>& GetVirtualPad(s32 a_virtualpad_index)
	{
		if(s_instance != nullptr){
			return s_instance->GetVirtualPad(a_virtualpad_index);
		}else{
			ASSERT(0);
			return sharedptr<Pad_Virtual>::null();
		}
	}

	/** �X�V�B
	*/
	void Update(bool a_device_update)
	{
		if(s_instance != nullptr){
			s_instance->Update(a_device_update);
		}else{
			ASSERT(0);
		}
	}

	/** �V�X�e���̏I���B
	*/
	void EndSystem()
	{
		s_instance.reset();
	}
}}
