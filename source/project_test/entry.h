#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �G���g���[�B
*/


/** include
*/
#include "./include.h"


/** include
*/
#if defined(PLATFORM_VCWIN)

	#include "../blib/include_windows.h"

#endif


/** EntryParam
*/
struct EntryParam
{
	#if defined(PLATFORM_VCWIN)

	HINSTANCE	hinstance;

	#endif
};


/** GetEntryParamReference
*/
EntryParam& GetEntryParamReference();

