#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �r�s�k�A���P�[�^�B
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

		/** �m�ہB
		*/
		static void* Alloc(size_t a_size);

		/** ����B
		*/
		static void Free(void* a_pointer);

	};

	/** STLAllocatorBase_String
	*/
	class STLAllocatorBase_String
	{
	public:

		/** �m�ہB
		*/
		static void* Alloc(size_t a_size);

		/** ����B
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

		/** constructor�B
		*/
		STLAllocator() throw()
			:
			size(0)
		{
		}

		/** constructor�B
		*/
		STLAllocator(const STLAllocator< T >& a_other) throw()
			:
			size(a_other.size)
		{
		}

		/** constructor�B
		*/
		template < class OTHER > STLAllocator(const STLAllocator< OTHER >& a_other) throw()
			:
			size(a_other.size)
		{
		}

		/** destructor�B
		*/
		nonvirtual ~STLAllocator() throw()
		{
		}

		/** �A�h���X�擾�B
		*/
		pointer address(reference a_value) const
		{
			return &a_value;
		}

		/** �A�h���X�擾�B
		*/
		const_pointer address(const_reference a_value) const
		{
			return &a_value;
		}

		/** �����Ă邱�Ƃ��ł���ő�̗v�f����Ԃ��B
		*/
		size_type max_size() const throw()
		{
			STATIC_ASSERT(sizeof(T) > 0);
			return std::numeric_limits<size_type>::max()/sizeof(T);
		}

		/** ����B
		*/
		template < class OTHER > STLAllocator< T >&  operator =(const STLAllocator< OTHER >&)
		{
			return (*this);
		}

		/** �����I�ȃR���X�g���N�^�̌Ăяo���B
		*/
		void construct(T* a_pointer)
		{
			//placement new
			::new (static_cast< void* >(a_pointer)) T();
		}

		/** �����I�ȃR���X�g���N�^�̌Ăяo���B
		*/
		void construct(pointer a_pointer,const T& a_value)
		{
			//placement new
			::new ((void*)a_pointer) T(a_value);
		}

		/** �����I�ȃf�X�g���N�^�̌Ăяo���B
		*/
		void destroy(pointer a_pointer)
		{
			a_pointer->~T();
		}

		/** �����I�ȃf�X�g���N�^�̌Ăяo���B
		*/
		template < class U > void destroy(U* a_pointer)
		{
			a_pointer->~U();
		}

		/** �̈�m�ہB
		*/
		pointer allocate(size_type a_count,const void* a_hint = nullptr)
		{
			this->size += (a_count);

			UNUSED(a_hint);
			return reinterpret_cast< pointer >(STLAllocatorBase::Alloc(a_count * sizeof(T)));
		}

		/** �̈�J���B
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

		/** constructor�B
		*/
		STLAllocator_String() throw()
			:
			size(0)
		{
		}

		/** constructor�B
		*/
		STLAllocator_String(const STLAllocator_String< T >& a_other) throw()
			:
			size(a_other.size)
		{
		}

		/** constructor�B
		*/
		template < class OTHER > STLAllocator_String(const STLAllocator_String< OTHER >& a_other) throw()
			:
			size(a_other.size)
		{
		}

		/** destructor�B
		*/
		nonvirtual ~STLAllocator_String() throw()
		{
		}

		/** �A�h���X�擾�B
		*/
		pointer address(reference a_value) const
		{
			return &a_value;
		}

		/** �A�h���X�擾�B
		*/
		const_pointer address(const_reference a_value) const
		{
			return &a_value;
		}

		/** �����Ă邱�Ƃ��ł���ő�̗v�f����Ԃ��B
		*/
		size_type max_size() const throw()
		{
			STATIC_ASSERT(sizeof(T) > 0);
			return std::numeric_limits<size_type>::max()/sizeof(T);
		}

		/** ����B
		*/
		template < class OTHER > STLAllocator_String< T >&  operator =(const STLAllocator_String< OTHER >&)
		{
			return (*this);
		}

		/** �����I�ȃR���X�g���N�^�̌Ăяo���B
		*/
		void construct(T* a_pointer)
		{
			//placement new
			::new (static_cast< void* >(a_pointer)) T();
		}

		/** �����I�ȃR���X�g���N�^�̌Ăяo���B
		*/
		void construct(pointer a_pointer,const T& a_value)
		{
			//placement new
			::new ((void*)a_pointer) T(a_value);
		}

		/** �����I�ȃf�X�g���N�^�̌Ăяo���B
		*/
		void destroy(pointer a_pointer)
		{
			a_pointer->~T();
		}

		/** �����I�ȃf�X�g���N�^�̌Ăяo���B
		*/
		template < class U > void destroy(U* a_pointer)
		{
			a_pointer->~U();
		}

		/** �̈�m�ہB
		*/
		pointer allocate(size_type a_count,const void* a_hint = nullptr)
		{
			this->size += (a_count);

			UNUSED(a_hint);
			return reinterpret_cast< pointer >(STLAllocatorBase_String::Alloc(a_count * sizeof(T)));
		}

		/** �̈�J���B
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

	/** ��r�B�A���P�[�^�[�Ɍ݊��������邩�ǂ����B
	*/
	template < class T1 , class T2 > inline bool operator ==(const STLAllocator< T1 >& /*a_allocator_1*/,const STLAllocator< T2 >& /*a_allocator_2*/) throw()
	{	
		return true;
	}

	/** ��r�B�A���P�[�^�[�Ɍ݊��������邩�ǂ����B
	*/
	template < class T1 , class T2 > inline bool operator !=(const STLAllocator< T1 >& /*a_allocator_1*/,const STLAllocator< T2 >& /*a_allocator_2*/) throw()
	{
		return false;
	}

	/** ��r�B�A���P�[�^�[�Ɍ݊��������邩�ǂ����B
	*/
	template < class T1 , class T2 > inline bool operator ==(const STLAllocator_String< T1 >& /*a_allocator_1*/,const STLAllocator_String< T2 >& /*a_allocator_2*/) throw()
	{	
		return true;
	}

	/** ��r�B�A���P�[�^�[�Ɍ݊��������邩�ǂ����B
	*/
	template < class T1 , class T2 > inline bool operator !=(const STLAllocator_String< T1 >& /*a_allocator_1*/,const STLAllocator_String< T2 >& /*a_allocator_2*/) throw()
	{
		return false;
	}

}

