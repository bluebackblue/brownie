

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


	/** constructor
	*/
	//OpenSsl::OpenSsl()
	//{
	//}


	/** destructor
	*/
	//OpenSsl::~OpenSsl()
	//{
	//}
}}
#endif

