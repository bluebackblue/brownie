

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �\�P�b�g�n���h���B
*/


/** include
*/
#include <blib_pch.h>


/** include
*/
#include "./types.h"
#include "./platform.h"


/** include
*/
#include "./sharedptr.h"
#include "./sockethandle.h"
#include "./sockethandle_impl.h"
#include "./stlstring.h"


/** NBlib
*/
namespace NBlib
{
	/** constructor
	*/
	SocketHandle::SocketHandle()
	{
		this->impl.reset(new SocketHandle_Impl());
	}

	/** constructor
	*/
	SocketHandle::SocketHandle(sharedptr<SocketHandle_Impl>& a_impl)
		:
		impl(a_impl)
	{
	}

	/** GetImpl
	*/
	sharedptr<SocketHandle_Impl>& SocketHandle::GetImpl()
	{
		return this->impl;
	}

	/** destructor
	*/
	SocketHandle::~SocketHandle()
	{
		this->impl.reset();
	}

	/** [static]GetHostIp
	*/
	bool SocketHandle::GetHostIp(STLString& a_ip_name)
	{
		return SocketHandle_Impl::GetHostIp(a_ip_name);
	}

	/** �J���B
	*/
	bool SocketHandle::OpenTcp()
	{
		return this->impl->OpenTcp();
	}

	/** �J���B
	*/
	bool SocketHandle::OpenUdp()
	{
		return this->impl->OpenUdp();
	}

	/** ����B
	*/
	void SocketHandle::Close()
	{
		this->impl->Close();
	}

	/** �ڑ��B
	*/
	bool SocketHandle::ConnectTcp(const STLString& a_ip,s32 a_port)
	{
		return this->impl->ConnectTcp(a_ip,a_port);
	}

	/** �ڑ��B
	*/
	bool SocketHandle::ConnectUdp(const STLString& a_ip,s32 a_port)
	{
		return this->impl->ConnectUdp(a_ip,a_port);
	}

	/** �o�C���h�B
	*/
	bool SocketHandle::Bind(s32 a_port)
	{
		return this->impl->Bind(a_port);
	}

	/** Listen
	*/
	bool SocketHandle::Listen()
	{
		return this->impl->Listen();
	}

	/** Accept
	*/
	sharedptr<SocketHandle> SocketHandle::Accept()
	{
		return this->impl->Accept();
	}

	/** �u���[�h�L���X�g�ݒ�B
	*/
	void SocketHandle::SetBroadcast(bool a_flag)
	{
		this->impl->SetBroadcast(a_flag);
	}

	/** �m���u���b�N�ݒ�B
	*/
	void SocketHandle::SetNonblock(bool a_flag)
	{
		this->impl->SetNonblock(a_flag);
	}

	/** ���M�B
	*/
	bool SocketHandle::Send(const u8* a_data,s64 a_size,s64 a_offsets)
	{
		return this->impl->Send(a_data,a_size,a_offsets);
	}

	/** ���M�B
	*/
	bool SocketHandle::SendUdp(const u8* a_data,s64 a_size,s64 a_offset)
	{
		return this->impl->SendUdp(a_data,a_size,a_offset);
	}

	/** ��M�B
	*/
	s64 SocketHandle::Recv(u8* a_data,s64 a_size,s64 a_offset,bool a_complete)
	{
		return this->impl->Recv(a_data,a_size,a_offset,a_complete);
	}

	/** �J���Ă��邩�ǂ����B
	*/
	bool SocketHandle::IsOpen() const
	{
		return this->impl->IsOpen();
	}
}

