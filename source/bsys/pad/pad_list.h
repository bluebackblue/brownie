#pragma once

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief パッド。
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
		/** デバイスリスト。
		*/
		STLVector<sharedptr<Pad_Device_Base>>::Type device_list;

		/** 仮想パッドリスト。
		*/
		STLVector<sharedptr<Pad_Virtual>>::Type virtual_list;

	public:
		/** デバイス追加。
		*/
		void AddDevice(sharedptr<Pad_Device_Base>& a_device_instance);

		/** 仮想パッド取得。
		*/
		sharedptr<Pad_Virtual>& GetVirtualPad(s32 a_virtualpad_index);

	public:
		/** 更新。
		*/
		void Update(bool a_device_update);

	};
}}

