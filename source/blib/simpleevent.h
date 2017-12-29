#pragma once

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
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

	#pragma warning(disable:4710)
	#pragma warning(push)
	#pragma warning(disable:4365 4820 4514 4548 4623 4626 5027 4625 5026 4987 4571)
	#include <mutex>
	#pragma warning(pop)

	#pragma warning(disable:4710)
	#pragma warning(push)
	#pragma warning(disable:4820 4987 4625 5026 4625 4626 4365 4623 5027 4571 4514)
	#include <condition_variable>
	#pragma warning(pop)

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

		/** mutex
		*/
		std::mutex					mutex;

		/** condition_variable
		*/
		std::condition_variable		condition_variable;

		/** flag
		*/
		bool						flag;

		/** manual_reset
		*/
		bool						manual_reset;

		/** パディング。
		*/
		#if defined(ROM_64BIT)
		u8 dummy[6];
		#else
		u8 dummy[2];
		#endif

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

	private:

		/** copy constructor禁止。
		*/
		SimpleEvent(const SimpleEvent& a_this) = delete;

		/** コピー禁止。
		*/
		void operator =(const SimpleEvent& a_this) = delete;

	public:

		/** 待ち。
		*/
		void Wait()
		{
			#if(BLIB_STDMUTEX_ENABLE)
			{
				//排他。
				std::unique_lock<std::mutex> t_lock(this->mutex);

				//排他解除=>待ち=>排他=>フラグチェック。
				this->condition_variable.wait(t_lock,[this]{
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
				this->condition_variable.notify_one();
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

