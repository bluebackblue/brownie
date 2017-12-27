﻿

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief 乱数。
*/


/** include
*/
#include <blib_pch.h>


/** include
*/
#include "./types.h"
#include "./platform.h"


/** include
*/
#include "./memorycontainer.h"


/** include
*/
#if(BLIB_STDRANDOM_ENABLE)

	#pragma warning(disable:4710)
	#pragma warning(push)
	#pragma warning(disable:4987 4820 4365 4625 4626 5027 4514 4571 4623 4774 5026)
	#include <random>
	#pragma warning(pop)

#endif

/** NBlib
*/
namespace NBlib
{
	/** 非決定論的乱数。
	*/
	u32 GetRandFromDevice()
	{
		#if(BLIB_STDRANDOM_ENABLE)
		{
			std::random_device t_random;
			return t_random();
		}
		#else
		{
			ASSERT(0);
			return 0;
		}
		#endif
	}


}

