#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief スレッドテンプレート。
*/


/** include
*/
#include "./types.h"
#include "./platform.h"


/** include
*/
#include "./sharedptr.h"
#include "./atomicvalue.h"
#include "./debugassert.h"
#include "./stlstring.h"


/** threadhandle
*/
#if(BLIB_STDTHREAD_ENABLE)

	#include <thread>

#endif


/** NBlib
*/
namespace NBlib
{
	/** ThreadSleep
	*/
	void ThreadSleep(u32 a_millisec);


	/** SetThreadName
	*/
	#if defined(PLATFORM_VCWIN)

	void SetThreadName(const STLString& a_threadname);

	#endif


	/** クラスのスレッド化。
	*/
	template <typename T> class ThreadTemplate
	{
	private:
		/** threadhandle
		*/
		#if(BLIB_STDTHREAD_ENABLE)

		sharedptr<std::thread> threadhandle;

		#endif

		/** implimentation
		*/
		sharedptr<T> implimentation;

		/** isopen
		*/
		AtomicValue<bool> isopen;

		/** スレッド開始時の引数。
		*/
		struct Argument
		{
			typename T::ThreadArgument	threadargument;
			sharedptr<T>				implimentation;
			ThreadTemplate*				me;
		};
		sharedptr<Argument> argument;

	public:
		/** constructor
		*/
		ThreadTemplate()
			:
			isopen(false)
		{
		}

		/** destructor
		*/
		nonvirtual ~ThreadTemplate()
		{
			this->EndWait();
		}

	public:
		/** スレッド開始。
		*/
		void Start(typename T::ThreadArgument& a_threadargument)
		{
			if(this->threadhandle == nullptr){
				if(this->implimentation == nullptr){
					//実装部分作成。
					this->implimentation.reset(new T());

					//フラグ設定。
					this->isopen.Store(true);

					//引数作成。
					this->argument.reset(new Argument());
					this->argument->me = this;
					this->argument->threadargument = a_threadargument;
					this->argument->implimentation = this->implimentation;

					//スレッド起動。
					#if(BLIB_STDTHREAD_ENABLE)
					{
						this->threadhandle.reset(new std::thread(&ThreadTemplate<T>::ThreadMain,*this->argument.get()));
					}
					#else
					{
						ASSERT(0);
					}
					#endif
				}
			}
		}

		/** スレッド停止確認。
		*/
		bool IsEnd() const
		{
			if(this->isopen.Load()){
				return false;
			}
			return true;
		}

		/** スレッド削除待ち。
		*/
		void EndWait()
		{
			if(this->threadhandle){

				TAGLOG("ThreadTemplate::EndWait","start");
				{
					#if(BLIB_STDTHREAD_ENABLE)
					{
						this->threadhandle->join();
					}
					#else
					{
						ASSERT(0);
					}
					#endif
				}
				TAGLOG("ThreadTemplate::EndWait","end");
			}
			this->threadhandle.reset();
			this->implimentation.reset();
		}

		/** ポインタのように振舞う。
		*/
		sharedptr<T>& operator ->()
		{
			return this->implimentation;
		}

		/** ポインタのように振舞う。
		*/
		const sharedptr<T>& operator ->() const
		{
			return this->implimentation;
		}

		sharedptr<T>& get()
		{
			return this->implimentation;
		}

		const sharedptr<T>& get() const
		{
			return this->implimentation;
		}

		/** ポインタのように振舞う。
		*/
		operator bool() const
		{
			if(this->implimentation){
				return true;
			}
			return false;
		}

	private:
		/** ThreadMain
		*/
		#if(BLIB_STDTHREAD_ENABLE)
		static void ThreadMain(Argument& a_argument_ref)
		#else
		static void ThreadMain(void* a_argument)
		#endif
		{
			#if(BLIB_STDTHREAD_ENABLE)

				Argument* t_argument = &a_argument_ref;
			
			#else

				ASSERT(0);
				Argument* t_argument = a_argument;

			#endif

			#if defined(PLATFORM_VCWIN)
			{
				SetThreadName(t_argument->threadargument.threadname);
			}
			#endif

			if(t_argument->implimentation){
				t_argument->implimentation->ThreadMain(t_argument->threadargument);
			}else{
				ASSERT(0);
			}

			TAGLOG("ThreadTemplate::ThreadMain","isopen.Store(false) : start");

			if(t_argument->me){
				t_argument->me->isopen.Store(false);
			}else{
				ASSERT(0);
			}

			TAGLOG("ThreadTemplate::ThreadMain","isopen.Store(false) : end");
		}

	private:
		/** 代入禁止。
		*/
		ThreadTemplate<T>& operator =(const ThreadTemplate<T>& a_instance);

		/** 代入禁止。
		*/
		ThreadTemplate(const ThreadTemplate<T>& a_instance);

	};
}

