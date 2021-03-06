﻿#pragma once

/**
 * Copyright (c) blueback
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
	class Wave_Ogg_Impl_Stream : public Wave_Stream
	{
	public:

		/** DataType
		*/
		struct DataType
		{
			/** データ。
			*/
			const u8* ogg_data;
		
			/** サイズ。
			*/
			s64 ogg_size;

			/** 現在位置。
			*/
			s64 ogg_offset;
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
		s64 ogg_size;

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

	public:

		/** constructor
		*/
		Wave_Ogg_Impl_Stream();

		/** destructor
		*/
		virtual ~Wave_Ogg_Impl_Stream();

	public:

		/** チャンネル数取得。
		*/
		virtual s32 GetChannel();

		/** 量子化ビット数取得。
		*/
		virtual s32 GetBit();

		/** レート取得。
		*/
		virtual s32 GetRate();

		/** シーク。
		*/
		virtual void SeekStart();

		/** ストリーム。
		*/
		virtual bool Stream(RingBufferBase<u8>& a_buffer,bool a_is_loop);

	public:

		/** 作成。
		*/
		void Create(const sharedptr<u8>& a_ogg_data,s64 a_ogg_size);

		/** 削除。
		*/
		void Delete();

		/** GetCountOfSample
		*/
		s32 GetCountOfSample();

	};


}}
#endif

