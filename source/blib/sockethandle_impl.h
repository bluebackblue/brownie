#pragma once

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ソケットハンドル。実装部分。
*/


/** include
*/
#include "./types.h"
#include "./platform.h"


/** include
*/
#include "./sharedptr.h"
#include "./sockethandle.h"
#include "./staticassert.h"
#include "./debugassert.h"
#include "./stlstring.h"


/** include
*/
#if defined(PLATFORM_VCWIN)

	#include <brownie_config/windows_include.h>

	//[include]
	#pragma warning(push)
	#pragma warning(disable:4710 4711 4514 4820 4668)
	#include <winsock2.h>
	#pragma warning(pop)

	//[include]
	#pragma warning(push)
	#pragma warning(disable:4710 4711 4514 4820 4668 4365 4574)
	#include <ws2tcpip.h>
	#pragma warning(pop)

#endif


/** NBlib
*/
namespace NBlib
{
	/** SocketHandle_Impl
	*/
	class SocketHandle_Impl
	{
	private:

		/** handle
		*/
		#if defined(PLATFORM_VCWIN)

		SOCKET rawhandle;

		addrinfo* rawaddrinfo;

		/** padding
		*/
		padding64(0,7);
		padding32(0,3);

		#endif

		/** isopen
		*/
		bool isopen;

	public:

		/** constructor
		*/
		SocketHandle_Impl() noexcept;

		/** constructor
		*/
		#if defined(PLATFORM_VCWIN)

		SocketHandle_Impl(SOCKET a_rawhandle) noexcept;

		#endif

		/** destructor
		*/
		nonvirtual ~SocketHandle_Impl() noexcept;

		/** GetHostIp
		*/
		static bool GetHostIp(STLString& a_ip_name);

	public:

		/** 開く。
		*/
		bool OpenTcp();

		/** 開く。
		*/
		bool OpenUdp();

		/** 閉じる。
		*/
		void Close();

		/** 接続。
		*/
		bool ConnectTcp(const STLString& a_ip,s32 a_port);

		/** 接続。
		*/
		bool ConnectUdp(const STLString& a_ip,s32 a_port);

		/** バインド。
		*/
		bool Bind(s32 a_port);

		/** Listen
		*/
		bool Listen();

		/** Accept
		*/
		sharedptr<SocketHandle> Accept();

		/** ブロードキャスト設定。
		*/
		void SetBroadcast(bool a_flag);
		
		/** ノンブロック設定。
		*/
		void SetNonblock(bool a_flag);

		/** 送信。
		*/
		bool SendUdp(const u8* a_data,s64 a_size,s64 a_offset);

		/** 送信。
		*/
		bool Send(const u8* a_data,s64 a_size,s64 a_offset);

		/** 受信。
		*/
		s64 Recv(u8* a_data,s64 a_size,s64 a_offset,bool a_complete);

		/** 開いているかどうか。
		*/
		bool IsOpen() const;

		/** GetRawHandle
		*/
		#if defined(PLATFORM_VCWIN)
		SOCKET GetRawHandle() const;
		#endif

	};


}

