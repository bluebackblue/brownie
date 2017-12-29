

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ウィンドウ。
*/


/** include
*/
#include <bsys_pch.h>


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** include
*/
#include "./winsock_impl.h"


/** include
*/
#include "./winsock.h"


/** warning

4710 : The given function was selected for inline expansion, but the compiler did not perform the inlining.

*/
#pragma warning(disable:4710)


/** NBsys::NWinsock
*/
#if(BSYS_WINSOCK_ENABLE)
namespace NBsys{namespace NWinsock
{
	/** s_instance
	*/
	sharedptr<Winsock_Impl> s_instance;

	/** システムの開始。
	*/
	void StartSystem()
	{
		if(s_instance == nullptr){
			s_instance.reset(new Winsock_Impl());
		}else{
			ASSERT(0);
		}
	}

	/** システムの終了。
	*/
	void EndSystem()
	{
		s_instance.reset();
	}

}}
#endif

