#pragma once

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ジオメトリ。
*/


/** include
*/
#include "../types/types.h"


/** NBsys::NGeometry
*/
#if(BSYS_GEOMETRY_ENABLE)
namespace NBsys{namespace NGeometry
{
	/** Geometry_Quaternion_Raw
	*/
	struct Geometry_Quaternion_Raw
	{
		union
		{
			struct
			{
				f32 x;
				f32 y;
				f32 z;
				f32 w;
			};

			f32 v[4];
		};
	};


}}
#endif

