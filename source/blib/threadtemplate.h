#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �X���b�h�e���v���[�g�B
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


	/** �N���X�̃X���b�h���B
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

		/** �X���b�h�J�n���̈����B
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
		/** �X���b�h�J�n�B
		*/
		void Start(typename T::ThreadArgument& a_threadargument)
		{
			if(this->threadhandle == nullptr){
				if(this->implimentation == nullptr){
					//���������쐬�B
					this->implimentation.reset(new T());

					//�t���O�ݒ�B
					this->isopen.Store(true);

					//�����쐬�B
					this->argument.reset(new Argument());
					this->argument->me = this;
					this->argument->threadargument = a_threadargument;
					this->argument->implimentation = this->implimentation;

					//�X���b�h�N���B
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

		/** �X���b�h��~�m�F�B
		*/
		bool IsEnd() const
		{
			if(this->isopen.Load()){
				return false;
			}
			return true;
		}

		/** �X���b�h�폜�҂��B
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

		/** �|�C���^�̂悤�ɐU�����B
		*/
		sharedptr<T>& operator ->()
		{
			return this->implimentation;
		}

		/** �|�C���^�̂悤�ɐU�����B
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

		/** �|�C���^�̂悤�ɐU�����B
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
		/** ����֎~�B
		*/
		ThreadTemplate<T>& operator =(const ThreadTemplate<T>& a_instance);

		/** ����֎~�B
		*/
		ThreadTemplate(const ThreadTemplate<T>& a_instance);

	};
}

