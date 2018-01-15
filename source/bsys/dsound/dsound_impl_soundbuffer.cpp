

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
/*
#pragma warning(push)
#pragma warning(disable:4464)
#include "../window/window_impl.h"
#include "../actionbatching/actionbatching.h"
#pragma warning(pop)
*/


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
#include "./dsound_impl_soundbuffer.h"


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
		/** GetPcmBlockSize
		*/
		static s32 GetPcmBlockSize(NBsys::NWave::WaveType::Id a_wavetype)
		{
			s32 t_block_size = 0;

			switch(a_wavetype){
			case NWave::WaveType::Mono_8_44100:
				{
					t_block_size = 1 * 1;
				}break;
			case NWave::WaveType::Mono_16_44100:
				{
					t_block_size = 1 * 2;
				}break;
			case NWave::WaveType::Stereo_8_44100:
				{
					t_block_size = 2 * 1;
				}break;
			case NWave::WaveType::Stereo_16_44100:
				{
					t_block_size = 2 * 2;
				}break;
			default:
				{
					DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
				}break;
			}

			return t_block_size;
		}

		/** CreatePcmWaveFormat
		*/
		static PCMWAVEFORMAT CreatePcmWaveFormat(NBsys::NWave::WaveType::Id a_wavetype)
		{
			PCMWAVEFORMAT t_format = {0};
			{
				s32 t_block_size = GetPcmBlockSize(a_wavetype);

				switch(a_wavetype){
				case NBsys::NWave::WaveType::Mono_8_44100:
					{
						t_format.wf.wFormatTag = WAVE_FORMAT_PCM;
						t_format.wf.nChannels = 1;
						t_format.wf.nSamplesPerSec = 44100;
						t_format.wf.nAvgBytesPerSec = t_block_size * t_format.wf.nSamplesPerSec;
						t_format.wf.nBlockAlign = t_block_size;
						t_format.wBitsPerSample = 8;
					}break;
				case NBsys::NWave::WaveType::Mono_16_44100:
					{
						t_format.wf.wFormatTag = WAVE_FORMAT_PCM;
						t_format.wf.nChannels = 1;
						t_format.wf.nSamplesPerSec = 44100;
						t_format.wf.nAvgBytesPerSec = t_block_size * t_format.wf.nSamplesPerSec;
						t_format.wf.nBlockAlign = t_block_size;
						t_format.wBitsPerSample = 16;
					}break;
				case NBsys::NWave::WaveType::Stereo_8_44100:
					{
						t_format.wf.wFormatTag = WAVE_FORMAT_PCM;
						t_format.wf.nChannels = 2;
						t_format.wf.nSamplesPerSec = 44100;
						t_format.wf.nAvgBytesPerSec = t_block_size * t_format.wf.nSamplesPerSec;
						t_format.wf.nBlockAlign = t_block_size;
						t_format.wBitsPerSample = 8;
					}break;
				case NBsys::NWave::WaveType::Stereo_16_44100:
					{
						t_format.wf.wFormatTag = WAVE_FORMAT_PCM;
						t_format.wf.nChannels = 2;
						t_format.wf.nSamplesPerSec = 44100;
						t_format.wf.nAvgBytesPerSec = t_block_size * t_format.wf.nSamplesPerSec;
						t_format.wf.nBlockAlign = t_block_size;
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
	Dsound_Impl_SoundBuffer::Dsound_Impl_SoundBuffer()
		:
		wave(),
		stream_callback(),
		soundbuffer(),
		soundbuffer_3d(),
		stream_buffer(),
		soundnotify_event(),

		create_stream(false),
		create_3d(false),
		create_autodelete(false),
		create_soundbuffer_size(0),
		lockobject(),
		state_loop(false),
		state_playstate(PlayState::Stop),
		state_playnow(false)
	{
	}


	/** destructor
	*/
	Dsound_Impl_SoundBuffer::~Dsound_Impl_SoundBuffer()
	{
		auto t_it_end = this->soundnotify_event.cend();
		for(auto t_it = this->soundnotify_event.cbegin();t_it != t_it_end;++t_it){
			if(t_it->hEventNotify != WIN_NULL){
				::CloseHandle(t_it->hEventNotify);
			}
		}
	}


	/** 作成。ＷＡＶＥ。
	*/
	void Dsound_Impl_SoundBuffer::Create_FromWave(const sharedptr<NBsys::NWave::Wave>& a_wave,bool a_is_3d)
	{
		this->wave = a_wave;
		this->create_stream = false;
		this->create_3d = a_is_3d;
		this->create_autodelete = false;

		this->create_soundbuffer_size = this->wave->GetCountOfSample() * NImpl::GetPcmBlockSize(this->wave->GetWaveType());
		this->stream_buffer.reset();

	}

	/** 作成。複製。
	*/
	void Dsound_Impl_SoundBuffer::Create_FromSoundbuffer(sharedptr<Dsound_Impl_SoundBuffer>& a_soundbuffer,bool a_autodelete)
	{
		this->wave = a_soundbuffer->wave;
		this->create_stream = false;
		this->create_3d = a_soundbuffer->Is3D();
		this->create_autodelete = a_autodelete;

		this->create_soundbuffer_size = this->wave->GetCountOfSample() * NImpl::GetPcmBlockSize(this->wave->GetWaveType());
		this->stream_buffer.reset();
	}


	/** 作成。ストリーム。
	*/
	void Dsound_Impl_SoundBuffer::Create_FromStream(const sharedptr<NBsys::NDsound::Dsound_StreamCallback_Base>& a_stream_callback,bool a_is_3d)
	{
		this->stream_callback = a_stream_callback;
		this->create_stream = true;	
		this->create_3d = a_is_3d;
		this->create_autodelete = false;
		
		this->create_soundbuffer_size = 44100 * 2 * 2;
		this->stream_buffer.reset(new RingBuffer<u8,44100 * 2 * 2 * 2,true>());
	}


	/** サウンドバッファ作成。
	*/
	void Dsound_Impl_SoundBuffer::CreateSoundBuffer(sharedptr<IDirectSound8>& a_directsound)
	{
		//t_pcm_wave_format
		PCMWAVEFORMAT t_pcm_wave_format = {0};

		if(this->IsStream() == true){
			//ストリーミング再生。

			NBsys::NWave::WaveType::Id t_wavetype = this->stream_callback->Callback_Initialize();
			
			//t_pcm_wave_format
			t_pcm_wave_format = NImpl::CreatePcmWaveFormat(t_wavetype);

		}else{
			//全コピー。

			//t_pcm_wave_format
			t_pcm_wave_format = NImpl::CreatePcmWaveFormat(this->wave->GetWaveType());
		}

		DSBUFFERDESC t_desc = {0};
		{
			t_desc.dwSize = sizeof(t_desc);

			t_desc.dwFlags = 0;

			//正確な再生カーソル位置を取得する。
			t_desc.dwFlags |= DSBCAPS_GETCURRENTPOSITION2;

			//オンボードハードウェアメモリをなるべく利用する。
			t_desc.dwFlags |= DSBCAPS_STATIC;

			//アプリケーションがバックグラウンドでも音をミュートしない。
			t_desc.dwFlags |= DSBCAPS_GLOBALFOCUS;

			//ボリューム操作を使用する。
			t_desc.dwFlags |= DSBCAPS_CTRLVOLUME;
			
			//周波数操作を使用する。
			t_desc.dwFlags |= DSBCAPS_CTRLFREQUENCY;

			//通知機能を使用する。
			t_desc.dwFlags |= DSBCAPS_CTRLPOSITIONNOTIFY;

			if(this->Is3D() == true){

				//３Ｄ再生機能を使用する。
				t_desc.dwFlags |= DSBCAPS_CTRL3D;

				#if(0)
				//最大距離で無音になる。ソフトウェアバッファのみ。
				t_desc.dwFlags |= DSBCAPS_MUTE3DATMAXDISTANCE;
				#endif

			}else{

				//パン操作を使用する。
				t_desc.dwFlags |= DSBCAPS_CTRLPAN;

			}

			#if(0)
			//エフェクト操作を使用する。
			t_desc.dwFlags |= DSBCAPS_CTRLFX;
			#endif

			t_desc.dwBufferBytes = this->GetSoundBufferSize();
			t_desc.lpwfxFormat = (LPWAVEFORMATEX)&t_pcm_wave_format;
		}

		{
			DEEPDEBUG_TAGLOG(BSYS_DSOUND_DEBUG_ENABLE,L"dsound_impl_soundbuffer","CreateSoundBuffer");

			IDirectSoundBuffer* t_raw = nullptr;
			HRESULT t_ret = a_directsound->CreateSoundBuffer(&t_desc,&t_raw,WIN_NULL);
			if(t_raw != nullptr){
				this->soundbuffer.reset(t_raw,release_delete<IDirectSoundBuffer>());
			}
			if(FAILED(t_ret)){
				DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
				this->soundbuffer.reset();
				return;
			}
		}

		if(this->Is3D() == true){

			DEEPDEBUG_TAGLOG(BSYS_DSOUND_DEBUG_ENABLE,L"dsound_impl_soundbuffer","IID_IDirectSound3DBuffer");

			IDirectSound3DBuffer* t_raw = nullptr;
			HRESULT t_ret = this->soundbuffer->QueryInterface(IID_IDirectSound3DBuffer,reinterpret_cast<LPVOID*>(&t_raw));
			if(t_raw != nullptr){
				this->soundbuffer_3d.reset(t_raw,release_delete<IDirectSound3DBuffer>());
			}
			if(FAILED(t_ret)){
				DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
				this->soundbuffer_3d = nullptr;
				return;
			}			
		}
	}


	/** サウンドバッファー複製。
	*/
	void Dsound_Impl_SoundBuffer::DuplicateSoundBuffer(sharedptr<IDirectSound8>& a_directsound,sharedptr<Dsound_Impl_SoundBuffer>& a_soundbuffer)
	{
		//DuplicateSoundBuffer
		{
			DEEPDEBUG_TAGLOG(BSYS_DSOUND_DEBUG_ENABLE,L"dsound_impl_soundbuffer","DuplicateSoundBuffer");

			IDirectSoundBuffer* t_raw = nullptr;
			HRESULT t_ret_duplicate = a_directsound->DuplicateSoundBuffer(a_soundbuffer->soundbuffer.get(),&t_raw);
			if(t_raw != nullptr){
				this->soundbuffer.reset(t_raw,release_delete<IDirectSoundBuffer>());
			}
			if(FAILED(t_ret_duplicate)){
				DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
				this->soundbuffer.reset();
				return;
			}
		}

		//IID_IDirectSound3DBuffer
		if(this->Is3D()){
			DEEPDEBUG_TAGLOG(BSYS_DSOUND_DEBUG_ENABLE,L"dsound_impl_soundbuffer","IID_IDirectSound3DBuffer");

			IDirectSound3DBuffer* t_raw = nullptr;
			HRESULT t_ret = this->soundbuffer->QueryInterface(IID_IDirectSound3DBuffer,reinterpret_cast<LPVOID*>(&t_raw));
			if(t_raw != nullptr){
				this->soundbuffer_3d.reset(t_raw,release_delete<IDirectSound3DBuffer>());
			}
			if(FAILED(t_ret)){
				DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
				this->soundbuffer_3d.reset();
				return;
			}			
		}
	}


	/** 通知作成。
	*/
	void Dsound_Impl_SoundBuffer::CreateNotify()
	{
		STLVector<DSBPOSITIONNOTIFY>::Type t_soundnotify_event_list;
		{
			this->soundnotify_event.resize(Dsound_Impl_SoundBuffer::NorifyEventType::Max);

			//バッファの真ん中を通過。
			{
				u32 t_index = Dsound_Impl_SoundBuffer::NorifyEventType::HalfPoint;

				if(this->IsStream() == true){
					//ストリーミング再生。

					this->soundnotify_event[t_index].dwOffset = this->GetSoundBufferSize() / 2;
					this->soundnotify_event[t_index].hEventNotify = ::CreateEvent(NULL,FALSE,FALSE,NULL);
					t_soundnotify_event_list.push_back(this->soundnotify_event[t_index]);
				}else{
					this->soundnotify_event[t_index].dwOffset = -1;
					this->soundnotify_event[t_index].hEventNotify = WIN_NULL;
				}
			}

			//バッファの最後を通過。
			{
				u32 t_index = Dsound_Impl_SoundBuffer::NorifyEventType::EndPoint;

				this->soundnotify_event[t_index].dwOffset =  this->GetSoundBufferSize() - 1;
				this->soundnotify_event[t_index].hEventNotify = ::CreateEvent(NULL,FALSE,FALSE,NULL);
				t_soundnotify_event_list.push_back(this->soundnotify_event[t_index]);
			}
		}

		if(t_soundnotify_event_list.size() > 0){
			sharedptr<IDirectSoundNotify> t_soundnotify;

			DEEPDEBUG_TAGLOG(BSYS_DSOUND_DEBUG_ENABLE,L"dsound_impl_soundbuffer","IID_IDirectSoundNotify");

			IDirectSoundNotify* t_raw = nullptr;
			HRESULT t_ret = this->soundbuffer->QueryInterface(IID_IDirectSoundNotify,(LPVOID*)(&t_raw));
			if(t_raw != nullptr){
				t_soundnotify.reset(t_raw,release_delete<IDirectSoundNotify>());
			}
			if(FAILED(t_ret)){
				DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
				t_soundnotify.reset();
				return;
			}
			if(t_soundnotify){
				t_soundnotify->SetNotificationPositions(static_cast<DWORD>(t_soundnotify_event_list.size()),&t_soundnotify_event_list.at(0));
				t_soundnotify.reset();
			}
		}
	}


	/** サウンドバッファーの初期化。
	*/
	void Dsound_Impl_SoundBuffer::InitializeSoundBuffer()
	{
		u8* t_data = nullptr;
		DWORD t_size = 0;

		HRESULT t_ret_lock = this->soundbuffer->Lock(0,this->GetSoundBufferSize(),(void**)&t_data,&t_size,WIN_NULL,WIN_NULL,0);
		if(SUCCEEDED(t_ret_lock)){
			if((t_data != nullptr)&&(t_size > 0)){
				if(this->IsStream() == true){
					//ストリーミング再生。
					NMemory::Set(t_data,0,this->GetSoundBufferSize());
				}else{
					//コピー。
					NMemory::Copy(t_data,t_size,this->wave->GetSample().get(),this->GetSoundBufferSize());
				}
			}
			HRESULT t_ret_unlock = this->soundbuffer->Unlock(t_data,t_size,WIN_NULL,0);
			if(FAILED(t_ret_unlock)){
				DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
				return;
			}
		}else{
			DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
			return;
		}
	}


	/** 通知チェック。ストリーム。
	*/
	s32 Dsound_Impl_SoundBuffer::CheckNotify_Stream()
	{
		s32 t_copy_to_offset = -1;

		//再生の開始を確認。
		if(this->soundnotify_event[Dsound_Impl_SoundBuffer::NorifyEventType::HalfPoint].hEventNotify != WIN_NULL){
			if(::WaitForSingleObject(this->soundnotify_event[Dsound_Impl_SoundBuffer::NorifyEventType::HalfPoint].hEventNotify,0) == WAIT_OBJECT_0){
				TAGLOG(L"dsound_impl","half point");
				t_copy_to_offset = 0;
			}
		}else{
			DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
		}

		if(this->soundnotify_event[Dsound_Impl_SoundBuffer::NorifyEventType::EndPoint].hEventNotify != WIN_NULL){
			if(::WaitForSingleObject(this->soundnotify_event[Dsound_Impl_SoundBuffer::NorifyEventType::EndPoint].hEventNotify,0) == WAIT_OBJECT_0){
				TAGLOG(L"dsound_impl","end point");
				t_copy_to_offset = this->GetSoundBufferSize() / 2;
			}
		}else{
			DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
		}

		return t_copy_to_offset;
	}


	/** 通知チェック。ＷＡＶＥ。
	*/
	bool Dsound_Impl_SoundBuffer::CheckNotify_Wave()
	{
		bool t_notify = false;

		if(this->soundnotify_event[Dsound_Impl_SoundBuffer::NorifyEventType::EndPoint].hEventNotify == WIN_NULL){
			DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
		}

		//再生の開始を確認。
		if(::WaitForSingleObject(this->soundnotify_event[Dsound_Impl_SoundBuffer::NorifyEventType::EndPoint].hEventNotify,0) == WAIT_OBJECT_0){
			t_notify = true;
		}

		return t_notify;
	}


	/** ストリーミング再生コールバック。データ取得。
	*/
	void Dsound_Impl_SoundBuffer::StreamCallback_GetData(s32 a_copyto_offset,s32 a_need_size,bool a_is_loop)
	{
		//コールバックの呼び出し。
		this->stream_callback->Callback_GetData(*this->stream_buffer,a_need_size,a_is_loop);

		if(this->stream_buffer->GetUseSize() >= a_need_size){

			u8* t_lock_data = nullptr;
			DWORD t_lock_size = 0;
			HRESULT t_ret_lock = this->soundbuffer->Lock(a_copyto_offset,a_need_size,(void**)&t_lock_data,&t_lock_size,WIN_NULL,WIN_NULL,0);
			if(SUCCEEDED(t_ret_lock)){

				s32 t_copy_to_size = a_need_size;

				if(t_copy_to_size > static_cast<s32>(t_lock_size)){
					//ロックサイズが足りない。
					t_copy_to_size = t_lock_size;
					DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
				}

				//ロックした領域にコピー。
				this->stream_buffer->CopyFromBuffer(t_lock_data,t_copy_to_size);

				HRESULT t_ret_unlock = this->soundbuffer->Unlock(t_lock_data,t_copy_to_size,WIN_NULL,0);
				if(FAILED(t_ret_unlock)){
					//アンロックに失敗。
					DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
					return;
				}
			}else{
				//ロックに失敗。
				DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
				return;
			}

		}else{
			//バッファサイズが足りない。
			DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);

			u8* t_lock_data = nullptr;
			DWORD t_lock_size = 0;
			HRESULT t_ret_lock = this->soundbuffer->Lock(a_copyto_offset,a_need_size,(void**)&t_lock_data,&t_lock_size,WIN_NULL,WIN_NULL,0);
			if(SUCCEEDED(t_ret_lock)){

				s32 t_copy_to_size = a_need_size;

				if(t_copy_to_size > static_cast<s32>(t_lock_size)){
					//ロックサイズが足りない。
					t_copy_to_size = t_lock_size;
					DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
				}

				//ロックした領域をクリア。
				NMemory::Set(t_lock_data,0,t_copy_to_size);

				HRESULT t_ret_unlock = this->soundbuffer->Unlock(t_lock_data,t_copy_to_size,WIN_NULL,0);
				if(FAILED(t_ret_unlock)){
					//アンロックに失敗。
					DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
					return;
				}
			}else{
				//ロックに失敗。
				DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
				return;
			}

			return;
		}

		//完了。
		return;
	}


	/** ストリームコールバック。再生。
	*/
	void Dsound_Impl_SoundBuffer::StreamCallback_Play()
	{
		this->stream_callback->Callback_Play();
	}


	/** ストリームコールバック。終端チェック。
	*/
	bool Dsound_Impl_SoundBuffer::StreamCallback_IsPlayEnd()
	{
		return this->stream_callback->Callback_IsPlayEnd();
	}


	/** サウンドバッファー。停止。
	*/
	void Dsound_Impl_SoundBuffer::Soundbuffer_Stop()
	{
		if(this->soundbuffer){
			HRESULT t_ret_stop = this->soundbuffer->Stop();
			DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,SUCCEEDED(t_ret_stop));
			UNUSED(t_ret_stop);
		}
	}


	/** サウンドバッファー。再生。
	*/
	void Dsound_Impl_SoundBuffer::Soundbuffer_Play(bool a_loop)
	{
		DWORD t_flag = 0;

		if(a_loop){
			t_flag |= DSBPLAY_LOOPING;
		}

		if(this->soundbuffer){
			HRESULT t_ret_play = this->soundbuffer->Play(0,0,t_flag);
			DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,SUCCEEDED(t_ret_play));
			UNUSED(t_ret_play);
		}
	}


	/** サウンドバッファー。位置設定。
	*/
	void Dsound_Impl_SoundBuffer::Soundbuffer_SetPosition(s32 a_position)
	{
		if(this->soundbuffer){
			HRESULT t_ret_position = this->soundbuffer->SetCurrentPosition(0);
			DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,SUCCEEDED(t_ret_position));
			UNUSED(t_ret_position);
		}
	}


	/** ストリーム。
	*/
	bool Dsound_Impl_SoundBuffer::IsStream()
	{
		return this->create_stream;
	}


	/** ３Ｄ。
	*/
	bool Dsound_Impl_SoundBuffer::Is3D()
	{
		return this->create_3d;
	}


	/** 自動削除。
	*/
	bool Dsound_Impl_SoundBuffer::IsAutoDelete()
	{
		return this->create_autodelete;
	}


	/** サウンドバッファーサイズ。
	*/
	s32 Dsound_Impl_SoundBuffer::GetSoundBufferSize()
	{
		return this->create_soundbuffer_size;
	}


	/** ループフラグ。
	*/
	void Dsound_Impl_SoundBuffer::SetState_LoopFlag(bool a_flag)
	{
		AutoLock t_autolock(this->lockobject);
		this->state_loop = a_flag;
	}


	/** ループフラグ。
	*/
	bool Dsound_Impl_SoundBuffer::GetState_LoopFlag()
	{
		AutoLock t_autolock(this->lockobject);
		return this->state_loop;
	}

	/** 再生状態。
	*/
	void Dsound_Impl_SoundBuffer::SetState_PlayState(Dsound_Impl_SoundBuffer::PlayState::Id a_playstate)
	{
		AutoLock t_autolock(this->lockobject);
		this->state_playstate = a_playstate;
	}

	/** 再生状態。
	*/
	Dsound_Impl_SoundBuffer::PlayState::Id Dsound_Impl_SoundBuffer::GetState_PlayState()
	{
		AutoLock t_autolock(this->lockobject);
		return this->state_playstate;
	}

	/** 再生監視。
	*/
	void Dsound_Impl_SoundBuffer::SetStaet_PlayNow(bool a_flag)
	{
		AutoLock t_autolock(this->lockobject);
		this->state_playnow = a_flag;
	}

	/** 再生監視。
	*/
	bool Dsound_Impl_SoundBuffer::GetState_PlayNow()
	{
		AutoLock t_autolock(this->lockobject);
		return this->state_playnow;
	}






























}}
#pragma warning(pop)
#endif

