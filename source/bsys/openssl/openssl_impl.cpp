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
#pragma warning(push)
#pragma warning(disable:4464)
#include "../../blib/sockethandle_impl.h"
#pragma warning(pop)


/** include
*/
#include "./openssl_impl.h"


/** lib
*/
#if(BSYS_OPENSSL_ENABLE)

	#include <brownie_config/openssl_lib.h>

#endif


/** NBsys::NOpenSsl
*/
#if(BSYS_OPENSSL_ENABLE)
#pragma warning(push)
#pragma warning(disable:4710 4820)
namespace NBsys{namespace NOpenSsl
{
	/** constructor
	*/
	OpenSsl_Impl::OpenSsl_Impl()
		:
		ssl_ctx(nullptr)
	{
	}


	/** destructor
	*/
	OpenSsl_Impl::~OpenSsl_Impl()
	{
	}


	/** Initialize
	*/
	void OpenSsl_Impl::Initialize()
	{
		DEEPDEBUG_TAGLOG(BSYS_OPENSSL_DEBUG_ENABLE,L"openssl_impl","SSL_load_error_strings");
		SSL_load_error_strings();

		DEEPDEBUG_TAGLOG(BSYS_OPENSSL_DEBUG_ENABLE,L"openssl_impl","SSL_library_init");
		SSL_library_init();

		DEEPDEBUG_TAGLOG(BSYS_OPENSSL_DEBUG_ENABLE,L"openssl_impl","SSL_CTX_new(SSLv23_client_method)");
		this->ssl_ctx = SSL_CTX_new(SSLv23_client_method());
	}


	/** Finalize
	*/
	void OpenSsl_Impl::Finalize()
	{
		DEEPDEBUG_TAGLOG(BSYS_OPENSSL_DEBUG_ENABLE,L"openssl_impl","SSL_CTX_free");
		SSL_CTX_free(this->ssl_ctx);
		this->ssl_ctx = nullptr;

		//エンジン。
		DEEPDEBUG_TAGLOG(BSYS_OPENSSL_DEBUG_ENABLE,L"openssl_impl","ENGINE_cleanup");
		ENGINE_cleanup();

		//モジュール。
		s32 t_all_flag = 1;
		DEEPDEBUG_TAGLOG(BSYS_OPENSSL_DEBUG_ENABLE,L"openssl_impl","CONF_modules_unload");
		CONF_modules_unload(t_all_flag);

		//SSL_load_error_strings
		DEEPDEBUG_TAGLOG(BSYS_OPENSSL_DEBUG_ENABLE,L"openssl_impl","ERR_free_strings");
		ERR_free_strings();

		//This function cleans up all "ex_data" state. It mustn't be called under * potential race-conditions.
		DEEPDEBUG_TAGLOG(BSYS_OPENSSL_DEBUG_ENABLE,L"openssl_impl","CRYPTO_cleanup_all_ex_data");
		CRYPTO_cleanup_all_ex_data();

		//envelope
		DEEPDEBUG_TAGLOG(BSYS_OPENSSL_DEBUG_ENABLE,L"openssl_impl","EVP_cleanup");
		EVP_cleanup();

		//スレッド関連ステート。
		DEEPDEBUG_TAGLOG(BSYS_OPENSSL_DEBUG_ENABLE,L"openssl_impl","ERR_remove_thread_state");
		ERR_remove_thread_state(nullptr);

		//SSL_COMP_add_compression_method
		DEEPDEBUG_TAGLOG(BSYS_OPENSSL_DEBUG_ENABLE,L"openssl_impl","sk_SSL_COMP_free");
		sk_SSL_COMP_free(SSL_COMP_get_compression_methods());
	}


	/** DeleteThreadState
	*/
	void OpenSsl_Impl::DeleteThreadState()
	{
		DEEPDEBUG_TAGLOG(BSYS_OPENSSL_DEBUG_ENABLE,L"openssl_impl","ERR_remove_thread_state");
		ERR_remove_thread_state(nullptr);
	}


