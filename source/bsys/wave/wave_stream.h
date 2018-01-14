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
#include "./wave_wav.h"
#include "./wave_ogg.h"


/** NBsys::NWave
*/
#if(BSYS_WAVE_ENABLE)
namespace NBsys{namespace NWave
{
	/** Wave_Stream
	*/
	class Wave_Stream
	{
	public:
		
		/** constructor
		*/
		Wave_Stream()
		{
		}

		/** destructor
		*/
		virtual ~Wave_Stream()
		{
		}

	public:

		
	};


}}
#endif

