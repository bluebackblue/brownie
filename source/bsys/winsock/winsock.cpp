

/**
* Copyright (c) 2017 blueback
* Released under the MIT License
* https://github.com/bluebackblue/brownie/blob/master/LICENSE
* http://bbbproject.sakura.ne.jp/wordpress/mitlicense
* @brief �E�B���h�E�B
*/


/** include
*/
#include <bsys_pch.h>


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./winsock_impl.h"


/** include
*/
#include "./winsock.h"


/** NBsys::NWinsock
*/
#if(BSYS_WINSOCK_ENABLE)
namespace NBsys{namespace NWinsock
{
	/** s_instance
	*/
	sharedptr<Winsock_Impl> s_instance;

	/** �V�X�e���̊J�n�B
	*/
	void StartSystem()
	{
		if(s_instance == nullptr){
			s_instance.reset(new Winsock_Impl());
		}else{
			ASSERT(0);
		}
	}

	/** �V�X�e���̏I���B
	*/
	void EndSystem()
	{
		s_instance.reset();
	}

}}
#endif

