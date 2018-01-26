#pragma once

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ウィンドウ。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** include
*/
#if defined(PLATFORM_VCWIN)

	#include <brownie_config/windows_include.h>

	//[include]
	#pragma warning(push)
	#pragma warning(disable:4514 4820 4668)
	#include <winsock2.h>
	#pragma warning(pop)

	//[include]
	#pragma warning(push)
	#pragma warning(disable:4514 4820 4668 4365 4574)
	#include <ws2tcpip.h>
	#pragma warning(pop)

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

