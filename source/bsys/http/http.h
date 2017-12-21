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


/** include
*/
#include "./http_recv_decl.h"
#include "./http_send_decl.h"
#include "./http_boundarystring.h"
#include "./http_type.h"


/** NBsys::NHttp
*/
#if(BSYS_HTTP_ENABLE)
namespace NBsys{namespace NHttp
{
	/** Http
	*/
	class Http
	{
	private:

		/** Step
		*/
		struct Step
		{
			enum Id
			{
				//�ڑ��B
				Connect,

				//���M�B����f�[�^�B
				Send_StartData,

				//���M�҂��B����f�[�^�B
				SendWait_StartData,

				//��M�҂��B
				RecvHeader,

				//��M�҂��B
				Recv,
			};
		};

	private:
	
		/** host
		*/
		STLString host;

		/** port
		*/
		s32 port;

		/** mode
		*/
		Http_Mode::Id mode;
		
		/** Url
		*/
		STLString url;
		
		/** boundary_string
		*/
		STLString boundary_string;

	private:

		/** step
		*/
		Step::Id step;

		/** socket
		*/
		sharedptr<SocketHandle> socket;

		/** iserror
		*/
		bool iserror;

		/** sendbuffer
		*/
		sharedptr<u8> send_buffer;

		/** recvbuffer
		*/
		sharedptr<RingBufferBase<u8>> recv_buffer;

		/** send
		*/
		sharedptr<Http_Send> send;

		/** recv
		*/
		sharedptr<Http_Recv> recv;

	public:

		/** constructor
		*/
		Http();

		/** destructor
		*/
		nonvirtual ~Http();

	public:

		/** SetHost
		*/
		void SetHost(const STLString& a_host);

		/** SetPort
		*/
		void SetPort(s32 a_port);

		/** SetMode
		*/
		void SetMode(Http_Mode::Id a_mode);

		/** SetUrl
		*/
		void SetUrl(const STLString& a_url);

		/** SetBoundaryString
		*/
		void SetBoundaryString(const STLString& a_boundary_string);

	public:

		/** IsRecvHeader
		*/
		bool IsRecvHeader();

		/** GetStatusCode
		*/
		s32 GetStatusCode();

		/** GetContentLength
		*/
		s32 GetContentLength();

	public:

		/** �J�n�B
		*/
		void ConnectStart(sharedptr<RingBufferBase<u8>>& a_recv_buffer);

		/** �I���B
		*/
		void ConnectEnd();

		/** �X�V�B

			�߂�l
				true	: �p��
				false	: �I��

		*/
		bool ConnectUpdate();



	};


}}
#endif

