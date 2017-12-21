

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
#include "./http.h"
#include "./http_recv.h"
#include "./http_send.h"
#include "./http_bodystring.h"


/** include
*/
//#include "../ssl/ssl.h"


/** NBsys::NHttp
*/
#if(BSYS_HTTP_ENABLE)
namespace NBsys{namespace NHttp
{
	/** constructor
	*/
	Http::Http()
		:
		host(""),
		port(80),
		mode(Http_Mode::Get),
		url(""),
		boundary_string(""),
		step(Step::Connect),
		socket(),
		iserror(false),
		send_buffer(),
		recv_buffer(),
		send(),
		recv()
	{
	}


	/** destructor
	*/
	Http::~Http()
	{
	}


	/** SetHost
	*/
	void Http::SetHost(const STLString& a_host)
	{
		this->host = a_host;
	}


	/** SetPort
	*/
	void Http::SetPort(s32 a_port)
	{
		this->port = a_port;
	}


	/** SetMode
	*/
	void Http::SetMode(Http_Mode::Id a_mode)
	{
		this->mode = a_mode;
	}


	/** SetUrl
	*/
	void Http::SetUrl(const STLString& a_url)
	{
		this->url = a_url;
	}


	/** SetBoundaryString
	*/
	void Http::SetBoundaryString(const STLString& a_boundary_string)
	{
		this->boundary_string = a_boundary_string;
	}


	/** IsRecvHeader
	*/
	bool Http::IsRecvHeader()
	{
		if(this->recv){
			return this->recv->IsRecvHeader();
		}

		return false;
	}


	/** IsRecvHeader
	*/
	s32 Http::GetStatusCode()
	{
		if(this->recv){
			return this->recv->GetStatusCode();
		}

		return -1;
	}


	/** GetContentLength
	*/
	s32 Http::GetContentLength()
	{
		if(this->recv){
			return this->recv->GetContentLength();
		}

		return -1;
	}


	/** �J�n�B
	*/
	void Http::ConnectStart(sharedptr<RingBufferBase<u8>>& a_recv_buffer)
	{
		this->recv_buffer = a_recv_buffer;
		this->step = Step::Connect;
		this->iserror = false;
	}


	/** �I���B
	*/
	void Http::ConnectEnd()
	{
		this->step = Step::Connect;
		this->socket.reset();
		this->iserror = false;
		this->send_buffer.reset();
		this->recv_buffer.reset();
		this->send.reset();
		this->recv.reset();
	}


	/** �X�V�B
	*/
	bool Http::ConnectUpdate()
	{
		if(this->iserror == true){
			//���f�B
			return false;
		}

		bool t_loop = true;
		while(t_loop){
			t_loop = false;

			if(this->send){
				if(this->send->Update() == true){
					//���[�v���N�G�X�g�B
					t_loop = true;
				}
				this->iserror = this->send->IsError();
			}
			if(this->recv){
				if(this->recv->Update() == true){
					//���[�v���N�G�X�g�B
					t_loop = true;
				}
			}

			switch(this->step){
			case Step::Connect:
				{
					//�ڑ��B

					//�\�P�b�g�쐬�B
					this->socket.reset(new SocketHandle());

					//��M�ݒ�B
					this->recv.reset(new Http_Recv(this->socket,this->recv_buffer));

					//���M�ݒ�B
					this->send.reset(new Http_Send());

					//�ڑ��B
					if(this->socket->OpenTcp()){
						if(this->socket->ConnectTcp(this->host.c_str(),this->port) == true){
							this->step = Step::Send_StartData;
							t_loop = true;
						}else{
							//�G���[�B
							this->iserror = true;
						}
					}else{
						//�G���[�B
						this->iserror = true;
					}
				}break;
			case Step::Send_StartData:
				{
					s32 t_binary_size = 0;
					s32 t_send_buffer_size = 0;

					//�o�C�i���쐬�B
					{
					}

					//�{�f�B�쐬�B				
					STLString t_send_body = NHttp::MakeBodyString_Header(this->boundary_string,this->mode,this->url,this->host,t_binary_size);
					t_send_buffer_size += t_send_body.length();

					this->send_buffer.reset( new u8[t_send_buffer_size + 1024],default_delete<u8>());

					s32 t_offset = 0;

					//�{�f�B�[�R�s�[�B
					{
						Memory::memcpy(&this->send_buffer.get()[t_offset],t_send_buffer_size - t_offset,t_send_body.c_str(),static_cast<s32>(t_send_body.length()));
						t_offset += t_send_body.length();
					}

					//�o�C�i���R�s�[�B
					{
					}

					//�f�o�b�O�B
					{
						this->send_buffer.get()[t_send_buffer_size] = 0x00;
						DEBUGLOG("%s",t_send_body.c_str());
					}

					//���M�o�b�t�@�ݒ�B
					this->send->Send(this->socket,this->send_buffer,t_send_buffer_size);

					this->step = Step::SendWait_StartData;

					t_loop = true;
				}break;
			case Step::SendWait_StartData:
				{
					if(this->send->IsBusy() == false){
						//��M�J�n�B
						this->recv->StartRecv();
						this->step = Step::RecvHeader;
					}
				}break;
			case Step::RecvHeader:
				{
					if(this->recv->IsRecvHeader()){
						this->step = Step::Recv;
					}
				}break;
			case Step::Recv:
				{
					if(this->recv->GetContentLength() <= this->recv->GetContentRecvSize()){
						if(this->socket != nullptr){
							this->socket.reset();
						}
					}

					bool t_close = false;
					if(this->socket == nullptr){
						t_close = true;
					}else{
						if(this->socket->IsOpen() == false){
							t_close = true;
						}
					}

					if(t_close == true){
						//��M�ς݂Ŗ���̓f�[�^�̃T�C�Y�B
						if(this->recv->GetRecvRingBufferUseSize() <= 0){
							//���f�I���B
							return false;
						}
					}
					
				}break;
			}
		}

		//�p���B
		return true;
	}


}}
#endif

