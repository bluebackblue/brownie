

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �v���Z�X��ԓ��Ń��j�[�N�Ȃh�c�B
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
#include "./muid.h"
#include "./autolock.h"
#include "./blib_bootinitialize.h"


/** NBlib
*/
namespace NBlib
{
	/** [static]�m�ہB
	*/
	void* Muid_Impl::Alloc(size_t a_size)
	{
		#if(BLIB_GLOBALFIXEDALLOCATOR_ENABLE)
		if(a_size <= GlobalFixedAllocator_Type::Config::BlockSize){
			AutoLock t_autolock(GlobalFixedAllocator_LockObject());
			void* t_pointer = GlobalFixedAllocator_Get().Alloc();
			if(t_pointer != nullptr){
				return t_pointer;
			}
		}
		#endif

		{
			void* t_pointer = new u8[a_size];
			if(t_pointer != nullptr){
				return t_pointer;
			}
		}

		ASSERT(0);
		return nullptr;
	}

	/** [static]����B
	*/
	void Muid_Impl::Free(void* a_pointer)
	{
		#if(BLIB_GLOBALFIXEDALLOCATOR_ENABLE)
		{
			AutoLock t_autolock(GlobalFixedAllocator_LockObject());
			bool t_ret = GlobalFixedAllocator_Get().Free(a_pointer);
			if(t_ret == true){
				return;
			}
		}
		#endif

		u8* t_pointer = reinterpret_cast<u8*>(a_pointer);
		delete [] t_pointer;
	}

}

