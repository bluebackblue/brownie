

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


/** include
*/
#include "./wave.h"


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
	#pragma pack(1)

	/** HEADER_CHUNK
	*/
	struct HEADER_CHUNK
	{
		/** チャンク名。
		*/
		char h_name[4];
		
		/** チャンクサイズ。
		*/
		u32 h_size;	
	};


	/** HEADER_WAV
	*/
	struct HEADER_WAV
	{
		/** RIFF : ファイルサイズ - sizeof(HEADER_CHUNK)。
		*/
		HEADER_CHUNK h_chunk_riff;

		/** WAVE。
		*/
		char h_wave[4];

		/** サブチャンク。
		*/
		HEADER_CHUNK h_subchunk;
	};


	/** HEADER_FMT
	*/
	struct HEADER_FMT
	{
		/** FMT : リニアPCM = 16。
		*/
		HEADER_CHUNK h_chunk_fmt;

		/** リニアPCM = 1。
		*/
		u16 h_format_tag;

		/** モノラル = 1 : ステレオ = 2。
		*/
		u16 h_channels;

		/** 44.1kHz = 44100。
		*/
		u32 h_samples_per_sec;

		/** (44.1kHz 16bitステレオ) = 44100×2×2 = 176400。
		*/
		u32 h_avg_bytes_per_sec;

		/** (16bitステレオ) = 2×2 = 4。
		*/
		u16 h_blockalign;

		/** WAV 8bit = 8 : 16bit = 16。
		*/
		u16 h_bits_per_sample;

		/** 拡張パラメータ。
		*/
		HEADER_CHUNK h_chunk_ex;
	};


	/** HEADER_DATA
	*/
	struct HEADER_DATA
	{
		/** h_chunk_data
		*/
		HEADER_CHUNK h_chunk_data;

		/** h_data
		*/
		u8 h_data[1];
	};

	#pragma pack()


	/** CreateWave_Wav
	*/
	sharedptr<Wave> CreateWave_Wav(const sharedptr<u8>& a_data,s32 a_size,const STLWString& a_name)
	{
		const HEADER_WAV* t_header = reinterpret_cast<const HEADER_WAV*>(a_data.get());

		if(NMemory::Compare(t_header->h_wave,"WAVE",4) != 0){
			DEEPDEBUG_ASSERT(BSYS_WAVE_DEBUG_ENABLE,0);
			return nullptr;
		}

		const HEADER_CHUNK* t_chunk = &t_header->h_subchunk;
		u64 t_offset = 4;

		const HEADER_FMT* t_chunk_fmt = nullptr;
		const HEADER_DATA* t_chunk_data = nullptr;

		while(1){
			if(NMemory::Compare(t_chunk->h_name,"fmt ",4) == 0){
				//fmt
				t_chunk_fmt = reinterpret_cast<const HEADER_FMT*>(t_chunk);
			}else if(NMemory::Compare(t_chunk->h_name,"data ",4) == 0){
				//data
				t_chunk_data = reinterpret_cast<const HEADER_DATA*>(t_chunk);
			}

			t_offset += 8 + t_chunk->h_size;

			if(t_offset >= t_header->h_chunk_riff.h_size){
				//end.
				break;
			}else{
				//next.
				t_chunk = reinterpret_cast<const HEADER_CHUNK*>(&reinterpret_cast<const u8*>(&t_chunk[1])[t_chunk->h_size]);
			}
		}

		WaveType::Id t_wavetype = WaveType::None;

		DEEPDEBUG_ASSERT(BSYS_WAVE_DEBUG_ENABLE,t_chunk_fmt->h_avg_bytes_per_sec == t_chunk_fmt->h_samples_per_sec * t_chunk_fmt->h_channels * t_chunk_fmt->h_bits_per_sample / 8);
		DEEPDEBUG_ASSERT(BSYS_WAVE_DEBUG_ENABLE,t_chunk_fmt->h_blockalign == t_chunk_fmt->h_channels * t_chunk_fmt->h_bits_per_sample / 8);

		if(t_chunk_fmt->h_format_tag == 1){
			if(t_chunk_fmt->h_channels == 1){
				//モノラル。
				if(t_chunk_fmt->h_samples_per_sec == 44100){
					//44.1kHz。
					if(t_chunk_fmt->h_bits_per_sample == 8){
						//8bit。
						t_wavetype = WaveType::Mono_8_44100;
					}else if(t_chunk_fmt->h_bits_per_sample == 16){
						//16bit。
						t_wavetype = WaveType::Mono_16_44100;
					}else{
						DEEPDEBUG_ASSERT(BSYS_WAVE_DEBUG_ENABLE,0);
						return nullptr;
					}
				}else{
					DEEPDEBUG_ASSERT(BSYS_WAVE_DEBUG_ENABLE,0);
					return nullptr;
				}
			}else if(t_chunk_fmt->h_channels == 2){
				//ステレオ。
				if(t_chunk_fmt->h_samples_per_sec == 44100){
					//44.1kHz。
					if(t_chunk_fmt->h_bits_per_sample == 8){
						//8bit。
						t_wavetype = WaveType::Stereo_8_44100;
					}else if(t_chunk_fmt->h_bits_per_sample == 16){
						//16bit。
						t_wavetype = WaveType::Stereo_16_44100;
					}else{
						DEEPDEBUG_ASSERT(BSYS_WAVE_DEBUG_ENABLE,0);
						return nullptr;
					}
				}else{
					DEEPDEBUG_ASSERT(BSYS_WAVE_DEBUG_ENABLE,0);
					return nullptr;
				}
			}
		}else{
			DEEPDEBUG_ASSERT(BSYS_WAVE_DEBUG_ENABLE,0);
			return nullptr;
		}

		s32 t_buffer_size = t_chunk_data->h_chunk_data.h_size;
		s32 t_countof_sample = t_buffer_size / t_chunk_fmt->h_blockalign;
		sharedptr<u8> t_sample(new u8[t_buffer_size],default_delete<u8[]>());

		NMemory::Copy(t_sample.get(),t_buffer_size,&t_chunk_data->h_data[0],t_buffer_size);
		sharedptr<Wave> t_wave(new Wave(t_sample,t_countof_sample,t_wavetype,a_name));

		return t_wave;
	}


}}
#pragma warning(pop)
#endif

