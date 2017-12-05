#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �A�g�~�b�N�ϐ��B
*/


/** include
*/
#include "./types.h"
#include "./platform.h"


/** include
*/
#include "./staticassert.h"


/** include
*/
#if(BLIB_STDATOMIC_ENABLE)

	#include <atomic>

#endif


/** NBlib
*/
namespace NBlib
{
	/** �g�p�\�Ȍ^�̗񋓁B
	*/
	template <typename T> class AtomicValue_Check;
	template <> class AtomicValue_Check<s8>{};
	template <> class AtomicValue_Check<u8>{};
	template <> class AtomicValue_Check<s16>{};
	template <> class AtomicValue_Check<u16>{};
	template <> class AtomicValue_Check<s32>{};
	template <> class AtomicValue_Check<u32>{};
	template <> class AtomicValue_Check<s64>{};
	template <> class AtomicValue_Check<u64>{};
	template <> class AtomicValue_Check<bool>{};


	/** AtomicValue�B
	*/
	template <typename T> class AtomicValue
	{
	private:

		/** atomicvalue
		*/
		#if(BLIB_STDATOMIC_ENABLE)

		std::atomic<T> atomicvalue;

		#endif

	public:
		/** constructor�B
		*/
		AtomicValue()
			:
			atomicvalue(0)
		{
			STATIC_ASSERT(sizeof(AtomicValue_Check<T>) > 0);
		}

		/** constructor�B
		*/
		explicit AtomicValue(T a_value)
			#if(BLIB_STDATOMIC_ENABLE)
			:
			atomicvalue(a_value)
			#endif
		{
		}

		/** destructor�B
		*/
		nonvirtual ~AtomicValue()
		{
		}

		/** Load
		*/
		T Load() const
		{
			#if(BLIB_STDATOMIC_ENABLE)

			return this->atomicvalue.load();

			#else

			ASSERT(0);
			return T();

			#endif
		}

		/** Store
		*/
		void Store(T a_value)
		{
			#if(BLIB_STDATOMIC_ENABLE)

			this->atomicvalue.store(a_value);

			#else

			ASSERT(0);

			#endif
		}


		/** ����ւ��B

		������O�̒l��Ԃ��B

		*/
		T Exchange(T a_value)
		{
			#if(BLIB_STDATOMIC_ENABLE)

			return this->atomicvalue.exchange(a_value);

			#else

			ASSERT(0);
			return false;

			#endif
		}

		/** ���Z�B
		*/
		void Add(s32 a_add_value)
		{
			#if(BLIB_STDATOMIC_ENABLE)

			this->atomicvalue.fetch_add(a_add_value);

			#else

			ASSERT(0);

			#endif
		}

		/** ���Z�B

		���Z�O�̒l��Ԃ��܂��B

		*/
		s32 Sub(s32 a_sub_value)
		{
			#if(BLIB_STDATOMIC_ENABLE)

			return this->atomicvalue.fetch_sub(a_sub_value);

			#else

			ASSERT(0);
			return 0;

			#endif
		}

	private:
		/** copy constructor�֎~�B
		*/
		AtomicValue(const AtomicValue& a_this) = delete;

	private:
		/** �R�s�[�֎~�B
		*/
		void operator =(const AtomicValue& a_this) = delete;

	};


	/** AtomicValue�B
	*/
	template <> class AtomicValue<bool>
	{
	private:

		/** atomicvalue
		*/
		#if(BLIB_STDATOMIC_ENABLE)

		std::atomic<bool> atomicvalue;

		#endif

	public:
		/** constructor�B
		*/
		AtomicValue()
			#if(BLIB_STDATOMIC_ENABLE)
			:
			atomicvalue(false)
			#endif
		{
			STATIC_ASSERT(sizeof(AtomicValue_Check<bool>) > 0);
			STATIC_ASSERT(sizeof(bool) == sizeof(s8));
		}

		/** constructor�B
		*/
		AtomicValue(bool a_value)
			#if(BLIB_STDATOMIC_ENABLE)
			:
			atomicvalue(a_value)
			#endif
		{
		}

		/** destructor�B
		*/
		nonvirtual ~AtomicValue()
		{
		}

		/** Load
		*/
		bool Load() const
		{
			#if(BLIB_STDATOMIC_ENABLE)

			return this->atomicvalue.load();

			#else

			ASSERT(0);

			#endif
		}

		/** Store
		*/
		void Store(bool a_value)
		{
			#if(BLIB_STDATOMIC_ENABLE)

			this->atomicvalue.store(a_value);

			#else

			ASSERT(0);

			#endif
		}

		/** ����ւ��B

		������O�̒l��Ԃ��B

		*/
		bool Exchange(bool a_value)
		{
			#if(BLIB_STDATOMIC_ENABLE)

			return this->atomicvalue.exchange(a_value);

			#else

			ASSERT(0);
			return false;

			#endif
		}

	private:
		/** copy constructor�֎~�B
		*/
		AtomicValue(const AtomicValue& a_this) = delete;

	private:
		/** �R�s�[�֎~�B
		*/
		void operator =(const AtomicValue& a_this) = delete;

	};

}

