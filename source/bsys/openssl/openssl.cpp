

/**
 * Copyright (c) 2016-2018 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ＯＰＥＮＳＳＬ。
*/


/** include
*/
#include <bsys_pch.h>


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** include
*/
#include "./openssl.h"
#include "./openssl_impl.h"


/** warning

4710 : この関数はインライン展開のために選択されましたが、コンパイラはインライン展開を実行しませんでした。

*/
#pragma warning(disable:4710)


/** NBsys::NOpenSsl
*/
#if(BSYS_OPENSSL_ENABLE)
namespace NBsys{namespace NOpenSsl
{
	/** s_openssl
	*/
	sharedptr<OpenSsl_Impl> s_openssl;


	/** システムの開始。
	*/
	void StartSystem()
	{
		if(s_openssl == nullptr){
			s_openssl.reset(new OpenSsl_Impl());
			
			s_openssl->Initialize();
		}else{
			ASSERT(0);
		}
	}

	/** システムの終了。
	*/
	void EndSystem()
	{
		if(s_openssl){
			s_openssl->Finalize();
		}else{
			ASSERT(0);
		}

		s_openssl.reset();
	}


	/** スレッド関連ステートの削除。
	*/
	void SslDeleteThreadState()
	{
		if(s_openssl){
			return s_openssl->DeleteThreadState();
		}
	}


	/** SslCreate
	*/
	s32 SslCreate()
	{
		if(s_openssl){
			return s_openssl->Ssl_Create();
		}
		return -1;
	}


	/** SslConnect
	*/
	bool SslConnect(s32 a_id,sharedptr<SocketHandle>& a_sockethandle)
	{
		if(s_openssl){
			return s_openssl->Ssl_Connect(a_id,a_sockethandle);
		}
		return false;
	}


	/** SslSend
	*/
	bool SslSend(s32 a_id,const u8* a_data,s64 a_size,s64 a_offset)
	{
		if(s_openssl){
			return s_openssl->Ssl_Send(a_id,a_data,a_size,a_offset);
		}
		return false;
	}


	/** SslRecv
	*/
	s64 SslRecv(s32 a_id,u8* a_data,s64 a_size,s64 a_offset,bool a_complete)
	{
		if(s_openssl){
			return s_openssl->Ssl_Recv(a_id,a_data,a_size,a_offset,a_complete);
		}
		return -1;
	}


	/** SslDelete
	*/
	void SslDelete(s32 a_id)
	{
		if(s_openssl){
			s_openssl->Ssl_Delete(a_id);
		}
	}


}}
#endif

