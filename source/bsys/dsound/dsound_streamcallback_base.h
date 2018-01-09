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


/** NBsys::NDsound
*/
#if(BSYS_DSOUND_ENABLE)
#pragma warning(push)
#pragma warning(disable:4710 4820)
namespace NBsys{namespace NDsound
{
	/** Dsound_StreamCallback_Base
	*/
	class Dsound_StreamCallback_Base
	{
	public:

		/** constructor
		*/
		Dsound_StreamCallback_Base()
		{
		}

		/** destructor
		*/
		virtual ~Dsound_StreamCallback_Base()
		{
		}

	public:

		/** 初期化待ち。
		*/
		virtual bool IsInitialize() = 0;

		/** コールバック。
		*/
		virtual void Callback_Proc(u8* a_data,s32 a_need_size) = 0;

	};





}}
#pragma warning(pop)
#endif

