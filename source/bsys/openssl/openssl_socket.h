#pragma once

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ＯＰＥＮＳＳＬ。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** include
*/
#include "./openssl_socket_impl_decl.h"
#include "./openssl_impl_decl.h"


/** NBsys::NOpenSsl
*/
#if(BSYS_OPENSSL_ENABLE)
#pragma warning(push)
#pragma warning(disable:4710 4820)
namespace NBsys{namespace NOpenSsl
{
	/** OpenSsl_Socket
	*/
	class OpenSsl_Socket
	{
	private:

		/** impl
		*/
		sharedptr<OpenSsl_Socket_Impl> impl;

	public:

		/** constructor
		*/
		OpenSsl_Socket();

		/** destructor
		*/
		nonvirtual ~OpenSsl_Socket();

	public:

		/** 開始。
		*/
		bool Start(sharedptr<SocketHandle>& a_sockethandle,sharedptr<OpenSsl_Impl>& a_openssl_impl);

		/** 終了。
		*/
		void End();

		/** 送信。
		*/
		bool Send(const u8* a_data,s64 a_size,s64 a_offset);

		/** 受信。
		*/
		s64 Recv(u8* a_data,s64 a_size,s64 a_offset,bool a_complete);

	};


}}
#pragma warning(pop)
#endif

