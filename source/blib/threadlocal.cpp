

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief スレッドローカル。
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
#include "./threadlocal.h"
#include "./blib_bootinitialize.h"


/** NBlib
*/
#if(BLIB_THREADLOCAL_ENABLE)
namespace NBlib
{
	/** thread_local
	*/
	#if(BLIB_STDTHREADLOCAL_ENABLE)

	thread_local void* s_threadlocal = nullptr;

	#else

	#error

	#endif


	/** ThreadLocalData
	*/
	struct ThreadLocalData
	{
		ThreadLocal slot[BLIB_THREADLOCAL_SLOTMAX];

		/** リセット。
		*/
		void Reset()
		{
			for(s32 ii=0;ii<COUNTOF(this->slot);ii++){
				this->slot[ii].pointer = nullptr;
			}
		}
	};


	/** GetThreadLocal
	*/
	ThreadLocal& GetThreadLocal(s32 a_index)
	{
		#if(BLIB_STDTHREADLOCAL_ENABLE)

		ThreadLocalData* t_data = reinterpret_cast<ThreadLocalData*>(s_threadlocal);

		#else

		ASSERT(0);
		ThreadLocalData* t_data = nullptr;

		#endif

		if(t_data == nullptr){
			t_data = reinterpret_cast<ThreadLocalData*>(std::malloc(sizeof(ThreadLocalData)));

			NBlib::CallOnExit(std::bind([](void* a_pointer){
				return std::free(a_pointer);
			},t_data));

			t_data->Reset();

			#if(BLIB_STDTHREADLOCAL_ENABLE)

			s_threadlocal = reinterpret_cast<void*>(t_data);

			#else

			ASSERT(0);

			#endif
		}

		ASSERT((0<=a_index)&&(a_index<COUNTOF(t_data->slot)));
		return t_data->slot[a_index];
	}


}
#endif

