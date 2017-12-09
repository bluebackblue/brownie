#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief 単純なイベント。
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

		/** 待ち。
		*/
		void Wait()
		{
			#if(BLIB_STDMUTEX_ENABLE)
			{
				//排他。
				std::unique_lock<std::mutex> t_lock(this->mutex);

				//排他解除=>待ち=>排他=>フラグチェック。
				this->cv.wait(t_lock,[this]{
					return this->flag;
				});

				//リセット。
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

		/** シグナル取得。
		*/
		bool TryWait()
		{
			#if(BLIB_STDMUTEX_ENABLE)
			{
				bool t_ret = false;

				{
					//排他。
					std::lock_guard<std::mutex> t_lock(this->mutex);

					//取得。
					t_ret = this->flag;

					//リセット。
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

		/** シグナル。
		*/
		void Signal()
		{
			#if(BLIB_STDMUTEX_ENABLE)
			{
				{
					//排他。
					std::lock_guard<std::mutex> t_lock(this->mutex);

					//設定。
					this->flag = true;
				}

				//待機しているスレッドをひとつ起床させる。
				this->cv.notify_one();
			}
			#else
			{
				ASSERT(0);
			}
			#endif
		}

		/** クリア。
		*/
		void Clear()
		{
			#if(BLIB_STDMUTEX_ENABLE)
			{
				//排他。
				std::lock_guard<std::mutex> t_lock(this->mutex);
				
				//設定。
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

