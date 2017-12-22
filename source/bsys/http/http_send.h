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
	/** Http_Send
	*/
	class Http_Send
	{
	private:

		/** socket
		*/
		sharedptr<SocketHandle> socket;

		/** iserror
		*/
		bool iserror;

		/** send_buffer
		*/
		sharedptr<u8> buffer;

		/**
		*/
		s32 buffer_offset;

		/**
		*/
		s32 buffer_size;

	public:

		/** constructor
		*/
		Http_Send();

		/** destructor
		*/
		nonvirtual ~Http_Send();

	public:

		/** ���M�B
		*/
		void Send(const sharedptr<SocketHandle>& a_socket,const sharedptr<u8>& a_buffer,s32 a_size);

		/** ���M�������������ǂ����B
		*/
		bool IsBusy();

		/** �G���[�B
		*/
		bool IsError();

		/** �X�V�B
		*/
		bool Update();

	};


}}
#endif
