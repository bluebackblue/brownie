#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
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

	#include <mutex>

#endif

/** NBlib
*/
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

		std::recursive_mutex raw;

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

		/** Lock
		*/
		void Lock()
		{
			#if(BLIB_STDMUTEX_ENABLE)

			this->raw.lock();

			#else

			ASSERT(0);

			#endif
		}

		/** Unlock
		*/
		void Unlock()
		{
			#if(BLIB_STDMUTEX_ENABLE)

			this->raw.unlock();

			#else

			ASSERT(0);

			#endif
		}

		/** TryLock
		*/
		bool TryLock()
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

