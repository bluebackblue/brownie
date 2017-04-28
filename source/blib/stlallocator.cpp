

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �r�s�k�A���P�[�^�B
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
#include "./autolock.h"
#include "./stlallocator.h"
#include "./blib_bootinitialize.h"


/** NBlib
*/
namespace NBlib
{
	/** [static]�m�ہB
	*/
	void* STLAllocatorBase::Alloc(size_t a_size)
	{
		#if defined(ROM_MASTER)

		#else

			ASSERT(IsBootInitialize() == true);

		#endif

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
	void STLAllocatorBase::Free(void* a_pointer)
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

		ASSERT(a_pointer != nullptr);

		u8* t_pointer = reinterpret_cast<u8*>(a_pointer);
		delete [] t_pointer;
	}

	/** [static]�m�ہB
	*/
	void* STLAllocatorBase_String::Alloc(size_t a_size)
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
	void STLAllocatorBase_String::Free(void* a_pointer)
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

		ASSERT(a_pointer != nullptr);

		u8* t_pointer = reinterpret_cast<u8*>(a_pointer);
		delete [] t_pointer;
	}

}

