﻿#pragma once

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief テスト。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../include.h"
#pragma warning(pop)


/** NTest::NCommon
*/
namespace NTest{namespace NCommon
{
	/** GetDebugLogString
	*/
	const wchar* GetDebugLogString(s32 a_index);


	/** GetDegubLogMax
	*/
	s32 GetDegubLogMax();


	/** GetDebugLogColor
	*/
	#if(BSYS_COLOR_ENABLE)
	NBsys::NColor::Color_F& GetDebugLogColor(s32 a_index);
	#endif


	/** GetDebugLogCounter
	*/
	s32 GetDebugLogCounter();


}}

