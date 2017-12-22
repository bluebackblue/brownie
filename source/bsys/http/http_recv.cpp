

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
#include "./http_recv.h"
#include "./http_find.h"


/** include
*/
#include<regex>


/** NBsys::NHttp
*/
#if(BSYS_HTTP_ENABLE)
namespace NBsys{namespace NHttp
{
	/** constructor
	*/
	Http_Recv::Http_Recv(const sharedptr<SocketHandle>& a_socket,sharedptr<RingBufferBase<u8>>& a_ringbuffer)
		:
		socket(a_socket),
		iserror(false),
		ringbuffer_recv(new RingBuffer<u8,1024 * 16,true>()),
		ringbuffer_data(a_ringbuffer),
		header_line(),
		need_recv_size(0),
		copy_chunk_size(0),
		copyfix_chunk_size(0),
		copy_content_size(0),
		header_is_recv(false),
		header_is_transfer_encodeing_chunked(false),
		header_content_length(-1),
		header_chunk_length(-1),
		header_status_code(-1),
		step(Step::None)
	{
	}


	/** destructor
	*/
	Http_Recv::~Http_Recv()
	{
	}


	/** ��M���J�n�B
	*/
	void Http_Recv::StartRecv()
	{
		ASSERT(this->step == Step::None);

		this->need_recv_size = -1;
		this->step = Step::StateCode;
	}


	/** �G���[�B
	*/
	bool Http_Recv::IsError()
	{
		return this->iserror;
	}


	/** ��M�ς݂Ŗ���̓f�[�^�̃T�C�Y�B
	*/
	s32 Http_Recv::GetRecvRingBufferUseSize()
	{
		return this->ringbuffer_recv->GetUseSize();
	}


	/** ��M�ς݂̃R���e���c�T�C�Y�B
	*/
	//s32 Http_Recv::GetContentRecvSize()
	//{
	//	return this->copy_content_recv_size;
	//}


	/** IsRecvHeader
	*/
	bool Http_Recv::IsRecvHeader()
	{
		return this->header_is_recv;
	}


	/** IsRecvContent
	*/
	bool Http_Recv::IsRecvContent()
	{
		if(this->header_content_length >= 0){
			if(this->header_content_length <= this->copy_content_size){
				return true;
			}
		}
		return false;
	}


	/** GetStatusCode
	*/
	s32 Http_Recv::GetStatusCode()
	{
		return this->header_status_code;
	}


	/** GetContentLength
	*/
	s32 Http_Recv::GetContentLength()
	{
		return this->header_content_length;
	}


