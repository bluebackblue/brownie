

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

	#pragma warning(push)
	#pragma warning(disable:4464)
	#include "../openssl/openssl.h"
	#pragma warning(pop)

#endif



/** include
*/
#include "./http.h"
#include "./http_recv.h"
#include "./http_send.h"
#include "./http_bodystring.h"
#include "./http_binaryitem.h"


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
	Http::Http()
		:
		host(""),
		port(80),
		mode(Http_Mode::Get),
		ssl(false),
		#if(BSYS_OPENSSL_ENABLE)
		ssl_socket(),
		#endif
		url(""),
		boundary_string(NHttp::MakeBoundaryString()),
		step(Step::None),
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


	/** SetSsl
	*/
	void Http::SetSsl(bool a_flag)
	{
		this->ssl = a_flag;
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


	/** コンテンツ追加。
	*/
	void Http::AddPostContent(const STLString& a_name,const STLString& a_filename,sharedptr< u8 >& a_data,s32 a_size)
	{
		//ヘッダー。
		STLString t_body_header = NHttp::MakeBodyString_BinaryHeader(this->boundary_string,a_name,a_filename);
		
		//フッター。
		STLString t_body_footer = NHttp::MakeBodyString_BinarFooter();

		//バッファ。
		u32 t_buffer_size = static_cast<u32>(a_size + t_body_header.length() + t_body_footer.length());
		sharedptr<Http_BinaryItem> t_binary_item(new Http_BinaryItem());
		t_binary_item->data.reset(new u8[t_buffer_size + 1],default_delete<u8>());
		t_binary_item->data.get()[t_buffer_size] = 0x00;
		u8* t_buffer_data = t_binary_item->data.get();
		t_binary_item->size = static_cast<s32>(t_buffer_size);

		//コピー。
		{
			u32 t_offset = 0;

			NMemory::Copy(&t_buffer_data[t_offset],(t_buffer_size - t_offset),t_body_header.c_str(),t_body_header.length());
			t_offset += static_cast<u32>(t_body_header.length());

			NMemory::Copy(&t_buffer_data[t_offset],(t_buffer_size - t_offset),a_data.get(),a_size);
			t_offset += static_cast<u32>(a_size);

			NMemory::Copy(&t_buffer_data[t_offset],(t_buffer_size - t_offset),t_body_footer.c_str(),t_body_footer.length());
			t_offset += static_cast<u32>(t_body_footer.length());

			ASSERT(t_offset == t_buffer_size);
		}

		this->binary_list.insert(std::make_pair(a_name,t_binary_item));
	}


	/** コンテンツ追加。
	*/
	void Http::AddPostContent(const STLString& a_name,const STLString& a_value)
	{
		//ヘッダー。
		STLString t_body_header = NHttp::MakeBodyString_TextHeader(this->boundary_string,a_name);
		
		//フッター。
		STLString t_body_footer = NHttp::MakeBodyString_TextFooter();

		//バッファ。
		u32 t_buffer_size = static_cast<u32>(a_value.length() + t_body_header.length() + t_body_footer.length());
		sharedptr<Http_BinaryItem> t_binary_item(new Http_BinaryItem());
		t_binary_item->data.reset(new u8[t_buffer_size + 1],default_delete<u8>());
		t_binary_item->data.get()[t_buffer_size] = 0x00;
		u8* t_buffer_data = t_binary_item->data.get();
		t_binary_item->size = static_cast<s32>(t_buffer_size);

		//コピー。
		{
			u32 t_offset = 0;

			NMemory::Copy(&t_buffer_data[t_offset],(t_buffer_size - t_offset),t_body_header.c_str(),t_body_header.length());
			t_offset += static_cast<u32>(t_body_header.length());

			NMemory::Copy(&t_buffer_data[t_offset],(t_buffer_size - t_offset),a_value.c_str(),a_value.length());
			t_offset += static_cast<u32>(a_value.length());

			NMemory::Copy(&t_buffer_data[t_offset],(t_buffer_size - t_offset),t_body_footer.c_str(),t_body_footer.length());
			t_offset += static_cast<u32>(t_body_footer.length());

			ASSERT(t_offset == t_buffer_size);
		}

		this->binary_list.insert(std::make_pair(a_name,t_binary_item));
	}


	/** IsError
	*/
	bool Http::IsError()
	{
		return this->iserror;
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


	/** 開始。
	*/
	void Http::ConnectStart(sharedptr<RingBufferBase<u8>> a_recv_buffer)
	{
		DEEPDEBUG_TAGLOG(BSYS_HTTP_DEBUG_ENABLE,L"http","ConnectStart");

		this->recv_buffer = a_recv_buffer;
		this->step = Step::Start;
		this->iserror = false;

		#if(BSYS_OPENSSL_ENABLE)
		if(this->ssl_socket != nullptr){
			this->ssl_socket->End();
			this->ssl_socket.reset();
		}
		#endif

		if(this->socket){
			if(this->socket->IsOpen()){
				this->socket->Close();
			}
		}

		//ソケット作成。
		this->socket.reset(new SocketHandle());
		#if(BSYS_OPENSSL_ENABLE)
		{
			this->ssl_socket.reset(new NBsys::NOpenSsl::OpenSsl_Socket());
		}
		#endif

		//受信設定。
		#if(BSYS_OPENSSL_ENABLE)
		this->recv.reset(new Http_Recv(this->socket,this->ssl_socket,this->recv_buffer));
		#else
		this->recv.reset(new Http_Recv(this->socket,this->recv_buffer));
		#endif

		//送信設定。
		this->send.reset(new Http_Send());
	}


	/** 終了。
	*/
	void Http::ConnectEnd()
	{
		DEEPDEBUG_TAGLOG(BSYS_HTTP_DEBUG_ENABLE,L"http","ConnectEnd");

		#if(BSYS_OPENSSL_ENABLE)
		if(this->ssl_socket != nullptr){
			this->ssl_socket->End();
			this->ssl_socket.reset();
		}
		#endif

		if(this->socket){
			if(this->socket->IsOpen()){
				this->socket->Close();
			}
		}

		this->step = Step::None;
		this->socket.reset();
		this->iserror = false;
		this->send_buffer.reset();
		this->recv_buffer.reset();
		this->send.reset();
		this->recv.reset();
	}


	/** 更新。
	*/
	bool Http::ConnectUpdate()
	{
		if(this->iserror == true){
			//中断。
			return false;
		}

		bool t_loop = true;
		while(t_loop){
			t_loop = false;

			if(this->send){
				if(this->send->Update() == true){
					//ループリクエスト。
					t_loop = true;
				}
				this->iserror = this->send->IsError();
			}
			if(this->recv){
				if(this->recv->Update() == true){
					//ループリクエスト。
					t_loop = true;
				}
				this->iserror = this->recv->IsError();
			}

			switch(this->step){
			case Step::None:
				{
				}break;
			case Step::Start:
				{
					{
						s32 t_binary_size = 0;

						//バイナリ総サイズ。
						if(this->mode == Http_Mode::Post){
							for(auto t_it = this->binary_list.cbegin();t_it!=this->binary_list.cend();t_it++){
								if(t_it->second != nullptr){
									t_binary_size += t_it->second->size;
								}
							}
						}

						//バイナリ終端文字列。
						STLString t_binary_footer = "";
						if(this->mode == Http_Mode::Post){
							NHttp::MakeBodyString_PostBinarFooter(this->boundary_string);
							t_binary_size += static_cast<s32>(t_binary_footer.length());
						}

						//ボディ作成。				
						STLString t_send_body = NHttp::MakeBodyString_Header(this->boundary_string,this->mode,this->url,this->host,t_binary_size);

						//バッファ。
						u32 t_buffer_size = static_cast<u32>(t_send_body.length() + t_binary_size);
						this->send_buffer.reset(new u8[t_buffer_size + 1],default_delete<u8>());
						this->send_buffer.get()[t_buffer_size] = 0x00;
						u8* t_buffer_data = this->send_buffer.get();

						//送信バッファの作成。
						{
							u32 t_offset = 0;

							//ボディー。
							NMemory::Copy(&t_buffer_data[t_offset],(t_buffer_size - t_offset),t_send_body.c_str(),t_send_body.length());
							t_offset += static_cast<u32>(t_send_body.length());

							if(this->mode == Http_Mode::Post){

								//バイナリ。
								for(auto t_it = this->binary_list.cbegin();t_it!=this->binary_list.cend();t_it++){
									if(t_it->second != nullptr){
										NMemory::Copy(&t_buffer_data[t_offset],(t_buffer_size - t_offset),t_it->second->data.get(),t_it->second->size);
										t_offset += static_cast<u32>(t_it->second->size);
									}
								}

								//バイナリ終端。
								NMemory::Copy(&t_buffer_data[t_offset],(t_buffer_size - t_offset),t_binary_footer.c_str(),t_binary_footer.length());
								t_offset += static_cast<u32>(t_binary_footer.length());
							}

							ASSERT(t_offset == t_buffer_size);
						}

						//送信バッファ設定。
						DEEPDEBUG_TAGLOG(BSYS_HTTP_DEBUG_ENABLE,L"http","sendrequest %d",t_buffer_size);
						#if(BSYS_OPENSSL_ENABLE)
						this->send->Send(this->socket,this->ssl_socket,this->send_buffer,static_cast<s32>(t_buffer_size));
						#else
						this->send->Send(this->socket,this->send_buffer,static_cast<s32>(t_buffer_size));
						#endif
					}

					this->step = Step::Connect;

					t_loop = true;
				}break;
			case Step::Connect:
				{
					//接続。

					if(this->socket->OpenTcp()){
						DEEPDEBUG_TAGLOG(BSYS_HTTP_DEBUG_ENABLE,L"http","OpenTcp");

						if(this->socket->ConnectTcp(this->host.c_str(),this->port) == true){
							DEEPDEBUG_TAGLOG(BSYS_HTTP_DEBUG_ENABLE,L"http","ConnectTcp : %s : %d",this->host.c_str(),this->port);

							#if(BSYS_OPENSSL_ENABLE)
							if(this->ssl == true){
								bool t_ret_connect = NBsys::NOpenSsl::Connect(this->socket,this->ssl_socket);
								if(t_ret_connect == false){
									//エラー。
									this->iserror = true;
								}
							}
							#endif

							if(this->iserror == false){
								this->step = Step::SendWait_StartData;
								t_loop = true;
							}
						}else{
							//エラー。
							this->iserror = true;
						}
					}else{
						//Winsockの初期化が行われていない等。

						//エラー。
						this->iserror = true;
					}
				}break;
			case Step::SendWait_StartData:
				{
					if(this->send->IsBusy() == false){
						//受信開始。
						this->recv->StartRecv();
						this->step = Step::RecvHeader;
					}else{
						//送信中。
					}

					//切断された。
					bool t_close = false;
					if(this->socket){
						if(this->socket->IsOpen() == false){
							t_close =  true;
						}
					}else{
						t_close = true;
					}

					if(t_close){
						//中断終了。
						return false;
					}
				}break;
			case Step::RecvHeader:
				{
					//ヘッダー受信完了チェック。
					if(this->recv->IsRecvHeader()){
						this->step = Step::Recv;
					}

					//切断された。
					bool t_close = false;
					if(this->socket){
						if(this->socket->IsOpen() == false){
							t_close =  true;
						}
					}else{
						t_close = true;
					}

					if(t_close){
						//中断終了。
						return false;
					}
				}break;
			case Step::Recv:
				{
					bool t_close = false;
					if(this->recv->IsCopyContent()){
						//コンテンツの外部バッファへのコピー完了。
						t_close = true;
					}

					if(this->socket){
						if(this->socket->IsOpen() == false){
							t_close =  true;
						}
					}else{
						t_close = true;
					}

					if(t_close == true){
						#if(BSYS_OPENSSL_ENABLE)
						if(this->ssl_socket != nullptr){
							this->ssl_socket->End();
							this->ssl_socket.reset();
						}
						#endif

						if(this->socket){
							if(this->socket->IsOpen()){
								this->socket->Close();
							}
						}

						//受信済みで未解析データのサイズ。
						if(this->recv){
							if(this->recv->GetRecvRingBufferUseSize() > 0){
								//継続。
								return true;
							}
						}

						//正常終了 or 中断終了。
						return false;
					}
				}break;
			}
		}

		//継続。
		return true;
	}


}}
#endif

