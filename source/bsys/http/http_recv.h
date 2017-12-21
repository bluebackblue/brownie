#pragma once

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ＨＴＴＰ。
*/


/** include
*/
#include "../types/types.h"


/** NBsys::NHttp
*/
#if(BSYS_HTTP_ENABLE)
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

				Data_NoChunkData,

				Data_ChunkSize,
				Data_ChunkData,
				Data_ChunkEnd,
			};
		};

	private:

		/** socket
		*/
		sharedptr<SocketHandle> socket;

		/** iserror
		*/
		bool iserror;

		/** 受信データ解析用バッファ。
		*/
		sharedptr<RingBufferBase<u8>> ringbuffer_recv;

		/** 受信データバッファ。
		*/
		sharedptr<RingBufferBase<u8>> ringbuffer_data;

		/** header_line
		*/
		STLVector<STLString>::Type header_line;

		/** need_recv_size
		*/
		s32 need_recv_size;

		/** copy_to_offset
		*/
		s32 copy_to_offset;

		/** is_transfer_encodeing_chunked
		*/
		bool is_transfer_encodeing_chunked;

		/** header_content_length
		*/
		s32 header_content_length;

		/** step
		*/
		Step::Id step;

	public:

		/** constructor
		*/
		Http_Recv(const sharedptr<SocketHandle>& a_socket,sharedptr<RingBufferBase<u8>>& a_ringbuffer);

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
		s32 GetRecvRingBufferSize();

		/** 更新。
		*/
		bool Update();

	};


}}
#endif

