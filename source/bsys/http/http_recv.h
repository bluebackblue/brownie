#pragma once

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �g�s�s�o�B
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

		/** iserror
		*/
		bool iserror;

		/** ��M�f�[�^��͗p�o�b�t�@�B
		*/
		sharedptr<RingBufferBase<u8>> ringbuffer_recv;

		/** ��M�f�[�^�o�b�t�@�B
		*/
		sharedptr<RingBufferBase<u8>> ringbuffer_data;

		/** header_line
		*/
		STLVector<STLString>::Type header_line;

		/** need_recv_size
		*/
		s32 need_recv_size;

		/** copy_content_recv_size
		*/
		s32 copy_content_recv_size;

		/** copy_chunk_size
		*/
		s32 copy_chunk_size;

		/** header_is_recv
		*/
		bool header_is_recv;

		/** header_is_transfer_encodeing_chunked
		*/
		bool header_is_transfer_encodeing_chunked;

		/** header_content_length
		*/
		s32 header_content_length;

		/** header_status_code
		*/
		s32 header_status_code;

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

		/** ��M���J�n�B
		*/
		void StartRecv();

		/** �G���[�B
		*/
		bool IsError();

		/** ��M�f�[�^��͗p�o�b�t�@�̎g�p�T�C�Y�B
		*/
		s32 GetRecvRingBufferUseSize();

		/** ��M�ς݂̃R���e���c�T�C�Y�B
		*/
		s32 GetContentRecvSize();

		/** IsRecvHeader
		*/
		bool IsRecvHeader();

		/** GetStatusCode
		*/
		s32 GetStatusCode();

		/** GetContentLength
		*/
		s32 GetContentLength();

		/** �X�V�B
		*/
		bool Update();

	};


}}
#endif

