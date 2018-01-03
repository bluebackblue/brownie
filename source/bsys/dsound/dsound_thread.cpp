

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
#include "./dsound_impl.h"
#include "./dsound_thread.h"


/** NBsys::NDsound
*/
#if(BSYS_DSOUND_ENABLE)
#pragma warning(push)
//#pragma warning(disable:0)
namespace NBsys{namespace NDsound
{
	/** constructor
	*/
	Dsound_Thread::Dsound_Thread()
		:
		endrequest(false),
		lockobject(),
		request_event(true),
		dsound_impl(nullptr)
	{
	}

	/** destructor
	*/
	Dsound_Thread::~Dsound_Thread()
	{
	}

	/** スレッドメイン。
	*/
	void Dsound_Thread::ThreadMain(Dsound_Thread::ThreadArgument& a_threadargument)
	{
		bool t_request = false;

		//MemoryContainer t_memorycontainer(BSYS_DSOUND_MEMORYCONTAINER);

		//初期化。
		{
			{
				HRESULT t_ret = ::CoInitializeEx(nullptr,COINIT_MULTITHREADED);
				if(FAILED(t_ret)){
					DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
					return;
				}
			}

			{
				//■排他処理。
				AutoLock t_autolock(this->lockobject);

				this->dsound_impl.reset(new Dsound_Impl());
				if(this->dsound_impl->Create(a_threadargument.window) == false){
					DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
				}
			}
		}

		while(1){

			//リクエスト待ち。
			if(t_request == false){
				this->request_event.Wait();
			}else{
				t_request = false;
			}

			//リクエスト受付開始。
			this->request_event.Clear();

			//リクエスト処理。
			{
				//■排他処理。
				AutoLock t_autolock(this->lockobject);

				this->dsound_impl->Player_Main();
			}

			//終了チェック。
			if(this->endrequest.Load()){
				break;
			}
		}

		//解放。
		{
			{
				//■排他処理。
				AutoLock t_autolock(this->lockobject);

				if(this->dsound_impl){
					this->dsound_impl->Delete();
				}
				this->dsound_impl.reset();
			}

			::CoUninitialize();
		}
	}


	/** [メインスレッド]終了リクエスト。
	*/
	void Dsound_Thread::EndRequest()
	{
		this->endrequest.Store(true);
		this->request_event.Signal();
	}


	/** 更新。
	*/
	void Dsound_Thread::Update()
	{
		this->request_event.Signal();
	}


	/** サウンドバッファ作成。
	*/
	s32 Dsound_Thread::CreateSoundBuffer(const sharedptr<NBsys::NWave::Wave>& a_wave)
	{
		//■排他処理。
		AutoLock t_autolock(this->lockobject);

		if(this->dsound_impl){
			return this->dsound_impl->CreateSoundBuffer(a_wave);
		}else{
			DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
			return -1;
		}
	}


	/** 再生。
	*/
	void Dsound_Thread::Play(s32 a_id)
	{
		//■排他処理。
		AutoLock t_autolock(this->lockobject);

		if(this->dsound_impl){
			return this->dsound_impl->Play(a_id);
		}
	}


}}
#pragma warning(pop)
#endif

