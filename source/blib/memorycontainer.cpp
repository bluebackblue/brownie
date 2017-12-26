

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
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
#include "./blib_bootinitialize.h"


/** NBlib
*/
namespace NBlib
{
	/** MemoryContainer_Data
	*/
	#if(BLIB_MEMORYCONTAINER_ENABLE)
	struct MemoryContainer_Data
	{
	public:

		/** index
		*/
		s32 index;

		/** containerindex_list
		*/
		s32 containerindex_list[BLIB_MEMORYCONTAINER_NESTMAX];

	public:

		/** Reset
		*/
		void Reset()
		{
			this->index = 0;
			for(s32 ii=0;ii<COUNTOF(this->containerindex_list);ii++){
				this->containerindex_list[ii] = 0;
			}
		}

	};
	#endif


	/** GetData_ThreadLocal
	*/
	#if(BLIB_MEMORYCONTAINER_ENABLE)
	static MemoryContainer_Data* GetData_ThreadLocal()
	{
		ThreadLocal& t_threadlocal_reference = GetThreadLocal(BLIB_MEMORYCONTAINER_THREADLOCALSLOT);

		MemoryContainer_Data* t_data;

		if(t_threadlocal_reference.pointer == nullptr){

			t_threadlocal_reference.pointer = std::malloc(sizeof(MemoryContainer_Data));

			NBlib::CallOnExit(std::bind([](void* a_pointer){
				return std::free(a_pointer);
			},t_threadlocal_reference.pointer));

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

