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
#pragma warning(push)
#pragma warning(disable:4464)
#include "../wave/wave.h"
#include "../window/window.h"
#pragma warning(pop)


/** include
*/
#include "./dsound_streamcallback_base.h"


/** NBsys::NDsound
*/
#if(BSYS_DSOUND_ENABLE)
#pragma warning(push)
#pragma warning(disable:4710)
namespace NBsys{namespace NDsound
{
	/** Dsound_Impl_SoundBuffer
	*/
	class Dsound_Impl_SoundBuffer
	{
	public:

		/** NorifyEventType
		*/
		struct NorifyEventType
		{
			enum Id
			{
				/** バッファの真ん中を通過。
				*/
				HalfPoint,

				/** バッファの最後を通過。
				*/
				EndPoint,

				Max,
			};
		};

		/** 再生ステータス。
		*/
		struct PlayState
		{
			enum Id
			{
				Stop = 0,
				Play,
				Pause,
			};
		};

	private:

		/** wave
		*/
		sharedptr<NBsys::NWave::Wave> wave;

		/** stream_callback
		*/
		sharedptr<NBsys::NDsound::Dsound_StreamCallback_Base> stream_callback;

		/** soundbuffer
		*/
		sharedptr<IDirectSoundBuffer> soundbuffer;

		/** soundbuffer_3d
		*/
		sharedptr<IDirectSound3DBuffer> soundbuffer_3d;

		/** stream_buffer
		*/
		sharedptr<RingBufferBase<u8>> stream_buffer;

		/** soundnotify_event
		*/
		STLVector<DSBPOSITIONNOTIFY>::Type soundnotify_event;

	private:

		/** create_stream
		*/
		bool create_stream;

		/** create_3d
		*/
		bool create_3d;

		/** create_autodelete
		*/
		bool create_autodelete;

		/** create_soundbuffer_size
		*/
		s32 create_soundbuffer_size;

	private:

		/** lockobject
		*/
		LockObject lockobject;

		/** state_loop
		*/
		bool state_loop;

		/** state_playstate
		*/
		PlayState::Id state_playstate;

		/** state_playnow
		*/
		bool state_playnow;

	public:

		/** constructor
		*/
		Dsound_Impl_SoundBuffer();

		/** destructor
		*/
		nonvirtual ~Dsound_Impl_SoundBuffer();

		/** 作成。ＷＡＶＥ。
		*/
		void Create_FromWave(const sharedptr<NBsys::NWave::Wave>& a_wave,bool a_is_3d);

		/** 作成。複製。
		*/
		void Create_FromSoundbuffer(sharedptr<Dsound_Impl_SoundBuffer>& a_soundbuffer,bool a_autodelete);

		/** 作成。ストリーム。
		*/
		void Create_FromStream(const sharedptr<NBsys::NDsound::Dsound_StreamCallback_Base>& a_stream_callback,bool a_is_3d);

		/** サウンドバッファー作成。
		*/
		void CreateSoundBuffer(sharedptr<IDirectSound8>& a_directsound);

		/** サウンドバッファー複製。
		*/
		void DuplicateSoundBuffer(sharedptr<IDirectSound8>& a_directsound,sharedptr<Dsound_Impl_SoundBuffer>& a_soundbuffer);

		/** 通知作成。
		*/
		void CreateNotify();

		/** サウンドバッファーの初期化。
		*/
		void InitializeSoundBuffer();

		/** 通知チェック。ストリーム。
		*/
		s32 CheckNotify_Stream();

		/** 通知チェック。ＷＡＶＥ。
		*/
		bool CheckNotify_Wave();

		/** ストリームコールバック。データ取得。
		*/
		void StreamCallback_GetData(s32 a_copyto_offset,s32 a_need_size,bool a_is_loop);

		/** ストリームコールバック。再生。
		*/
		void StreamCallback_Play();

		/** ストリームコールバック。終端チェック。
		*/
		bool StreamCallback_IsPlayEnd();

		/** サウンドバッファー。停止。
		*/
		void Soundbuffer_Stop();

		/** サウンドバッファー。再生。
		*/
		void Soundbuffer_Play(bool a_loop);

		/** サウンドバッファー。位置設定。
		*/
		void Soundbuffer_SetPosition(s32 a_position);

	public:

		/** ストリーム。
		*/
		bool IsStream();

		/** ３Ｄ。
		*/
		bool Is3D();

		/** 自動削除。
		*/
		bool IsAutoDelete();

		/** サウンドバッファーサイズ。
		*/
		s32 GetSoundBufferSize();

	public:

		/** ループフラグ。
		*/
		void SetState_LoopFlag(bool a_flag);

		/** ループフラグ。
		*/
		bool GetState_LoopFlag();

		/** 再生状態。
		*/
		void SetState_PlayState(Dsound_Impl_SoundBuffer::PlayState::Id a_playstate);

		/** 再生状態。
		*/
		Dsound_Impl_SoundBuffer::PlayState::Id GetState_PlayState();

		/** 再生監視。
		*/
		void SetStaet_PlayNow(bool a_flag);

		/** 再生監視。
		*/
		bool GetState_PlayNow();


	};

}}
#pragma warning(pop)
#endif

