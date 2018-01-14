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
#include "./wave_decl.h"


/** NBsys::NWave
*/
#if(BSYS_WAVE_ENABLE)
namespace NBsys{namespace NWave
{
	/** CreateWave_Wav
	*/
	sharedptr<Wave> CreateWave_Wav(const sharedptr<u8>& a_wav_data,s32 a_wav_size,const STLWString& a_name);

	
	/** CreateWave_FromOgg
	*/
	sharedptr<Wave> CreateWave_Ogg(const sharedptr<u8>& a_ogg_data,s32 a_ogg_size,const STLWString& a_name);


}}
#endif

