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


/** NBsys::NGeometry
*/
#if(BSYS_GEOMETRY_ENABLE)
namespace NBsys{namespace NGeometry
{
	/** [�쐬]��Z�B
	*/
	inline Geometry_Vector2 operator *(f32 a_scale,const Geometry_Vector2& a_vector)
	{
		Geometry_Vector2 t_temp;
		{
			t_temp.x = a_vector.x * a_scale;
			t_temp.y = a_vector.y * a_scale;
		}
		return t_temp;
	}

	/** [�쐬]��Z�B
	*/
	inline Geometry_Vector3 operator *(f32 a_scale,const Geometry_Vector3& a_vector)
	{
		Geometry_Vector3 t_temp;
		{
			t_temp.x = a_vector.x * a_scale;
			t_temp.y = a_vector.y * a_scale;
			t_temp.z = a_vector.z * a_scale;
		}
		return t_temp;
	}

	/** [�쐬]��Z�B
	*/
	inline Geometry_Vector4 operator *(f32 a_scale,const Geometry_Vector4& a_vector)
	{
		Geometry_Vector4 t_temp;
		{
			t_temp.x = a_vector.x * a_scale;
			t_temp.y = a_vector.y * a_scale;
			t_temp.z = a_vector.z * a_scale;
			t_temp.w = a_vector.w * a_scale;
		}
		return t_temp;
	}

	/** constructor�B
	*/
	inline Geometry_Vector2::Geometry_Vector2()
	{
	}

	/** constructor�B
	*/
	inline Geometry_Vector2::Geometry_Vector2(f32 a_x,f32 a_y)
	{
		this->x = a_x;
		this->y = a_y;
	}

	/** constructor�B
	*/
	inline Geometry_Vector2::Geometry_Vector2(f32 a_value)
	{
		this->x = a_value;
		this->y = a_value;
	}

	/** constructor�B
	*/
	inline Geometry_Vector2::Geometry_Vector2(const f32* a_value_pointer)
	{
		this->x = a_value_pointer[0];
		this->y = a_value_pointer[1];
	}

	/** constructor�B
	*/
	inline Geometry_Vector2::Geometry_Vector2(const Geometry_Vector2& a_vector)
	{
		*this = a_vector;
	}

	/** constructor�B
	*/
	inline Geometry_Vector2::Geometry_Vector2(const Geometry_Identity& /*a_identity*/)
	{
		this->Set_Zero();
	}

	/** destructor�B
	*/
	inline Geometry_Vector2::~Geometry_Vector2()
	{
	}

	/** [static]Zero�B
	*/
	inline const Geometry_Vector2& Geometry_Vector2::Zero()
	{
		static const NGeometry::Geometry_Vector2 s_zero(0.0f,0.0f);

		return s_zero;
	}

	/** [static]One�B
	*/
	inline const Geometry_Vector2& Geometry_Vector2::One()
	{
		static const NGeometry::Geometry_Vector2 s_one(1.0f,1.0f);

		return s_one;
	}

	/** [�ݒ�]�B
	*/
	inline Geometry_Vector2& Geometry_Vector2::Set(f32 a_x,f32 a_y)
	{
		this->x = a_x;
		this->y = a_y;

		return *this;
	}

	/** [�ݒ�]�B
	*/
	inline Geometry_Vector2& Geometry_Vector2::Set(const Geometry_Vector2& a_vector)
	{
		this->x = a_vector.x;
		this->y = a_vector.y;

		return *this;
	}

	/** [�ݒ�]Set_Zero�B
	*/
	inline Geometry_Vector2& Geometry_Vector2::Set_Zero()
	{
		*this = Geometry_Vector2::Zero();

		return *this;
	}

	/** [�L���X�g]�B
	*/
	inline Geometry_Vector2::operator f32*()
	{
		return &this->v[0];
	}

	/** [�L���X�g]�B
	*/
	inline Geometry_Vector2::operator const f32*() const
	{
		return &this->v[0];
	}

	/** constructor�B
	*/
	inline Geometry_Vector3::Geometry_Vector3()
	{
	}

	/** constructor�B
	*/
	inline Geometry_Vector3::Geometry_Vector3(f32 a_x,f32 a_y,f32 a_z)
	{
		this->x = a_x;
		this->y = a_y;
		this->z = a_z;
	}

	/** constructor�B
	*/
	inline Geometry_Vector3::Geometry_Vector3(f32 a_value)
	{
		this->x = a_value;
		this->y = a_value;
		this->z = a_value;
	}

