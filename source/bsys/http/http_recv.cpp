

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
					t_size = static_cast<s32>(this->socket->Recv(t_data,t_need_recv_size,0,false));
					if(t_size < 0){
						//サーバからの切断。
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
			//エラー。
			this->iserror = true;

			//ループリクエスト。なし。
			return false;
		}

		//受信バッファ解析。
		switch(this->step){
		case Step::StateCode:
			{
				//ステータス。

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

						//ループリクエスト。連続処理。
						return true;
					}else{
						//解析エラー。
						this->iserror = true;

						//受信データ解析用バッファ。破棄。
						this->ringbuffer_recv.reset();
					}
				}else{
					//受信中。
					this->need_recv_size = -1;
				}
			}break;
		case Step::Header:
			{
				//ヘッダー。

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
							//ヘッダー終端。

							if(this->header_is_transfer_encodeing_chunked == true){
								this->step = Step::Data_ChunkSize;
							}else{
								this->step = Step::Data_OneChunkData;
							}

							this->copy_content_size = 0;
							this->copy_chunk_size = 0;
							this->copyfix_chunk_size = 0;

							this->header_is_recv = true;

							//ループリクエスト。連続処理。
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

							//ループリクエスト。連続処理。
							return true;
						}
					}else{
						//解析エラー。
						this->iserror = true;

						//受信データ解析用バッファ。破棄。
						this->ringbuffer_recv.reset();
					}
				}else{
					//受信中。
					this->need_recv_size = -1;
				}
			}break;
		case Step::Data_OneChunkData:
			{
				//データ。

				//TODO:Data_ChunkDataに合わせる。

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

				//コピー済みのコンテンツ総サイズ。
				this->copy_content_size = this->copy_chunk_size;

				if(this->header_content_length >= 0){
					this->need_recv_size = this->header_content_length - (this->copy_chunk_size + this->ringbuffer_recv->GetUseSize());

					if(this->need_recv_size < 0){
						this->need_recv_size = 0;
					}
				}else{
					//受信サイズが不明なので切断されるまで受信する。
					this->need_recv_size = -1;
				}

				//ループリクエスト。なし。
				return false;
			}break;
		case Step::Data_ChunkSize:
			{
				//チャンクサイズ。

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
							//コンテンツの終端。
							this->header_content_length = this->copy_content_size;
						}
						
						this->step = Step::Data_ChunkData;

						//ループリクエスト。連続処理。
						return true;
					}else{
						//解析エラー。
						this->iserror = true;

						//受信データ解析用バッファ。破棄。
						this->ringbuffer_recv.reset();
					}
				}else{
					//受信中。
					this->need_recv_size = -1;
				}
			}break;
		case Step::Data_ChunkData:
			{
				//チャンクデータ。
				
				//受信データ解析用リングバッファから受信データリングバッファにデータを移動。
				s32 t_size_from_continuous = this->ringbuffer_recv->GetContinuousUseSize();
				s32 t_size_to_freesize = this->ringbuffer_data->GetFreeSize();

				//空き容量以上のコピーはできない。
				if(t_size_from_continuous > t_size_to_freesize){
					t_size_from_continuous = t_size_to_freesize;
				}

				//残りのコピーが必要なサイズ。
				if(t_size_from_continuous >= this->header_chunk_length - this->copy_chunk_size){
					t_size_from_continuous = this->header_chunk_length - this->copy_chunk_size;
				}

				//コピー。
				if(t_size_from_continuous > 0){
					this->ringbuffer_data->CopyToBuffer(this->ringbuffer_recv->GetItemFromUseList(0),t_size_from_continuous);
					this->ringbuffer_recv->AddFree(t_size_from_continuous);
					this->copy_chunk_size += t_size_from_continuous;
				}

				//コピー済みのコンテンツ総サイズ。
				this->copy_content_size = this->copyfix_chunk_size + this->copy_chunk_size;

				//受信が必要なサイズ。
				this->need_recv_size = this->header_chunk_length - (this->copy_chunk_size + this->ringbuffer_recv->GetUseSize());
				if(this->need_recv_size < 0){
					this->need_recv_size = 0;
				}

				if(this->copy_chunk_size >= this->header_chunk_length){
					//チャンクのコピー完了。
					this->step = Step::Data_ChunkEnd;

					//ループリクエスト。連続処理。
					return true;
				}

				//ループリクエスト。なし。
				return false;
			}break;
		case Step::Data_ChunkEnd:
			{
				//チャンクエンド。

				s32 t_end_offset = NHttp::FindFromRingBuffer(*this->ringbuffer_recv.get(),'\r','\n');
				if(t_end_offset >= 0){
					u8 t_tempbuffer[1024];
					if(t_end_offset < (sizeof(t_tempbuffer) - 2)){

						this->ringbuffer_recv->CopyFromBuffer(t_tempbuffer,t_end_offset + 2);
						t_tempbuffer[t_end_offset + 0] = 0x00;
						t_tempbuffer[t_end_offset + 1] = 0x00;
						ASSERT(sizeof(t_tempbuffer) >= t_end_offset + 2);

						this->step = Step::Data_ChunkSize;

						//ループリクエスト。連続処理。
						return true;
					}else{
						//解析エラー。
						this->iserror = true;

						//受信データ解析用バッファ。破棄。
						this->ringbuffer_recv.reset();
					}
				}else{
					//受信中。
					this->need_recv_size = -1;
				}
			}break;
		}

		//ループリクエスト。なし。
		return false;
	}


}}
#endif

