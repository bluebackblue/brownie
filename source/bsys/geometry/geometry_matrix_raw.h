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
	struct Geometry_Matrix_44_Raw
	{
		union
		{
			struct
			{
				#if(BSYS_GEOMETRY_ROWCOLUMN_TYPE == 0x00)

				//行優先(Row-major)
				//D3DXMATRIX

				f32 m_11;
				f32 m_12;
				f32 m_13;
				f32 m_14;

				f32 m_21;
				f32 m_22;
				f32 m_23;
				f32 m_24;

				f32 m_31;
				f32 m_32;
				f32 m_33;
				f32 m_34;

				f32 m_41;
				f32 m_42;
				f32 m_43;
				f32 m_44;

				#else

				//列優先(Column-major)
				//HLSL

				f32 m_11;
				f32 m_12;
				f32 m_13;
				f32 m_14;

				f32 m_21;
				f32 m_22;
				f32 m_23;
				f32 m_24;

				f32 m_31;
				f32 m_32;
				f32 m_33;
				f32 m_34;

				f32 m_41;
				f32 m_42;
				f32 m_43;
				f32 m_44;

				#endif
			};

			struct
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
			};

			f32 m[4][4];
		};
	};


}}
#endif

