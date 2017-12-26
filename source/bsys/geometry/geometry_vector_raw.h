#pragma once

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
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
	/** Geometry_Vector_2_Raw
	*/
	struct Geometry_Vector_2_Raw
	{
		union
		{
			struct
			{
				f32 x;
				f32 y;
			};

			f32 v[2];
		};
	};


	/** Geometry_Vector_3_Raw
	*/
	struct Geometry_Vector_3_Raw
	{
		union
		{
			struct
			{
				f32 x;
				f32 y;
				f32 z;
			};

			f32 v[3];
		};
	};


	/** Geometry_Vector_4_Raw
	*/
	struct Geometry_Vector_4_Raw
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