	/** GetSslCtx
	*/
	SSL_CTX* OpenSsl_Impl::GetSslCtx()
	{
		return this->ssl_ctx;
	}


	/** [static]CalcMD5
	*/
	STLString OpenSsl_Impl::CalcMD5(sharedptr<u8>& a_data,s32 a_size)
	{
		MD5_CTX t_md5_ctx;

		MD5_Init(&t_md5_ctx);
		MD5_Update(&t_md5_ctx,a_data.get(),a_size);

		u8 t_buffer[MD5_DIGEST_LENGTH + 1] = {0};
		MD5_Final(t_buffer,&t_md5_ctx);

		STLString t_ret;

		for(s32 ii=0;ii<MD5_DIGEST_LENGTH;ii++){
			char t_temp[4] = {0};
			t_ret += VASTRING(t_temp,sizeof(t_temp),"%02x",t_buffer[ii]);
		}

		return t_ret;
	}


	/** [static]MakeKey
	*/
	void OpenSsl_Impl::MakeKey()
	{
		//キーペアの作成。
		s32 t_size = 1024;
		u32 t_expornent = 65537;
		void (*t_callback)(int,int,void*) = nullptr;
		void* t_callback_argument = nullptr;
		RSA* t_rsakey = RSA_generate_key(t_size,t_expornent,t_callback,t_callback_argument);
		if(t_rsakey != nullptr){

			{
				FILE* t_public = nullptr;
				errno_t t_ret_open = ::fopen_s(&t_public,"./public.key","w");
				if(t_ret_open == 0){
					if(t_public != nullptr){
						s32 t_ret_write = PEM_write_RSAPublicKey(t_public,t_rsakey);
						if(t_ret_write != 1){
							ASSERT(0);
						}
						::fclose(t_public);
						t_public = nullptr;
					}else{
						ASSERT(0);
					}
				}else{
					ASSERT(0);
				}
			}

			{
				FILE* t_private = nullptr;
				errno_t t_ret_open = ::fopen_s(&t_private,"./private.key","w");
				if(t_ret_open == 0){
					if(t_private != nullptr){
						s32 t_ret_write = PEM_write_RSAPrivateKey(t_private,t_rsakey,nullptr,nullptr,0,nullptr,nullptr);
						if(t_ret_write != 1){
							ASSERT(0);
						}
						::fclose(t_private);
						t_private = nullptr;
					}else{
						ASSERT(0);
					}
				}else{
					ASSERT(0);
				}
			}

			RSA_free(t_rsakey);
		}else{
			ASSERT(0);
		}

		

		#if(0)

		if(RSA_print_fp(stdout, rsaKey, 0) != 1)
		{
		printError("failed to RSA_print_fp",
		ERR_get_error());
		exit(-1);
		}

		// 公開鍵をPEM形式で書き出し
		if(PEM_write_RSAPublicKey(publicKeyFile, rsaKey) != 1)
		{
		printError("failed to PEM_write_RSAPublicKey",
		ERR_get_error());
		exit(-1);
		}

		// 秘密鍵をPEM形式で書き出し
		if(PEM_write_RSAPrivateKey(privateKeyFile, rsaKey,	NULL,	NULL, 0,		NULL, NULL) != 1)
		{
		printError("failed to PEM_write_RSAPrivateKey",
		ERR_get_error());
		exit(-1);
		}

		// 領域の開放
		RSA_free(rsaKey);

		fclose(privateKeyFile);
		fclose(publicKeyFile);
		#endif
	}


	/** [static]Encrypt
	*/
	void OpenSsl_Impl::Encrypt()
	{
	}


	/** [static]Decrypt
	*/
	void OpenSsl_Impl::Decrypt()
	{
	}


}}
#pragma warning(pop)
#endif