	/** constructor�B
	*/
	inline Geometry_Vector3::Geometry_Vector3(const f32* a_value_pointer)
	{
		this->x = a_value_pointer[0];
		this->y = a_value_pointer[1];
		this->z = a_value_pointer[2];
	}

	/** constructor�B
	*/
	inline Geometry_Vector3::Geometry_Vector3(const Geometry_Vector3& a_vector)
	{
		this->x = a_vector.x;
		this->y = a_vector.y;
		this->z = a_vector.z;
	}

	/** constructor�B
	*/
	inline Geometry_Vector3::Geometry_Vector3(const Geometry_Identity& /*a_identity*/)
	{
		this->Set_Zero();
	}

	/** destructor�B
	*/
	inline Geometry_Vector3::~Geometry_Vector3()
	{
	}

	/** [static]Zero�B
	*/
	inline const Geometry_Vector3& Geometry_Vector3::Zero()
	{
		static const NGeometry::Geometry_Vector3 s_zero(0.0f,0.0f,0.0f);

		return s_zero;
	}

	/** [static]One�B
	*/
	inline const Geometry_Vector3& Geometry_Vector3::One()
	{
		static const NGeometry::Geometry_Vector3 s_one(1.0f,1.0f,1.0f);

		return s_one;
	}

	/** [�ݒ�]�B
	*/
	inline Geometry_Vector3& Geometry_Vector3::Set(f32 a_x,f32 a_y,f32 a_z)
	{
		this->x = a_x;
		this->y = a_y;
		this->z = a_z;

		return *this;
	}

	/** [�ݒ�]�B
	*/
	inline Geometry_Vector3& Geometry_Vector3::Set(const Geometry_Vector3& a_vector)
	{
		this->x = a_vector.x;
		this->y = a_vector.y;
		this->z = a_vector.z;

		return *this;
	}

	/** [�ݒ�]Set_Zero�B
	*/
	inline Geometry_Vector3& Geometry_Vector3::Set_Zero()
	{
		*this = Geometry_Vector3::Zero();

		return *this;
	}

	/** [�L���X�g]�B
	*/
	inline Geometry_Vector3::operator f32*()
	{
		return &this->v[0];
	}

	/** [�L���X�g]�B
	*/
	inline Geometry_Vector3::operator const f32*() const
	{
		return &this->v[0];
	}

	/** [�쐬]�O�ρB
	*/
	inline Geometry_Vector3 Geometry_Vector3::Make_Cross(const Geometry_Vector3& a_vector) const
	{
		Geometry_Vector3 t_temp;
		{
			t_temp.x = (this->y * a_vector.z) - (this->z * a_vector.y);
			t_temp.y = (this->z * a_vector.x) - (this->x * a_vector.z);
			t_temp.z = (this->x * a_vector.y) - (this->y * a_vector.x);
		}
		return t_temp;
	}

	/** [�ݒ�]�O�ρB
	*/
	inline Geometry_Vector3& Geometry_Vector3::Set_Cross(const Geometry_Vector3& a_vector)
	{
		f32 t_temp_x = (this->y * a_vector.z) - (this->z * a_vector.y);
		f32 t_temp_y = (this->z * a_vector.x) - (this->x * a_vector.z);
		f32 t_temp_z = (this->x * a_vector.y) - (this->y * a_vector.x);

		this->x = t_temp_x;
		this->y = t_temp_y;
		this->z = t_temp_z;

		return *this;
	}

	/** [�ݒ�]�O�ρB
	*/
	inline Geometry_Vector3& Geometry_Vector3::Set_Cross(const Geometry_Vector3& a_vector_1,const Geometry_Vector3& a_vector_2)
	{
		f32 t_temp_x = (a_vector_1.y * a_vector_2.z) - (a_vector_1.z * a_vector_2.y);
		f32 t_temp_y = (a_vector_1.z * a_vector_2.x) - (a_vector_1.x * a_vector_2.z);
		f32 t_temp_z = (a_vector_1.x * a_vector_2.y) - (a_vector_1.y * a_vector_2.x);

		this->x = t_temp_x;
		this->y = t_temp_y;
		this->z = t_temp_z;

		return *this;
	}

