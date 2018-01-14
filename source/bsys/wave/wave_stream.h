#pragma once

/**
 * Copyright (c) 2016-2018 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ＷＡＶＥ。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** NBsys::NWave
*/
#if(BSYS_WAVE_ENABLE)
namespace NBsys{namespace NWave
{
	/** Wave_Stream
	*/
	class Wave_Stream
	{
	public:
		
		/** constructor
		*/
		Wave_Stream()
		{
		}

		/** destructor
		*/
		virtual ~Wave_Stream()
		{
		}

	public:

		/** チャンネル数取得。
		*/
		virtual s32 GetChannel() = 0;

		/** 量子化ビット数取得。
		*/
		virtual s32 GetBit() = 0;

		/** レート取得。
		*/
		virtual s32 GetRate() = 0;

		/** ストリーム。
		*/
		virtual bool Stream(RingBufferBase<u8>& a_buffer,bool a_is_loop) = 0;

	};


}}
#endif

