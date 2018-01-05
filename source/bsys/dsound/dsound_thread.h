#pragma once

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


#pragma warning(push)
#pragma warning(disable:4464)
#include "../window/window.h"
#pragma warning(pop)


/** include
*/
#include "./dsound_impl.h"


/** NBsys::NDsound
*/
#if(BSYS_DSOUND_ENABLE)
#pragma warning(push)
//#pragma warning(disable:0)
namespace NBsys{namespace NDsound
{
	/** Dsound_Thread
	*/
	class Dsound_Thread
	{
	private:

		/** endrequest
		*/
		AtomicValue<bool> endrequest;

		/** ロックオブジェクト。
		*/
		mutable LockObject lockobject;

		/** [リクエスト]イベント。
		*/
		SimpleEvent request_event;

		/** dsound_impl
		*/
		Dsound_Impl dsound_impl;

	public:

		/** constructor
		*/
		Dsound_Thread();

		/** destructor
		*/
		nonvirtual ~Dsound_Thread();

	private:

		/** copy constructor禁止。
		*/
		Dsound_Thread(const Dsound_Thread& a_this) = delete;

		/** コピー禁止。
		*/
		void operator =(const Dsound_Thread& a_this) = delete;

	public:

		/** 引数。
		*/
		struct ThreadArgument
		{
			/** threadname
			*/
			STLString threadname;

			/** stacksize
			*/
			size_t stacksize;

			/** priority
			*/
			s32 priority;

			/** window
			*/
			sharedptr<NBsys::NWindow::Window> window;

			/** constructor
			*/
			ThreadArgument()
				:
				threadname("dsound_thread"),
				stacksize(64 * 1024),
				priority(0),
				window()
			{
			}

			/** destructor
			*/
			nonvirtual ~ThreadArgument()
			{
			}
		};

		/** スレッドメイン。
		*/
		void ThreadMain(ThreadArgument& a_threadargument);

		/** [メインスレッド]終了リクエスト。
		*/
		void EndRequest();

	public:

		/** 更新。
		*/
		void Update();

		/** サウンドバッファ作成。
		*/
		s32 CreateSoundBuffer(const sharedptr<NBsys::NWave::Wave>& a_wave,bool a_is_3d);

		/** サウンドバッファ削除。
		*/
		void DeleteSoundBuffer(s32 a_id);

		/** 再生。
		*/
		s32 Play(s32 a_id,bool a_duplicate,bool a_loop,bool a_auto_delete);

	};


}}
#pragma warning(pop)
#endif

