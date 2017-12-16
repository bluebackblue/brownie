#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief テスト。
*/


/** include
*/
#include "../include.h"


/** DEF_TEST12
*/
#if defined(DEF_TEST12)

/** GetDebugLogString
*/
const char* GetDebugLogString(s32 a_index);

/** GetDebugLogColor
*/
NBsys::NColor::Color_F& GetDebugLogColor(s32 a_index);

/** GetDebugLogCounter
*/
s32 GetDebugLogCounter();

#endif

