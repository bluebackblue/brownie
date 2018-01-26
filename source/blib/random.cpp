

/**
 * Copyright (c) blueback
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

	#pragma warning(push)
	#pragma warning(disable:4710 4987 4820 4365 4625 4626 5027 4514 4571 4623 4774 5026)
	#include <random>
	#pragma warning(pop)

#endif


/** warning

4710 : この関数はインライン展開のために選択されましたが、コンパイラはインライン展開を実行しませんでした。

*/
#pragma warning(disable:4710)


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

