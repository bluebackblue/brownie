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


/** include
*/
#if(BSYS_OPENSSL_ENABLE)
	#include <brownie_config/openssl_include.h>
#endif


/** include
*/
#include "./openssl_item.h"


/** NBsys::NOpenSsl
*/
#if(BSYS_OPENSSL_ENABLE)
#pragma warning(push)
#pragma warning(disable:4710 4820)
namespace NBsys{namespace NOpenSsl
{
	/** OpenSsl_Impl
	*/
	class OpenSsl_Impl
	{
	private:

		/** ctx
		*/
		SSL_CTX* ctx;

		/** id_maker
		*/
		IDMaker id_maker;
		
		/** list
		*/
		STLMap<s32,sharedptr<OpenSsl_Item>>::Type list;

	public:
		/** constructor
		*/
		OpenSsl_Impl();

		/** destructor
		*/
		nonvirtual ~OpenSsl_Impl();

	public:

		/** Initialize
		*/
		void Initialize();

		/** Finalize
		*/
		void Finalize();
		
	public:

		/** Ssl_Create
		*/
		s32 Ssl_Create();

		/** Ssl_Connect
		*/
		bool Ssl_Connect(s32 a_id,sharedptr<SocketHandle>& a_sockethandle);

		/** Ssl_Send
		*/
		bool Ssl_Send(s32 a_id,const u8* a_data,s64 a_size,s64 a_offset);

		/** Ssl_Recv
		*/
		s64 Ssl_Recv(s32 a_id,u8* a_data,s64 a_size,s64 a_offset,bool a_complete);

		/** Ssl_Delete
		*/
		void Ssl_Delete(s32 a_id);

	};


}}
#pragma warning(pop)
#endif

