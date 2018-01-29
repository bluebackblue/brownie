

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ＨＴＴＰ。
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


#if(BSYS_OPENSSL_ENABLE)

	/** include
	*/
	#pragma warning(push)
	#pragma warning(disable:4464)
	#include "../openssl/openssl.h"
	#pragma warning(pop)

#endif


/** include
*/
#include "./http_send.h"


/** warning

4710 : この関数はインライン展開のために選択されましたが、コンパイラはインライン展開を実行しませんでした。

*/
#pragma warning(disable:4710)


/** NBsys::NHttp
*/
#if(BSYS_HTTP_ENABLE)
namespace NBsys{namespace NHttp
{
	/** constructor
	*/
	Http_Send::Http_Send()
		:
		socket(),
		#if(BSYS_OPENSSL_ENABLE)
		ssl_socket(),
		#endif
		iserror(false),
		buffer(),
		buffer_offset(0),
		buffer_size(0)
	{
	}


	/** destructor
	*/
	Http_Send::~Http_Send()
	{
	}


	/** 送信バッファにデータをコピー。
	*/
	#if(BSYS_OPENSSL_ENABLE)
	void Http_Send::Send(const sharedptr<SocketHandle>& a_socket,const sharedptr<NBsys::NOpenSsl::OpenSsl_Socket>& a_ssl_socket,const sharedptr<u8>& a_buffer,s32 a_size)
	#else
	void Http_Send::Send(const sharedptr<SocketHandle>& a_socket,const sharedptr<u8>& a_buffer,s32 a_size)
	#endif
	{
		this->socket = a_socket;

		#if(BSYS_OPENSSL_ENABLE)
		this->ssl_socket = a_ssl_socket;
		#endif

		this->iserror = false;
		this->buffer = a_buffer;
		this->buffer_offset = 0;
		this->buffer_size = a_size;
	}


	/** 送信が完了したかどうか。
	*/
	bool Http_Send::IsBusy()
	{
		if(this->buffer_offset >= this->buffer_size){
			return false;
		}
		return true;
	}


	/** エラー。
	*/
	bool Http_Send::IsError()
	{
		return this->iserror;
	}


	/** 更新。
	*/
	bool Http_Send::Update()
	{
		if(this->socket){
			if(this->socket->IsOpen()){
				if(this->buffer_offset < this->buffer_size){
					s32 t_send_size = this->buffer_size - this->buffer_offset;

					bool t_ret = false;
					bool t_do = false;

					#if(BSYS_OPENSSL_ENABLE)
					if(this->ssl_socket != nullptr){
						if(t_do == false){
							t_do = true;
							if(this->ssl_socket->Send(this->buffer.get(),this->buffer_offset + t_send_size,this->buffer_offset) == true){
								t_ret = true;
							}
						}
					}
					#endif

					if(t_do == false){
						t_do = true;

						if(this->socket->Send(this->buffer.get(),this->buffer_offset + t_send_size,this->buffer_offset) == true){
							t_ret = true;
						}
					}

					if(t_ret == true){
						DEEPDEBUG_TAGLOG(BSYS_HTTP_DEBUG_ENABLE,L"http_recv","send : %d",t_send_size);
						this->buffer_offset += t_send_size;
					}else{
						//エラー。
						this->iserror = true;

						#if(BSYS_OPENSSL_ENABLE)
						if(this->ssl_socket != nullptr){
							this->ssl_socket->End();
							this->ssl_socket.reset();
						}
						#endif

						this->socket->Close();
						DEEPDEBUG_TAGLOG(BSYS_HTTP_DEBUG_ENABLE,L"http_recv","close");
					}
				}
			}
		}

		//ループリクエスト。なし。
		return false;
	}


}}
#endif

