#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �I�[�g���b�N�B
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
		/** �A�����b�N�̃l�X�g�p�B
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
				//������A�����b�N���Ă΂�Ă��邽�߃��b�N���Ȃ��B
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
		/** copy constructor�֎~�B
		*/
		AutoLock(const AutoLock& a_this) = delete;

	private:
		/** �R�s�[�֎~�B
		*/
		void operator =(const AutoLock& a_this) = delete;

	};

	/** �I�[�g���b�N���Ɉꎞ�I�ɃA�����b�N����B
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

