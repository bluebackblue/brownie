

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
	/** コンストラクタ。
	*/
	Wave::Wave(const sharedptr<u8>& a_sample,s32 a_sample_size,s32 a_countof_sample,WaveType::Id a_wavetype,const STLWString& a_name)
		:
		sample(a_sample),
		sample_size(a_sample_size),
		wavetype(a_wavetype),
		name(a_name),
		countof_sample(a_countof_sample)
	{
	}


	/** デストラクタ。
	*/
	Wave::~Wave()
	{
	}


	/** GetSample
	*/
	sharedptr<u8> Wave::GetSample()
	{
		return this->sample;
	}


	/** GetSample
	*/
	const sharedptr<u8> Wave::GetSample() const
	{
		return this->sample;
	}


	/** GetSampleSize
	*/
	s32 Wave::GetSampleSize() const
	{
		return this->sample_size;
	}


	/** WaveType
	*/
	WaveType::Id Wave::GetWaveType() const
	{
		return this->wavetype;
	}


	/** GetCountOfSample
	*/
	s32 Wave::GetCountOfSample() const
	{
		return this->countof_sample;
	}


}}
#pragma warning(pop)
#endif

