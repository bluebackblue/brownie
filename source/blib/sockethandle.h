#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ソケットハンドル。
*/


/** include
*/
#include "./types.h"
#include "./platform.h"


/** include
*/
#include "./sharedptr.h"
#include "./stlstring.h"


/** NBlib
*/
namespace NBlib
{
	/** SocketHandle_Impl
	*/
	class SocketHandle_Impl;

	/** SocketHandle
	*/
	class SocketHandle
	{
	private:
		/** impl
		*/
		sharedptr<SocketHandle_Impl> impl;

	public:
		/** GetImpl
		*/
		sharedptr<SocketHandle_Impl>& GetImpl();

	public:
		/** constructor
		*/
		SocketHandle();

		/** constructor
		*/
		SocketHandle(sharedptr<SocketHandle_Impl>& a_impl);

		/** destructor
		*/
		nonvirtual ~SocketHandle();

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
		bool Send(const u8* a_data,s64 a_size,s64 a_offsets);

		/** 送信。
		*/
		bool SendUdp(const u8* a_data,s64 a_size,s64 a_offset);

		/** 受信。
		*/
		s64 Recv(u8* a_data,s64 a_size,s64 a_offset,bool a_complete);

		/** 開いているかどうか。
		*/
		bool IsOpen() const;

	};
}

