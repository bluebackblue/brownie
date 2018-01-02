

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
	Wave::Wave(WaveType::Id a_wavetype,const STLWString& a_name)
		:
		wavetype(a_wavetype),
		name(a_name)
	{
	}


	/** デストラクタ。
	*/
	Wave::~Wave()
	{
	}


	/** WaveType
	*/
	WaveType::Id Wave::GetWaveType() const
	{
		return this->wavetype;
	}


}}
#pragma warning(pop)
#endif

