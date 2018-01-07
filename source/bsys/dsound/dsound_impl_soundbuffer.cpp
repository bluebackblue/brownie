

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
	/** constructor
	*/
	Dsound_Impl_SoundBuffer::Dsound_Impl_SoundBuffer()
		:
		playstate(PlayState::Stop),
		soundbuffer(),
		soundbuffer_size(-1),
		wave(),
		is_3d(false),
		is_duplicate(false),
		soundbuffer_3d(),
		soundnotify_event()
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


}}
#pragma warning(pop)
#endif

