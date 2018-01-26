#pragma once

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ジオメトリ。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** NBsys::NGeometry
*/
#if(BSYS_GEOMETRY_ENABLE)
namespace NBsys{namespace NGeometry
{
	/** Geometry_Quaternion_Raw
	*/
	union Geometry_Quaternion_Raw
	{
		struct Quaternion
		{
			f32 xx;
			f32 yy;
			f32 zz;
			f32 ww;
		}q;

		f32 quaternion[4];
	};


}}
#endif

