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
#include "../window/window.h"
#pragma warning(pop)


/** NBsys::NDsound
*/
#if(BSYS_DSOUND_ENABLE)
#pragma warning(push)
#pragma warning(disable:4710)
namespace NBsys{namespace NDsound
{
	/** Dsound
	*/
	class Dsound_Impl
	{
	private:

		/** directsound
		*/
		sharedptr<IDirectSound8> directsound;

		/** soundbuffer_primary
		*/
		sharedptr<IDirectSoundBuffer> soundbuffer_primary;

		/** soundlistener
		*/
		sharedptr<IDirectSound3DListener8> soundlistener;

	public:

		/** constructor
		*/
		Dsound_Impl();

		/** destructor
		*/
		nonvirtual ~Dsound_Impl();

	private:

		/** copy constructor禁止。
		*/
		Dsound_Impl(const Dsound_Impl& a_this) = delete;

		/** コピー禁止。
		*/
		void operator =(const Dsound_Impl& a_this) = delete;

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

			/** constructor
			*/
			ThreadArgument()
				:
				threadname("file_thread"),
				stacksize(64 * 1024),
				priority(0)
			{
			}

			/** destructor
			*/
			nonvirtual ~ThreadArgument()
			{
			}

		};

	public:

		/** Create
		*/
		bool Create(const sharedptr<NBsys::NWindow::Window>& a_window);

		/** Delete
		*/
		void Delete();

		/** デフォルト設定。
		*/
		void SetListenerParam_Default();

	};


}}
#pragma warning(pop)
#endif

