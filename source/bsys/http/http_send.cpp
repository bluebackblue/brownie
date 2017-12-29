

/**
 * Copyright (c) 2016-2017 blueback
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


/** include
*/
#include "./http_send.h"


/** warning

4710 : The given function was selected for inline expansion, but the compiler did not perform the inlining.

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
	void Http_Send::Send(const sharedptr<SocketHandle>& a_socket,const sharedptr<u8>& a_buffer,s32 a_size)
	{
		this->socket = a_socket;
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
					if(this->socket->Send(this->buffer.get(),this->buffer_offset + t_send_size,this->buffer_offset) == true){
						this->buffer_offset += t_send_size;
					}else{
						//エラー。
						this->iserror = true;
					}
				}
			}
		}

		//ループリクエスト。なし。
		return false;
	}


}}
#endif

