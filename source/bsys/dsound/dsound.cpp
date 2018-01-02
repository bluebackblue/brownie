

/**
 * Copyright (c) 2016-2018 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief DirectSound
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../window/window.h"
#include "../window/window_impl.h"
#pragma warning(pop)


/** include
*/
#include "./dsound_thread.h"


/** NBsys::NDsound
*/
#if(BSYS_DSOUND_ENABLE)
#pragma warning(push)
#pragma warning(disable:4710 4820)
namespace NBsys{namespace NDsound
{
	/** s_instance
	*/
	sharedptr<ThreadTemplate<Dsound_Thread>> s_thread;

	/** システムの開始。
	*/
	void StartSystem(const sharedptr<NBsys::NWindow::Window>& a_window)
	{
		if(s_thread == nullptr){
			Dsound_Thread::ThreadArgument t_threadargument;
			{
				t_threadargument.window = a_window;
			}

			s_thread.reset(new ThreadTemplate<Dsound_Thread>());
			s_thread->Start(t_threadargument);
		}else{
			ASSERT(0);
		}
	}


	/** システムの終了リクエスト。
	*/
	void EndSystemRequest()
	{
		if(s_thread){
			s_thread->get()->EndRequest();
		}else{
			ASSERT(0);
		}
	}


	/** システムの終了。
	*/
	void EndSystem()
	{
		s_thread.reset();
	}


}}
#pragma warning(pop)
#endif

