#pragma once

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ＨＴＴＰ。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** include
*/
#include "./http_recv_decl.h"
#include "./http_send_decl.h"
#include "./http_boundarystring.h"
#include "./http_type.h"
#include "./http_binaryitem.h"


/** NBsys::NHttp
*/
#if(BSYS_HTTP_ENABLE)
#pragma warning(push)
#pragma warning(disable:4710 4820)
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
				//待ち。
				None = 0,

				//開始。
				Start,

				//接続。
				Connect,

				//送信待ち。初回データ。
				SendWait_StartData,

				//受信待ち。
				RecvHeader,

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

		/** binary_list
		*/
		STLMap<STLString,sharedptr<Http_BinaryItem>>::Type binary_list;

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

		/** コンテンツ追加。
		*/
		void AddPostContent(const STLString& a_name,const STLString& a_filename,sharedptr< u8 >& a_data,s32 a_size);

		/** コンテンツ追加。
		*/
		void AddPostContent(const STLString& a_name,const STLString& a_value);

	public:

		/** IsError
		*/
		bool IsError();

		/** IsRecvHeader
		*/
		bool IsRecvHeader();

		/** GetStatusCode
		*/
		s32 GetStatusCode();

		/** GetContentLength
		*/
		s32 GetContentLength();

	public:

		/** 開始。
		*/
		void ConnectStart(sharedptr<RingBufferBase<u8>>& a_recv_buffer);

		/** 終了。
		*/
		void ConnectEnd();

		/** 更新。

			戻り値
				true	: 継続
				false	: 終了

		*/
		bool ConnectUpdate();

	};


}}
#pragma warning(pop)
#endif

