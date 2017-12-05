

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief メモリーコンテナー。
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
#include "./memorycontainer.h"
#include "./debugassert.h"
#include "./threadlocal.h"


/** NBlib
*/
namespace NBlib
{
	#if(BLIB_MEMORYCONTAINER_ENABLE)

	/** MemoryContainer_Data
	*/
	struct MemoryContainer_Data
	{
	public:
		s32 index;
		s32 containerindex_list[BLIB_MEMORYCONTAINER_NESTMAX];

	public:
		void Reset()
		{
			this->index = 0;
			for(s32 ii=0;ii<COUNTOF(this->containerindex_list);ii++){
				this->containerindex_list[ii] = 0;
			}
		}
	};

	/** GetData_ThreadLocal
	*/
	static MemoryContainer_Data* GetData_ThreadLocal()
	{
		ThreadLocal& t_threadlocal_reference = GetThreadLocal(BLIB_MEMORYCONTAINER_THREADLOCALSLOT);

		MemoryContainer_Data* t_data;

		if(t_threadlocal_reference.pointer == nullptr){

			t_threadlocal_reference.pointer = ::malloc(sizeof(MemoryContainer_Data));

			t_data = reinterpret_cast<MemoryContainer_Data*>(t_threadlocal_reference.pointer);
			t_data->Reset();

		}else{

			t_data = reinterpret_cast<MemoryContainer_Data*>(t_threadlocal_reference.pointer);

		}

		return t_data;
	}

	#endif

	/** constructor
	*/
	MemoryContainer::MemoryContainer(s32 a_containerindex)
	{
		#if(BLIB_MEMORYCONTAINER_ENABLE)
		{
			MemoryContainer_Data* t_data = GetData_ThreadLocal();

			t_data->index++;
		
			ASSERT(t_data->index < COUNTOF(t_data->containerindex_list));

			t_data->containerindex_list[t_data->index] = a_containerindex;
		}
		#endif
	}

	/** destructor
	*/
	MemoryContainer::~MemoryContainer()
	{
		#if(BLIB_MEMORYCONTAINER_ENABLE)
		{
			MemoryContainer_Data* t_data = GetData_ThreadLocal();

			t_data->index--;
		}
		#endif
	}

	/** [static]GetContainerIndex
	*/
	s32 MemoryContainer::GetContainerIndex()
	{
		#if(BLIB_MEMORYCONTAINER_ENABLE)
		{
			MemoryContainer_Data* t_data = GetData_ThreadLocal();

			return t_data->containerindex_list[t_data->index];
		}
		#else
		{
			return -1;
		}
		#endif
	}
}

