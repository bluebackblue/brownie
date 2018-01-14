

/**
 * Copyright (c) 2016-2018 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ＷＡＶＥ。
*/


/** include
*/
#include <bsys_pch.h>


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** lib
*/
#if(BSYS_WAVE_ENABLE)
	#include <brownie_config/wave_ogg_lib.h>
#endif


/** include
*/
#if(BSYS_WAVE_ENABLE)
	#include <brownie_config/wave_ogg_include.h>
#endif


/** include
*/
#include "./wave.h"
#include "./wave_ogg_impl_stream.h"


/** warning

4710 : この関数はインライン展開のために選択されましたが、コンパイラはインライン展開を実行しませんでした。

*/
#pragma warning(disable:4710)


/** NBsys::NWave
*/
#if(BSYS_WAVE_ENABLE)
#pragma warning(push)
#pragma warning(disable:4514)
namespace NBsys{namespace NWave
{
	/** CreateWave_FromOgg
	*/
	sharedptr<Wave> CreateWave_Ogg(const sharedptr<u8>& a_ogg_data,s32 a_ogg_size,const STLWString& a_name)
	{
		sharedptr<Wave> t_wave;

		RingBuffer<u8,16 * 1024,true> t_ringbuffer;

		Wave_Ogg_Impl_Stream t_stream;
		t_stream.Create(a_ogg_data,a_ogg_size);
		{
			s32 t_count_of_sample = t_stream.GetCountOfSample();
			s32 t_channel = t_stream.GetChannel();
			s32 t_bit = t_stream.GetBit();
			s32 t_rate = t_stream.GetRate();

			s32 t_offset = 0;
			s32 t_size = t_count_of_sample * t_channel * (t_bit / 8);
			sharedptr<u8> t_data(new u8[t_size]);

			NBsys::NWave::WaveType::Id t_wavetype = NBsys::NWave::WaveType::None;
			if(t_rate == 44100){
				if(t_bit == 8){
					if(t_channel == 1){
						t_wavetype = NBsys::NWave::WaveType::Mono_8_44100;
					}else if(t_channel == 2){
						t_wavetype = NBsys::NWave::WaveType::Stereo_8_44100;
					}
				}else if(t_bit == 16){
					if(t_channel == 1){
						t_wavetype = NBsys::NWave::WaveType::Mono_16_44100;
					}else if(t_channel == 2){
						t_wavetype = NBsys::NWave::WaveType::Stereo_16_44100;
					}
				}
			}

			t_wave.reset(new Wave(t_data,t_size,t_count_of_sample,t_wavetype,a_name));

			while(t_stream.Stream(t_ringbuffer,false) == true){
				s32 t_use_size = t_ringbuffer.GetUseSize();
				t_ringbuffer.CopyFromBuffer(&t_data.get()[t_offset],t_use_size);
				t_offset += t_use_size;
			}
		}
		t_stream.Delete();

		return t_wave;
	}


	/** CreateStream_Ogg
	*/
	sharedptr<Wave_Stream> CreateStream_Ogg(const sharedptr<u8>& a_ogg_data,s32 a_ogg_size)
	{
		sharedptr<Wave_Ogg_Impl_Stream> t_stream(new Wave_Ogg_Impl_Stream());
		t_stream->Create(a_ogg_data,a_ogg_size);
		return t_stream;
	}


}}
#pragma warning(pop)
#endif

