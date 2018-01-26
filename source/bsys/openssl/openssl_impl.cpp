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
		ssl_ctx(nullptr),
		id_maker(),
		list()
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


	/** 作成。
	*/
	s32 OpenSsl_Impl::Ssl_Create()
	{
		s32 t_id = this->id_maker.MakeID();

		this->list.insert(std::make_pair(t_id,new OpenSsl_Item(t_id)));

		return t_id;
	}


	/** 接続。
	*/
	bool OpenSsl_Impl::Ssl_Connect(s32 a_id,sharedptr<SocketHandle>& a_sockethandle)
	{
		DEEPDEBUG_TAGLOG(BSYS_OPENSSL_DEBUG_ENABLE,L"openssl_impl","Connect");

		auto t_it = this->list.find(a_id);
		if(t_it != this->list.end()){

			SSL* t_ssl = SSL_new(this->ssl_ctx);
			if(t_ssl != nullptr){
				t_it->second->SetSsl(t_ssl);
			}

			if(t_ssl != nullptr){

				//SSL_set_fd
				s32 t_ret_setfd = SSL_set_fd(t_ssl,static_cast<s32>(a_sockethandle->GetImpl()->GetRawHandle()));
				if(t_ret_setfd == 0){
					DEEPDEBUG_TAGLOG(BSYS_OPENSSL_DEBUG_ENABLE,L"openssl_impl","error : SSL_set_fd %d : %s",t_ret_setfd,ERR_reason_error_string(ERR_get_error()));
					return false;
				}else{
					DEEPDEBUG_TAGLOG(BSYS_OPENSSL_DEBUG_ENABLE,L"openssl_impl","SSL_set_fd");
				}

				//SSL_connect
				s32 t_ret_connect = SSL_connect(t_ssl);
				if(t_ret_connect != 1){
					DEEPDEBUG_TAGLOG(BSYS_OPENSSL_DEBUG_ENABLE,L"openssl_impl","error : SSL_connect %d : %s",t_ret_connect,ERR_reason_error_string(ERR_get_error()));
					return false;
				}else{
					DEEPDEBUG_TAGLOG(BSYS_OPENSSL_DEBUG_ENABLE,L"openssl_impl","SSL_connect");
				}

				return true;
			}
		}else{
			ASSERT(0);
		}

		return false;
	}


	/** Send
	*/
	bool OpenSsl_Impl::Ssl_Send(s32 a_id,const u8* a_data,s64 a_size,s64 a_offset)
	{
		auto t_it = this->list.find(a_id);
		if(t_it != this->list.end()){

			SSL* t_ssl = (t_it->second)->GetSsl();
			if(t_ssl != nullptr){

				s64 t_offset = 0LL;
				while(1){
					s64 t_size = a_size - t_offset;
					if(t_size <= 0){
						//送信完了。
						return true;
					}else{
						s32 t_fix = SSL_write(t_ssl,reinterpret_cast<const char*>(&a_data[t_offset+a_offset]),(int)t_size);
						if(t_fix > 0){
							//送信中。
							t_offset += t_fix;
						}else{
							//切断。
							return false;
						}
					}
				}

			}else{
				ASSERT(0);
			}
		}else{
			ASSERT(0);
		}

		return false;
	}

	/** Recv
	*/
	s64 OpenSsl_Impl::Ssl_Recv(s32 a_id,u8* a_data,s64 a_size,s64 a_offset,bool a_complete)
	{
		auto t_it = this->list.find(a_id);
		if(t_it != this->list.end()){

			SSL* t_ssl = (t_it->second)->GetSsl();
			if(t_ssl != nullptr){

				s64 t_offset = 0LL;
				while(1){
					s64 t_size = a_size - t_offset;
					if(t_size <= 0){
						//受信完了。
						return a_size;
					}else{
						s32 t_fix = SSL_read(t_ssl,reinterpret_cast<char*>(&a_data[t_offset+a_offset]),(int)t_size);
						if(a_complete == true){
							if(t_fix > 0){
								//受信中。
								t_offset += t_fix;
							}else{
								//切断。
								return -1;
							}
						}else{
							if(t_fix > 0){
								//受信完了。
								return t_fix;
							}else{
								//切断。
								return -1;
							}
						}
					}
				}

			}else{
				ASSERT(0);
			}

		}else{
			ASSERT(0);
		}

		return -1;
	}

	/** Ssl_Delete
	*/
	void OpenSsl_Impl::Ssl_Delete(s32 a_id)
	{
		auto t_it = this->list.find(a_id);
		if(t_it != this->list.end()){

			SSL* t_ssl = (t_it->second)->GetSsl();
			if(t_ssl != nullptr){
				DEEPDEBUG_TAGLOG(BSYS_OPENSSL_DEBUG_ENABLE,L"openssl_impl","SSL_shutdown");
				SSL_shutdown(t_ssl);

				SSL_free(t_ssl);
				DEEPDEBUG_TAGLOG(BSYS_OPENSSL_DEBUG_ENABLE,L"openssl_impl","SSL_free");
			}

			this->list.erase(t_it);
		}else{
			ASSERT(0);
		}
	}


	/** CalcMD5
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


}}
#pragma warning(pop)
#endif

