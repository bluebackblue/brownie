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
#include "./geometry_identity.h"
#include "./geometry_vector_raw.h"


/** NBsys::NGeometry
*/
#if(BSYS_GEOMETRY_ENABLE)
namespace NBsys{namespace NGeometry
{

	/** Geometry_Vector2
	*/
	struct Geometry_Vector2 : public Geometry_Vector_2_Raw
	{
		/** constructor�B
		*/
		inline Geometry_Vector2();

		/** constructor�B
		*/
		inline Geometry_Vector2(f32 a_x,f32 a_y);

		/** constructor�B
		*/
		inline Geometry_Vector2(f32 a_value);

		/** constructor�B
		*/
		inline Geometry_Vector2(const f32* a_value_pointer);

		/** constructor�B
		*/
		inline Geometry_Vector2(const Geometry_Vector2& a_vector);

		/** constructor�B
		*/
		inline Geometry_Vector2(const Geometry_Identity_Type& /*a_identity*/);

		/** destructor�B
		*/
		nonvirtual inline ~Geometry_Vector2();

		/** [static]Zero�B
		*/
		static inline const Geometry_Vector2& Zero();

		/** [static]One�B
		*/
		static inline const Geometry_Vector2& One();

		/** [�ݒ�]�B
		*/
		inline Geometry_Vector2& Set(f32 a_x,f32 a_y);

		/** [�ݒ�]�B
		*/
		inline Geometry_Vector2& Set(const Geometry_Vector2& a_vector);

		/** [�ݒ�]Set_Zero�B
		*/
		inline Geometry_Vector2& Set_Zero();

		/** [�L���X�g]�B
		*/
		inline operator f32*();

		/** [�L���X�g]�B
		*/
		inline operator const f32*() const;
	};

	/** Geometry_Vector3
	*/
	struct Geometry_Vector3 : public Geometry_Vector_3_Raw
	{
		/** constructor�B
		*/
		inline Geometry_Vector3();

		/** constructor�B
		*/
		inline Geometry_Vector3(f32 a_x,f32 a_y,f32 a_z);

		/** constructor�B
		*/
		inline Geometry_Vector3(f32 a_value);

		/** constructor�B
		*/
		inline Geometry_Vector3(const f32* a_value_pointer);

		/** constructor�B
		*/
		inline Geometry_Vector3(const Geometry_Vector3& a_vector);

		/** constructor�B
		*/
		inline Geometry_Vector3(const Geometry_Identity_Type& /*a_identity*/);

		/** destructor�B
		*/
		nonvirtual inline ~Geometry_Vector3();

		/** [static]Zero�B
		*/
		static inline const Geometry_Vector3& Zero();

		/** [static]One�B
		*/
		static inline const Geometry_Vector3& One();

		/** [�ݒ�]�B
		*/
		inline Geometry_Vector3& Set(f32 a_x,f32 a_y,f32 a_z);

		/** [�ݒ�]�B
		*/
		inline Geometry_Vector3& Set(const Geometry_Vector3& a_vector);

		/** [�ݒ�]Set_Zero�B
		*/
		inline Geometry_Vector3& Set_Zero();

		/** [�L���X�g]�B
		*/
		inline operator f32*();

		/** [�L���X�g]�B
		*/
		inline operator const f32*() const;

		/** [�쐬]�O�ρB
		*/
		inline Geometry_Vector3 Make_Cross(const Geometry_Vector3& a_vector) const;

		/** [�ݒ�]�O�ρB
		*/
		inline Geometry_Vector3& Set_Cross(const Geometry_Vector3& a_vector);

		/** [�ݒ�]�O�ρB
		*/
		inline Geometry_Vector3& Set_Cross(const Geometry_Vector3& a_vector_1,const Geometry_Vector3& a_vector_2);

		/** [�ݒ�]���K���B
		*/
		inline Geometry_Vector3& Set_Normalize();

		/** [�ݒ�]���K���B
		*/
		inline Geometry_Vector3& Set_Normalize_Safe(const Geometry_Vector3& a_vector_safe);

		/** [�ݒ�]���K���B
		*/
		inline f32 Set_Normalize_GetLength();

		/** [�쐬]���K���B
		*/
		inline Geometry_Vector3 Make_Normalize() const;

		/** [�쐬]���K���B
		*/
		inline Geometry_Vector3 Make_Normalize_Safe(const Geometry_Vector3& a_vector_safe) const;

		/** [�ݒ�]���Z�B
		*/
		inline Geometry_Vector3& operator +=(const Geometry_Vector3& a_vector);

