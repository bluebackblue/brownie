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
	/** エルミート曲線。

	a_start_pos		: 始点
	a_start_vector	: 始点ベクトル
	a_end_pos		: 終点
	a_end_vector	: 終点ベクトル

	a_rate			: レート

	*/
	inline Geometry_Vector2 HermiteCurve(Geometry_Vector2& a_start_pos,Geometry_Vector2& a_start_vector,Geometry_Vector2& a_end_pos,Geometry_Vector2& a_end_vector,f32 a_rate)
	{
		f32 t_start_pos = 2 * a_rate * a_rate * a_rate - 3 * a_rate * a_rate + 0 + 1;
		f32 t_start_vector = a_rate * a_rate * a_rate - 2 * a_rate * a_rate + a_rate;
		f32 t_end_pos = -2 * a_rate * a_rate * a_rate + 3 * a_rate * a_rate;
		f32 t_end_vector = a_rate * a_rate * a_rate - a_rate * a_rate;
		
		return Geometry_Vector2(
			a_start_pos.x * t_start_pos + a_start_vector.x * t_start_vector + a_end_pos.x * t_end_pos + a_end_vector.x * t_end_vector,
			a_start_pos.y * t_start_pos + a_start_vector.y * t_start_vector + a_end_pos.y * t_end_pos + a_end_vector.y * t_end_vector
		);
	}


	/** ベジェ曲線。４点。
	*/
	inline f32 GetBezierCurve(f32 a_pos_1,f32 a_pos_2,f32 a_pos_3,f32 a_pos_4,f32 a_rate)
	{
		f32 t_rate_inv = 1 - a_rate;

		f32 t_1 = t_rate_inv * t_rate_inv * t_rate_inv;
		f32 t_2 = 3 * t_rate_inv * t_rate_inv * a_rate;
		f32 t_3 = 3 * t_rate_inv * a_rate * a_rate;
		f32 t_4 = a_rate * a_rate * a_rate;

		return t_1 * a_pos_1 + t_2 * a_pos_2 + t_3 * a_pos_3 + t_4 * a_pos_4;
	}


	/** ベジェ曲線。３点。
	*/
	inline Geometry_Vector2 GetBezierCurve(Geometry_Vector2& a_pos_1,Geometry_Vector2& a_pos_2,Geometry_Vector2& a_pos_3,f32 a_rate)
	{
		f32 t_rate_inv = 1 - a_rate;

		f32 t_1 = t_rate_inv * t_rate_inv;
		f32 t_2 = 2 * t_rate_inv * a_rate;
		f32 t_3 = a_rate * a_rate;

		return Geometry_Vector2(
			t_1 * a_pos_1.x + t_2 * a_pos_2.x + t_3 * a_pos_3.x,
			t_1 * a_pos_1.y + t_2 * a_pos_2.y + t_3 * a_pos_3.y
		);
	}


	/** ベジェ曲線。４点。
	*/
	inline Geometry_Vector2 GetBezierCurve(Geometry_Vector2& a_pos_1,Geometry_Vector2& a_pos_2,Geometry_Vector2& a_pos_3,Geometry_Vector2& a_pos_4,f32 a_rate)
	{
		f32 t_rate_inv = 1 - a_rate;

		f32 t_1 = t_rate_inv * t_rate_inv * t_rate_inv;
		f32 t_2 = 3 * t_rate_inv * t_rate_inv * a_rate;
		f32 t_3 = 3 * t_rate_inv * a_rate * a_rate;
		f32 t_4 = a_rate * a_rate * a_rate;

		return Geometry_Vector2(
			t_1 * a_pos_1.x + t_2 * a_pos_2.x + t_3 * a_pos_3.x + t_4 * a_pos_4.x,
			t_1 * a_pos_1.y + t_2 * a_pos_2.y + t_3 * a_pos_3.y + t_4 * a_pos_4.y
		);
	}


	/** ベジェ曲線。５点。
	*/
	inline Geometry_Vector2 GetBezierCurve(Geometry_Vector2& a_pos_1,Geometry_Vector2& a_pos_2,Geometry_Vector2& a_pos_3,Geometry_Vector2& a_pos_4,Geometry_Vector2& a_pos_5,f32 a_rate)
	{
		f32 t_rate_inv = 1 - a_rate;

		f32 t_1 = t_rate_inv * t_rate_inv * t_rate_inv * t_rate_inv;
		f32 t_2 = 4 * t_rate_inv * t_rate_inv * t_rate_inv * a_rate;
		f32 t_3 = 6 * t_rate_inv * t_rate_inv * a_rate * a_rate;
		f32 t_4 = 4 * t_rate_inv * a_rate * a_rate * a_rate;
		f32 t_5 = a_rate * a_rate * a_rate;

		return Geometry_Vector2(
			t_1 * a_pos_1.x + t_2 * a_pos_2.x + t_3 * a_pos_3.x + t_4 * a_pos_4.x + t_5 * a_pos_5.x,
			t_1 * a_pos_1.y + t_2 * a_pos_2.y + t_3 * a_pos_3.y + t_4 * a_pos_4.y + t_5 * a_pos_5.y
		);
	}


}}
#endif

