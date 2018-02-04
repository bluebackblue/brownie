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
#if(BSYS_OPENSSL_ENABLE)

	#include <brownie_config/openssl_include.h>

#endif


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
	/** OpenSsl_Impl
	*/
	class OpenSsl_Impl
	{
	private:

		/** ctx
		*/
		SSL_CTX* ssl_ctx;

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

		/** DeleteThreadState
		*/
		void DeleteThreadState();

		/** GetSslCtx
		*/
		SSL_CTX* GetSslCtx();
		
	public:

		/** CalcMD5
		*/
		static STLString CalcMD5(const void* a_data,s32 a_size);

		/** MakeKey
		*/
		static void MakeKey();

		/** EncryptFromPrivateKey
		*/
		static std::tuple<sharedptr<u8>,s32> EncryptFromPrivateKey(const void* a_data,s32 a_size,const STLWString& a_path);

		/** DecryptFromPublicKey
		*/
		static std::tuple<sharedptr<u8>,s32> DecryptFromPublicKey(const void* a_data,s32 a_size,const STLWString& a_path);

	};


}}
#pragma warning(pop)
#endif

