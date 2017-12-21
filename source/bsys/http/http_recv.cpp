

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ＨＴＴＰ。
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
		copy_content_recv_size(0),
		copy_chunk_size(0),
		header_is_recv(false),
		header_is_transfer_encodeing_chunked(false),
		header_content_length(-1),
		header_status_code(-1),
		step(Step::None)
	{
	}


	/** destructor
	*/
	Http_Recv::~Http_Recv()
	{
	}


	/** 受信を開始。
	*/
	void Http_Recv::StartRecv()
	{
		ASSERT(this->step == Step::None);

		this->need_recv_size = -1;
		this->step = Step::StateCode;
	}


	/** エラー。
	*/
	bool Http_Recv::IsError()
	{
		return this->iserror;
	}


	/** 受信済みで未解析データのサイズ。
	*/
	s32 Http_Recv::GetRecvRingBufferUseSize()
	{
		return this->ringbuffer_recv->GetUseSize();
	}


	/** 受信済みのコンテンツサイズ。
	*/
	s32 Http_Recv::GetContentRecvSize()
	{
		return this->copy_content_recv_size;
	}


	/** IsRecvHeader
	*/
	bool Http_Recv::IsRecvHeader()
	{
		return this->header_is_recv;
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


	/** 更新。
	*/
	bool Http_Recv::Update()
	{
		u8 t_data[1024 * 16];
		s32 t_size = 0;
		s32 t_need_recv_size = 0;

		if(this->need_recv_size < 0){
			//受信が必要。サイズは自動。
			t_need_recv_size = sizeof(t_data);
		}else if(this->need_recv_size > 0){
			//指定サイズ分の受信が必要。
			t_need_recv_size = this->need_recv_size;
			if(t_need_recv_size > sizeof(t_data)){
				t_need_recv_size = sizeof(t_data);
			}
		}

		if(this->socket){
			if(this->socket->IsOpen()){
				if(t_need_recv_size > 0){
					TAGLOG(L"Http_Recv","needrecvsize = %d\n",t_need_recv_size);
					t_size = static_cast<s32>(this->socket->Recv(t_data,t_need_recv_size,0,false));
					if(t_size < 0){
						TAGLOG(L"Http_Recv","Close\n");
						//通信切断。
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

		//受信バッファ解析。
		switch(this->step){
		case Step::StateCode:
			{
				//ステータス。

				s32 t_end_offset = NHttp::FindFromRingBuffer(*this->ringbuffer_recv.get(),'\r','\n');
				if(t_end_offset >= 0){

					u8 t_tempbuffer[1024];

					this->ringbuffer_recv->CopyFromBuffer(t_tempbuffer,t_end_offset + 2);
					t_tempbuffer[t_end_offset + 0] = 0x00;
					t_tempbuffer[t_end_offset + 1] = 0x00;

					STLString t_line = reinterpret_cast<char*>(&t_tempbuffer[0]);

					this->header_line.push_back(t_line);

					this->header_status_code = FindStatusCode(t_line);

					this->step = Step::Header;

					//再評価するために、ループリクエスト。
					return true;
				}else{
					//受信データ不足。

					if(this->socket){
						if(this->socket->IsOpen()){
							//受信データ不足、データが必要。ループリクエスト。
							this->need_recv_size = -1;
							return true;
						}
					}

					//エラー。
					this->iserror = true;
						
					//受信データ解析用バッファ。破棄。
					this->ringbuffer_recv.reset();
				}

			}break;
		case Step::Header:
			{
				//ヘッダー。

				for(;;){
					s32 t_end_offset = NHttp::FindFromRingBuffer(*this->ringbuffer_recv.get(),'\r','\n');
					if(t_end_offset >= 0){

						u8 t_tempbuffer[1024];

						this->ringbuffer_recv->CopyFromBuffer(t_tempbuffer,t_end_offset + 2);
						t_tempbuffer[t_end_offset + 0] = 0x00;
						t_tempbuffer[t_end_offset + 1] = 0x00;

						STLString t_line = reinterpret_cast<const char*>(&t_tempbuffer[0]);

						if(t_line == ""){
							//ヘッダー終端。

							if(this->header_is_transfer_encodeing_chunked == true){
								this->step = Step::Data_ChunkSize;
							}else{
								this->step = Step::Data_OneChunkData;
							}

							this->copy_content_recv_size = 0;
							this->copy_chunk_size = 0;

							this->header_is_recv = true;

							//再評価するために、ループリクエスト。
							return true;
						}else{
							//行。

							TAGLOG(L"Http_Recv","%s",t_line.c_str());

							this->header_line.push_back(t_line);

							if(t_line == "Transfer-Encoding: chunked"){
								this->header_is_transfer_encodeing_chunked = true;
							}

							s32 t_content_length = NHttp::FindContentsLength(t_line);
							if(t_content_length >= 0){
								this->header_content_length = t_content_length;
							}
						}
					}else{
						//受信データ不足。

						if(this->socket){
							if(this->socket->IsOpen()){
								//受信データ不足、データが必要。ループリクエスト。
								this->need_recv_size = -1;
								return true;
							}
						}

						//エラー。
						this->iserror = true;
						
						//受信データ解析用バッファ。破棄。
						this->ringbuffer_recv.reset();
					}
				}
			}break;
		case Step::Data_OneChunkData:
			{
				//データ。

				//受信データ解析用リングバッファから受信データリングバッファにデータを移動。
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

				//コピー済みのサイズ + コピー待ちのサイズ。
				this->copy_content_recv_size = this->copy_chunk_size + this->ringbuffer_recv->GetUseSize();

				if(this->header_content_length >= 0){
					if(this->header_content_length <= this->copy_content_recv_size){
						//受信完了。
						this->need_recv_size = 0;
					}else{
						//受信継続。
						this->need_recv_size = this->header_content_length - this->copy_content_recv_size;
					}
				}else{
					//受信サイズ不明。
				}
			}break;
		case Step::Data_ChunkSize:
			{
				//チャンクサイズ。

				/*
				s32 t_end_offset = NHttp::FindFromRingBuffer(*this->buffer.get(),'\r','\n');
				if(t_end_offset >= 0){
					//サイズあり。

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
				//チャンクデータ。
				
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
				//チャンクエンド。

				/*
				s32 t_end_offset = NHttp::FindFromRingBuffer(*this->buffer.get(),'\r','\n');
				if(t_end_offset >= 0){
					//サイズあり。

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

		//ループリクエスト。なし。
		return false;
	}


}}
#endif

