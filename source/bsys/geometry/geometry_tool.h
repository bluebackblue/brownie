#pragma once

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �W�I���g���B
*/


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./geometry_vector.h"
#include "./geometry_matrix.h"
#include "./geometry_quaternion.h"


/** NBsys::NGeometry
*/
#if(BSYS_GEOMETRY_ENABLE)
namespace NBsys{namespace NGeometry
{

	/** �G���~�[�g�Ȑ��B
	*/
	inline Geometry_Vector2 HermiteCurve(Geometry_Vector2& a_p0,Geometry_Vector2& a_v0,Geometry_Vector2& a_p1,Geometry_Vector2& a_v1,f32 a_rate);

	/** �x�W�F�Ȑ��B�S�_�B
	*/
	inline f32 GetBezierCurve(f32 a_pos_1,f32 a_pos_2,f32 a_pos_3,f32 a_pos_4,f32 a_rate);

	/** �x�W�F�Ȑ��B�R�_�B
	*/
	inline Geometry_Vector2 GetBezierCurve(Geometry_Vector2& a_pos_1,Geometry_Vector2& a_pos_2,Geometry_Vector2& a_pos_3,f32 a_rate);

	/** �x�W�F�Ȑ��B�S�_�B
	*/
	inline Geometry_Vector2 GetBezierCurve(Geometry_Vector2& a_pos_1,Geometry_Vector2& a_pos_2,Geometry_Vector2& a_pos_3,Geometry_Vector2& a_pos_4,f32 a_rate);

	/** �x�W�F�Ȑ��B�T�_�B
	*/
	inline Geometry_Vector2 GetBezierCurve(Geometry_Vector2& a_pos_1,Geometry_Vector2& a_pos_2,Geometry_Vector2& a_pos_3,Geometry_Vector2& a_pos_4,Geometry_Vector2& a_pos_5,f32 a_rate);

}}
#endif

