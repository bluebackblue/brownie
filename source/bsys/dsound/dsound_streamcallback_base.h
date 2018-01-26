#pragma once

/**
 * Copyright (c) blueback
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

		/** 初期化。
		*/
		virtual NBsys::NWave::WaveType::Id Callback_Initialize() = 0;

		/** 再生。
		*/
		virtual void Callback_Play() = 0;

		/** データ取得。
		*/
		virtual void Callback_GetData(RingBufferBase<u8>& a_buffer,s32 a_need_size,bool a_is_loop) = 0;

		/** 再生終了チェック。
		*/
		virtual bool Callback_IsPlayEnd() = 0;

	};


}}
#pragma warning(pop)
#endif

