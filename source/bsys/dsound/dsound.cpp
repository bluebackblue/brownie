

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


	/** s_lockobject
	*/
	LockObject s_lockobject;


	/** システムの開始。
	*/
	void StartSystem(const sharedptr<NBsys::NWindow::Window>& a_window)
	{
		AutoLock t_autolock(s_lockobject);
	
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
		AutoLock t_autolock(s_lockobject);

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
		AutoLock t_autolock(s_lockobject);

		s_thread.reset();
	}


	/** 更新。
	*/
	void Update()
	{
		AutoLock t_autolock(s_lockobject);

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
		AutoLock t_autolock(s_lockobject);

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
		AutoLock t_autolock(s_lockobject);

		if(s_thread){
			s_thread->get()->DeleteSoundBuffer(a_id);
		}else{
			DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
		}
	}


	/** ストリーミングサウンドバッファ作成。
	*/
	s32 CreateStreamSoundBuffer(const sharedptr<NBsys::NDsound::Dsound_StreamCallback_Base>& a_stream_callback,bool a_is_3d)
	{
		AutoLock t_autolock(s_lockobject);

		if(s_thread){
			return s_thread->get()->CreateStreamSoundBuffer(a_stream_callback,a_is_3d);
		}else{
			DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
			return -1;
		}
	}


	/** ストリーミングサウンドバッファ作成。
	*/
	void DeleteStreamSoundBuffer(s32 a_id)
	{
		AutoLock t_autolock(s_lockobject);

		if(s_thread){
			s_thread->get()->DeleteStreamSoundBuffer(a_id);
		}else{
			DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
		}
	}


	/** 再生。
	*/
	s32 Play(s32 a_id,bool a_duplicate,bool a_is_loop)
	{
		AutoLock t_autolock(s_lockobject);

		if(s_thread){
			return s_thread->get()->Play(a_id,a_duplicate,a_is_loop,false);
		}else{
			DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
			return -1;
		}
	}


	/** 単発再生。
	*/
	void OnceShotPlay(s32 a_id)
	{
		AutoLock t_autolock(s_lockobject);

		if(s_thread){
			s_thread->get()->Play(a_id,true,false,true);
		}else{
			DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
		}
	}


	/** 再生中チェック。
	*/
	bool IsPlay(s32 a_id)
	{
		AutoLock t_autolock(s_lockobject);

		if(s_thread){
			return s_thread->get()->IsPlay(a_id);
		}else{
			DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
			return false;
		}
	}


	/** 有効チェック。
	*/
	bool IsExist(s32 a_id)
	{
		AutoLock t_autolock(s_lockobject);

		if(s_thread){
			return s_thread->get()->IsExist(a_id);
		}else{
			DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
			return false;
		}
	}

}}
#pragma warning(pop)
#endif

