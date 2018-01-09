

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


/** lib
*/
#if(BSYS_DSOUND_ENABLE)

	#include <brownie_config/dsound_lib.h>

#endif


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../window/window_impl.h"
#include "../actionbatching/actionbatching.h"
#pragma warning(pop)


/** include
*/
#if(BSYS_DSOUND_ENABLE)

	#pragma warning(push)
	#pragma warning(disable:4464)
	#include <brownie_config/dsound_include.h>
	#pragma warning(pop)

#endif


/** include
*/
#include "./dsound_impl.h"
#include "./dsound_impl_actionbatching_soundbuffer_create.h"
#include "./dsound_impl_actionbatching_soundbuffer_delete.h"
#include "./dsound_impl_actionbatching_play.h"
#include "./dsound_impl_actionbatching_autodelete.h"
#include "./dsound_impl_actionbatching_streamplay.h"
#include "./dsound_streamcallback_base.h"


/** NBsys::NDsound
*/
#if(BSYS_DSOUND_ENABLE)
#pragma warning(push)
#pragma warning(disable:4710 4820)
namespace NBsys{namespace NDsound
{
	/** NImpl
	*/
	namespace NImpl
	{
		/** CreatePcmWaveFormat
		*/
		static PCMWAVEFORMAT CreatePcmWaveFormat(NBsys::NWave::WaveType::Id a_wavetype)
		{
			PCMWAVEFORMAT t_format = {0};
			{
				switch(a_wavetype){
				case NBsys::NWave::WaveType::Mono_8_44100:
					{
						t_format.wf.wFormatTag = WAVE_FORMAT_PCM;
						t_format.wf.nChannels = 1;
						t_format.wf.nSamplesPerSec = 44100;
						t_format.wf.nAvgBytesPerSec = 1 * 1 * 44100;
						t_format.wf.nBlockAlign = 1 * 1;
						t_format.wBitsPerSample = 8;
					}break;
				case NBsys::NWave::WaveType::Mono_16_44100:
					{
						t_format.wf.wFormatTag = WAVE_FORMAT_PCM;
						t_format.wf.nChannels = 1;
						t_format.wf.nSamplesPerSec = 44100;
						t_format.wf.nAvgBytesPerSec = 1 * 2 * 44100;
						t_format.wf.nBlockAlign = 1 * 2;
						t_format.wBitsPerSample = 16;
					}break;
				case NBsys::NWave::WaveType::Stereo_8_44100:
					{
						t_format.wf.wFormatTag = WAVE_FORMAT_PCM;
						t_format.wf.nChannels = 2;
						t_format.wf.nSamplesPerSec = 44100;
						t_format.wf.nAvgBytesPerSec = 2 * 1 * 44100;
						t_format.wf.nBlockAlign = 2 * 1;
						t_format.wBitsPerSample = 8;
					}break;
				case NBsys::NWave::WaveType::Stereo_16_44100:
					{
						t_format.wf.wFormatTag = WAVE_FORMAT_PCM;
						t_format.wf.nChannels = 2;
						t_format.wf.nSamplesPerSec = 44100;
						t_format.wf.nAvgBytesPerSec = 2 * 2 * 44100;
						t_format.wf.nBlockAlign = 2 * 2;
						t_format.wBitsPerSample = 16;
					}break;
				default:
					{
						DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
					}break;
				}
			}

			return t_format;
		}
	}


	/** constructor
	*/
	Dsound_Impl::Dsound_Impl()
		:
		directsound(),
		soundbuffer_primary(),
		soundlistener(),
		id_maker(),
		actionbatching_lockobject(),
		actionbatching(),
		soundbuffer_list()
	{
	}


	/** destructor
	*/
	Dsound_Impl::~Dsound_Impl()
	{
	}


