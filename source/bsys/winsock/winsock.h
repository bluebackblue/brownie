#pragma once

/**
* Copyright (c) 2017 blueback
* Released under the MIT License
* https://github.com/bluebackblue/brownie/blob/master/LICENSE
* http://bbbproject.sakura.ne.jp/wordpress/mitlicense
* @brief �E�B���h�E�B
*/


/** include
*/
#include "../types/types.h"


/** NBsys::NWinsock
*/
#if(BSYS_WINSOCK_ENABLE)
namespace NBsys{namespace NWinsock
{
	/** �V�X�e���̊J�n�B
	*/
	void StartSystem();

	/** �V�X�e���̏I���B
	*/
	void EndSystem();


}}
#endif

