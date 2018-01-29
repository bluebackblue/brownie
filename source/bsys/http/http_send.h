#pragma once

/**
 * Copyright (c) blueback
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


#if(BSYS_OPENSSL_ENABLE)

	#pragma warning(push)
	#pragma warning(disable:4464)
	#include "../openssl/openssl.h"
	#pragma warning(pop)

#endif


/** NBsys::NHttp
*/
#if(BSYS_HTTP_ENABLE)
#pragma warning(push)
#pragma warning(disable:4710 4820)
namespace NBsys{namespace NHttp
{
	/** Http_Send
	*/
	class Http_Send
	{
	private:

		/** socket
		*/
		sharedptr<SocketHandle> socket;

		/** ssl_socket
		*/
		#if(BSYS_OPENSSL_ENABLE)
		sharedptr<NBsys::NOpenSsl::OpenSsl_Socket> ssl_socket;
		#endif

		/** iserror
		*/
		bool iserror;

		/** send_buffer
		*/
		sharedptr<u8> buffer;

		/**
		*/
		s32 buffer_offset;

		/**
		*/
		s32 buffer_size;

	public:

		/** constructor
		*/
		Http_Send();

		/** destructor
		*/
		nonvirtual ~Http_Send();

	public:

		/** 送信。
		*/
		#if(BSYS_OPENSSL_ENABLE)
		void Send(const sharedptr<SocketHandle>& a_socket,const sharedptr<NBsys::NOpenSsl::OpenSsl_Socket>& a_ssl_socket,const sharedptr<u8>& a_buffer,s32 a_size);
		#else
		void Send(const sharedptr<SocketHandle>& a_socket,const sharedptr<u8>& a_buffer,s32 a_size);
		#endif

		/** 送信が完了したかどうか。
		*/
		bool IsBusy();

		/** エラー。
		*/
		bool IsError();

		/** 更新。
		*/
		bool Update();

	};


}}
#pragma warning(pop)
#endif

