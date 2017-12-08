

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
#include "./pad_list.h"


/** NBsys::NPad
*/
namespace NBsys{namespace NPad
{
	/** constructor
	*/
	Pad_List::Pad_List(s32 a_virtualpad_max)
	{
		for(int ii=0;ii<a_virtualpad_max;ii++){
			sharedptr<Pad_Virtual> t_virtual_pad(new Pad_Virtual(ii));
			this->virtual_list.push_back(t_virtual_pad);
		}
	}

	/** destructor
	*/
	Pad_List::~Pad_List()
	{
	}

	/** �f�o�C�X�ǉ��B
	*/
	void Pad_List::AddDevice(sharedptr<Pad_Device_Base>& a_device_instance)
	{
		this->device_list.push_back(a_device_instance);
	}

	/** ���z�p�b�h�擾�B
	*/
	sharedptr<Pad_Virtual>& Pad_List::GetVirtualPad(s32 a_virtualpad_index)
	{
		return this->virtual_list[a_virtualpad_index];
	}

	/** �X�V�B
	*/
	void Pad_List::Update(bool a_device_update)
	{
		//�f�o�C�X�̍X�V�B
		if(a_device_update == true){
			STLVector<sharedptr<Pad_Device_Base>>::iterator t_it_end = this->device_list.end();
			for(STLVector<sharedptr<Pad_Device_Base>>::iterator t_it = this->device_list.begin();t_it!=t_it_end;++t_it){
				if(*t_it != nullptr){
					(*t_it)->DeviceUpdate();
				}
			}
		}

		//���z�p�b�h�X�V�B
		{
			STLVector<sharedptr<Pad_Virtual>>::iterator t_it_end = this->virtual_list.end();
			for(STLVector<sharedptr<Pad_Virtual>>::iterator t_it = this->virtual_list.begin();t_it!=t_it_end;++t_it){
				if(*t_it != nullptr){
					(*t_it)->Update();
				}
			}
		}
	}
}}

