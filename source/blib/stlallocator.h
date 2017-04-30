#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
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
	template < class T > class STLAllocator
	{
	public:
		/** typedef
		*/
		typedef T			value_type;
		typedef T*			pointer;
		typedef const T*	const_pointer;
		typedef T&			reference;
		typedef const T&	const_reference;
		typedef size_t		size_type;
		typedef ptrdiff_t	difference_type;

		/** size
		*/
		size_type size;

		/** rebind
		*/
		template < class OTHER > struct rebind
		{
			typedef STLAllocator< OTHER > other;
		};

		/** constructor。
		*/
		STLAllocator() throw()
			:
			size(0)
		{
		}

		/** constructor。
		*/
		STLAllocator(const STLAllocator< T >& a_other) throw()
			:
			size(a_other.size)
		{
		}

		/** constructor。
		*/
		template < class OTHER > STLAllocator(const STLAllocator< OTHER >& a_other) throw()
			:
			size(a_other.size)
		{
		}

		/** destructor。
		*/
		nonvirtual ~STLAllocator() throw()
		{
		}

		/** アドレス取得。
		*/
		pointer address(reference a_value) const
		{
			return &a_value;
		}

		/** アドレス取得。
		*/
		const_pointer address(const_reference a_value) const
		{
			return &a_value;
		}

		/** 割当てることができる最大の要素数を返す。
		*/
		size_type max_size() const throw()
		{
			STATIC_ASSERT(sizeof(T) > 0);
			return std::numeric_limits<size_type>::max()/sizeof(T);
		}

		/** 代入。
		*/
		template < class OTHER > STLAllocator< T >&  operator =(const STLAllocator< OTHER >&)
		{
			return (*this);
		}

		/** 明示的なコンストラクタの呼び出し。
		*/
		void construct(T* a_pointer)
		{
			//placement new
			::new (static_cast< void* >(a_pointer)) T();
		}

		/** 明示的なコンストラクタの呼び出し。
		*/
		void construct(pointer a_pointer,const T& a_value)
		{
			//placement new
			::new ((void*)a_pointer) T(a_value);
		}

		/** 明示的なデストラクタの呼び出し。
		*/
		void destroy(pointer a_pointer)
		{
			a_pointer->~T();
		}

		/** 明示的なデストラクタの呼び出し。
		*/
		template < class U > void destroy(U* a_pointer)
		{
			a_pointer->~U();
		}

		/** 領域確保。
		*/
		pointer allocate(size_type a_count,const void* a_hint = nullptr)
		{
			this->size += (a_count);

			UNUSED(a_hint);
			return reinterpret_cast< pointer >(STLAllocatorBase::Alloc(a_count * sizeof(T)));
		}

		/** 領域開放。
		*/
		void deallocate(pointer a_pointer,size_type a_count)
		{
			if((a_pointer == nullptr)&&(a_count == 0)){
			}else{

				this->size -= (a_count);

				STLAllocatorBase::Free(a_pointer);
			}
		}
	};

	/** STLAllocator_String
	*/
	template < class T > class STLAllocator_String
	{
	public:
		/** typedef
		*/
		typedef T			value_type;
		typedef T*			pointer;
		typedef const T*	const_pointer;
		typedef T&			reference;
		typedef const T&	const_reference;
		typedef size_t		size_type;
		typedef ptrdiff_t	difference_type;

		/** size
		*/
		size_type size;

		/** rebind
		*/
		template < class OTHER > struct rebind
		{
			typedef STLAllocator_String< OTHER > other;
		};

		/** constructor。
		*/
		STLAllocator_String() throw()
			:
			size(0)
		{
		}

		/** constructor。
		*/
		STLAllocator_String(const STLAllocator_String< T >& a_other) throw()
			:
			size(a_other.size)
		{
		}

		/** constructor。
		*/
		template < class OTHER > STLAllocator_String(const STLAllocator_String< OTHER >& a_other) throw()
			:
			size(a_other.size)
		{
		}

		/** destructor。
		*/
		nonvirtual ~STLAllocator_String() throw()
		{
		}

		/** アドレス取得。
		*/
		pointer address(reference a_value) const
		{
			return &a_value;
		}

		/** アドレス取得。
		*/
		const_pointer address(const_reference a_value) const
		{
			return &a_value;
		}

		/** 割当てることができる最大の要素数を返す。
		*/
		size_type max_size() const throw()
		{
			STATIC_ASSERT(sizeof(T) > 0);
			return std::numeric_limits<size_type>::max()/sizeof(T);
		}

		/** 代入。
		*/
		template < class OTHER > STLAllocator_String< T >&  operator =(const STLAllocator_String< OTHER >&)
		{
			return (*this);
		}

		/** 明示的なコンストラクタの呼び出し。
		*/
		void construct(T* a_pointer)
		{
			//placement new
			::new (static_cast< void* >(a_pointer)) T();
		}

		/** 明示的なコンストラクタの呼び出し。
		*/
		void construct(pointer a_pointer,const T& a_value)
		{
			//placement new
			::new ((void*)a_pointer) T(a_value);
		}

		/** 明示的なデストラクタの呼び出し。
		*/
		void destroy(pointer a_pointer)
		{
			a_pointer->~T();
		}

		/** 明示的なデストラクタの呼び出し。
		*/
		template < class U > void destroy(U* a_pointer)
		{
			a_pointer->~U();
		}

		/** 領域確保。
		*/
		pointer allocate(size_type a_count,const void* a_hint = nullptr)
		{
			this->size += (a_count);

			UNUSED(a_hint);
			return reinterpret_cast< pointer >(STLAllocatorBase_String::Alloc(a_count * sizeof(T)));
		}

		/** 領域開放。
		*/
		void deallocate(pointer a_pointer,size_type a_count)
		{
			if((a_pointer == nullptr)&&(a_count == 0)){
			}else{

				this->size -= (a_count);

				STLAllocatorBase_String::Free(a_pointer);
			}
		}
	};

	/** 比較。アロケーターに互換性があるかどうか。
	*/
	template < class T1 , class T2 > inline bool operator ==(const STLAllocator< T1 >& /*a_allocator_1*/,const STLAllocator< T2 >& /*a_allocator_2*/) throw()
	{	
		return true;
	}

	/** 比較。アロケーターに互換性があるかどうか。
	*/
	template < class T1 , class T2 > inline bool operator !=(const STLAllocator< T1 >& /*a_allocator_1*/,const STLAllocator< T2 >& /*a_allocator_2*/) throw()
	{
		return false;
	}

	/** 比較。アロケーターに互換性があるかどうか。
	*/
	template < class T1 , class T2 > inline bool operator ==(const STLAllocator_String< T1 >& /*a_allocator_1*/,const STLAllocator_String< T2 >& /*a_allocator_2*/) throw()
	{	
		return true;
	}

	/** 比較。アロケーターに互換性があるかどうか。
	*/
	template < class T1 , class T2 > inline bool operator !=(const STLAllocator_String< T1 >& /*a_allocator_1*/,const STLAllocator_String< T2 >& /*a_allocator_2*/) throw()
	{
		return false;
	}

}

