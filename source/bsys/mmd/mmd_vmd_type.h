#pragma once

/**
* Copyright (c) 2017 blueback
* Released under the MIT License
* https://github.com/bluebackblue/brownie/blob/master/LICENSE
* http://bbbproject.sakura.ne.jp/wordpress/mitlicense
* @brief �l�l�c�B�o�l�w�B
*/


/** include
*/
#include "../types/types.h"


/** include
*/
#include "../geometry/geometry.h"
#include "../color/color.h"


/** NBsys::NMmd
*/
#if(BSYS_MMD_PMX_ENABLE)
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

