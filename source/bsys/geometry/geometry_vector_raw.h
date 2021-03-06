﻿#pragma once

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
	/** Geometry_Vector_2_Raw
	*/
	union Geometry_Vector_2_Raw
	{
		/** Vector
		*/
		struct Vector
		{
			f32 xx;
			f32 yy;
		}v;

		/** vector
		*/
		f32 vector[2];
	};


	/** Geometry_Vector_3_Raw
	*/
	union Geometry_Vector_3_Raw
	{
		/** Vector
		*/
		struct Vector
		{
			f32 xx;
			f32 yy;
			f32 zz;
		}v;

		/** vector
		*/
		f32 vector[3];
	};


	/** Geometry_Vector_4_Raw
	*/
	union Geometry_Vector_4_Raw
	{
		/** Vector
		*/
		struct Vector
		{
			f32 xx;
			f32 yy;
			f32 zz;
			f32 ww;
		}v;

		/** vector
		*/
		f32 vector[4];
	};


}}
#endif

