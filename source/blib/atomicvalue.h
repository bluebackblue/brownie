#pragma once

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief アトミック変数。
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

	#pragma warning(push)
	#pragma warning(disable:4365 4061 4514)
	#include <atomic>
	#pragma warning(pop)

#endif


/** NBlib
*/
namespace NBlib
{
	/** 使用可能な型の列挙。
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


	/** AtomicValue。
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

		/** constructor
		*/
		AtomicValue()
			:
			atomicvalue(0)
		{
			STATIC_ASSERT(sizeof(AtomicValue_Check<T>) > 0);
		}

		/** constructor
		*/
		explicit AtomicValue(T a_value)
			#if(BLIB_STDATOMIC_ENABLE)
			:
			atomicvalue(a_value)
			#endif
		{
		}

		/** destructor
		*/
		nonvirtual ~AtomicValue()
		{
		}

	private:

		/** copy constructor禁止。
		*/
		AtomicValue(const AtomicValue& a_this) = delete;

		/** コピー禁止。
		*/
		void operator =(const AtomicValue& a_this) = delete;

	public:

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

		/** 入れ替え。

		代入前の値を返す。

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

		/** 加算。
		*/
		void Add(s32 a_add_value)
		{
			#if(BLIB_STDATOMIC_ENABLE)

			this->atomicvalue.fetch_add(a_add_value);

			#else

			ASSERT(0);

			#endif
		}

		/** 減算。

		減算前の値を返す。

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

	};


	/** AtomicValue。
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

		/** constructor
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

		/** constructor
		*/
		AtomicValue(bool a_value)
			#if(BLIB_STDATOMIC_ENABLE)
			:
			atomicvalue(a_value)
			#endif
		{
		}

		/** destructor
		*/
		nonvirtual ~AtomicValue()
		{
		}

	private:

		/** copy constructor禁止。
		*/
		AtomicValue(const AtomicValue& a_this) = delete;

		/** コピー禁止。
		*/
		void operator =(const AtomicValue& a_this) = delete;

	public:

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

		/** 入れ替え。

		代入直前の値を返す。

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

	};


}

