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
		/** soundbuffer
		*/
		sharedptr<IDirectSoundBuffer> soundbuffer;

		/** soundbuffer_size
		*/
		s32 soundbuffer_size;

		/** wave
		*/
		sharedptr<NBsys::NWave::Wave> wave;

		/** soundbuffer_3d
		*/
		//sharedptr<IDirectSound3DBuffer> soundbuffer_3d;
	};

}}
#pragma warning(pop)
#endif

