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

	#include <brownie_config/windows_include.h>

	//[include]
	#pragma warning(push)
	#pragma warning(disable:4710 4711 4514 4820 4668)
	#include <winsock2.h>
	#pragma warning(pop)

	//[include]
	#pragma warning(push)
	#pragma warning(disable:4710 4711 4514 4820 4668 4365 4574)
	#include <ws2tcpip.h>
	#pragma warning(pop)

	#include <brownie_config/openssl_include.h>

#endif


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../blib/sockethandle_impl.h"
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
		ctx(nullptr),
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

		DEEPDEBUG_TAGLOG(BSYS_OPENSSL_DEBUG_ENABLE,L"openssl_impl","SSL_CTX_new : SSLv23_client_method");
		this->ctx = SSL_CTX_new(SSLv23_client_method());
	}


	/** Finalize
	*/
	void OpenSsl_Impl::Finalize()
	{
		DEEPDEBUG_TAGLOG(BSYS_OPENSSL_DEBUG_ENABLE,L"openssl_impl","SSL_library_init");
		SSL_CTX_free(this->ctx);
		this->ctx = nullptr;

		DEEPDEBUG_TAGLOG(BSYS_OPENSSL_DEBUG_ENABLE,L"openssl_impl","ERR_free_strings");
		ERR_free_strings();
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

			SSL* t_ssl = SSL_new(this->ctx);
			if(t_ssl != nullptr){
				t_it->second->SetSsl(t_ssl);
			}

			if(t_ssl != nullptr){

				//SSL_set_fd
				s32 t_ret_setfd = SSL_set_fd(t_ssl,static_cast<s32>(a_sockethandle->GetImpl()->GetRawHandle()));
				if(t_ret_setfd == 0){
					//ERR_print_errors_fp(stderr);
					DEEPDEBUG_TAGLOG(BSYS_OPENSSL_DEBUG_ENABLE,L"openssl_impl","error : SSL_set_fd");
					return false;
				}else{
					DEEPDEBUG_TAGLOG(BSYS_OPENSSL_DEBUG_ENABLE,L"openssl_impl","SSL_set_fd");
				}

				//SSL_connect
				s32 t_ret_connect = SSL_connect(t_ssl);
				if(t_ret_connect != 1){
					//ERR_print_errors_fp(stderr);
					DEEPDEBUG_TAGLOG(BSYS_OPENSSL_DEBUG_ENABLE,L"openssl_impl","error : SSL_connect %d",t_ret_connect);
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
				SSL_free(t_ssl);
				DEEPDEBUG_TAGLOG(BSYS_OPENSSL_DEBUG_ENABLE,L"openssl_impl","SSL_free");
			}

			this->list.erase(t_it);
		}else{
			ASSERT(0);
		}
	}

}}
#pragma warning(pop)
#endif