	/** [�ݒ�]���K���B
	*/
	inline Geometry_Vector3& Geometry_Vector3::Set_Normalize()
	{
		f32 t_value = this->SquareLength();
		ASSERT(t_value != 0.0f);

		t_value = Math::sqrtf(t_value);
		ASSERT(t_value != 0.0f);

		t_value = 1.0f / t_value;

		this->x *= t_value;
		this->y *= t_value;
		this->z *= t_value;

		return *this;
	}

	/** [�ݒ�]���K���B
	*/
	inline Geometry_Vector3& Geometry_Vector3::Set_Normalize_Safe(const Geometry_Vector3& a_vector_safe)
	{
		f32 t_value = this->SquareLength();
		if(t_value == 0.0f){
			*this = a_vector_safe;
			return *this;
		}

		t_value = Math::sqrtf(t_value);
		if(t_value == 0.0f){
			*this = a_vector_safe;
			return *this;
		}

		t_value = 1.0f / t_value;

		this->x *= t_value;
		this->y *= t_value;
		this->z *= t_value;

		return *this;
	}

	/** [�ݒ�]���K���B
	*/
	inline f32 Geometry_Vector3::Set_Normalize_GetLength()
	{
		f32 t_value = this->SquareLength();
		if(t_value == 0.0f){
			return 0.0f;
		}

		t_value = Math::sqrtf(t_value);
		if(t_value == 0.0f){
			return 0.0f;
		}

		f32 t_length = t_value;

		t_value = 1.0f / t_value;

		this->x *= t_value;
		this->y *= t_value;
		this->z *= t_value;

		return t_length;
	}

	/** [�쐬]���K���B
	*/
	inline Geometry_Vector3 Geometry_Vector3::Make_Normalize() const
	{
		Geometry_Vector3 t_temp;
		{
			f32 t_value = this->SquareLength();
			ASSERT(t_value != 0.0f);

			t_value = Math::sqrtf(t_value);
			ASSERT(t_value != 0.0f);

			t_value = 1.0f / t_value;

			t_temp.x = this->x * t_value;
			t_temp.y = this->y * t_value;
			t_temp.z = this->z * t_value;
		}
		return t_temp;
	}

	/** [�쐬]���K���B
	*/
	inline Geometry_Vector3 Geometry_Vector3::Make_Normalize_Safe(const Geometry_Vector3& a_vector_safe) const
	{
		Geometry_Vector3 t_temp;
		{
			f32 t_value = this->SquareLength();
			if(t_value == 0.0f){
				return a_vector_safe;
			}

			t_value = Math::sqrtf(t_value);
			if(t_value == 0.0f){
				return a_vector_safe;
			}

			t_value = 1.0f / t_value;

			t_temp.x = this->x * t_value;
			t_temp.y = this->y * t_value;
			t_temp.z = this->z * t_value;
		}
		return t_temp;
	}

	/** [�ݒ�]���Z�B
	*/
	inline Geometry_Vector3& Geometry_Vector3::operator +=(const Geometry_Vector3& a_vector)
	{
		this->x += a_vector.x;
		this->y += a_vector.y;
		this->z += a_vector.z;

		return *this;
	}

	/** [�ݒ�]���Z�B
	*/
	inline Geometry_Vector3& Geometry_Vector3::operator -=(const Geometry_Vector3& a_vector)
	{
		this->x -= a_vector.x;
		this->y -= a_vector.y;
		this->z -= a_vector.z;

		return *this;
	}

	/** [�ݒ�]��Z�B
	*/
	inline Geometry_Vector3& Geometry_Vector3::operator *=(f32 a_value)
	{
		this->x *= a_value;
		this->y *= a_value;
		this->z *= a_value;

		return *this;
	}

	/** [�ݒ�]��Z�B
	*/
	inline Geometry_Vector3& Geometry_Vector3::operator *=(const Geometry_Vector3& a_vector)
	{
		this->x *= a_vector.x;
		this->y *= a_vector.y;
		this->z *= a_vector.z;

		return *this;
	}

	/** [�ݒ�]���Z�B
	*/
	inline Geometry_Vector3& Geometry_Vector3::operator /=(f32 a_value)
	{
		ASSERT(a_value != 0.0f);

		return operator *=(1.0f / a_value);
	}

	/** [�쐬]���g�̃x�N�g����Ԃ��܂��B
	*/
	inline Geometry_Vector3 Geometry_Vector3::operator +() const
	{
		return *this;
	}

	/** [�쐬]�t�����x�N�g���B
	*/
	inline Geometry_Vector3 Geometry_Vector3::operator -() const
	{
		Geometry_Vector3 t_temp(-this->x,-this->y,-this->z);

		return t_temp;
	}

