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
#include "./wave_decl.h"
#include "./wave_stream.h"


/** NBsys::NWave
*/
#if(BSYS_WAVE_ENABLE)
namespace NBsys{namespace NWave
{
	/** CreateWave_FromOgg
	*/
	sharedptr<Wave> CreateWave_Ogg(const sharedptr<u8>& a_ogg_data,s32 a_ogg_size,const STLWString& a_name);


	/** CreateStream_Ogg
	*/
	sharedptr<Wave_Stream> CreateStream_Ogg(const sharedptr<u8>& a_ogg_data,s32 a_ogg_size);


}}
#endif

