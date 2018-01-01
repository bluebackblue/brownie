#pragma once

/**
 * Copyright (c) 2016-2018 blueback
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


	/** SslCreate
	*/
	s32 SslCreate();

	/** SslConnect
	*/
	bool SslConnect(s32 a_id,sharedptr<SocketHandle>& a_sockethandle);


	/** SslSend
	*/
	bool SslSend(s32 a_id,const u8* a_data,s64 a_size,s64 a_offset);


	/** SslRecv
	*/
	s64 SslRecv(s32 a_id,u8* a_data,s64 a_size,s64 a_offset,bool a_complete);


	/** SslDelete
	*/
	void SslDelete(s32 a_id);


}}
#pragma warning(pop)
#endif

