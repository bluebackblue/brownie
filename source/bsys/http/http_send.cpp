

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �g�s�s�o�B
*/


/** include
*/
#include <bsys_pch.h>


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./http_send.h"


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


	/** ���M�o�b�t�@�Ƀf�[�^���R�s�[�B
	*/
	void Http_Send::Send(const sharedptr<SocketHandle>& a_socket,const sharedptr<u8>& a_buffer,s32 a_size)
	{
		this->socket = a_socket;
		this->iserror = false;
		this->buffer = a_buffer;
		this->buffer_offset = 0;
		this->buffer_size = a_size;
	}


	/** ���M�������������ǂ����B
	*/
	bool Http_Send::IsBusy()
	{
		if(this->buffer_offset >= this->buffer_size){
			return false;
		}
		return true;
	}


	/** �G���[�B
	*/
	bool Http_Send::IsError()
	{
		return this->iserror;
	}


	/** �X�V�B
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
						//�G���[�B
						this->iserror = true;
					}
				}
			}
		}

		//���[�v���N�G�X�g�B�Ȃ��B
		return false;
	}


}}
#endif