		/** [�ݒ�]���Z�B
		*/
		inline Geometry_Vector3& operator -=(const Geometry_Vector3& a_vector);

		/** [�ݒ�]��Z�B
		*/
		inline Geometry_Vector3& operator *=(f32 a_value);

		/** [�ݒ�]��Z�B
		*/
		inline Geometry_Vector3& operator *=(const Geometry_Vector3& a_vector);

		/** [�ݒ�]���Z�B
		*/
		inline Geometry_Vector3& operator /=(f32 a_value);

		/** [�쐬]���g�̃x�N�g����Ԃ��܂��B
		*/
		inline Geometry_Vector3 operator +() const;

		/** [�쐬]�t�����x�N�g���B
		*/
		inline Geometry_Vector3 operator -() const;

		/** [�쐬]���Z�B
		*/
		inline Geometry_Vector3 operator +(const Geometry_Vector3& a_vector) const;

		/** [�쐬]���Z�B
		*/
		inline Geometry_Vector3 operator -(const Geometry_Vector3& a_vector) const;

		/** [�쐬]��Z�B
		*/
		inline Geometry_Vector3 operator *(f32 a_value) const;

		/** [�쐬]���Z�B
		*/
		inline Geometry_Vector3 operator /(f32 a_value) const;

		/** [��r]�B
		*/
		inline bool operator ==(const Geometry_Vector3& a_vector) const;

		/** [��r]�B
		*/
		inline bool operator !=(const Geometry_Vector3& a_vector) const;

		/** [����]length(this)*length(a_vector)*cos(��)�B
		*/
		inline f32 Dot(const Geometry_Vector3& a_vector) const;

		/** [�`�F�b�N]�B
		*/
		inline bool IsZero() const;

		/** [�쐬]�����B
		*/
		inline f32 Length() const;

		/** [�쐬]�����̂Q��B
		*/
		inline f32 SquareLength() const;

		/** [�쐬]�Q�_�Ԃ̋����̂Q��B
		*/
		inline f32 SquareDistance(const Geometry_Vector3& a_vector) const;

		/** [�쐬]Make_Lerp�B

		a_per = 0.0f : return = this
		a_per = 1.0f : return = a_vector

		*/
		inline Geometry_Vector3 Make_Lerp(const Geometry_Vector3& a_vector,f32 a_per) const;

		/** [static][�쐬]Lerp

		a_per = 0.0f : return = this
		a_per = 1.0f : return = a_vector

		*/
		static inline Geometry_Vector3 Make_Lerp(const Geometry_Vector3& a_vector_1,const Geometry_Vector3& a_vector_2,f32 a_per);

		/** [�ݒ�]Lerp�B

		a_per = 0.0f : this = this
		a_per = 1.0f : this = a_vector

		*/
		inline void Set_Lerp(const Geometry_Vector3& a_vector,f32 a_per);

		/** [�ݒ�]Lerp�B

		a_per = 0.0f : this = a_vector_1
		a_per = 1.0f : this = a_vector_2

		*/
		inline void Set_Lerp(const Geometry_Vector3& a_vector_1,const Geometry_Vector3& a_vector_2,f32 a_per);
	};

	/** Geometry_Vector4
	*/
	struct Geometry_Vector4 : public Geometry_Vector_4_Raw
	{
		/** constructor�B
		*/
		inline Geometry_Vector4();

		/** constructor�B
		*/
		inline Geometry_Vector4(f32 a_x,f32 a_y,f32 a_z,f32 a_w);

		/** constructor�B
		*/
		inline Geometry_Vector4(const f32* a_value_pointer);

		/** constructor�B
		*/
		inline Geometry_Vector4(const Geometry_Vector4& a_vector);

		/** constructor�B
		*/
		inline Geometry_Vector4(const Geometry_Identity_Type& /*a_identity*/);

		/** destructor�B
		*/
		nonvirtual inline ~Geometry_Vector4();

		/** [static]Make_Zero�B
		*/
		static inline const Geometry_Vector4& Zero();

		/** [static]Make_One�B
		*/
		static inline const Geometry_Vector4& One();

		/** [�ݒ�]�B
		*/
		inline Geometry_Vector4& Set(f32 a_x,f32 a_y,f32 a_z,f32 a_w);

		/** [�ݒ�]�B
		*/
		inline Geometry_Vector4& Set(const Geometry_Vector4& a_vector);

		/** [�ݒ�]Set_Zero�B
		*/
		inline Geometry_Vector4& Set_Zero();

		/** [�L���X�g]�B
		*/
		inline operator f32*();

		/** [�L���X�g]�B
		*/
		inline operator const f32*() const;

	};

}}
#endif

