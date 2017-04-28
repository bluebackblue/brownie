#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �X���b�h���[�J���B
*/


/** include
*/
#include "./types.h"
#include "./platform.h"


/** NBlib
*/
#if(BLIB_THREADLOCAL_ENABLE)
namespace NBlib
{
	/** ThreadLocal
	*/
	struct ThreadLocal
	{
		void* pointer;
	};

	/** GetThreadLocal
	*/
	ThreadLocal& GetThreadLocal(s32 a_index);
}
#endif