	/** [�쐬]���Z�B
	*/
	inline Geometry_Vector3 Geometry_Vector3::operator +(const Geometry_Vector3& a_vector) const
	{
		Geometry_Vector3 t_temp;
		{
			t_temp.x = this->x + a_vector.x;
			t_temp.y = this->y + a_vector.y;
			t_temp.z = this->z + a_vector.z;
		}

		return t_temp;
	}

	/** [�쐬]���Z�B
	*/
	inline Geometry_Vector3 Geometry_Vector3::operator -(const Geometry_Vector3& a_vector) const
	{
		Geometry_Vector3 t_temp;
		{
			t_temp.x = this->x - a_vector.x;
			t_temp.y = this->y - a_vector.y;
			t_temp.z = this->z - a_vector.z;
		}

		return t_temp;
	}

	/** [�쐬]��Z�B
	*/
	inline Geometry_Vector3 Geometry_Vector3::operator *(f32 a_value) const
	{
		Geometry_Vector3 t_temp;
		{
			t_temp.x = this->x * a_value;
			t_temp.y = this->y * a_value;
			t_temp.z = this->z * a_value;
		}

		return t_temp;
	}

	/** [�쐬]���Z�B
	*/
	inline Geometry_Vector3 Geometry_Vector3::operator /(f32 a_value) const
	{
		ASSERT(a_value != 0.0f);

		f32 t_value = 1.0f / a_value;

		return operator *(t_value);
	}

	/** [��r]�B
	*/
	inline bool Geometry_Vector3::operator ==(const Geometry_Vector3& a_vector) const
	{
		return (this->x == a_vector.x) && (this->y == a_vector.y) && (this->z == a_vector.z);
	}

	/** [��r]�B
	*/
	inline bool Geometry_Vector3::operator !=(const Geometry_Vector3& a_vector) const
	{
		return (x != a_vector.x) || (y != a_vector.y) || (z != a_vector.z);
	}

	/** [����]length(this)*length(a_vector)*cos(��)�B
	*/
	inline f32 Geometry_Vector3::Dot(const Geometry_Vector3& a_vector) const
	{
		f32 t_value = (this->x * a_vector.x) + (this->y * a_vector.y) + (this->z * a_vector.z);

		return t_value;
	}

	/** [�`�F�b�N]�B
	*/
	inline bool Geometry_Vector3::IsZero() const
	{
		return (this->x == 0.0f)&&(this->y == 0.0f)&&(this->z == 0.0f);
	}

	/** [�쐬]�����B
	*/
	inline f32 Geometry_Vector3::Length() const
	{
		f32 t_value = this->SquareLength();

		t_value = Math::sqrtf(t_value);

		return t_value;
	}

	/** [�쐬]�����̂Q��B
	*/
	inline f32 Geometry_Vector3::SquareLength() const
	{
		return (this->x * this->x) + (this->y * this->y) + (this->z * this->z);
	}

	/** [�쐬]�Q�_�Ԃ̋����̂Q��B
	*/
	inline f32 Geometry_Vector3::SquareDistance(const Geometry_Vector3& a_vector) const
	{
		f32 t_temp_x = (this->x - a_vector.x);
		f32 t_temp_y = (this->y - a_vector.y);
		f32 t_temp_z = (this->z - a_vector.z);

		f32 t_value = (t_temp_x * t_temp_x) + (t_temp_y * t_temp_y) + (t_temp_z * t_temp_z);

		return t_value;
	}

	/** [�쐬]Make_Lerp�B

	a_per = 0.0f : return = this
	a_per = 1.0f : return = a_vector

	*/
	inline Geometry_Vector3 Geometry_Vector3::Make_Lerp(const Geometry_Vector3& a_vector,f32 a_per) const
	{
		Geometry_Vector3 t_temp;
		{
			t_temp.x = this->x + (a_vector.x - this->x) * a_per;
			t_temp.y = this->y + (a_vector.y - this->y) * a_per;
			t_temp.z = this->z + (a_vector.z - this->z) * a_per;
		}
		return t_temp;
	}

