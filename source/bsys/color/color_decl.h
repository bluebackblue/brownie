#pragma once

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief 色。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** NBsys::NColor
*/
#if(BSYS_COLOR_ENABLE)
namespace NBsys{namespace NColor
{
	/** Color_F
	*/
	struct Color_F;


	/** Color_B
	*/
	struct Color_B;


}}
#endif

