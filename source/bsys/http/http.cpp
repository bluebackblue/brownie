

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
#include "./http_binaryitem.h"


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
		boundary_string(NHttp::MakeBoundaryString()),
		step(Step::Connect),
		socket(),
		iserror(false),
		send_buffer(),
		recv_buffer(),
		send(),
		recv(),
		binary_list()
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


	/** �R���e���c�ǉ��B
	*/
	void Http::AddPostContent(const STLString& a_name,const STLString& a_filename,sharedptr< u8 >& a_data,s32 a_size)
	{
		//�w�b�_�[�B
		STLString t_body_header = NHttp::MakeBodyString_BinaryHeader(this->boundary_string,a_name,a_filename);
		
		//�t�b�^�[�B
		STLString t_body_footer = NHttp::MakeBodyString_BinarFooter();

		//�o�b�t�@�B
		s32 t_buffer_size = a_size + t_body_header.length() + t_body_footer.length();
		sharedptr<Http_BinaryItem> t_binary_item(new Http_BinaryItem());
		t_binary_item->data.reset(new u8[t_buffer_size],default_delete<u8>());
		u8* t_buffer_data = t_binary_item->data.get();
		t_binary_item->size = t_buffer_size;

		//�R�s�[�B
		{
			s32 t_offset = 0;

			Memory::memcpy(&t_buffer_data[t_offset],(t_buffer_size - t_offset),t_body_header.c_str(),static_cast<s32>(t_body_header.length()));
			t_offset += static_cast<s32>(t_body_header.length());

			Memory::memcpy(&t_buffer_data[t_offset],(t_buffer_size - t_offset),a_data.get(),a_size);
			t_offset += static_cast<s32>(a_size);

			Memory::memcpy(&t_buffer_data[t_offset],(t_buffer_size - t_offset),t_body_footer.c_str(),static_cast<s32>(t_body_footer.length()));
			t_offset += static_cast<s32>(t_body_footer.length());

			ASSERT(t_offset == t_buffer_size);
		}

		this->binary_list.insert(STLMap<STLString,sharedptr<Http_BinaryItem>>::value_type(a_name,t_binary_item));
	}


	/** �R���e���c�ǉ��B
	*/
	void Http::AddPostContent(const STLString& a_name,const STLString& a_value)
	{
		//�w�b�_�[�B
		STLString t_body_header = NHttp::MakeBodyString_TextHeader(this->boundary_string,a_name);
		
		//�t�b�^�[�B
		STLString t_body_footer = NHttp::MakeBodyString_TextFooter();

		//�o�b�t�@�B
		s32 t_buffer_size = a_value.length() + t_body_header.length() + t_body_footer.length();
		sharedptr<Http_BinaryItem> t_binary_item(new Http_BinaryItem());
		t_binary_item->data.reset(new u8[t_buffer_size],default_delete<u8>());
		u8* t_buffer_data = t_binary_item->data.get();
		t_binary_item->size = t_buffer_size;

		//�R�s�[�B
		{
			s32 t_offset = 0;

			Memory::memcpy(&t_buffer_data[t_offset],(t_buffer_size - t_offset),t_body_header.c_str(),static_cast<s32>(t_body_header.length()));
			t_offset += static_cast<s32>(t_body_header.length());

			Memory::memcpy(&t_buffer_data[t_offset],(t_buffer_size - t_offset),a_value.c_str(),a_value.length());
			t_offset += static_cast<s32>(a_value.length());

			Memory::memcpy(&t_buffer_data[t_offset],(t_buffer_size - t_offset),t_body_footer.c_str(),static_cast<s32>(t_body_footer.length()));
			t_offset += static_cast<s32>(t_body_footer.length());

			ASSERT(t_offset == t_buffer_size);
		}

		this->binary_list.insert(STLMap<STLString,sharedptr<Http_BinaryItem>>::value_type(a_name,t_binary_item));
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

					//�o�C�i�����T�C�Y�B
					if(this->mode == Http_Mode::Post){
						for(STLMap<STLString,sharedptr<Http_BinaryItem>>::iterator t_it = this->binary_list.begin();t_it!=this->binary_list.end();t_it++){
							if(t_it->second != nullptr){
								t_binary_size += t_it->second->size;
							}
						}
					}

					//�o�C�i���I�[������B
					STLString t_binary_footer = "";
					if(this->mode == Http_Mode::Post){
						NHttp::MakeBodyString_PostBinarFooter(this->boundary_string);
						t_binary_size += static_cast<s32>(t_binary_footer.length());
					}

					//�{�f�B�쐬�B				
					STLString t_send_body = NHttp::MakeBodyString_Header(this->boundary_string,this->mode,this->url,this->host,t_binary_size);

					//�o�b�t�@�B
					s32 t_buffer_size = t_send_body.length() + t_binary_size;
					this->send_buffer.reset(new u8[t_buffer_size],default_delete<u8>());
					u8* t_buffer_data = this->send_buffer.get();

					{
						s32 t_offset = 0;

						//�{�f�B�[�̃R�s�[�B
						Memory::memcpy(&t_buffer_data[t_offset],(t_buffer_size - t_offset),t_send_body.c_str(),static_cast<s32>(t_send_body.length()));
						t_offset += static_cast<s32>(t_send_body.length());

						if(this->mode == Http_Mode::Post){

							//�o�C�i���̃R�s�[�B
							for(STLMap<STLString,sharedptr<Http_BinaryItem>>::iterator t_it = this->binary_list.begin();t_it!=this->binary_list.end();t_it++){
								if(t_it->second != nullptr){
									Memory::memcpy(&t_buffer_data[t_offset],(t_buffer_size - t_offset),t_it->second->data.get(),t_it->second->size);
									t_offset += static_cast<s32>(t_send_body.length());
								}
							}

							//�o�C�i���I�[�̃R�s�[�B
							Memory::memcpy(&t_buffer_data[t_offset],(t_buffer_size - t_offset),t_binary_footer.c_str(),static_cast<s32>(t_binary_footer.length()));
							t_offset += static_cast<s32>(t_binary_footer.length());
						}

						ASSERT(t_offset == t_buffer_size);
					}

					//���M�o�b�t�@�ݒ�B
					this->send->Send(this->socket,this->send_buffer,t_buffer_size);

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
					//�w�b�_�[��M�����`�F�b�N�B
					if(this->recv->IsRecvHeader()){
						this->step = Step::Recv;
					}
				}break;
			case Step::Recv:
				{
					//�R���e���c��M�����`�F�b�N�B
					if(this->recv->IsRecvContent()){
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

