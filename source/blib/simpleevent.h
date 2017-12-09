#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �P���ȃC�x���g�B
*/


/** include
*/
#include "./types.h"
#include "./platform.h"


/** include
*/
#if(BLIB_STDMUTEX_ENABLE)

	#include <mutex>
	#include <condition_variable>

#endif


/** NBlib
*/
namespace NBlib
{
	/** SimpleEvent
	*/
	class SimpleEvent
	{
	private:

		#if(BLIB_STDMUTEX_ENABLE)

		std::mutex					mutex;
		std::condition_variable		cv;
		bool						flag;
		bool						manual_reset;

		#endif

	public:

		/** constructor
		*/
		SimpleEvent(bool a_manual_reset)
			#if(BLIB_STDMUTEX_ENABLE)
			:
			flag(false),
			manual_reset(a_manual_reset)
			#endif
		{
			#if(BLIB_STDMUTEX_ENABLE)

			#else

			ASSERT(0);

			#endif
		}

		/** destructor
		*/
		nonvirtual ~SimpleEvent()
		{
		}

		/** �҂��B
		*/
		void Wait()
		{
			#if(BLIB_STDMUTEX_ENABLE)
			{
				//�r���B
				std::unique_lock<std::mutex> t_lock(this->mutex);

				//�r������=>�҂�=>�r��=>�t���O�`�F�b�N�B
				this->cv.wait(t_lock,[this]{
					return this->flag;
				});

				//���Z�b�g�B
				if(this->manual_reset == false){
					this->flag = false;
				}				
			}
			#else
			{
				ASSERT(0);
			}
			#endif
		}

		/** �V�O�i���擾�B
		*/
		bool TryWait()
		{
			#if(BLIB_STDMUTEX_ENABLE)
			{
				bool t_ret = false;

				{
					//�r���B
					std::lock_guard<std::mutex> t_lock(this->mutex);

					//�擾�B
					t_ret = this->flag;

					//���Z�b�g�B
					if(t_ret == true){
						if(this->manual_reset == false){
							this->flag = false;
						}
					}
				}

				return t_ret;
			}
			#else
			{
				ASSERT(0);
			}
			#endif
		}

		/** �V�O�i���B
		*/
		void Signal()
		{
			#if(BLIB_STDMUTEX_ENABLE)
			{
				{
					//�r���B
					std::lock_guard<std::mutex> t_lock(this->mutex);

					//�ݒ�B
					this->flag = true;
				}

				//�ҋ@���Ă���X���b�h���ЂƂN��������B
				this->cv.notify_one();
			}
			#else
			{
				ASSERT(0);
			}
			#endif
		}

		/** �N���A�B
		*/
		void Clear()
		{
			#if(BLIB_STDMUTEX_ENABLE)
			{
				//�r���B
				std::lock_guard<std::mutex> t_lock(this->mutex);
				
				//�ݒ�B
				this->flag = false;
			}
			#else
			{
				ASSERT(0);
			}
			#endif
		}

	};
}

