

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
#include "../wave/wave.h"
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
			DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
		}
	}


	/** システムの終了リクエスト。
	*/
	void EndSystemRequest()
	{
		if(s_thread){
			s_thread->get()->EndRequest();
		}else{
			DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
		}
	}


	/** システムの終了。
	*/
	void EndSystem()
	{
		s_thread.reset();
	}


	/** 更新。
	*/
	void Update()
	{
		if(s_thread){
			s_thread->get()->Update();
		}else{
			DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
		}
	}


	/** サウンドバッファ作成。
	*/
	s32 CreateSoundBuffer(const sharedptr<NBsys::NWave::Wave>& a_wave,bool a_is_3d)
	{
		if(s_thread){
			return s_thread->get()->CreateSoundBuffer(a_wave,a_is_3d);
		}else{
			DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
			return -1;
		}
	}


	/** サウンドバッファ削除。
	*/
	void DeleteSoundBuffer(s32 a_id)
	{
		if(s_thread){
			s_thread->get()->DeleteSoundBuffer(a_id);
		}else{
			DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
		}
	}


	/** 再生。
	*/
	s32 Play(s32 a_id,bool a_duplicate,bool a_loop,bool a_auto_delete)
	{
		if(s_thread){
			return s_thread->get()->Play(a_id,a_duplicate,a_loop,a_auto_delete);
		}else{
			DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
			return -1;
		}
	}


}}
#pragma warning(pop)
#endif

