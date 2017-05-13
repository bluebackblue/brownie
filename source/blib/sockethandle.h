#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �\�P�b�g�n���h���B
*/


/** include
*/
#include "./types.h"
#include "./platform.h"


/** include
*/
#include "./sharedptr.h"
#include "./stlstring.h"


/** NBlib
*/
namespace NBlib
{
	/** SocketHandle_Impl
	*/
	class SocketHandle_Impl;

	/** SocketHandle
	*/
	class SocketHandle
	{
	private:
		/** impl
		*/
		sharedptr< SocketHandle_Impl > impl;

	public:
		/** GetImpl
		*/
		sharedptr< SocketHandle_Impl >& GetImpl();

	public:
		/** constructor
		*/
		SocketHandle();

		/** constructor
		*/
		SocketHandle(sharedptr< SocketHandle_Impl >& a_impl);

		/** destructor
		*/
		nonvirtual ~SocketHandle();

		/** GetHostIp
		*/
		static bool GetHostIp(STLString& a_ip_name);

	public:

		/** �J���B
		*/
		bool OpenTcp();

		/** �J���B
		*/
		bool OpenUdp();

		/** ����B
		*/
		void Close();

		/** �ڑ��B
		*/
		bool ConnectTcp(const STLString& a_ip,s32 a_port);

		/** �ڑ��B
		*/
		bool ConnectUdp(const STLString& a_ip,s32 a_port);

		/** �o�C���h�B
		*/
		bool Bind(s32 a_port);

		/** Listen
		*/
		bool Listen();

		/** Accept
		*/
		sharedptr< SocketHandle > Accept();

		/** �u���[�h�L���X�g�ݒ�B
		*/
		void SetBroadcast(bool a_flag);

		/** �m���u���b�N�ݒ�B
		*/
		void SetNonblock(bool a_flag);

		/** ���M�B
		*/
		bool Send(const u8* a_data,s64 a_size,s64 a_offsets);

		/** ���M�B
		*/
		bool SendUdp(const u8* a_data,s64 a_size,s64 a_offset);

		/** ��M�B
		*/
		s64 Recv(u8* a_data,s64 a_size,s64 a_offset,bool a_complete);

		/** �J���Ă��邩�ǂ����B
		*/
		bool IsOpen() const;

	};
}

