﻿#pragma once

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ＨＴＴＰ。
*/


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


/** NBsys::NHttp
*/
#if(BSYS_HTTP_ENABLE)
#pragma warning(push)
#pragma warning(disable:4710 4820)
namespace NBsys{namespace NHttp
{
	/** Http_Recv
	*/
	class Http_Recv
	{
	private:

		/** Step
		*/
		struct Step
		{
			enum Id
			{
				None = 0,

				StateCode,
				Header,

				Data_OneChunkData,

				Data_ChunkSize,
				Data_ChunkData,
				Data_ChunkEnd,
			};
		};

	private:

		/** socket
		*/
		sharedptr<SocketHandle> socket;

		/** ssl_socket
		*/
		#if(BSYS_OPENSSL_ENABLE)
		sharedptr<NBsys::NOpenSsl::OpenSsl_Socket> ssl_socket;
		#endif

		/** iserror
		*/
		bool iserror;

		/** 受信バッファ。
		*/
		sharedptr<u8> recvbuffer;

		/** 受信バッファサイズ。
		*/
		s32 recvbuffer_size;

		/** 受信データ解析用バッファ。
		*/
		sharedptr<RingBufferBase<u8>> ringbuffer_recv;

		/** 受信データバッファ。
		*/
		sharedptr<RingBufferBase<u8>> ringbuffer_data;

		/** header_line
		*/
		STLVector<STLString>::Type header_line;

		/** 受信が必要なサイズ。
		*/
		s32 need_recv_size;

		/** 現在のチャンクのコピー済みサイズ。
		*/
		s32 copy_chunk_size;

		/** 完了しているチャンクのコピー済みサイズ。
		*/
		s32 copyfix_chunk_size;

		/** コピー済みコンテンツサイズ。
		*/
		s32 copy_content_size;

		/** header_is_recv
		*/
		bool header_is_recv;

		/** header_is_transfer_encodeing_chunked
		*/
		bool header_is_transfer_encodeing_chunked;

		/** header_content_length
		*/
		s32 header_content_length;

		/** header_chunk_length
		*/
		s32 header_chunk_length;

		/** header_status_code
		*/
		s32 header_status_code;

		/** step
		*/
		Step::Id step;

	public:

		/** constructor
		*/
		#if(BSYS_OPENSSL_ENABLE)
		Http_Recv(const sharedptr<SocketHandle>& a_socket,const sharedptr<NBsys::NOpenSsl::OpenSsl_Socket>& a_ssl_socket,sharedptr<RingBufferBase<u8>>& a_ringbuffer);
		#else
		Http_Recv(const sharedptr<SocketHandle>& a_socket,sharedptr<RingBufferBase<u8>>& a_ringbuffer);
		#endif

		/** destructor
		*/
		nonvirtual ~Http_Recv();

	public:

		/** 受信を開始。
		*/
		void StartRecv();

		/** エラー。
		*/
		bool IsError();

		/** 受信データ解析用バッファの使用サイズ。
		*/
		s32 GetRecvRingBufferUseSize();

		/** IsRecvHeader
		*/
		bool IsRecvHeader();

		/** IsCopyContent
		*/
		bool IsCopyContent();

		/** GetStatusCode
		*/
		s32 GetStatusCode();

		/** GetContentLength
		*/
		s32 GetContentLength();

		/** 更新。
		*/
		bool Update();

	};


}}
#pragma warning(pop)
#endif

