﻿#pragma once

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ロックオブジェクト。
*/


/** include
*/
#include "./types.h"
#include "./platform.h"


/** include
*/
#if(BLIB_STDMUTEX_ENABLE)

	#pragma warning(push)
	#pragma warning(disable:4710 4365 4820 4514 4548 4623 4626 5027 4625 5026 4987 4571)
	#include <mutex>
	#pragma warning(pop)

#endif


/** NBlib
*/
#pragma warning(push)
#pragma warning(disable:4514)
namespace NBlib
{
	/** LockObject
	*/
	class LockObject
	{
	private:

		/** 再帰ロック可能なミューテックス。
		*/
		#if(BLIB_STDMUTEX_ENABLE)

		mutable std::recursive_mutex raw;

		#endif

	public:

		/** constructor
		*/
		LockObject()
		{
		}

		/** destructor
		*/
		nonvirtual ~LockObject()
		{
		}

	private:

		/** copy constructor禁止。
		*/
		LockObject(const LockObject& a_this) = delete;

		/** コピー禁止。
		*/
		void operator =(const LockObject& a_this) = delete;

	public:

		/** Lock
		*/
		void Lock() const
		{
			#if(BLIB_STDMUTEX_ENABLE)

			this->raw.lock();

			#else

			ASSERT(0);

			#endif
		}

		/** Unlock
		*/
		void Unlock() const
		{
			#if(BLIB_STDMUTEX_ENABLE)

			this->raw.unlock();

			#else

			ASSERT(0);

			#endif
		}

		/** TryLock
		*/
		bool TryLock() const
		{
			#if(BLIB_STDMUTEX_ENABLE)

			return this->raw.try_lock();

			#else

			ASSERT(0);
			return false;

			#endif
		}

		/** Lock
		*/
		static void Lock(LockObject& a_raw)
		{
			a_raw.Lock();
		}

		/** Unlock
		*/
		static void Unlock(LockObject& a_raw)
		{
			a_raw.Unlock();
		}

		/** TryLock
		*/
		static bool TryLock(LockObject& a_raw)
		{
			return a_raw.TryLock();
		}

	};


}
#pragma warning(pop)

