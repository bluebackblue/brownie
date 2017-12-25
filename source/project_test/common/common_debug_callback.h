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
	NBsys::NColor::Color_F& GetDebugLogColor(s32 a_index);


	/** GetDebugLogCounter
	*/
	s32 GetDebugLogCounter();


}}

