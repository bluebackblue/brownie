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
	struct Dsound_Impl_SoundBuffer
	{
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

		/** playstate
		*/
		PlayState::Id playstate;

		/** soundbuffer
		*/
		sharedptr<IDirectSoundBuffer> soundbuffer;

		/** soundbuffer_size
		*/
		s32 soundbuffer_size;

		/** wave
		*/
		sharedptr<NBsys::NWave::Wave> wave;

		/** is_3d
		*/
		bool is_3d;

		/** is_loop
		*/
		bool is_loop;

		/** is_duplicate
		*/
		bool is_duplicate;

		/** is_autodelete
		*/
		bool is_autodelete;

		/** is_stream
		*/
		bool is_stream;

		/** have_playnow
		*/
		bool have_playnow;

		/** soundbuffer_3d
		*/
		sharedptr<IDirectSound3DBuffer> soundbuffer_3d;

		/** soundnotify_event
		*/
		STLVector<DSBPOSITIONNOTIFY>::Type soundnotify_event;

		/** stream_callback
		*/
		sharedptr<NBsys::NDsound::Dsound_StreamCallback_Base> stream_callback;

		/** stream_buffer
		*/
		sharedptr<RingBufferBase<u8>> stream_buffer;

		/** constructor
		*/
		Dsound_Impl_SoundBuffer();

		/** destructor
		*/
		nonvirtual ~Dsound_Impl_SoundBuffer();

		/** ストリーミング再生コールバックの呼び出し。
		*/
		void StreamCallback(s32 a_copyto_offset,s32 a_need_size,bool a_is_loop);

		/** CreateNotify
		*/
		void CreateNotify();
	};

}}
#pragma warning(pop)
#endif

