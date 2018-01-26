

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ソケットハンドル。実装部分。
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
#include "./debugassert.h"
#include "./sockethandle_impl.h"
#include "./memory.h"


/** winsock2
*/
#if defined(PLATFORM_VCWIN)

	#pragma comment(lib,"ws2_32.lib")

#endif


/** warning

4710 : この関数はインライン展開のために選択されましたが、コンパイラはインライン展開を実行しませんでした。

*/
#pragma warning(disable:4710)


/** NBlib
*/
#pragma warning(push)
#pragma warning(disable:4711)
namespace NBlib
{
	/** constructor
	*/
	SocketHandle_Impl::SocketHandle_Impl() noexcept
		:
		#if defined(PLATFORM_VCWIN)

		rawhandle(INVALID_SOCKET),
		rawaddrinfo(nullptr),

		#endif

		isopen(false)
	{
	}


	/** constructor
	*/
	#if defined(PLATFORM_VCWIN)
	SocketHandle_Impl::SocketHandle_Impl(SOCKET a_rawhandle) noexcept
		:
		rawhandle(a_rawhandle),
		rawaddrinfo(nullptr),
		isopen(true)
	{
	}
	#endif


	/** destructor
	*/
	SocketHandle_Impl::~SocketHandle_Impl() noexcept
	{
		this->Close();
	}


	/** [static]GetHostIp
	*/
	bool SocketHandle_Impl::GetHostIp(STLString& a_ip_name)
	{
		bool t_ret = false;

		#if defined(PLATFORM_VCWIN)
		{
			char t_hostname[NI_MAXHOST + 1] = {nullchar};
			if(::gethostname(t_hostname,sizeof(t_hostname)) == 0){
				addrinfo t_addrinfo_hints = {0};
				{
					t_addrinfo_hints.ai_family = PF_INET;
					t_addrinfo_hints.ai_flags = AI_CANONNAME;
				}

				addrinfo* t_addrinfo_reference = nullptr;
				if(::getaddrinfo(t_hostname,0,&t_addrinfo_hints,&t_addrinfo_reference) == 0){
					char t_ip_name[256] = {0};
					if(::getnameinfo(t_addrinfo_reference->ai_addr,static_cast<s32>(t_addrinfo_reference->ai_addrlen),t_ip_name,sizeof(t_ip_name),0,0,NI_NUMERICHOST) == 0){
						a_ip_name = t_ip_name;
						t_ret = true;
					}
					::freeaddrinfo(t_addrinfo_reference);
				}
			}
		}
		#else
		{
			ASSERT(0);
			UNUSED(a_ip_name);
		}
		#endif

		return t_ret;
	}


	/** 開く。
	*/
	bool SocketHandle_Impl::OpenTcp()
	{
		if(this->isopen == false){

			#if defined(PLATFORM_VCWIN)
			{
				this->rawhandle = ::socket(AF_INET,SOCK_STREAM,0);
				if(this->rawhandle == INVALID_SOCKET){
					return false;
				}
			}
			#else
			{
				ASSERT(0);
				return false;
			}
			#endif

			this->isopen = true;
			return true;
		}else{
			return false;
		}
	}


	/** 開く。
	*/
	bool SocketHandle_Impl::OpenUdp()
	{
		if(this->isopen == false){

			#if defined(PLATFORM_VCWIN)
			{
				this->rawhandle = ::socket(AF_INET,SOCK_DGRAM,0);
				if(this->rawhandle == INVALID_SOCKET){
					return false;
				}
			}
			#else
			{
				ASSERT(0);
				return false;
			}
			#endif

			this->isopen = true;
			return true;
		}else{
			return false;
		}
	}


	/** 閉じる。
	*/
	void SocketHandle_Impl::Close()
	{
		if(this->isopen){
			this->isopen = false;

			#if defined(PLATFORM_VCWIN)
			{
				::closesocket(this->rawhandle);
				this->rawhandle = INVALID_SOCKET;

				if(this->rawaddrinfo != nullptr){
					::freeaddrinfo(this->rawaddrinfo);
					this->rawaddrinfo = nullptr;
				}
			}
			#else
			{
				ASSERT(0);
			}
			#endif
		}
	}


