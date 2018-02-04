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
	STLString OpenSsl_Impl::CalcMD5(const void* a_data,s32 a_size)
	{
		MD5_CTX t_md5_ctx;

		MD5_Init(&t_md5_ctx);
		MD5_Update(&t_md5_ctx,a_data,a_size);

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
				FILE* t_file_public = nullptr;
				errno_t t_ret_open = ::fopen_s(&t_file_public,"./public.key","w");
				if(t_ret_open == 0){
					if(t_file_public != nullptr){
						s32 t_ret_write = PEM_write_RSAPublicKey(t_file_public,t_rsakey);
						if(t_ret_write != 1){
							ASSERT(0);
						}
						::fclose(t_file_public);
						t_file_public = nullptr;
					}else{
						ASSERT(0);
					}
				}else{
					ASSERT(0);
				}
			}

			{
				FILE* t_file_private = nullptr;
				errno_t t_ret_open = ::fopen_s(&t_file_private,"./private.key","w");
				if(t_ret_open == 0){
					if(t_file_private != nullptr){
						s32 t_ret_write = PEM_write_RSAPrivateKey(t_file_private,t_rsakey,nullptr,nullptr,0,nullptr,nullptr);
						if(t_ret_write != 1){
							ASSERT(0);
						}
						::fclose(t_file_private);
						t_file_private = nullptr;
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
	}


	/** [static]EncryptFromPrivateKey
	*/
	std::tuple<sharedptr<u8>,s32> OpenSsl_Impl::EncryptFromPrivateKey(const void* a_data,s32 a_size,const STLWString& a_path)
	{
		RSA* t_rsakey = nullptr;

		FILE* t_file_private = nullptr;
		errno_t t_ret_open = ::fopen_s(&t_file_private,"./private.key","r");
		if(t_ret_open == 0){
			if(t_file_private != nullptr){
				pem_password_cb* t_callback = nullptr;
				void* t_callback_argument = nullptr;

				RSA* t_ret_rsakey = PEM_read_RSAPrivateKey(t_file_private,&t_rsakey,t_callback,t_callback_argument);
				if(t_ret_rsakey == nullptr){
					//失敗。
					ASSERT(0);
				}
				::fclose(t_file_private);
				t_file_private = nullptr;
			}else{
				//失敗。
				ASSERT(0);
			}
		}else{
			//失敗。
			ASSERT(0);
		}

		if(t_rsakey != nullptr){

			s32 t_ret_size_max = 1024;
			sharedptr<u8> t_ret_data(new u8[t_ret_size_max],default_delete<u8[]>());

			s32 t_ret_size = RSA_private_encrypt(a_size,reinterpret_cast<const u8*>(a_data),t_ret_data.get(),t_rsakey,RSA_PKCS1_PADDING);

			if(t_ret_size < 0){
				char t_buffer[128];
				DEEPDEBUG_TAGLOG(BSYS_OPENSSL_DEBUG_ENABLE,L"openssl_impl","RSA_private_encrypt : %s",ERR_error_string(ERR_get_error(),t_buffer));

				//失敗。
				ASSERT(0);
				t_ret_size = 0;
				return std::tuple<sharedptr<u8>,s32>(nullptr,0);
			}

			RSA_free(t_rsakey);
			t_rsakey = nullptr;

			ASSERT(t_ret_size <= t_ret_size_max);
			return std::tuple<sharedptr<u8>,s32>(t_ret_data,t_ret_size);
		}else{
			//失敗。
			ASSERT(0);
			return std::tuple<sharedptr<u8>,s32>(nullptr,0);
		}
	}


	/** [static]DecryptFromPublicKey
	*/
	std::tuple<sharedptr<u8>,s32> OpenSsl_Impl::DecryptFromPublicKey(const void* a_data,s32 a_size,const STLWString& a_path)
	{
		RSA* t_rsakey = nullptr;

		FILE* t_file_public = nullptr;
		errno_t t_ret_open = ::fopen_s(&t_file_public,"./public.key","r");
		if(t_ret_open == 0){
			if(t_file_public != nullptr){
				pem_password_cb* t_callback = nullptr;
				void* t_callback_argument = nullptr;

				RSA* t_ret_rsakey = PEM_read_RSAPublicKey(t_file_public,&t_rsakey,t_callback,t_callback_argument);
				if(t_ret_rsakey == nullptr){
					//失敗。
					ASSERT(0);
				}
				::fclose(t_file_public);
				t_file_public = nullptr;
			}else{
				//失敗。
				ASSERT(0);
			}
		}else{
			//失敗。
			ASSERT(0);
		}

		if(t_rsakey != nullptr){

			s32 t_ret_size_max = 1024;
			sharedptr<u8> t_ret_data(new u8[t_ret_size_max],default_delete<u8[]>());

			s32 t_ret_size = RSA_public_decrypt(a_size,reinterpret_cast<const u8*>(a_data),t_ret_data.get(),t_rsakey,RSA_PKCS1_PADDING);

			if(t_ret_size < 0){
				char t_buffer[128];
				DEEPDEBUG_TAGLOG(BSYS_OPENSSL_DEBUG_ENABLE,L"openssl_impl","RSA_public_encrypt : %s",ERR_error_string(ERR_get_error(),t_buffer));

				//失敗。
				ASSERT(0);
				t_ret_size = 0;
				return std::tuple<sharedptr<u8>,s32>(nullptr,0);
			}

			RSA_free(t_rsakey);
			t_rsakey = nullptr;

			ASSERT(t_ret_size <= t_ret_size_max);
			return std::tuple<sharedptr<u8>,s32>(t_ret_data,t_ret_size);
		}else{
			//失敗。
			ASSERT(0);
			return std::tuple<sharedptr<u8>,s32>(nullptr,0);
		}
	}


}}
#pragma warning(pop)
#endif

