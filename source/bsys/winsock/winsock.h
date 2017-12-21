#pragma once

/**
* Copyright (c) 2017 blueback
* Released under the MIT License
* https://github.com/bluebackblue/brownie/blob/master/LICENSE
* http://bbbproject.sakura.ne.jp/wordpress/mitlicense
* @brief ウィンドウ。
*/


/** include
*/
#include "../types/types.h"


/** NBsys::NWinsock
*/
#if(BSYS_WINSOCK_ENABLE)
namespace NBsys{namespace NWinsock
{
	/** システムの開始。
	*/
	void StartSystem();

	/** システムの終了。
	*/
	void EndSystem();


}}
#endif