	/** 接続。
	*/
	bool SocketHandle_Impl::ConnectTcp(const STLString& a_ip,s32 a_port)
	{
		if(this->isopen){

			#if defined(PLATFORM_VCWIN)
			{
				{
					addrinfo t_addrinfo_hints = {0};
					{
						t_addrinfo_hints.ai_socktype = SOCK_STREAM;
						t_addrinfo_hints.ai_family = AF_INET;
					}
				
					STLString t_port(ToString(a_port));

					if(::getaddrinfo(a_ip.c_str(),t_port.c_str(),&t_addrinfo_hints,&this->rawaddrinfo) != 0){
						this->rawaddrinfo = nullptr;
						return false;
					}
				}

				if(::connect(this->rawhandle,this->rawaddrinfo->ai_addr,static_cast<s32>(this->rawaddrinfo->ai_addrlen)) != 0){
					return false;
				}
			}
			#else
			{
				ASSERT(0);

				UNUSED(a_ip);
				UNUSED(a_port);
			}
			#endif

			return true;
		}else{
			return false;
		}
	}


	/** 接続。
	*/
	bool SocketHandle_Impl::ConnectUdp(const STLString& a_ip,s32 a_port)
	{
		if(this->isopen){

			#if defined(PLATFORM_VCWIN)
			{
				STLString t_port(ToString(a_port));

				addrinfo t_addrinfo_hints = {0};
				{
					t_addrinfo_hints.ai_family = AF_INET;
					t_addrinfo_hints.ai_socktype = SOCK_DGRAM;
				}

				if(::getaddrinfo(a_ip.c_str(),t_port.c_str(),&t_addrinfo_hints,&this->rawaddrinfo) != 0){
					return false;
				}
			}
			#else
			{
				ASSERT(0);

				UNUSED(a_ip);
				UNUSED(a_port);
			}
			#endif

			return true;
		}else{
			return false;
		}
	}


	/** バインド。
	*/
	bool SocketHandle_Impl::Bind(s32 a_port)
	{
		if(this->isopen){

			#if defined(PLATFORM_VCWIN)
			{
				sockaddr_in t_sockaddr_in = {0};
				{
					t_sockaddr_in.sin_family = AF_INET;
					t_sockaddr_in.sin_port = ::htons(static_cast<USHORT>(a_port));
					t_sockaddr_in.sin_addr.S_un.S_addr = INADDR_ANY;
				}

				if(::bind(this->rawhandle,(struct sockaddr*)&t_sockaddr_in,sizeof(t_sockaddr_in)) != 0){
					return false;
				}
			}
			#else
			{
				ASSERT(0);

				UNUSED(a_port);
			}
			#endif

			return true;
		}else{
			return false;
		}
	}


	/** Listen
	*/
	bool SocketHandle_Impl::Listen()
	{
		if(this->isopen){

			#if defined(PLATFORM_VCWIN)
			{
				if(::listen(this->rawhandle,1) != 0){
					return false;
				}
			}
			#else
			{
				ASSERT(0);
				return false;
			}
			#endif

			return true;
		}else{
			return false;
		}
	}
	

	/** Accept
	*/
	sharedptr<SocketHandle> SocketHandle_Impl::Accept()
	{
		if(this->isopen){

			#if defined(PLATFORM_VCWIN)
			{
				struct sockaddr_in t_addr_client;
				s32 t_addr_client_len = sizeof(t_addr_client);

				SOCKET t_rawhandle_client = ::accept(this->rawhandle,(struct sockaddr *)&t_addr_client,&t_addr_client_len);

				sharedptr<SocketHandle_Impl> t_client_impl(new SocketHandle_Impl(t_rawhandle_client));

				sharedptr<SocketHandle> t_client(new SocketHandle(t_client_impl));

				return t_client;
			}
			#else
			{
				ASSERT(0);

				return nullptr;
			}
			#endif

		}else{
			return nullptr;
		}
	}


