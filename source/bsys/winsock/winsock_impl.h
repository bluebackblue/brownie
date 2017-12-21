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


/** include
*/
#if defined(PLATFORM_VCWIN)

	#include <brownie_config/windows_include.h>

	#include <winsock2.h>
	#include <ws2tcpip.h>

#endif


/** NBsys::NWinsock
*/
#if(BSYS_WINSOCK_ENABLE)
namespace NBsys{namespace NWinsock
{
	/** Winsock_Impl
	*/
	class Winsock_Impl
	{
	public:

		/** constructor
		*/
		Winsock_Impl();

		/** destructor
		*/
		nonvirtual ~Winsock_Impl();

	};


}}
#endif

