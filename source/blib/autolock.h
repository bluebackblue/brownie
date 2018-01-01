#pragma once

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief オートロック。
*/


/** include
*/
#include "./types.h"
#include "./platform.h"


/** include
*/
#include "./lockobject.h"
#include "./atomicvalue.h"


/** NBlib
*/
#pragma warning(push)
#pragma warning(disable:4514)
namespace NBlib
{
	/** AutoLock
	*/
	class AutoLock
	{
	private:

		/** アンロックのネスト用。
		*/
		AtomicValue<s32> nestvalue;

		/** padding
		*/
		padding64(0,4);

		/** lockobject
		*/
		LockObject& lockobject;

	public:

		/** constructor
		*/
		AutoLock(LockObject& a_lockobject)
			:
			nestvalue(0),
			lockobject(a_lockobject)
		{
			this->Lock();
		}

		/** destructor
		*/
		nonvirtual ~AutoLock()
		{
			this->Unlock();
		}

	private:

		/** copy constructor禁止。
		*/
		AutoLock(const AutoLock& a_this) = delete;

		/** コピー禁止。
		*/
		void operator =(const AutoLock& a_this) = delete;

	public:

		/** Lock
		*/
		void Lock()
		{
			if(this->nestvalue.Load() >= 0){
				this->lockobject.Lock();
			}else{
				//すでにロック済み。
			}

			this->nestvalue.Add(1);
		}

		/** Unlock
		*/
		void Unlock()
		{
			s32 t_before_value =  this->nestvalue.Sub(1);

			if(t_before_value  > 0){
				this->lockobject.Unlock();
			}
		}

	};


	/** オートロック中に一時的にアンロックする。
	*/
	class AutoUnlock
	{
	private:

		/** autolock
		*/
		AutoLock& autolock;

	public:

		/** constructor
		*/
		AutoUnlock(AutoLock& a_autolock)
			:
			autolock(a_autolock)
		{
			autolock.Unlock();
		}

		/** destructor
		*/
		nonvirtual ~AutoUnlock()
		{
			autolock.Lock();
		}

	private:

		/** copy constructor禁止。
		*/
		AutoUnlock(const AutoUnlock& a_this) = delete;

		/** コピー禁止。
		*/
		void operator =(const AutoUnlock& a_this) = delete;

	};


}
#pragma warning(pop)