	/** Create
	*/
	bool Dsound_Impl::Create(const sharedptr<NBsys::NWindow::Window>& a_window)
	{
		//CoCreateInstance
		{
			IDirectSound8* t_raw = nullptr;

			DEEPDEBUG_TAGLOG(BSYS_DSOUND_DEBUG_ENABLE,L"dsound_impl","CoCreateInstance");
			HRESULT t_ret = ::CoCreateInstance(CLSID_DirectSound,nullptr,CLSCTX_INPROC_SERVER,IID_IDirectSound,(void**)&t_raw);
			if(t_raw != nullptr){
				this->directsound.reset(t_raw,release_delete<IDirectSound8>());
			}
			if(FAILED(t_ret)){
				DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
				this->directsound.reset();
				return false;
			}
		}

		//Initialize
		if(this->directsound){

			DEEPDEBUG_TAGLOG(BSYS_DSOUND_DEBUG_ENABLE,L"dsound_impl","Initialize");
			HRESULT t_ret = this->directsound->Initialize(nullptr);
			if(FAILED(t_ret)){
				DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
				return false;
			}
		}

		//SetCooperativeLevel
		if(this->directsound != nullptr){

			DEEPDEBUG_TAGLOG(BSYS_DSOUND_DEBUG_ENABLE,L"dsound_impl","SetCooperativeLevel");

			HWND t_handle = a_window->GetImpl()->GetHandle();
			HRESULT t_ret = this->directsound->SetCooperativeLevel(t_handle,DSSCL_PRIORITY);
			if(FAILED(t_ret)){
				DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
				return false;
			}
		}

		//CreateSoundBuffer
		if(this->directsound != nullptr){
			DSBUFFERDESC t_desc = {0};
			{
				t_desc.dwSize = sizeof(t_desc); 
				t_desc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRL3D;
				t_desc.dwBufferBytes = 0; 
				t_desc.lpwfxFormat = nullptr;
			}

			DEEPDEBUG_TAGLOG(BSYS_DSOUND_DEBUG_ENABLE,L"dsound_impl","CreateSoundBuffer : DSBCAPS_PRIMARYBUFFER : DSBCAPS_CTRL3D");

			IDirectSoundBuffer* t_raw = nullptr;
			HRESULT t_ret = this->directsound->CreateSoundBuffer(&t_desc,&t_raw,nullptr); 
			if(t_raw != nullptr){
				this->soundbuffer_primary.reset(t_raw,release_delete<IDirectSoundBuffer>());
			}
			if(FAILED(t_ret)){
				DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
				this->soundbuffer_primary.reset();
				return false;
			}
		}

		//IID_IDirectSound3DListener
		if(this->soundbuffer_primary != nullptr){

			DEEPDEBUG_TAGLOG(BSYS_DSOUND_DEBUG_ENABLE,L"dsound_impl","IID_IDirectSound3DListener");

			IDirectSound3DListener* t_raw = nullptr;
			HRESULT t_ret = this->soundbuffer_primary->QueryInterface(IID_IDirectSound3DListener,reinterpret_cast<LPVOID*>(&t_raw));
			if(t_raw != nullptr){
				this->soundlistener.reset(t_raw,release_delete<IDirectSound3DListener>());
			}
			if(FAILED(t_ret)){
				DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
				this->soundlistener.reset();
				return false;
			}
		}
	
		//デフォルト設定。
		this->SetListenerParam_Default();

		return true;
	}


	/** Delete
	*/
	void Dsound_Impl::Delete()
	{
		this->soundbuffer_list.clear();

		this->soundlistener.reset();
		this->soundbuffer_primary.reset();
		this->directsound.reset();
	}


	/** デフォルト設定。
	*/
	void Dsound_Impl::SetListenerParam_Default()
	{
		//soundlistenerのデフォルト設定。
		if(this->soundlistener != nullptr){
			HRESULT t_ret_position = this->soundlistener->SetPosition(0,0,0,DS3D_IMMEDIATE);
			DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,SUCCEEDED(t_ret_position));
			UNUSED(t_ret_position);

			HRESULT t_ret_velocity = this->soundlistener->SetVelocity(0,0,0,DS3D_IMMEDIATE);
			DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,SUCCEEDED(t_ret_velocity));
			UNUSED(t_ret_velocity);

			HRESULT t_ret_orientation = this->soundlistener->SetOrientation(0,0,1,0,1,0,DS3D_IMMEDIATE);
			DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,SUCCEEDED(t_ret_orientation));
			UNUSED(t_ret_orientation);

