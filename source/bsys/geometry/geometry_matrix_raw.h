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
				f32 m_11;	//ax_x
				f32 m_12;	//ax_y
				f32 m_13;	//ax_z
				f32 m_14;	//ax_w

				f32 m_21;	//ay_x
				f32 m_22;	//ay_y
				f32 m_23;	//ay_z
				f32 m_24;	//ay_w

				f32 m_31;	//az_x
				f32 m_32;	//az_y
				f32 m_33;	//az_z
				f32 m_34;	//az_w

				f32 m_41;	//tr_x
				f32 m_42;	//tr_y
				f32 m_43;	//tr_z
				f32 m_44;	//tr_w
			};

			struct
			{
				f32 ax_x;	 //m[0][0]
				f32 ax_y;	 //m[0][1]
				f32 ax_z;	 //m[0][2]
				f32 ax_w;	 //m[0][3]

				f32 ay_x;	 //m[1][0]
				f32 ay_y;	 //m[1][1]
				f32 ay_z;	 //m[1][2]
				f32 ay_w;	 //m[1][3]

				f32 az_x;	 //m[2][0]
				f32 az_y;	 //m[2][1]
				f32 az_z;	 //m[2][2]
				f32 az_w;	 //m[2][3]

				f32 tr_x;	 //m[3][0]
				f32 tr_y;	 //m[3][1]
				f32 tr_z;	 //m[3][2]
				f32 tr_w;	 //m[3][3]
			};

			f32 m[4][4];
		};
	};
}}
#endif
