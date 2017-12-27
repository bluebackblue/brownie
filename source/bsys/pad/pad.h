#pragma once

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief パッド。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** include
*/
#include "./pad_list.h"
#include "./pad_device_base.h"
#include "./pad_virtual.h"


/** NBsys::NPad
*/
#if(BSYS_PAD_ENABLE)
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
#endif

