#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �e�X�g�B
*/


/** include
*/
#include "../include.h"


/** NTest::NCommon
*/
#if(DEF_TEST_INDEX == 12)
namespace NTest{namespace NCommon
{
	/** GetDebugLogString
	*/
	const wchar* GetDebugLogString(s32 a_index);


	/** GetDebugLogColor
	*/
	NBsys::NColor::Color_F& GetDebugLogColor(s32 a_index);


	/** GetDebugLogCounter
	*/
	s32 GetDebugLogCounter();


}}
#endif

