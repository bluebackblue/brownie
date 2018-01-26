

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief メモリー。
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
#include "./memory.h"


/** include
*/
#pragma warning(push)
#pragma warning(disable:4710 4711 4987 4365 4820 4514 4623 4626 5027)
#include <memory>
#pragma warning(pop)


/** include
*/
#if defined(PLATFORM_GNUCWIN)

	//[include]
	#include <memory.h>

#endif


/** warning

4710 : この関数はインライン展開のために選択されましたが、コンパイラはインライン展開を実行しませんでした。

*/
#pragma warning(disable:4710)


/** NBlib
*/
namespace NBlib
{
	/** NMemory
	*/
	namespace NMemory
	{
	}


}

