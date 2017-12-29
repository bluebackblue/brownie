#pragma once

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ＳＴＬアロケータ。
*/


/** include
*/
#include "./types.h"
#include "./platform.h"


/** include
*/
#include "./staticassert.h"
#include "./debugassert.h"


/** include
*/
#pragma warning(push)
#pragma warning(disable:4710 4711 4514)
#include <limits>
#pragma warning(pop)


/** include
*/
#pragma warning(push)
#pragma warning(disable:4710 4711 4987 4365 4820 4514 4623 4626 5027 4571)
#include <memory>
#pragma warning(pop)


/** NBlib
*/
namespace NBlib
{
	/** STLAllocatorBase
	*/
	class STLAllocatorBase
	{
	public:

		/** 確保。
		*/
		static void* Alloc(size_t a_size);

		/** 解放。
		*/
		static void Free(void* a_pointer);

	};


	/** STLAllocatorBase_String
	*/
	class STLAllocatorBase_String
	{
	public:

		/** 確保。
		*/
		static void* Alloc(size_t a_size);

		/** 解放。
		*/
		static void Free(void* a_pointer);

	};


	/** STLAllocator
	*/
	#if(0)

	#define STLAllocator std::allocator

	#else

	template <typename T> class STLAllocator : public std::allocator<T>
	{
	public:

		/** constructor
		*/
		STLAllocator()
		{
		}

		/** constructor
		*/
		STLAllocator(const STLAllocator& /*a_allocator*/)
		{
		}

		/** constructor
		*/
		template<class T2> STLAllocator(const STLAllocator<T2>& /*a_allocator*/)
		{
		}

		/** allocate
		*/
		typename std::allocator<T>::pointer allocate(typename std::allocator<T>::size_type a_count)
		{
			return reinterpret_cast<typename std::allocator<T>::pointer>(STLAllocatorBase::Alloc(a_count * sizeof(T)));
		}

		/** deallocate
		*/
		void deallocate(T* a_pointer,size_t /*a_count*/)
		{
			STLAllocatorBase::Free(a_pointer);
		}

		/** rebind
		*/
		template<class T2> struct rebind
		{
			typedef STLAllocator<T2> other;
		};

	};

	/** 比較演算子
	*/
	template <class T1,class T2> bool operator==(const STLAllocator<T1>&,const STLAllocator<T2>&){return true;}
	template <class T1,class T2> bool operator!=(const STLAllocator<T1>&,const STLAllocator<T2>&){return false;}

	#endif


	/** STLAllocator_String
	*/
	#if(0)
	#define STLAllocator_String std::allocator
	#else
	template <typename T> class STLAllocator_String : public std::allocator<T>
	{
	public:

		/** constructor
		*/
		STLAllocator_String()
		{
		}

		/** constructor
		*/
		STLAllocator_String(const STLAllocator_String& /*a_allocator*/)
		{
		}

		/** constructor
		*/
		template <class T2> STLAllocator_String(const STLAllocator_String<T2>& /*a_allocator*/)
		{
		}

		/** allocate
		*/
		typename std::allocator<T>::pointer allocate(typename std::allocator<T>::size_type a_count)
		{
			return reinterpret_cast<typename std::allocator<T>::pointer>(STLAllocatorBase_String::Alloc(a_count * sizeof(T)));
		}

		/** deallocate
		*/
		void deallocate(T* a_pointer,size_t a_count)
		{
			UNUSED(a_count);
			STLAllocatorBase_String::Free(a_pointer);
		}

		/** rebind
		*/
		template<class T2> struct rebind
		{
			typedef STLAllocator_String<T2> other;
		};

	};

	/** 比較演算子
	*/
	template <class T1,class T2> bool operator==(const STLAllocator_String<T1>&,const STLAllocator_String<T2>&){return true;}
	template <class T1,class T2> bool operator!=(const STLAllocator_String<T1>&,const STLAllocator_String<T2>&){return false;}

	#endif


}

