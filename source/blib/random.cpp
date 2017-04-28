

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �����B
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

	#include <random>

#endif

/** NBlib
*/
namespace NBlib
{
	/** �񌈒�_�I�����B
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

