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
#include "./geometry_identity.h"
#include "./geometry_vector_raw.h"


/** NBsys::NGeometry
*/
#if(BSYS_GEOMETRY_ENABLE)
namespace NBsys{namespace NGeometry
{
	/** Geometry_Vector2
	*/
	struct Geometry_Vector2
	{
		/** raw
		*/
		Geometry_Vector_2_Raw raw;

		/** x
		*/
		inline f32& x();

		/** y
		*/
		inline f32& y();

		/** x
		*/
		inline const f32& x() const;

		/** y
		*/
		inline const f32& y() const;

		/** constructor
		*/
		inline Geometry_Vector2() noexcept;

		/** constructor
		*/
		inline Geometry_Vector2(f32 a_x,f32 a_y) noexcept;

		/** constructor
		*/
		inline Geometry_Vector2(f32 a_value) noexcept;

		/** constructor
		*/
		inline Geometry_Vector2(const f32* a_value_pointer) noexcept;

		/** copy constructor
		*/
		inline Geometry_Vector2(const Geometry_Vector2& a_vector) noexcept;

		/** constructor
		*/
		inline Geometry_Vector2(const Geometry_Identity_Type& /*a_identity*/) noexcept;

		/** destructor
		*/
		inline nonvirtual ~Geometry_Vector2();

		/** t_1 = t_2;
		*/
		inline Geometry_Vector2& operator =(const Geometry_Vector2& a_right);

		/** t_1 = +t_2;
		*/
		inline Geometry_Vector2 operator +() const;

		/** t_1 = -t_2;
		*/
		inline Geometry_Vector2 operator -() const;

		/** t_1 += t_2;
		*/
		inline Geometry_Vector2& operator +=(const Geometry_Vector2& a_right);

		/** t_1 -= t_2;
		*/
		inline Geometry_Vector2& operator -=(const Geometry_Vector2& a_right);

		/** t_1 *= t_2;
		*/
		inline Geometry_Vector2& operator *=(const Geometry_Vector2& a_right);

		/** t_1 /= t_2;
		*/
		inline Geometry_Vector2& operator /=(const Geometry_Vector2& a_right);

		/** t_1 = 2;
		*/
		inline Geometry_Vector2& operator =(f32 a_right_value);

		/** t_1 += 2;
		*/
		inline Geometry_Vector2& operator +=(f32 a_right_value);

		/** t_1 -= 2;
		*/
		inline Geometry_Vector2& operator -=(f32 a_right_value);

		/** t_1 *= 2;
		*/
		inline Geometry_Vector2& operator *=(f32 a_right_value);

		/** t_1 /= 2;
		*/
		inline Geometry_Vector2& operator /=(f32 a_right_value);

		/** [static]Zero。
		*/
		static inline const Geometry_Vector2& Zero();

		/** [static]One。
		*/
		static inline const Geometry_Vector2& One();

		/** [設定]。
		*/
		inline Geometry_Vector2& Set(f32 a_x,f32 a_y);

		/** [設定]。
		*/
		inline Geometry_Vector2& Set_X(f32 a_x);

		/** [設定]。
		*/
		inline Geometry_Vector2& Set_Y(f32 a_y);

		/** [設定]。
		*/
		inline Geometry_Vector2& Set(const Geometry_Vector2& a_vector);

		/** [設定]Set_Zero。
		*/
		inline Geometry_Vector2& Set_Zero();

		/** [取得]。
		*/
		inline f32 Get_X();

		/** [取得]。
		*/
		inline f32 Get_Y();
	};


}}
#endif

