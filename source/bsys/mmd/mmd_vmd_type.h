﻿#pragma once

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ＭＭＤ。ＰＭＸ。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../geometry/geometry.h"
#include "../color/color.h"
#pragma warning(pop)


/** NBsys::NMmd
*/
#if(BSYS_MMD_ENABLE)
namespace NBsys{namespace NMmd
{
	/** Mmd_Vmd_Header_A
	*/
	struct Mmd_Vmd_Header_A
	{
		/** string
		*/
		char string[30];
		char string_end;

		Mmd_Vmd_Header_A()
		{
			this->string_end = 0x00;
		}
	};


	/** Mmd_Vmd_Header_B
	*/
	struct Mmd_Vmd_Header_B
	{
		/** string
		*/
		char string[20];
		char string_end;

		Mmd_Vmd_Header_B()
		{
			this->string_end = 0x00;
		}
	};


}}
#endif

