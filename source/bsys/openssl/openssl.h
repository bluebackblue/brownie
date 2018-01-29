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
#include "./openssl_socket.h"


/** NBsys::NOpenSsl
*/
#if(BSYS_OPENSSL_ENABLE)
#pragma warning(push)
#pragma warning(disable:4710 4820)
namespace NBsys{namespace NOpenSsl
{
	/** システムの開始。
	*/
	void StartSystem();


	/** システムの終了。
	*/
	void EndSystem();

	
	/** スレッドに関連付けらたステートを削除します。
	*/
	void SslDeleteThreadState();


	/** 接続。
	*/
	sharedptr<OpenSsl_Socket> Connect(sharedptr<SocketHandle>& a_sockethandle);


	/** CalcMD5
	*/
	STLString CalcMD5(sharedptr<u8>& a_data,s32 a_size);

	/** MakeKey
	*/
	void MakeKey();


	/** Encrypt
	*/
	void Encrypt();


	/** Decrypt
	*/
	void Decrypt();


}}
#pragma warning(pop)
#endif

