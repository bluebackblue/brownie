#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
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

		/** lockobject
		*/
		LockObject& lockobject;

	public:
		/** constructor
		*/
		explicit AutoLock(LockObject& a_lockobject)
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

	public:
		/** Lock
		*/
		void Lock()
		{
			if(this->nestvalue.Load() >= 0){
				this->lockobject.Lock();
			}else{
				//複数回アンロックが呼ばれているためロックしない。
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

	private:
		/** copy constructor禁止。
		*/
		AutoLock(const AutoLock& a_this) = delete;

	private:
		/** コピー禁止。
		*/
		void operator =(const AutoLock& a_this) = delete;

	};

	/** オートロック中に一時的にアンロックする。
	*/
	class AutoUnlock
	{
	private:
		/** 
		*/
		AutoLock& autolock;

	public:
		/** constructor
		*/
		explicit AutoUnlock(AutoLock& a_autolock)
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
	};
}

