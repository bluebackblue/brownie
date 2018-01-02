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
	/** WaveType
	*/
	struct WaveType
	{
		enum Id
		{
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

		/** wavetype
		*/
		WaveType::Id wavetype;

		/** name
		*/
		STLWString name;

	public:

		/** constructor
		*/
		Wave(WaveType::Id a_texturetype,const STLWString& a_name);

		/** destructor
		*/
		nonvirtual ~Wave();

	public:

		/** WaveType
		*/
		WaveType::Id GetWaveType() const;

	};


}}
#endif