	/** �X�V�B
	*/
	bool Http_Recv::Update()
	{
		u8 t_data[1024 * 16];
		s32 t_size = 0;
		s32 t_need_recv_size = 0;

		if(this->need_recv_size < 0){
			//��M���K�v�B�T�C�Y�͎����B
			t_need_recv_size = sizeof(t_data);
		}else if(this->need_recv_size > 0){
			//�w��T�C�Y���̎�M���K�v�B
			t_need_recv_size = this->need_recv_size;
			if(t_need_recv_size > sizeof(t_data)){
				t_need_recv_size = sizeof(t_data);
			}
		}

		if(this->socket){
			if(this->socket->IsOpen()){
				if(t_need_recv_size > 0){
					t_size = static_cast<s32>(this->socket->Recv(t_data,t_need_recv_size,0,false));
					if(t_size < 0){
						//�T�[�o����̐ؒf�B
						this->socket.reset();
					}else{
						if(this->ringbuffer_recv){
							this->ringbuffer_recv->CopyToBuffer(t_data,t_size);
						}
						this->need_recv_size = 0;
					}
				}
			}
		}

		if(this->ringbuffer_recv == nullptr){
			//�G���[�B
			this->iserror = true;

			//���[�v���N�G�X�g�B�Ȃ��B
			return false;
		}

		//��M�o�b�t�@��́B
		switch(this->step){
		case Step::StateCode:
			{
				//�X�e�[�^�X�B

				s32 t_end_offset = NHttp::FindFromRingBuffer(*this->ringbuffer_recv.get(),'\r','\n');
				if(t_end_offset >= 0){
					u8 t_tempbuffer[1024];
					if(t_end_offset < (sizeof(t_tempbuffer) - 2)){

						this->ringbuffer_recv->CopyFromBuffer(t_tempbuffer,t_end_offset + 2);
						t_tempbuffer[t_end_offset + 0] = 0x00;
						t_tempbuffer[t_end_offset + 1] = 0x00;
						ASSERT(sizeof(t_tempbuffer) >= t_end_offset + 2);

						STLString t_line = reinterpret_cast<char*>(&t_tempbuffer[0]);

						TAGLOG(L"Http_Recv","%s",t_line.c_str());

						this->header_line.push_back(t_line);

						this->header_status_code = FindStatusCode(t_line);

						this->step = Step::Header;

						//���[�v���N�G�X�g�B�A�������B
						return true;
					}else{
						//��̓G���[�B
						this->iserror = true;

						//��M�f�[�^��͗p�o�b�t�@�B�j���B
						this->ringbuffer_recv.reset();
					}
				}else{
					//��M���B
					this->need_recv_size = -1;
				}
			}break;
		case Step::Header:
			{
				//�w�b�_�[�B

				s32 t_end_offset = NHttp::FindFromRingBuffer(*this->ringbuffer_recv.get(),'\r','\n');
				if(t_end_offset >= 0){
					u8 t_tempbuffer[1024];
					if(t_end_offset < (sizeof(t_tempbuffer) - 2)){

						this->ringbuffer_recv->CopyFromBuffer(t_tempbuffer,t_end_offset + 2);
						t_tempbuffer[t_end_offset + 0] = 0x00;
						t_tempbuffer[t_end_offset + 1] = 0x00;
						ASSERT(sizeof(t_tempbuffer) >= t_end_offset + 2);

						STLString t_line = reinterpret_cast<const char*>(&t_tempbuffer[0]);

						if(t_line == ""){
							//�w�b�_�[�I�[�B

							if(this->header_is_transfer_encodeing_chunked == true){
								this->step = Step::Data_ChunkSize;
							}else{
								this->step = Step::Data_OneChunkData;
							}

							this->copy_content_size = 0;
							this->copy_chunk_size = 0;
							this->copyfix_chunk_size = 0;

							this->header_is_recv = true;

							//���[�v���N�G�X�g�B�A�������B
							return true;
						}else{
							//�s�B

							TAGLOG(L"Http_Recv","%s",t_line.c_str());

							this->header_line.push_back(t_line);

							if(t_line == "Transfer-Encoding: chunked"){
								this->header_is_transfer_encodeing_chunked = true;
							}

							s32 t_content_length = NHttp::FindContentsLength(t_line);
							if(t_content_length >= 0){
								this->header_content_length = t_content_length;
							}

							//���[�v���N�G�X�g�B�A�������B
							return true;
						}
					}else{
						//��̓G���[�B
						this->iserror = true;

						//��M�f�[�^��͗p�o�b�t�@�B�j���B
						this->ringbuffer_recv.reset();
					}
				}else{
					//��M���B
					this->need_recv_size = -1;
				}
			}break;
		case Step::Data_OneChunkData:
			{
				//�f�[�^�B

				//TODO:Data_ChunkData�ɍ��킹��B

				//��M�f�[�^��͗p�����O�o�b�t�@�����M�f�[�^�����O�o�b�t�@�Ƀf�[�^���ړ��B
				s32 t_size_from_continuous = this->ringbuffer_recv->GetContinuousUseSize();
				s32 t_size_to_freesize = this->ringbuffer_data->GetFreeSize();
				while((t_size_from_continuous > 0)&&(t_size_to_freesize > 0)){

					if(t_size_from_continuous > t_size_to_freesize){
						t_size_from_continuous = t_size_to_freesize;
					}

					this->ringbuffer_data->CopyToBuffer(this->ringbuffer_recv->GetItemFromUseList(0),t_size_from_continuous);
					this->ringbuffer_recv->AddFree(t_size_from_continuous);
					this->copy_chunk_size += t_size_from_continuous;

					t_size_from_continuous = this->ringbuffer_recv->GetContinuousUseSize();
					t_size_to_freesize = this->ringbuffer_data->GetFreeSize();
				}

				//�R�s�[�ς݂̃R���e���c���T�C�Y�B
				this->copy_content_size = this->copy_chunk_size;

				if(this->header_content_length >= 0){
					this->need_recv_size = this->header_content_length - (this->copy_chunk_size + this->ringbuffer_recv->GetUseSize());

					if(this->need_recv_size < 0){
						this->need_recv_size = 0;
					}
				}else{
					//��M�T�C�Y���s���Ȃ̂Őؒf�����܂Ŏ�M����B
					this->need_recv_size = -1;
				}

				//���[�v���N�G�X�g�B�Ȃ��B
				return false;
			}break;
		case Step::Data_ChunkSize:
			{
				//�`�����N�T�C�Y�B

				s32 t_end_offset = NHttp::FindFromRingBuffer(*this->ringbuffer_recv.get(),'\r','\n');
				if(t_end_offset >= 0){
					u8 t_tempbuffer[1024];
					if(t_end_offset < (sizeof(t_tempbuffer) - 2)){

						this->ringbuffer_recv->CopyFromBuffer(t_tempbuffer,t_end_offset + 2);
						t_tempbuffer[t_end_offset + 0] = 0x00;
						t_tempbuffer[t_end_offset + 1] = 0x00;
						ASSERT(sizeof(t_tempbuffer) >= t_end_offset + 2);

						STLString t_line = reinterpret_cast<const char*>(&t_tempbuffer[0]);

						HexCharToInt(t_line,this->header_chunk_length);
						this->copy_chunk_size = 0;

						TAGLOG(L"Http_Recv","ChunkSize = %d",this->header_chunk_length);

						if(this->header_chunk_length == 0){
							//�R���e���c�̏I�[�B
							this->header_content_length = this->copy_content_size;
						}
						
						this->step = Step::Data_ChunkData;

						//���[�v���N�G�X�g�B�A�������B
						return true;
					}else{
						//��̓G���[�B
						this->iserror = true;

						//��M�f�[�^��͗p�o�b�t�@�B�j���B
						this->ringbuffer_recv.reset();
					}
				}else{
					//��M���B
					this->need_recv_size = -1;
				}
			}break;
		case Step::Data_ChunkData:
			{
				//�`�����N�f�[�^�B
				
				//��M�f�[�^��͗p�����O�o�b�t�@�����M�f�[�^�����O�o�b�t�@�Ƀf�[�^���ړ��B
				s32 t_size_from_continuous = this->ringbuffer_recv->GetContinuousUseSize();
				s32 t_size_to_freesize = this->ringbuffer_data->GetFreeSize();

				//�󂫗e�ʈȏ�̃R�s�[�͂ł��Ȃ��B
				if(t_size_from_continuous > t_size_to_freesize){
					t_size_from_continuous = t_size_to_freesize;
				}

				//�c��̃R�s�[���K�v�ȃT�C�Y�B
				if(t_size_from_continuous >= this->header_chunk_length - this->copy_chunk_size){
					t_size_from_continuous = this->header_chunk_length - this->copy_chunk_size;
				}

				//�R�s�[�B
				if(t_size_from_continuous > 0){
					this->ringbuffer_data->CopyToBuffer(this->ringbuffer_recv->GetItemFromUseList(0),t_size_from_continuous);
					this->ringbuffer_recv->AddFree(t_size_from_continuous);
					this->copy_chunk_size += t_size_from_continuous;
				}

				//�R�s�[�ς݂̃R���e���c���T�C�Y�B
				this->copy_content_size = this->copyfix_chunk_size + this->copy_chunk_size;

				//��M���K�v�ȃT�C�Y�B
				this->need_recv_size = this->header_chunk_length - (this->copy_chunk_size + this->ringbuffer_recv->GetUseSize());
				if(this->need_recv_size < 0){
					this->need_recv_size = 0;
				}

				if(this->copy_chunk_size >= this->header_chunk_length){
					//�`�����N�̃R�s�[�����B
					this->step = Step::Data_ChunkEnd;

					//���[�v���N�G�X�g�B�A�������B
					return true;
				}

				//���[�v���N�G�X�g�B�Ȃ��B
				return false;
			}break;
		case Step::Data_ChunkEnd:
			{
				//�`�����N�G���h�B

				s32 t_end_offset = NHttp::FindFromRingBuffer(*this->ringbuffer_recv.get(),'\r','\n');
				if(t_end_offset >= 0){
					u8 t_tempbuffer[1024];
					if(t_end_offset < (sizeof(t_tempbuffer) - 2)){

						this->ringbuffer_recv->CopyFromBuffer(t_tempbuffer,t_end_offset + 2);
						t_tempbuffer[t_end_offset + 0] = 0x00;
						t_tempbuffer[t_end_offset + 1] = 0x00;
						ASSERT(sizeof(t_tempbuffer) >= t_end_offset + 2);

						this->step = Step::Data_ChunkSize;

						//���[�v���N�G�X�g�B�A�������B
						return true;
					}else{
						//��̓G���[�B
						this->iserror = true;

						//��M�f�[�^��͗p�o�b�t�@�B�j���B
						this->ringbuffer_recv.reset();
					}
				}else{
					//��M���B
					this->need_recv_size = -1;
				}
			}break;
		}

		//���[�v���N�G�X�g�B�Ȃ��B
		return false;
	}


}}
#endif

