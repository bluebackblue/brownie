#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief スレッド間での値の共有。
*/


/** include
*/
#include "./types.h"
#include "./platform.h"


/** include
*/
#include "./sharedptr.h"
#include "./lockobject.h"


/** NBlib
*/
namespace NBlib
{
	/** AsyncResult
	*/
	template <typename T> class AsyncResult
	{
	private:
		/** instance
		*/
		sharedptr<T> instance;

	public:
		/** constructor
		*/
		AsyncResult()
		{
		}

		/** destructor
		*/
		nonvirtual ~AsyncResult()
		{
		}

		/** GetLockObject
		*/
		static LockObject& GetLockObject()
		{
			static LockObject s_lockobject;
			return s_lockobject;
		}

		/** Create
		*/
		void Create(const T& a_value)
		{
			AutoLock t_autolock(AsyncResult::GetLockObject());

			{
				this->instance.reset(new T());
				this->Set(a_value);
			}
		}

		/** IsCreate
		*/
		bool IsCreate()
		{
			if(this->instance){
				return true;
			}
			return false;
		}

		/** Set
		*/
		void Set(const T& a_value)
		{
			AutoLock t_autolock(AsyncResult::GetLockObject());

			if(this->instance != nullptr){
				(*this->instance.get()) = a_value;
			}else{
				ASSERT(0);
			}
		}

		/** Get
		*/
		T Get()
		{
			AutoLock t_autolock(AsyncResult::GetLockObject());

			if(this->instance != nullptr){
				return (*this->instance.get());
			}else{
				ASSERT(0);
				return T();
			}
		}
	};
}

