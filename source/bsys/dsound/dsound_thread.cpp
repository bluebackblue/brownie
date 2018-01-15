

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
		dsound_impl()
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

		//CoInitializeEx
		{
			HRESULT t_ret_co = ::CoInitializeEx(nullptr,COINIT_MULTITHREADED);
			if(FAILED(t_ret_co)){
				DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
				return;
			}
		}

		//作成。
		this->dsound_impl.Create(a_threadargument.window);

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
			this->dsound_impl.Player_Main();

			//終了チェック。
			if(this->endrequest.Load()){
				break;
			}

		}

		//削除。
		this->dsound_impl.Delete();

		//CoUninitialize
		::CoUninitialize();
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


	/** [複数スレッドから]サウンドバッファ作成。
	*/
	s32 Dsound_Thread::CreateSoundBuffer(const sharedptr<NBsys::NWave::Wave>& a_wave,bool a_is_3d)
	{
		return this->dsound_impl.CreateSoundBuffer(a_wave,a_is_3d);
	}


	/** [複数スレッドから]サウンドバッファ削除。
	*/
	void Dsound_Thread::DeleteSoundBuffer(s32 a_id)
	{
		this->dsound_impl.DeleteSoundBuffer(a_id);
	}


	/** ストリーミングサウンドバッファ作成。
	*/
	s32 Dsound_Thread::CreateStreamSoundBuffer(const sharedptr<NBsys::NDsound::Dsound_StreamCallback_Base>& a_stream_callback,bool a_is_3d)
	{
		return this->dsound_impl.CreateStreamSoundBuffer(a_stream_callback,a_is_3d);
	}


	/** ストリーミングサウンドバッファ作成。
	*/
	void Dsound_Thread::DeleteStreamSoundBuffer(s32 a_id)
	{
		this->dsound_impl.DeleteStreamSoundBuffer(a_id);
	}


	/** [複数スレッドから]再生。
	*/
	s32 Dsound_Thread::Play(s32 a_id,bool a_duplicate,bool a_is_loop,bool a_auto_delete)
	{
		return this->dsound_impl.Play(a_id,a_duplicate,a_is_loop,a_auto_delete);
	}


	/** 再生中チェック。
	*/
	bool Dsound_Thread::IsPlay(s32 a_id)
	{
		return this->dsound_impl.IsPlay(a_id);
	}


	/** 有効チェック。
	*/
	bool Dsound_Thread::IsExist(s32 a_id)
	{
		return this->dsound_impl.IsExist(a_id);
	}

}}
#pragma warning(pop)
#endif