			HRESULT t_ret_rollofffactor = this->soundlistener->SetRolloffFactor(1.0f,DS3D_IMMEDIATE);
			DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,SUCCEEDED(t_ret_rollofffactor));
			UNUSED(t_ret_rollofffactor);

			HRESULT t_ret_dopplerfactor = this->soundlistener->SetDopplerFactor(1.0f,DS3D_IMMEDIATE);
			DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,SUCCEEDED(t_ret_dopplerfactor));
			UNUSED(t_ret_dopplerfactor);
		}else{
			DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
		}
	}


	/** GetDirectSound
	*/
	sharedptr<IDirectSound8>& Dsound_Impl::GetDirectSound()
	{
		return this->directsound;
	}


	/** GetDirectSound
	*/
	const sharedptr<IDirectSound8>& Dsound_Impl::GetDirectSound() const
	{
		return this->directsound;
	}


	/** リクエスト登録。
	*/
	void Dsound_Impl::StartBatching(sharedptr<NBsys::NActionBatching::ActionBatching_ActionList>& a_actionlist)
	{
		//アクションバッチング実行中はロック。
		AutoLock t_autolock_actionbatching(this->actionbatching_lockobject);

		//ワークリストへの追加とStartの呼び出し。
		this->actionbatching.StartBatching(a_actionlist);
	}


	/** リクエスト処理。
	*/
	void Dsound_Impl::Player_Main()
	{
		//アクションバッチング実行中はロック。
		AutoLock t_autolock_actionbatching(this->actionbatching_lockobject);

		//ワークリストからの削除とDoの呼び出し。
		this->actionbatching.Update(1.0f);
	}


	/** [複数スレッドから]サウンドバッファ作成。
	*/
	s32 Dsound_Impl::CreateSoundBuffer(const sharedptr<NBsys::NWave::Wave>& a_wave,bool a_is_3d)
	{
		//ＩＤ。
		s32 t_soundbuffer_id = this->id_maker.MakeID();

		//■親サウンドバッファ。
		sharedptr<Dsound_Impl_SoundBuffer> t_soundbuffer = new Dsound_Impl_SoundBuffer();
		{
			t_soundbuffer->playstate = Dsound_Impl_SoundBuffer::PlayState::Stop;
			//t_soundbuffer->soundbuffer;
			t_soundbuffer->soundbuffer_size = -1;
			t_soundbuffer->wave = a_wave;
			t_soundbuffer->is_3d = a_is_3d;
			t_soundbuffer->is_duplicate = false;
			//t_soundbuffer->soundbuffer_3d;
			//t_soundbuffer->soundnotify_event;
			//t_soundbuffer->stream_callback;
			//t_soundbuffer->stream_buffer;
		}

		//管理リスト。
		this->soundbuffer_list.insert(std::make_pair(t_soundbuffer_id,t_soundbuffer));

		//プレイヤーコマンド。
		sharedptr<NBsys::NActionBatching::ActionBatching_ActionList> t_actionlist = new NBsys::NActionBatching::ActionBatching_ActionList();
		{ 
			t_actionlist->Add(new Dsound_Impl_ActionBatching_SoundBuffer_Create(*this,t_soundbuffer_id));
		}
		this->StartBatching(t_actionlist);

		return t_soundbuffer_id;
	}


	/** [複数スレッドから]サウンドバッファ削除。
	*/
	void Dsound_Impl::DeleteSoundBuffer(s32 a_id)
	{
		//プレイヤーコマンド。
		sharedptr<NBsys::NActionBatching::ActionBatching_ActionList> t_actionlist = new NBsys::NActionBatching::ActionBatching_ActionList();
		{ 
			t_actionlist->Add(new Dsound_Impl_ActionBatching_SoundBuffer_Delete(*this,a_id));
		}
		this->StartBatching(t_actionlist);
	}


	/** ストリーミングサウンドバッファ作成。
	*/
	s32 Dsound_Impl::CreateStreamSoundBuffer(const sharedptr<NBsys::NDsound::Dsound_StreamCallback_Base>& a_stream_callback)
	{
		//ＩＤ。
		s32 t_soundbuffer_id = this->id_maker.MakeID();

		//■ストリーミングサウンドバッファ。
		sharedptr<Dsound_Impl_SoundBuffer> t_soundbuffer = new Dsound_Impl_SoundBuffer();
		{
			t_soundbuffer->playstate = Dsound_Impl_SoundBuffer::PlayState::Stop;
			//t_soundbuffer->soundbuffer;
			t_soundbuffer->soundbuffer_size = -1;
			//t_soundbuffer->wave = a_wave;
			t_soundbuffer->is_3d = false;//a_is_3d;
			t_soundbuffer->is_duplicate = false;
			t_soundbuffer->is_stream = true;
			//t_soundbuffer->soundbuffer_3d;
			//t_soundbuffer->soundnotify_event;
			t_soundbuffer->stream_callback = a_stream_callback;
			//t_soundbuffer->stream_buffer;
		}

		//管理リスト。
		this->soundbuffer_list.insert(std::make_pair(t_soundbuffer_id,t_soundbuffer));

		//プレイヤーコマンド。
		sharedptr<NBsys::NActionBatching::ActionBatching_ActionList> t_actionlist = new NBsys::NActionBatching::ActionBatching_ActionList();
		{ 
			t_actionlist->Add(new Dsound_Impl_ActionBatching_SoundBuffer_Create(*this,t_soundbuffer_id));
		}
		this->StartBatching(t_actionlist);

		return t_soundbuffer_id;
	}


	/** ストリーミングサウンドバッファ作成。
	*/
	void Dsound_Impl::DeleteStreamSoundBuffer(s32 a_id)
	{
		//プレイヤーコマンド。
		sharedptr<NBsys::NActionBatching::ActionBatching_ActionList> t_actionlist = new NBsys::NActionBatching::ActionBatching_ActionList();
		{ 
			t_actionlist->Add(new Dsound_Impl_ActionBatching_SoundBuffer_Delete(*this,a_id));
		}
		this->StartBatching(t_actionlist);
	}


	/** [複数スレッドから]再生。
	*/
	s32  Dsound_Impl::Play(s32 a_id,bool a_duplicate,bool a_loop,bool a_auto_delete)
	{
		auto t_it = this->soundbuffer_list.find(a_id);
		if(t_it == this->soundbuffer_list.end()){
			DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
			return -1;
		}

		//プレイヤーコマンド。
		sharedptr<NBsys::NActionBatching::ActionBatching_ActionList> t_actionlist = new NBsys::NActionBatching::ActionBatching_ActionList();

		s32 t_duplicate_id = -1;

		if(t_it->second->is_stream == true){
			//ストリーミング再生。
			t_it->second->playstate = Dsound_Impl_SoundBuffer::PlayState::Play;
		}else{
			//複製ＩＤ。
			if(a_duplicate){
				//ＩＤ。
				t_duplicate_id = this->id_maker.MakeID();

				//■複製サウンドバッファ。
				sharedptr<Dsound_Impl_SoundBuffer> t_soundbuffer = new Dsound_Impl_SoundBuffer();
				{
					t_soundbuffer->playstate = Dsound_Impl_SoundBuffer::PlayState::Play;
					//t_soundbuffer->soundbuffer;
					t_soundbuffer->soundbuffer_size = -1;
					t_soundbuffer->wave = t_it->second->wave;
					t_soundbuffer->is_3d = t_it->second->is_3d;
					t_soundbuffer->is_duplicate = true;
					t_soundbuffer->is_stream = false;
					//t_soundbuffer->soundbuffer_3d;
					//t_soundbuffer->soundnotify_event;
					//t_soundbuffer->stream_callback;
					//t_soundbuffer->stream_buffer;
				}

				//管理リスト。
				this->soundbuffer_list.insert(std::make_pair(t_duplicate_id,t_soundbuffer));
			}
		}

		{
			t_actionlist->Add(new Dsound_Impl_ActionBatching_Play(*this,a_id,t_duplicate_id,a_loop,a_auto_delete));
		}

		this->StartBatching(t_actionlist);

		return t_duplicate_id;
	}


	/** [複数スレッドから]再生中チェック。
	*/
	bool Dsound_Impl::IsPlay(s32 a_id)
	{
		auto t_it = this->soundbuffer_list.find(a_id);
		if(t_it == this->soundbuffer_list.end()){
			//削除済み。
			return false;
		}

		if(t_it->second->playstate == Dsound_Impl_SoundBuffer::PlayState::Play){
			//再生中。
			return true;
		}

		return false;
	}


	/** Player_CreateSoundBuffer
	*/
	void Dsound_Impl::Player_CreateSoundBuffer(s32 a_id)
	{
		auto t_it = this->soundbuffer_list.find(a_id);
		if(t_it == this->soundbuffer_list.end()){
			//削除済み。
			return;
		}

		if(this->directsound == nullptr){
			DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
			return;
		}

		//t_pcm_wave_format
		PCMWAVEFORMAT t_pcm_wave_format = {0};

		if(t_it->second->is_stream == true){
			//ストリーミング再生。

			NBsys::NWave::WaveType::Id t_wavetype = t_it->second->stream_callback->Callback_GetWaveType();
			
			//t_pcm_wave_format
			t_pcm_wave_format = NImpl::CreatePcmWaveFormat(t_wavetype);

			//soundbuffer_size
			t_it->second->soundbuffer_size = 44100 * 2 * 2;

			//stream_buffer
			t_it->second->stream_buffer.reset(new RingBuffer<u8,44100 * 2 * 2,true>());

		}else{
			//全コピー。

			//t_pcm_wave_format
			t_pcm_wave_format = NImpl::CreatePcmWaveFormat(t_it->second->wave->GetWaveType());

			//soundbuffer_size
			t_it->second->soundbuffer_size = t_pcm_wave_format.wf.nBlockAlign * t_it->second->wave->GetCountOfSample();
		}

		DSBUFFERDESC t_desc = {0};
		{
			t_desc.dwSize = sizeof(t_desc);

			t_desc.dwFlags = 0;

			/** 正確な再生カーソル位置を取得する。
			*/
			t_desc.dwFlags |= DSBCAPS_GETCURRENTPOSITION2;

			/** オンボードハードウェアメモリをなるべく利用する。
			*/
			t_desc.dwFlags |= DSBCAPS_STATIC;

			/** アプリケーションがバックグラウンドでも音をミュートしない。
			*/
			t_desc.dwFlags |= DSBCAPS_GLOBALFOCUS;

			/** ボリューム操作を使用する。
			*/
			t_desc.dwFlags |= DSBCAPS_CTRLVOLUME;
			
			/** 周波数操作を使用する。
			*/
			t_desc.dwFlags |= DSBCAPS_CTRLFREQUENCY;

			/** 通知機能を使用する。
			*/
			t_desc.dwFlags |= DSBCAPS_CTRLPOSITIONNOTIFY;


			if(t_it->second->is_3d == true){

				/** ３Ｄ再生機能を使用すｋる。
				*/
				t_desc.dwFlags |= DSBCAPS_CTRL3D;

				/** 最大距離で無音になる。ソフトウェアバッファのみ。
				*/
				#if(0)
				t_desc.dwFlags |= DSBCAPS_MUTE3DATMAXDISTANCE;
				#endif

			}else{

				/** パン操作を使用する。
				*/
				t_desc.dwFlags |= DSBCAPS_CTRLPAN;
			}

			/** エフェクト操作を使用する。
			*/
			#if(0)
			t_desc.dwFlags |= DSBCAPS_CTRLFX;
			#endif

			t_desc.dwBufferBytes = t_it->second->soundbuffer_size;
			t_desc.lpwfxFormat = (LPWAVEFORMATEX)&t_pcm_wave_format;
		}

		{
			DEEPDEBUG_TAGLOG(BSYS_DSOUND_DEBUG_ENABLE,L"dsound_impl","CreateSoundBuffer");

			IDirectSoundBuffer* t_raw = nullptr;
			HRESULT t_ret = this->directsound->CreateSoundBuffer(&t_desc,&t_raw,WIN_NULL);
			if(t_raw != nullptr){
				t_it->second->soundbuffer.reset(t_raw,release_delete<IDirectSoundBuffer>());
			}
			if(FAILED(t_ret)){
				DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
				t_it->second->soundbuffer.reset();
				return;
			}
		}

		if(t_it->second->soundbuffer == nullptr){
			DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
			return;
		}

		if(t_it->second->is_3d == true){

			DEEPDEBUG_TAGLOG(BSYS_DSOUND_DEBUG_ENABLE,L"dsound_impl","IID_IDirectSound3DBuffer");

			IDirectSound3DBuffer* t_raw = nullptr;
			HRESULT t_ret = t_it->second->soundbuffer->QueryInterface(IID_IDirectSound3DBuffer,reinterpret_cast<LPVOID*>(&t_raw));
			if(t_raw != nullptr){
				t_it->second->soundbuffer_3d.reset(t_raw,release_delete<IDirectSound3DBuffer>());
			}
			if(FAILED(t_ret)){
				DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
				t_it->second->soundbuffer_3d = nullptr;
				return;
			}			
		}

		{
			u8* t_data = nullptr;
			DWORD t_size = 0;

			HRESULT t_ret_lock = t_it->second->soundbuffer->Lock(0,t_it->second->soundbuffer_size,(void**)&t_data,&t_size,WIN_NULL,WIN_NULL,0);
			if(SUCCEEDED(t_ret_lock)){
				if((t_data != nullptr)&&(t_size > 0)){
					if(t_it->second->is_stream == true){
						//ストリーミング再生。
						NMemory::Set(t_data,0,t_it->second->soundbuffer_size);
					}else{
						NMemory::Copy(t_data,t_size,t_it->second->wave->GetSample().get(),t_it->second->soundbuffer_size);
					}
				}
				HRESULT t_ret_unlock = t_it->second->soundbuffer->Unlock(t_data,t_size,WIN_NULL,0);
				if(FAILED(t_ret_unlock)){
					DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
					return;
				}
			}else{
				DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
				return;
			}
		}
	}


	/** Player_DeleteSoundBuffer
	*/
	void Dsound_Impl::Player_DeleteSoundBuffer(s32 a_id)
	{
		DEEPDEBUG_TAGLOG(BSYS_DSOUND_DEBUG_ENABLE,L"dsound_impl","Player_DeleteSoundBuffer");

		auto t_it = this->soundbuffer_list.find(a_id);
		if(t_it == this->soundbuffer_list.end()){
			DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
			return;
		}

		//停止。
		if(t_it->second->soundbuffer){
			HRESULT t_ret_stop = t_it->second->soundbuffer->Stop();
			DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,SUCCEEDED(t_ret_stop));
			UNUSED(t_ret_stop);
		}

		this->soundbuffer_list.erase(t_it);
	}


	/** Player_Play
	*/
	void Dsound_Impl::Player_Play(s32 a_id,s32 a_duplicate_id,bool a_loop,bool a_auto_delete)
	{
		if(this->directsound == nullptr){
			DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,SUCCEEDED(0));
			return;
		}

		s32 t_id = a_id;

		auto t_it = this->soundbuffer_list.find(t_id);
		if(t_it == this->soundbuffer_list.end()){
			DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
			return;
		}

		if(t_it->second->soundbuffer == nullptr){
			DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
			return;
		}

		//複製。
		if(a_duplicate_id >= 0){

			auto t_it_duplicate = this->soundbuffer_list.find(a_duplicate_id);
			if(t_it_duplicate == this->soundbuffer_list.end()){
				DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
				return;
			}

			//DuplicateSoundBuffer
			{
				DEEPDEBUG_TAGLOG(BSYS_DSOUND_DEBUG_ENABLE,L"dsound_impl","DuplicateSoundBuffer");

				IDirectSoundBuffer* t_raw = nullptr;
				HRESULT t_ret_duplicate = this->directsound->DuplicateSoundBuffer(t_it->second->soundbuffer.get(),&t_raw);
				if(t_raw != nullptr){
					t_it_duplicate->second->soundbuffer.reset(t_raw,release_delete<IDirectSoundBuffer>());
				}
				if(FAILED(t_ret_duplicate)){
					DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
					t_it_duplicate->second->soundbuffer.reset();
					return;
				}
			}

			//IID_IDirectSound3DBuffer
			if(t_it_duplicate->second->is_3d){
				DEEPDEBUG_TAGLOG(BSYS_DSOUND_DEBUG_ENABLE,L"dsound_impl","IID_IDirectSound3DBuffer");

				IDirectSound3DBuffer* t_raw = nullptr;
				HRESULT t_ret = this->directsound->QueryInterface(IID_IDirectSound3DBuffer,reinterpret_cast<LPVOID*>(&t_raw));
				if(t_raw != nullptr){
					t_it_duplicate->second->soundbuffer_3d.reset(t_raw,release_delete<IDirectSound3DBuffer>());
				}
				if(FAILED(t_ret)){
					DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
					t_it_duplicate->second->soundbuffer_3d.reset();
					return;
				}			
			}

			t_it = t_it_duplicate;
			t_id = a_duplicate_id;
		}

		//通知設定。
		{
			DEEPDEBUG_TAGLOG(BSYS_DSOUND_DEBUG_ENABLE,L"dsound_impl","IID_IDirectSoundNotify");

			STLVector<DSBPOSITIONNOTIFY>::Type t_soundnotify_event_list;
			{
				t_it->second->soundnotify_event.resize(Dsound_Impl_SoundBuffer::NorifyEventType::Max);

				//バッファの真ん中を通過。
				{
					u32 t_index = Dsound_Impl_SoundBuffer::NorifyEventType::HalfPoint;

					if(t_it->second->is_stream == true){
						//ストリーミング再生。

						t_it->second->soundnotify_event[t_index].dwOffset = t_it->second->soundbuffer_size / 2;
						t_it->second->soundnotify_event[t_index].hEventNotify = ::CreateEvent(NULL,FALSE,FALSE,NULL);
						t_soundnotify_event_list.push_back(t_it->second->soundnotify_event[t_index]);
					}else{
						t_it->second->soundnotify_event[t_index].dwOffset = -1;
						t_it->second->soundnotify_event[t_index].hEventNotify = WIN_NULL;
					}
				}

				//バッファの最後を通過。
				{
					u32 t_index = Dsound_Impl_SoundBuffer::NorifyEventType::EndPoint;

					t_it->second->soundnotify_event[t_index].dwOffset =  t_it->second->soundbuffer_size - 1;
					t_it->second->soundnotify_event[t_index].hEventNotify = ::CreateEvent(NULL,FALSE,FALSE,NULL);
					t_soundnotify_event_list.push_back(t_it->second->soundnotify_event[t_index]);
				}
			}

			if(t_soundnotify_event_list.size() > 0){
				sharedptr<IDirectSoundNotify> t_soundnotify;

				IDirectSoundNotify* t_raw = nullptr;
				HRESULT t_ret = t_it->second->soundbuffer->QueryInterface(IID_IDirectSoundNotify,(LPVOID*)(&t_raw));
				if(t_raw != nullptr){
					t_soundnotify.reset(t_raw,release_delete<IDirectSoundNotify>());
				}
				if(FAILED(t_ret)){
					DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
					t_soundnotify.reset();
					return;
				}
				if(t_soundnotify){
					t_soundnotify->SetNotificationPositions(t_soundnotify_event_list.size(),&t_soundnotify_event_list.at(0));
					t_soundnotify.reset();
				}
			}
		}

		//Stop
		HRESULT t_ret_stop = t_it->second->soundbuffer->Stop();
		DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,SUCCEEDED(t_ret_stop));
		UNUSED(t_ret_stop);

		//再生位置をバイト数で指定。
		HRESULT t_ret_position = t_it->second->soundbuffer->SetCurrentPosition(0);
		DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,SUCCEEDED(t_ret_position));
		UNUSED(t_ret_position);

		//フラグ。
		DWORD t_flag = 0;
		
		if(t_it->second->is_stream == true){
			//ストリーミング再生。

			if(t_it->second->StreamCallback(0,t_it->second->soundbuffer_size) == false){
				DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
				return;
			}

			//ループ再生。
			t_flag |= DSBPLAY_LOOPING;
		}

		if(a_loop){
			t_flag |= DSBPLAY_LOOPING;
		}

		//再生。
		{
			DEEPDEBUG_TAGLOG(BSYS_DSOUND_DEBUG_ENABLE,L"dsound_impl","Play");

			HRESULT t_ret_play = t_it->second->soundbuffer->Play(0,0,t_flag);
			DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,SUCCEEDED(t_ret_play));
			UNUSED(t_ret_play);
		}

		
		if(t_it->second->is_stream == true){
			//ストリーミング再生。

			//プレイヤーコマンド。
			sharedptr<NBsys::NActionBatching::ActionBatching_ActionList> t_actionlist = new NBsys::NActionBatching::ActionBatching_ActionList();
			{
				t_actionlist->Add(new Dsound_Impl_ActionBatching_StreamPlay(*this,t_id));
			}
			this->StartBatching(t_actionlist);

		}else{

			if(a_auto_delete == true){
				//プレイヤーコマンド。
				sharedptr<NBsys::NActionBatching::ActionBatching_ActionList> t_actionlist = new NBsys::NActionBatching::ActionBatching_ActionList();
				{
					t_actionlist->Add(new Dsound_Impl_ActionBatching_AutoDelete(*this,t_id));
				}
				this->StartBatching(t_actionlist);
			}

		}

		return;
	}


	/** Player_AutoDelete
	*/
	bool Dsound_Impl::Player_AutoDelete(s32 a_id)
	{
		auto t_it = this->soundbuffer_list.find(a_id);
		if(t_it == this->soundbuffer_list.end()){
			return true;
		}

		if(t_it->second->playstate == Dsound_Impl_SoundBuffer::PlayState::Play){
			//通知チェックは再生中のみ。

			if(t_it->second->soundnotify_event[Dsound_Impl_SoundBuffer::NorifyEventType::EndPoint].hEventNotify == WIN_NULL){
				DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
				return true;
			}

			//再生の開始を確認。
			if(::WaitForSingleObject(t_it->second->soundnotify_event[Dsound_Impl_SoundBuffer::NorifyEventType::EndPoint].hEventNotify,0) == WAIT_OBJECT_0){
				//削除。
				this->Player_DeleteSoundBuffer(a_id);

				//完了。
				return true;
			}
		}

		//継続。
		return false;
	}


	/** Player_StreamPlay
	*/
	bool Dsound_Impl::Player_StreamPlay(s32 a_id)
	{
		auto t_it = this->soundbuffer_list.find(a_id);
		if(t_it == this->soundbuffer_list.end()){
			return true;
		}

		if(t_it->second->playstate == Dsound_Impl_SoundBuffer::PlayState::Play){
			//通知チェックは再生中のみ。

			s32 t_copy_to_offset = -1;

			//再生の開始を確認。
			if(t_it->second->soundnotify_event[Dsound_Impl_SoundBuffer::NorifyEventType::HalfPoint].hEventNotify != WIN_NULL){
				if(::WaitForSingleObject(t_it->second->soundnotify_event[Dsound_Impl_SoundBuffer::NorifyEventType::HalfPoint].hEventNotify,0) == WAIT_OBJECT_0){
					TAGLOG(L"dsound_impl","half point");
					t_copy_to_offset = 0;
				}
			}else{
				DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
				return true;
			}

			if(t_it->second->soundnotify_event[Dsound_Impl_SoundBuffer::NorifyEventType::EndPoint].hEventNotify != WIN_NULL){
				if(::WaitForSingleObject(t_it->second->soundnotify_event[Dsound_Impl_SoundBuffer::NorifyEventType::EndPoint].hEventNotify,0) == WAIT_OBJECT_0){
					TAGLOG(L"dsound_impl","end point");
					t_copy_to_offset = t_it->second->soundbuffer_size / 2;
				}
			}else{
				DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
				return true;
			}

			if(t_copy_to_offset >= 0){
				if(t_it->second->StreamCallback(t_copy_to_offset,t_it->second->soundbuffer_size / 2) == false){
					return true;
				}
			}
		}

		//継続。
		return false;
	}

}}
#pragma warning(pop)
#endif

