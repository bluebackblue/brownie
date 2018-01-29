﻿

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
#include "./openssl.h"
#include "./openssl_impl.h"


/** warning

4710 : この関数はインライン展開のために選択されましたが、コンパイラはインライン展開を実行しませんでした。

*/
#pragma warning(disable:4710)


/** NBsys::NOpenSsl
*/
#if(BSYS_OPENSSL_ENABLE)
namespace NBsys{namespace NOpenSsl
{
	/** s_openssl
	*/
	sharedptr<OpenSsl_Impl> s_openssl;


	/** システムの開始。
	*/
	void StartSystem()
	{
		if(s_openssl == nullptr){
			s_openssl.reset(new OpenSsl_Impl());
			
			s_openssl->Initialize();
		}else{
			ASSERT(0);
		}
	}

	/** システムの終了。
	*/
	void EndSystem()
	{
		if(s_openssl){
			s_openssl->Finalize();
		}else{
			ASSERT(0);
		}

		s_openssl.reset();
	}


	/** スレッド関連ステートの削除。
	*/
	void SslDeleteThreadState()
	{
		if(s_openssl){
			return s_openssl->DeleteThreadState();
		}
	}


	/** 接続。
	*/
	sharedptr<OpenSsl_Socket> Connect(sharedptr<SocketHandle>& a_sockethandle)
	{
		sharedptr<OpenSsl_Socket> t_socket(new OpenSsl_Socket());
		
		bool t_ret = t_socket->Start(a_sockethandle,s_openssl);
		if(t_ret == false){
			ASSERT(0);
			return nullptr;
		}

		return t_socket;
	}


	/** CalcMD5
	*/
	STLString CalcMD5(sharedptr<u8>& a_data,s32 a_size)
	{
		return OpenSsl_Impl::CalcMD5(a_data,a_size);
	}


	/** MakeKey
	*/
	void MakeKey()
	{
		OpenSsl_Impl::MakeKey();
	}


	/** Encrypt
	*/
	void Encrypt()
	{
		OpenSsl_Impl::Encrypt();
	}


	/** Decrypt
	*/
	void Decrypt()
	{
		OpenSsl_Impl::Decrypt();
	}


}}
#endif

