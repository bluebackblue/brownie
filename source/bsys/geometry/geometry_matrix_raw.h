#pragma once

/**
 * Copyright (c) 2016-2017 blueback
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


/** include
*/
#include "./geometry_vector_raw.h"


/** NBsys::NGeometry
*/
#if(BSYS_GEOMETRY_ENABLE)
namespace NBsys{namespace NGeometry
{
	/** Geometry_Matrix_44_Raw
	*/
	union Geometry_Matrix_44_Raw
	{
		struct Matrix
		{
			#if(BSYS_GEOMETRY_ROWCOLUMN_TYPE == 0x00)

			//行優先(Row-major)
			//D3DXMATRIX
			//Maya

			f32 ax_x;
			f32 ax_y;
			f32 ax_z;
			f32 ax_w;

			f32 ay_x;
			f32 ay_y;
			f32 ay_z;
			f32 ay_w;

			f32 az_x;
			f32 az_y;
			f32 az_z;
			f32 az_w;

			f32 tr_x;
			f32 tr_y;
			f32 tr_z;
			f32 tr_w;

			#else

			//列優先(Column-major)
			//HLSL
			//OpenGL

			f32 ax_x;
			f32 ay_x;
			f32 az_x;
			f32 tr_x;

			f32 ax_y;
			f32 ay_y;
			f32 az_y;
			f32 tr_y;

			f32 ax_z;
			f32 ay_z;
			f32 az_z;
			f32 tr_z;

			f32 ax_w;
			f32 ay_w;
			f32 az_w;
			f32 tr_w;

			#endif
		}m;

		f32 matrix[4][4];
	};


}}
#endif

