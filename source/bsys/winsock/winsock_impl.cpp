

/**
* Copyright (c) 2017 blueback
* Released under the MIT License
* https://github.com/bluebackblue/brownie/blob/master/LICENSE
* http://bbbproject.sakura.ne.jp/wordpress/mitlicense
* @brief ウィンドウ。
*/


/** include
*/
#include <bsys_pch.h>


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./winsock_impl.h"


/** NBsys::NWinsock
*/
#if(BSYS_WINSOCK_ENABLE)
namespace NBsys{namespace NWinsock
{
	/** constructor
	*/
	Winsock_Impl::Winsock_Impl()
	{
		#if defined(PLATFORM_VCWIN)

		WSADATA t_wsadata;
		int t_ret = ::WSAStartup(MAKEWORD(2,0),&t_wsadata);

		switch (t_ret){
		case 0:break;
		case WSASYSNOTREADY:		DEBUGLOG("WSASYSNOTREADY\n");			break;
		case WSAVERNOTSUPPORTED:	DEBUGLOG("WSAVERNOTSUPPORTED\n");		break;
		case WSAEINPROGRESS:		DEBUGLOG("WSAEINPROGRESS\n");			break;
		case WSAEPROCLIM:			DEBUGLOG("WSAEPROCLIM\n");				break;
		case WSAEFAULT:				DEBUGLOG("WSAEFAULT\n");				break;
		default:					DEBUGLOG("WSAStartup = 0x%8x\n",t_ret);	break;
		}

		#endif
	}


	/** destructor
	*/
	Winsock_Impl::~Winsock_Impl()
	{
		#if defined(PLATFORM_VCWIN)

		::WSACleanup();

		#endif
	}


}}
#endif

