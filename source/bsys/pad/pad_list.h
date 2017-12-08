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
#include "./pad_device_base.h"
#include "./pad_virtual.h"


/** NBsys::NPad
*/
namespace NBsys{namespace NPad
{
	/** Pad_List
	*/
	class Pad_List
	{
	public:
		/** constructor
		*/
		Pad_List(s32 a_virtualpad_max);

		/** destructor
		*/
		nonvirtual ~Pad_List();

	private:
		/** �f�o�C�X���X�g�B
		*/
		STLVector<sharedptr<Pad_Device_Base>>::Type device_list;

		/** ���z�p�b�h���X�g�B
		*/
		STLVector<sharedptr<Pad_Virtual>>::Type virtual_list;

	public:
		/** �f�o�C�X�ǉ��B
		*/
		void AddDevice(sharedptr<Pad_Device_Base>& a_device_instance);

		/** ���z�p�b�h�擾�B
		*/
		sharedptr<Pad_Virtual>& GetVirtualPad(s32 a_virtualpad_index);

	public:
		/** �X�V�B
		*/
		void Update(bool a_device_update);

	};
}}

