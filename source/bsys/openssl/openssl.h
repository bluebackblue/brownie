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


	#if(0)
		/** 接続。
		*/
		bool Connect(Muid& a_muid,sharedptr< SocketHandle >& a_sockethandle);

		/** Send
		*/
		bool Send(Muid& a_muid,const u8* a_data,s64 a_size,s64 a_offset);

		/** Resv
		*/
		s64 Recv(Muid& a_muid,u8* a_data,s64 a_size,s64 a_offset,bool a_complete);

		/** Delete
		*/
		void Delete(Muid& a_muid);

	#endif


}}
#pragma warning(pop)
#endif

