

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ソケットハンドル。
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


/** warning

4710 : この関数はインライン展開のために選択されましたが、コンパイラはインライン展開を実行しませんでした。

*/
#pragma warning(disable:4710)


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


	/** 開く。
	*/
	bool SocketHandle::OpenTcp()
	{
		return this->impl->OpenTcp();
	}


	/** 開く。
	*/
	bool SocketHandle::OpenUdp()
	{
		return this->impl->OpenUdp();
	}


	/** 閉じる。
	*/
	void SocketHandle::Close()
	{
		this->impl->Close();
	}


	/** 接続。
	*/
	bool SocketHandle::ConnectTcp(const STLString& a_ip,s32 a_port)
	{
		return this->impl->ConnectTcp(a_ip,a_port);
	}


	/** 接続。
	*/
	bool SocketHandle::ConnectUdp(const STLString& a_ip,s32 a_port)
	{
		return this->impl->ConnectUdp(a_ip,a_port);
	}


	/** バインド。
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


	/** ブロードキャスト設定。
	*/
	void SocketHandle::SetBroadcast(bool a_flag)
	{
		this->impl->SetBroadcast(a_flag);
	}


	/** ノンブロック設定。
	*/
	void SocketHandle::SetNonblock(bool a_flag)
	{
		this->impl->SetNonblock(a_flag);
	}


	/** 送信。
	*/
	bool SocketHandle::Send(const u8* a_data,s64 a_size,s64 a_offsets)
	{
		return this->impl->Send(a_data,a_size,a_offsets);
	}


	/** 送信。
	*/
	bool SocketHandle::SendUdp(const u8* a_data,s64 a_size,s64 a_offset)
	{
		return this->impl->SendUdp(a_data,a_size,a_offset);
	}


	/** 受信。
	*/
	s64 SocketHandle::Recv(u8* a_data,s64 a_size,s64 a_offset,bool a_complete)
	{
		return this->impl->Recv(a_data,a_size,a_offset,a_complete);
	}


	/** 開いているかどうか。
	*/
	bool SocketHandle::IsOpen() const
	{
		return this->impl->IsOpen();
	}


}

