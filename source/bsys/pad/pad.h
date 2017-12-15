﻿#pragma once

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
#include "./pad_list.h"
#include "./pad_device_base.h"
#include "./pad_virtual.h"


/** NBsys::NPad
*/
namespace NBsys{namespace NPad
{
	/** システムの開始。
	*/
	void StartSystem(s32 a_virtualpad_max);

	/** システムのインスタンス取得。
	*/
	sharedptr<Pad_List>& GetSystemInstance();

	/** デバイス追加。
	*/
	void AddDevice(sharedptr<Pad_Device_Base> a_device_instance);

	/** 仮想パッド取得。
	*/
	sharedptr<Pad_Virtual>& GetVirtualPad(s32 a_virtualpad_index);

	/** 更新。
	*/
	void Update(bool a_device_update);

	/** システムの終了。
	*/
	void EndSystem();
}}

