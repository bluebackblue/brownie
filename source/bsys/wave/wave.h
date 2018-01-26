#pragma once

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
#include "./wave_stream.h"
#include "./wave_wav.h"
#include "./wave_ogg.h"


/** NBsys::NWave
*/
#if(BSYS_WAVE_ENABLE)
namespace NBsys{namespace NWave
{
	/** WaveType
	*/
	struct WaveType
	{
		enum Id
		{
			None = 0,

			Mono_8_44100,
			Mono_16_44100,
			Stereo_8_44100,
			Stereo_16_44100,
		};
	};


	/** Wave
	*/
	class Wave
	{
	private:

		/** sample
		*/
		sharedptr<u8> sample;

		/** sample_size
		*/
		s32 sample_size;

		/** wavetype
		*/
		WaveType::Id wavetype;

		/** name
		*/
		STLWString name;

		/** countof_sample
		*/
		s32 countof_sample;

	public:

		/** constructor
		*/
		Wave(const sharedptr<u8>& a_sample,s32 a_sample_size,s32 a_countof_sample,WaveType::Id a_wavetype,const STLWString& a_name);

		/** destructor
		*/
		nonvirtual ~Wave();

	public:

		/** GetSample
		*/
		sharedptr<u8> GetSample();

		/** GetSampleSize
		*/
		s32 GetSampleSize() const;

		/** GetSample
		*/
		const sharedptr<u8> GetSample() const;

		/** GetWaveType
		*/
		WaveType::Id GetWaveType() const;

		/** GetCountOfSample
		*/
		s32 GetCountOfSample() const;

	};


}}
#endif

