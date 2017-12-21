

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
		copy_to_offset(0),
		is_transfer_encodeing_chunked(false),
		header_content_length(-1),
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


	/** ��M�f�[�^��͗p�o�b�t�@�̎g�p�T�C�Y�B
	*/
	s32 Http_Recv::GetRecvRingBufferSize()
	{
		return this->ringbuffer_recv->GetUseSize();
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
		}

		if(this->socket){
			if(this->socket->IsOpen()){
				if(t_need_recv_size > 0){
					TAGLOG(L"Http_Recv","needrecvsize = %d\n",t_need_recv_size);
					t_size = static_cast<s32>(this->socket->Recv(t_data,t_need_recv_size,0,false));
					if(t_size < 0){
						TAGLOG(L"Http_Recv","Close\n");
						//�ʐM�ؒf�B
						this->socket->Close();
						this->socket.reset();
					}else{
						TAGLOG(L"Http_Recv","resvsize = %d\n",t_size);
						this->ringbuffer_recv->CopyToBuffer(t_data,t_size);
						this->need_recv_size = 0;
					}
				}
			}
		}

		//��M�o�b�t�@��́B
		switch(this->step){
		case Step::StateCode:
			{
				//�X�e�[�^�X�B

				s32 t_end_offset = NHttp::FindFromRingBuffer(*this->ringbuffer_recv.get(),'\r','\n');
				if(t_end_offset >= 0){

					u8 t_tempbuffer[1024];

					this->ringbuffer_recv->CopyFromBuffer(t_tempbuffer,t_end_offset + 2);
					t_tempbuffer[t_end_offset + 0] = 0x00;
					t_tempbuffer[t_end_offset + 1] = 0x00;

					//TODO:this->statecode = reinterpret_cast<const char*>(&t_tempbuffer[0]);

					this->step = Step::Header;

					//�ĕ]�����邽�߂ɁA���[�v���N�G�X�g�B
					return true;
				}else{
					//��M�f�[�^�s���B

					if(this->socket){
						if(this->socket->IsOpen()){
							//��M�f�[�^�s���A�f�[�^���K�v�B���[�v���N�G�X�g�B
							this->need_recv_size = -1;
							return true;
						}
					}

					//�G���[�B
					this->iserror = true;
						
					//��M�f�[�^��͗p�o�b�t�@�B�j���B
					this->ringbuffer_recv.reset();
				}

			}break;
		case Step::Header:
			{
				//�w�b�_�[�B

				for(;;){
					s32 t_end_offset = NHttp::FindFromRingBuffer(*this->ringbuffer_recv.get(),'\r','\n');
					if(t_end_offset >= 0){

						u8 t_tempbuffer[1024];

						this->ringbuffer_recv->CopyFromBuffer(t_tempbuffer,t_end_offset + 2);
						t_tempbuffer[t_end_offset + 0] = 0x00;
						t_tempbuffer[t_end_offset + 1] = 0x00;

						STLString t_line = reinterpret_cast<const char*>(&t_tempbuffer[0]);

						if(t_line == ""){
							//�w�b�_�[�I�[�B

							if(this->is_transfer_encodeing_chunked == true){
								this->step = Step::Data_ChunkSize;
							}else{
								this->step = Step::Data_NoChunkData;
							}

							this->copy_to_offset = 0;

							//�ĕ]�����邽�߂ɁA���[�v���N�G�X�g�B
							return true;
						}else{
							//�s�B

							this->header_line.push_back(t_line);

							if(t_line == "Transfer-Encoding: chunked"){
								this->is_transfer_encodeing_chunked = true;
							}

							s32 t_content_length = NHttp::FindContentsLength(t_line);
							if(t_content_length >= 0){
								this->header_content_length = t_content_length;
							}
						}
					}else{
						//��M�f�[�^�s���B

						if(this->socket){
							if(this->socket->IsOpen()){
								//��M�f�[�^�s���A�f�[�^���K�v�B���[�v���N�G�X�g�B
								this->need_recv_size = -1;
								return true;
							}
						}

						//�G���[�B
						this->iserror = true;
						
						//��M�f�[�^��͗p�o�b�t�@�B�j���B
						this->ringbuffer_recv.reset();
					}
				}
			}break;
		case Step::Data_NoChunkData:
			{
				//�f�[�^�B

				//��M�f�[�^��͗p�����O�o�b�t�@�����M�f�[�^�����O�o�b�t�@�Ƀf�[�^���ړ��B
				s32 t_size_from_continuous = this->ringbuffer_recv->GetContinuousUseSize();
				s32 t_size_to_freesize = this->ringbuffer_data->GetFreeSize();
				while((t_size_from_continuous > 0)&&(t_size_to_freesize > 0)){

					if(t_size_from_continuous > t_size_to_freesize){
						t_size_from_continuous = t_size_to_freesize;
					}

					this->ringbuffer_data->CopyToBuffer(this->ringbuffer_recv->GetItemFromUseList(0),t_size_from_continuous);
					this->ringbuffer_recv->AddFree(t_size_from_continuous);
					this->copy_to_offset += t_size_from_continuous;

					t_size_from_continuous = this->ringbuffer_recv->GetContinuousUseSize();
					t_size_to_freesize = this->ringbuffer_data->GetFreeSize();
				}

				if(this->copy_to_offset >= 0){
					if(this->copy_to_offset >= this->header_content_length){
						//��M�����B
						//�ĕ]�����邽�߂ɁA���[�v���N�G�X�g�B
						this->need_recv_size = -1;
					}else{
						//TODO:���m�F�B
						this->need_recv_size = this->header_content_length - (this->copy_to_offset + this->ringbuffer_recv->GetUseSize());
					}
				}
			}break;
		case Step::Data_ChunkSize:
			{
				//�`�����N�T�C�Y�B

				/*
				s32 t_end_offset = NHttp::FindFromRingBuffer(*this->buffer.get(),'\r','\n');
				if(t_end_offset >= 0){
					//�T�C�Y����B

					this->ringbuffer->CopyFromBuffer(this->tempbuffer,t_end_offset + 2);
					this->tempbuffer[t_end_offset + 0] = 0x00;
					this->tempbuffer[t_end_offset + 1] = 0x00;

					STLString t_line = reinterpret_cast<const char*>(&this->tempbuffer[0]);

					HexCharToInt(t_line,this->chunksize);

					TAGLOG(L"Http_Recv","chunk size = %d",this->chunksize);

					this->step = Step::Data_ChunkData;

					return ResultType::Result_ChunkSize;
				}else{
					return ResultType::NeedData;
				}
				*/

			}break;
		case Step::Data_ChunkData:
			{
				//�`�����N�f�[�^�B
				
				/*
				{
					s32 t_size = this->ringbuffer->GetUseSize();

					if(t_size > this->chunksize){
						t_size = this->chunksize;
					}

					if(t_size > 0){

						for(s32 ii=0;ii<t_size;ii++){
							u8 t_temp;
							this->ringbuffer->CopyFromBuffer(&t_temp,1);
							if(this->recvdata != nullptr){
								this->recvdata->CopyToBuffer(&t_temp,1);
							}
						}

						this->chunksize -= t_size;
					}
				}

				if(this->chunksize == 0){
					this->step = Step::Data_ChunkEnd;

					return ResultType::Result_ChunkData;
				}else{
					return ResultType::NeedData;
				}
				*/

			}break;
		case Step::Data_ChunkEnd:
			{
				//�`�����N�G���h�B

				/*
				s32 t_end_offset = NHttp::FindFromRingBuffer(*this->buffer.get(),'\r','\n');
				if(t_end_offset >= 0){
					//�T�C�Y����B

					this->ringbuffer->CopyFromBuffer(this->tempbuffer,t_end_offset + 2);
					this->tempbuffer[t_end_offset + 0] = 0x00;
					this->tempbuffer[t_end_offset + 1] = 0x00;

					this->step = Step::Data_ChunkSize;

					TAGLOG(L"Http_Recv","chunk end");

					return ResultType::Result_ChunkEnd;
				}else{
					return ResultType::NeedData;
				}
				*/

			}break;
		}

		//���[�v���N�G�X�g�B�Ȃ��B
		return false;
	}


}}
#endif

