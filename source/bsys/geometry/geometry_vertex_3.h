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
	/** Geometry_Vector3
	*/
	struct Geometry_Vector3
	{
		/** raw
		*/
		Geometry_Vector_3_Raw raw;

		/** x
		*/
		inline const f32& x() const;

		/** x
		*/
		inline f32& x();

		/** y
		*/
		inline const f32& y() const;

		/** y
		*/
		inline f32& y();

		/** z
		*/
		inline const f32& z() const;

		/** z
		*/
		inline f32& z();

		/** constructor
		*/
		inline Geometry_Vector3() noexcept;

		/** constructor
		*/
		inline Geometry_Vector3(f32 a_x,f32 a_y,f32 a_z) noexcept;

		/** constructor
		*/
		inline Geometry_Vector3(f32 a_value) noexcept;

		/** constructor
		*/
		inline Geometry_Vector3(const f32* a_value_pointer) noexcept;

		/** copy constructor
		*/
		inline Geometry_Vector3(const Geometry_Vector3& a_vector) noexcept;

		/** constructor
		*/
		inline Geometry_Vector3(const Geometry_Identity_Type& /*a_identity*/) noexcept;

		/** destructor
		*/
		inline nonvirtual ~Geometry_Vector3();

		/** t_1 = t_2;
		*/
		inline Geometry_Vector3& operator =(const Geometry_Vector3& a_right);

		/** t_1 = +t_2;
		*/
		inline Geometry_Vector3 operator +() const;

		/** t_1 = -t_2;
		*/
		inline Geometry_Vector3 operator -() const;

		/** t_1 += t_2;
		*/
		inline Geometry_Vector3& operator +=(const Geometry_Vector3& a_right);

		/** t_1 -= t_2;
		*/
		inline Geometry_Vector3& operator -=(const Geometry_Vector3& a_right);

		/** t_1 *= t_2;
		*/
		inline Geometry_Vector3& operator *=(const Geometry_Vector3& a_right);

		/** t_1 /= t_2;
		*/
		inline Geometry_Vector3& operator /=(const Geometry_Vector3& a_right);

		/** t_1 = 2;
		*/
		inline Geometry_Vector3& operator =(f32 a_right_value);

		/** t_1 += 2;
		*/
		inline Geometry_Vector3& operator +=(f32 a_right_value);

		/** t_1 -= 2;
		*/
		inline Geometry_Vector3& operator -=(f32 a_right_value);

		/** t_1 *= 2;
		*/
		inline Geometry_Vector3& operator *=(f32 a_right_value);

		/** t_1 /= 2;
		*/
		inline Geometry_Vector3& operator /=(f32 a_right_value);

		/** [static]Zero。
		*/
		static inline const Geometry_Vector3& Zero();

		/** [static]One。
		*/
		static inline const Geometry_Vector3& One();

		/** [設定]。
		*/
		inline Geometry_Vector3& Set(f32 a_x,f32 a_y,f32 a_z);

		/** [設定]。
		*/
		inline Geometry_Vector3& Set_X(f32 a_x);

		/** [設定]。
		*/
		inline Geometry_Vector3& Set_Y(f32 a_y);

		/** [設定]。
		*/
		inline Geometry_Vector3& Set_Z(f32 a_z);

		/** [設定]。
		*/
		inline Geometry_Vector3& Set(const Geometry_Vector3& a_vector);

		/** [設定]Set_Zero。
		*/
		inline Geometry_Vector3& Set_Zero();

		/** [取得]。
		*/
		inline f32 Get_X();

		/** [取得]。
		*/
		inline f32 Get_Y();

		/** [取得]。
		*/
		inline f32 Get_Z();

		/** [作成]外積。
		*/
		inline Geometry_Vector3 Make_Cross(const Geometry_Vector3& a_vector) const;

		/** [設定]外積。
		*/
		inline Geometry_Vector3& Set_Cross(const Geometry_Vector3& a_vector);

		/** [設定]外積。
		*/
		inline Geometry_Vector3& Set_Cross(const Geometry_Vector3& a_vector_1,const Geometry_Vector3& a_vector_2);

		/** [設定]正規化。
		*/
		inline Geometry_Vector3& Set_Normalize();

		/** [設定]正規化。
		*/
		inline Geometry_Vector3& Set_Normalize_Safe(const Geometry_Vector3& a_vector_safe);

		/** [設定]正規化。
		*/
		inline f32 Set_Normalize_GetLength();

		/** [作成]正規化。
		*/
		inline Geometry_Vector3 Make_Normalize() const;

		/** [作成]正規化。
		*/
		inline Geometry_Vector3 Make_Normalize_Safe(const Geometry_Vector3& a_vector_safe) const;

		/** [内積]length(this)*length(a_vector)*cos(θ)。
		*/
		inline f32 Dot(const Geometry_Vector3& a_vector) const;

		/** [チェック]。
		*/
		inline bool IsZero() const;

		/** [作成]長さ。
		*/
		inline f32 Length() const;

		/** [作成]長さの２乗。
		*/
		inline f32 SquareLength() const;

		/** [作成]２点間の距離の２乗。
		*/
		inline f32 SquareDistance(const Geometry_Vector3& a_vector) const;

		/** [作成]Make_Lerp。

		a_per = 0.0f : return = this
		a_per = 1.0f : return = a_vector

		*/
		inline Geometry_Vector3 Make_Lerp(const Geometry_Vector3& a_vector,f32 a_per) const;

		/** [static][作成]Lerp

		a_per = 0.0f : return = this
		a_per = 1.0f : return = a_vector

		*/
		static inline Geometry_Vector3 Make_Lerp(const Geometry_Vector3& a_vector_1,const Geometry_Vector3& a_vector_2,f32 a_per);

		/** [設定]Lerp。

		a_per = 0.0f : this = this
		a_per = 1.0f : this = a_vector

		*/
		inline void Set_Lerp(const Geometry_Vector3& a_vector,f32 a_per);

		/** [設定]Lerp。

		a_per = 0.0f : this = a_vector_1
		a_per = 1.0f : this = a_vector_2

		*/
		inline void Set_Lerp(const Geometry_Vector3& a_vector_1,const Geometry_Vector3& a_vector_2,f32 a_per);
	};


}}
#endif

