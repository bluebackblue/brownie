#pragma once

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief フォント。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** NBsys::NFont
*/
#if(BSYS_FONT_ENABLE)
#pragma warning(push)
//#pragma warning(disable:0)
namespace NBsys{namespace NFont
{
	/** Font_Alignment
	*/
	struct Font_Alignment
	{
		enum Id
		{
			Left_Top = 0,	// x = 左。y = 上。
			Left_VCenter,	// x = 左。y = 中。
			Left_Bottom,	// x = 左。y = 下。
			Center_Top,		// x = 中。y = 下。
			Center_VCenter,	// x = 中。y = 中。
			Center_Bottom,	// x = 中。y = 下。
			Right_Top,		// x = 右。y = 上。
			Right_VCenter,	// x = 右。y = 中。
			Right_Bottom,	// x = 右。y = 下。
		};
	};


}}
#pragma warning(pop)
#endif