	/** ブロードキャスト設定。
	*/
	void SocketHandle_Impl::SetBroadcast(bool a_flag)
	{
		#if defined(PLATFORM_VCWIN)
		{
			s32 t_flag = (a_flag ? 1 : 0);

			s32 t_ret = ::setsockopt(this->rawhandle,SOL_SOCKET,SO_BROADCAST,reinterpret_cast<char*>(&t_flag),sizeof(t_flag));
			UNUSED(t_ret);
			ASSERT(t_ret == 0);
		}
		#else
		{
			ASSERT(0);

			UNUSED(a_flag);
		}
		#endif
	}


	/** ノンブロック設定。
	*/
	void SocketHandle_Impl::SetNonblock(bool a_flag)
	{
		#if defined(PLATFORM_VCWIN)
		{
			u32 t_flag = static_cast<u32>(a_flag ? 1 : 0);

			s32 t_ret = ::ioctlsocket(this->rawhandle,FIONBIO,reinterpret_cast<u_long*>(&t_flag));
			UNUSED(t_ret);
			ASSERT(t_ret == 0);
		}
		#else
		{
			ASSERT(0);

			UNUSED(a_flag);
		}
		#endif
	}


	/** 送信。
	*/
	bool SocketHandle_Impl::SendUdp(const u8* a_data,s64 a_size,s64 a_offset)
	{
		#if defined(PLATFORM_VCWIN)
		{
			s64 t_offset = 0LL;
			s64 t_size = a_size - t_offset;
			s32 t_ret = ::sendto(this->rawhandle,reinterpret_cast<const char*>(&a_data[t_offset+a_offset]),static_cast<s32>(t_size),0,this->rawaddrinfo->ai_addr,static_cast<s32>(this->rawaddrinfo->ai_addrlen));
			if(t_ret <= 0){
				return false;
			}
		}
		#else
		{
			ASSERT(0);

			UNUSED(a_data);
			UNUSED(a_size);
			UNUSED(a_offset);
		}
		#endif

		return true;
	}


	/** 送信。
	*/
	bool SocketHandle_Impl::Send(const u8* a_data,s64 a_size,s64 a_offset)
	{
		if(this->isopen){

			#if defined(PLATFORM_VCWIN)
			{
				s64 t_offset = 0LL;
				while(1){
					s64 t_size = a_size - t_offset;
					if(t_size <= 0){
						return true;
					}else{
						s32 t_fix = ::send(this->rawhandle,reinterpret_cast<const char*>(&a_data[t_offset+a_offset]),static_cast<s32>(t_size),0);
						if(t_fix > 0){
							t_offset += t_fix;
						}else{
							return false;
						}
					}
				}
			}
			#else
			{
				ASSERT(0);

				UNUSED(a_data);
				UNUSED(a_size);
				UNUSED(a_offset);

				return false;
			}
			#endif

		}else{
			return false;
		}
	}


	/** 受信。
	*/
	s64 SocketHandle_Impl::Recv(u8* a_data,s64 a_size,s64 a_offset,bool a_complete)
	{
		if(this->isopen){

			#if defined(PLATFORM_VCWIN)
			{
				s64 t_offset = 0LL;
				while(1){
					s64 t_size = a_size - t_offset;
					if(t_size <= 0){
						//完了。
						return a_size;
					}else{
						s32 t_fix = ::recv(this->rawhandle,reinterpret_cast<char*>(&a_data[t_offset+a_offset]),static_cast<s32>(t_size),0);
						if(a_complete == true){
							if(t_fix > 0){
								t_offset += t_fix;
							}else{
								return -1;
							}
						}else{
							if(t_fix > 0){
								return t_fix;
							}else{
								return -1;
							}
						}
					}
				}

				return -1;
			}
			#else
			{
				ASSERT(0);

				UNUSED(a_data);
				UNUSED(a_size);
				UNUSED(a_offset);
				UNUSED(a_complete);

				return -1;
			}
			#endif
		}else{
			return -1;
		}
	}


	/** 開いているかどうか。
	*/
	bool SocketHandle_Impl::IsOpen() const
	{
		return this->isopen;
	}


	/** GetRawHandle
	*/
	#if defined(PLATFORM_VCWIN)
	SOCKET SocketHandle_Impl::GetRawHandle() const
	{
		return this->rawhandle;
	}
	#endif


}
#pragma warning(pop)

