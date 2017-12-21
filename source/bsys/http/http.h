#pragma once

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ＨＴＴＰ。
*/


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./http_recv.h"
#include "./http_send.h"
#include "./http_type.h"


/** NBsys::NHttp
*/
#if(BSYS_HTTP_ENABLE)
namespace NBsys{namespace NHttp
{
	/** Http
	*/
	class Http
	{
	private:

		/** Step
		*/
		struct Step
		{
			enum Id
			{
				//接続。
				Connect,

				//送信。初回データ。
				Send_StartData,

				//送信待ち。初回データ。
				SendWait_StartData,

				//受信待ち。
				Recv,
			};
		};

	private:
	
		/** host
		*/
		STLString host;

		/** port
		*/
		s32 port;

		/** mode
		*/
		Http_Mode::Id mode;
		
		/** Url
		*/
		STLString url;
		
		/** boundary_string
		*/
		STLString boundary_string;

	private:

		/** step
		*/
		Step::Id step;

		/** socket
		*/
		sharedptr<SocketHandle> socket;

		/** iserror
		*/
		bool iserror;

		/** sendbuffer
		*/
		sharedptr<u8> send_buffer;

		/** recvbuffer
		*/
		sharedptr<RingBufferBase<u8>> recv_buffer;

		/** send
		*/
		sharedptr<Http_Send> send;

		/** recv
		*/
		sharedptr<Http_Recv> recv;

	public:

		/** constructor
		*/
		Http();

		/** destructor
		*/
		nonvirtual ~Http();

	public:

		/** SetHost
		*/
		void SetHost(const STLString& a_host);

		/** SetPort
		*/
		void SetPort(s32 a_port);

		/** SetMode
		*/
		void SetMode(Http_Mode::Id a_mode);

		/** SetUrl
		*/
		void SetUrl(const STLString& a_url);

		/** SetBoundaryString
		*/
		void SetBoundaryString(const STLString& a_boundary_string);

	public:

		/** 開始。
		*/
		void ConnectStart(sharedptr<RingBufferBase<u8>>& a_recv_buffer);

		/** 更新。

			戻り値
				true	: 継続
				false	: 終了

		*/
		bool ConnectUpdate();

	};


}}
#endif

