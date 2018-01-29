

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ＯＰＥＮＳＳＬ。
*/


/** include
*/
#include <bsys_pch.h>


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** include
*/
#include "./openssl_socket.h"
#include "./openssl_socket_impl.h"
#include "./openssl_impl_decl.h"


/** warning

4710 : この関数はインライン展開のために選択されましたが、コンパイラはインライン展開を実行しませんでした。

*/
#pragma warning(disable:4710)


/** NBsys::NOpenSsl
*/
#if(BSYS_OPENSSL_ENABLE)
namespace NBsys{namespace NOpenSsl
{
	/** constructor
	*/
	OpenSsl_Socket::OpenSsl_Socket()
	{
		this->impl.reset(new OpenSsl_Socket_Impl());
	}


	/** destructor
	*/
	OpenSsl_Socket::~OpenSsl_Socket()
	{
		this->impl.reset();
	}


	/** 開始。
	*/
	bool OpenSsl_Socket::Start(sharedptr<SocketHandle>& a_sockethandle,sharedptr<OpenSsl_Impl>& a_openssl_impl)
	{
		return this->impl->Start(a_sockethandle,a_openssl_impl);
	}


	/** 終了。
	*/
	void OpenSsl_Socket::End()
	{
		this->impl->End();
	}


	/** 送信。
	*/
	bool OpenSsl_Socket::Send(const u8* a_data,s64 a_size,s64 a_offset)
	{
		return this->impl->Send(a_data,a_size,a_offset);
	}


	/** 受信。
	*/
	s64 OpenSsl_Socket::Recv(u8* a_data,s64 a_size,s64 a_offset,bool a_complete)
	{
		return this->impl->Recv(a_data,a_size,a_offset,a_complete);
	}


}}
#endif

