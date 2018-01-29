

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
#pragma warning(push)
#pragma warning(disable:4464)
#include "../../blib/sockethandle_impl.h"
#pragma warning(pop)


/** include
*/
#include "./openssl_socket_impl.h"
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
	/** constructor
	*/
	OpenSsl_Socket_Impl::OpenSsl_Socket_Impl()
		:
		ssl(nullptr)
	{
	}


	/** destructor
	*/
	OpenSsl_Socket_Impl::~OpenSsl_Socket_Impl()
	{
		this->End();
	}


	/** 開始。
	*/
	bool OpenSsl_Socket_Impl::Start(sharedptr<SocketHandle>& a_sockethandle,sharedptr<OpenSsl_Impl>& a_openssl_impl)
	{
		DEEPDEBUG_TAGLOG(BSYS_OPENSSL_DEBUG_ENABLE,L"openssl_socket_impl","Connect");

		this->End();

		if(a_openssl_impl != nullptr){
			SSL_CTX* t_ssl_ctx = a_openssl_impl->GetSslCtx();
			if(t_ssl_ctx != nullptr){
				this->ssl = SSL_new(t_ssl_ctx);
				if(this->ssl != nullptr){

					bool t_ret = true;

					//SSL_set_fd
					s32 t_ret_setfd = SSL_set_fd(this->ssl,static_cast<s32>(a_sockethandle->GetImpl()->GetRawHandle()));
					if(t_ret_setfd == 0){
						DEEPDEBUG_TAGLOG(BSYS_OPENSSL_DEBUG_ENABLE,L"openssl_socket_impl","error : SSL_set_fd %d : %s",t_ret_setfd,ERR_reason_error_string(ERR_get_error()));
						t_ret = false;
					}else{
						DEEPDEBUG_TAGLOG(BSYS_OPENSSL_DEBUG_ENABLE,L"openssl_socket_impl","SSL_set_fd");
					}

					//SSL_connect
					s32 t_ret_connect = SSL_connect(this->ssl);
					if(t_ret_connect != 1){
						DEEPDEBUG_TAGLOG(BSYS_OPENSSL_DEBUG_ENABLE,L"openssl_socket_impl","error : SSL_connect %d : %s",t_ret_connect,ERR_reason_error_string(ERR_get_error()));
						t_ret = false;
					}else{
						DEEPDEBUG_TAGLOG(BSYS_OPENSSL_DEBUG_ENABLE,L"openssl_socket_impl","SSL_connect");
					}

					if(t_ret == false){
						this->End();
					}

					return true;
				}else{
					ASSERT(0);
				}
			}else{
				ASSERT(0);
			}
		}else{
			ASSERT(0);
		}

		return false;	
	}


	/** 終了。
	*/
	void OpenSsl_Socket_Impl::End()
	{
		if(this->ssl != nullptr){
			DEEPDEBUG_TAGLOG(BSYS_OPENSSL_DEBUG_ENABLE,L"openssl_impl","SSL_shutdown");
			SSL_shutdown(this->ssl);

			DEEPDEBUG_TAGLOG(BSYS_OPENSSL_DEBUG_ENABLE,L"openssl_impl","SSL_free");
			SSL_free(this->ssl);

			this->ssl = nullptr;
		}
	}


	/** 送信。
	*/
	bool OpenSsl_Socket_Impl::Send(const u8* a_data,s64 a_size,s64 a_offset)
	{
		if(this->ssl != nullptr){
			s64 t_offset = 0LL;
			while(1){
				s64 t_size = a_size - t_offset;
				if(t_size <= 0){
					//送信完了。
					return true;
				}else{
					s32 t_fix = SSL_write(this->ssl,reinterpret_cast<const char*>(&a_data[t_offset+a_offset]),(int)t_size);
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

		return false;
	}


	/** 受信。
	*/
	s64 OpenSsl_Socket_Impl::Recv(u8* a_data,s64 a_size,s64 a_offset,bool a_complete)
	{
		if(this->ssl != nullptr){
			s64 t_offset = 0LL;
			while(1){
				s64 t_size = a_size - t_offset;
				if(t_size <= 0){
					//受信完了。
					return a_size;
				}else{
					s32 t_fix = SSL_read(this->ssl,reinterpret_cast<char*>(&a_data[t_offset+a_offset]),(int)t_size);
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

		return -1;
	}


}}
#endif

