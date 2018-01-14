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


/** include
*/
#if(BSYS_WAVE_ENABLE)
	#include <brownie_config/wave_ogg_include.h>
#endif


/** include
*/
#include "./wave.h"
#include "./wave_stream.h"


/** NBsys::NWave
*/
#if(BSYS_WAVE_ENABLE)
namespace NBsys{namespace NWave
{
	/** Wave_Ogg_Impl_Stream
	*/
	class Wave_Ogg_Impl_Stream
	{
	public:

		/** DataType
		*/
		struct DataType
		{
			const u8* data;
		
			/** サイズ。
			*/
			s32 size;

			/** 現在位置。
			*/
			s32 offset;
		};

	private:

		/** data
		*/
		DataType data;

		/** ogg_data
		*/
		sharedptr<u8> ogg_data;

		/** ogg_size
		*/
		s32 ogg_size;

		/** 仮想ハンドル。
		*/
		bool virtual_filehandle_enable;

		/** 仮想ハンドル。
		*/
		OggVorbis_File virtual_filehandle;

		/** countof_sample
		*/
		s32 countof_sample;

		/** channel
		*/
		s32 channel;

		/** bit
		*/
		s32 bit;

		/** rate
		*/
		s32 rate;

		/** wavetype
		*/
		WaveType::Id wavetype;

	public:

		/** constructor
		*/
		Wave_Ogg_Impl_Stream();

		/** destructor
		*/
		virtual ~Wave_Ogg_Impl_Stream();

		/** 作成。
		*/
		void Create(const sharedptr<u8>& a_ogg_data,s32 a_ogg_size);

		/** 削除。
		*/
		void Delete();

		/** GetWaveType
		*/
		WaveType::Id GetWaveType();

		/** GetCountOfSample
		*/
		s32 GetCountOfSample();

		/** GetChannel
		*/
		s32 GetChannel();

		/** GetBit
		*/
		s32 GetBit();

		/** GetRate
		*/
		s32 GetRate();

		/** Stream

			a_seek < 0 : 自動シーク。

		*/
		bool Stream(RingBufferBase<u8>& a_buffer,bool a_loop);

	};


}}
#endif

