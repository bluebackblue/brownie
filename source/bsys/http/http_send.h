#pragma once

/**
 * Copyright (c) 2016-2017 blueback
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


/** NBsys::NHttp
*/
#if(BSYS_HTTP_ENABLE)
#pragma warning(push)
#pragma warning(disable:4710 4820)
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

		/** 送信。
		*/
		void Send(const sharedptr<SocketHandle>& a_socket,const sharedptr<u8>& a_buffer,s32 a_size);

		/** 送信が完了したかどうか。
		*/
		bool IsBusy();

		/** エラー。
		*/
		bool IsError();

		/** 更新。
		*/
		bool Update();

	};


}}
#pragma warning(pop)
#endif

