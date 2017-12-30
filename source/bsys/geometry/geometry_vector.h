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

		/** raw
		*/
		inline f32& x();
		inline f32& y();
		inline const f32& x() const;
		inline const f32& y() const;

		/** constructor
		*/
		inline Geometry_Vector2();

		/** constructor
		*/
		inline Geometry_Vector2(f32 a_x,f32 a_y);

		/** constructor
		*/
		inline Geometry_Vector2(f32 a_value);

		/** constructor
		*/
		inline Geometry_Vector2(const f32* a_value_pointer);

		/** constructor
		*/
		inline Geometry_Vector2(const Geometry_Vector2& a_vector);

		/** constructor
		*/
		inline Geometry_Vector2(const Geometry_Identity_Type& /*a_identity*/);

		/** destructor
		*/
		nonvirtual inline ~Geometry_Vector2();

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

		/** [キャスト]。
		*/
		inline operator f32*();

		/** [キャスト]。
		*/
		inline operator const f32*() const;
	};


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
		inline Geometry_Vector3();

		/** constructor
		*/
		inline Geometry_Vector3(f32 a_x,f32 a_y,f32 a_z);

		/** constructor
		*/
		inline Geometry_Vector3(f32 a_value);

		/** constructor
		*/
		inline Geometry_Vector3(const f32* a_value_pointer);

		/** constructor
		*/
		inline Geometry_Vector3(const Geometry_Vector3& a_vector);

		/** constructor
		*/
		inline Geometry_Vector3(const Geometry_Identity_Type& /*a_identity*/);

		/** destructor
		*/
		nonvirtual inline ~Geometry_Vector3();

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

		/** [キャスト]。
		*/
		inline operator f32*();

		/** [キャスト]。
		*/
		inline operator const f32*() const;

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

		/** [設定]加算。
		*/
		inline Geometry_Vector3& operator +=(const Geometry_Vector3& a_vector);

		/** [設定]減算。
		*/
		inline Geometry_Vector3& operator -=(const Geometry_Vector3& a_vector);

		/** [設定]乗算。
		*/
		inline Geometry_Vector3& operator *=(f32 a_value);

		/** [設定]乗算。
		*/
		inline Geometry_Vector3& operator *=(const Geometry_Vector3& a_vector);

		/** [設定]除算。
		*/
		inline Geometry_Vector3& operator /=(f32 a_value);

		/** [作成]自身のベクトルを返します。
		*/
		inline Geometry_Vector3 operator +() const;

		/** [作成]逆向きベクトル。
		*/
		inline Geometry_Vector3 operator -() const;

		/** [作成]加算。
		*/
		inline Geometry_Vector3 operator +(const Geometry_Vector3& a_vector) const;

		/** [作成]減算。
		*/
		inline Geometry_Vector3 operator -(const Geometry_Vector3& a_vector) const;

		/** [作成]乗算。
		*/
		inline Geometry_Vector3 operator *(f32 a_value) const;

		/** [作成]除算。
		*/
		inline Geometry_Vector3 operator /(f32 a_value) const;

		/** [比較]。
		*/
		inline bool operator ==(const Geometry_Vector3& a_vector) const;

		/** [比較]。
		*/
		inline bool operator !=(const Geometry_Vector3& a_vector) const;

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


	/** Geometry_Vector4
	*/
	struct Geometry_Vector4
	{
		/** raw
		*/
		Geometry_Vector_4_Raw raw;

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

		/** w
		*/
		inline const f32& w() const;

		/** w
		*/
		inline f32& w();

		/** constructor
		*/
		inline Geometry_Vector4();

		/** constructor
		*/
		inline Geometry_Vector4(f32 a_x,f32 a_y,f32 a_z,f32 a_w);

		/** constructor
		*/
		inline Geometry_Vector4(const f32* a_value_pointer);

		/** constructor
		*/
		inline Geometry_Vector4(const Geometry_Vector4& a_vector);

		/** constructor
		*/
		inline Geometry_Vector4(const Geometry_Identity_Type& /*a_identity*/);

		/** destructor
		*/
		nonvirtual inline ~Geometry_Vector4();

		/** [static]Make_Zero。
		*/
		static inline const Geometry_Vector4& Zero();

		/** [static]Make_One。
		*/
		static inline const Geometry_Vector4& One();

		/** [設定]。
		*/
		inline Geometry_Vector4& Set(f32 a_x,f32 a_y,f32 a_z,f32 a_w);

		/** [設定]。
		*/
		inline Geometry_Vector4& Set_X(f32 a_x);

		/** [設定]。
		*/
		inline Geometry_Vector4& Set_Y(f32 a_y);

		/** [設定]。
		*/
		inline Geometry_Vector4& Set_Z(f32 a_z);

		/** [設定]。
		*/
		inline Geometry_Vector4& Set_W(f32 a_w);

		/** [設定]。
		*/
		inline Geometry_Vector4& Set(const Geometry_Vector4& a_vector);

		/** [設定]Set_Zero。
		*/
		inline Geometry_Vector4& Set_Zero();

		/** [取得]。
		*/
		inline f32 Get_X();

		/** [取得]。
		*/
		inline f32 Get_Y();

		/** [取得]。
		*/
		inline f32 Get_Z();

		/** [取得]。
		*/
		inline f32 Get_W();

		/** [キャスト]。
		*/
		inline operator f32*();

		/** [キャスト]。
		*/
		inline operator const f32*() const;
	};


}}
#endif