	/** [static][�쐬]Lerp

	a_per = 0.0f : return = this
	a_per = 1.0f : return = a_vector

	*/
	inline Geometry_Vector3 Geometry_Vector3::Make_Lerp(const Geometry_Vector3& a_vector_1,const Geometry_Vector3& a_vector_2,f32 a_per)
	{
		Geometry_Vector3 t_temp;
		{
			t_temp.x = a_vector_1.x + (a_vector_2.x - a_vector_1.x) * a_per;
			t_temp.y = a_vector_1.y + (a_vector_2.y - a_vector_1.y) * a_per;
			t_temp.z = a_vector_1.z + (a_vector_2.z - a_vector_1.z) * a_per;
		}
		return t_temp;
	}

	/** [�ݒ�]Set_Lerp�B

	a_per = 0.0f : this = this
	a_per = 1.0f : this = a_vector

	*/
	inline void Geometry_Vector3::Set_Lerp(const Geometry_Vector3& a_vector,f32 a_per)
	{
		this->x += (a_vector.x - this->x) * a_per;
		this->y += (a_vector.y - this->y) * a_per;
		this->z += (a_vector.z - this->z) * a_per;
	}

	/** [�ݒ�]Lerp�B

	a_per = 0.0f : this = a_vector_1
	a_per = 1.0f : this = a_vector_2

	*/
	inline void Geometry_Vector3::Set_Lerp(const Geometry_Vector3& a_vector_1,const Geometry_Vector3& a_vector_2,f32 a_per)
	{
		this->x = a_vector_1.x + (a_vector_2.x - a_vector_1.x) * a_per;
		this->y = a_vector_1.y + (a_vector_2.y - a_vector_1.y) * a_per;
		this->z = a_vector_1.z + (a_vector_2.z - a_vector_1.z) * a_per;
	}

	/** constructor�B
	*/
	inline Geometry_Vector4::Geometry_Vector4()
	{
	}

	/** constructor�B
	*/
	inline Geometry_Vector4::Geometry_Vector4(f32 a_x,f32 a_y,f32 a_z,f32 a_w)
	{
		this->x = a_x;
		this->y = a_y;
		this->z = a_z;
		this->w = a_w;
	}

	/** constructor�B
	*/
	inline Geometry_Vector4::Geometry_Vector4(const f32* a_value_pointer)
	{
		this->x = a_value_pointer[0];
		this->y = a_value_pointer[1];
		this->z = a_value_pointer[2];
		this->w = a_value_pointer[3];
	}

	/** constructor�B
	*/
	inline Geometry_Vector4::Geometry_Vector4(const Geometry_Vector4& a_vector)
	{
		this->x = a_vector.x;
		this->y = a_vector.y;
		this->z = a_vector.z;
		this->w = a_vector.w;
	}

	/** constructor�B
	*/
	inline Geometry_Vector4::Geometry_Vector4(const Geometry_Identity& /*a_identity*/)
	{
		this->Set_Zero();
	}

	/** destructor�B
	*/
	inline Geometry_Vector4::~Geometry_Vector4()
	{
	}

	/** [static]Zero�B
	*/
	inline const Geometry_Vector4& Geometry_Vector4::Zero()
	{
		static const NGeometry::Geometry_Vector4 s_zero(0.0f,0.0f,0.0f,0.0f);

		return s_zero;
	}

	/** [static]One�B
	*/
	inline const Geometry_Vector4& Geometry_Vector4::One()
	{
		static const NGeometry::Geometry_Vector4 s_one(1.0f,1.0f,1.0f,1.0f);

		return s_one;
	}

	/** [�ݒ�]�B
	*/
	inline Geometry_Vector4& Geometry_Vector4::Set(f32 a_x,f32 a_y,f32 a_z,f32 a_w)
	{
		this->x = a_x;
		this->y = a_y;
		this->z = a_z;
		this->w = a_w;

		return *this;
	}

	/** [�ݒ�]�B
	*/
	inline Geometry_Vector4& Geometry_Vector4::Set(const Geometry_Vector4& a_vector)
	{
		this->x = a_vector.x;
		this->y = a_vector.y;
		this->z = a_vector.z;
		this->w = a_vector.w;

		return *this;
	}

	/** [�ݒ�]Set_Zero�B
	*/
	inline Geometry_Vector4& Geometry_Vector4::Set_Zero()
	{
		*this = Geometry_Vector4::Zero();

		return *this;
	}

	/** [�L���X�g]�B
	*/
	inline Geometry_Vector4::operator f32*()
	{
		return &this->v[0];
	}

	/** [�L���X�g]�B
	*/
	inline Geometry_Vector4::operator const f32*() const
	{
		return &this->v[0];
	}

}}
#endif
