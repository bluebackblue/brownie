#pragma once

/**
 * Copyright (c) blueback
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


/** NBsys::NGeometry
*/
#if(BSYS_GEOMETRY_ENABLE)
#pragma warning(push)
#pragma warning(disable:4514)
namespace NBsys{namespace NGeometry
{
	/** NBsys::NGeometry::NImpl_RandomCurve
	*/
	namespace NImpl_RandomCurve
	{
		/** sinf
		*/
		inline f32 sinf(f32 a_rad)
		{
			return NMath::sin_f(a_rad);
		}

		/** cosf
		*/
		inline f32 cosf(f32 a_rad)
		{
			return NMath::cos_f(a_rad);
		}
	}


	/** Geometry_RandomCurve
	*/
	struct Geometry_RandomCurve
	{
	public:

		/** 速度。
		*/
		s32 speed_inverse_range;
		s32 speed_inverse;

		/** オフセット。
		*/
		f32 value_0;

		/** 比率用。
		*/
		f32 value_1;
		f32 value_2;
		f32 value_3;
		f32 value_4;
		f32 value_5;
		f32 value_6;

		/** サイン波用。
		*/
		f32 value_11;
		f32 value_12;
		f32 value_13;
		f32 value_14;
		f32 value_15;
		f32 value_16;
		f32 value_17;

	public:

		/** constructor
		*/
		Geometry_RandomCurve()
		{
			this->SetParam(1,2,3,4,5,6,7,8,9,10,11,12,13,10,10);
		}

		/** constructor
		*/
		Geometry_RandomCurve(s32 a_k)
		{
			this->SetParam(a_k,a_k+1,a_k+2,a_k+3,a_k+4,a_k+5,a_k+6,a_k+7,a_k+8,a_k+9,a_k+10,a_k+11,a_k+12,10,10);
		}

		/** constructor
		*/
		Geometry_RandomCurve(s32 a_k1,s32 a_k2,s32 a_k3,s32 a_k4,s32 a_k5,s32 a_k6,s32 a_k7,s32 a_k8,s32 a_k9,s32 a_k10,s32 a_k11,s32 a_k12,s32 a_k13,s32 a_speed_inverse_range,s32 a_speed_inverse)
		{
			this->SetParam(a_k1,a_k2,a_k3,a_k4,a_k5,a_k6,a_k7,a_k8,a_k9,a_k10,a_k11,a_k12,a_k13,a_speed_inverse_range,a_speed_inverse);
		}

		/** destructor
		*/
		nonvirtual ~Geometry_RandomCurve()
		{
		}

		/** 設定。
		*/
		void SetParam(s32 a_k1,s32 a_k2,s32 a_k3,s32 a_k4,s32 a_k5,s32 a_k6,s32 a_k7,s32 a_k8,s32 a_k9,s32 a_k10,s32 a_k11,s32 a_k12,s32 a_k13,s32 a_speed_inverse_range,s32 a_speed_inverse)
		{
			this->speed_inverse_range = a_speed_inverse_range;
			this->speed_inverse = a_speed_inverse;

			NBlib::RandomTemplate<> t_rand;
			t_rand.SetSeed(static_cast<u32>(a_k1));

			//-1000 - 0
			u32 t_rand_value = (t_rand.Get() % 1000);
			this->value_0  = - static_cast<f32>(t_rand_value);

			//0 - t_speed_inverse
			t_rand_value = (t_rand.Get() % 1000) + 1;
			this->value_1  = (1 + NMath::sin_f_fast(t_rand_value * a_k2  * (NMath::pi() - 0.001f))) * 0.5f * this->speed_inverse_range;

			t_rand_value = (t_rand.Get() % 1000) + 1;
			this->value_2  = (1 + NMath::sin_f_fast(t_rand_value * a_k3  * (NMath::pi() - 0.001f))) * 0.5f * this->speed_inverse_range;

			t_rand_value = (t_rand.Get() % 1000) + 1;
			this->value_3  = (1 + NMath::sin_f_fast(t_rand_value * a_k4  * (NMath::pi() - 0.001f))) * 0.5f * this->speed_inverse_range;

			t_rand_value = (t_rand.Get() % 1000) + 1;
			this->value_4  = (1 + NMath::sin_f_fast(t_rand_value * a_k5  * (NMath::pi() - 0.001f))) * 0.5f * this->speed_inverse_range;

			t_rand_value = (t_rand.Get() % 1000) + 1;
			this->value_5  = (1 + NMath::sin_f_fast(t_rand_value * a_k6  * (NMath::pi() - 0.001f))) * 0.5f * this->speed_inverse_range;

			t_rand_value = (t_rand.Get() % 1000) + 1;
			this->value_6  = (1 + NMath::sin_f_fast(t_rand_value * a_k6  * (NMath::pi() - 0.001f))) * 0.5f * this->speed_inverse_range;

			t_rand_value = (t_rand.Get() % 1000) + 1;
			this->value_11 = (1 + NMath::sin_f_fast(t_rand_value * a_k7  * (NMath::pi() - 0.001f))) * 0.5f * this->speed_inverse_range;

			t_rand_value = (t_rand.Get() % 1000) + 1;
			this->value_12 = (1 + NMath::sin_f_fast(t_rand_value * a_k8  * (NMath::pi() - 0.001f))) * 0.5f * this->speed_inverse_range;

			t_rand_value = (t_rand.Get() % 1000) + 1;
			this->value_13 = (1 + NMath::sin_f_fast(t_rand_value * a_k9  * (NMath::pi() - 0.001f))) * 0.5f * this->speed_inverse_range;

			t_rand_value = (t_rand.Get() % 1000) + 1;
			this->value_14 = (1 + NMath::sin_f_fast(t_rand_value * a_k10 * (NMath::pi() - 0.001f))) * 0.5f * this->speed_inverse_range;

			t_rand_value = (t_rand.Get() % 1000) + 1;
			this->value_15 = (1 + NMath::sin_f_fast(t_rand_value * a_k11 * (NMath::pi() - 0.001f))) * 0.5f * this->speed_inverse_range;

			t_rand_value = (t_rand.Get() % 1000) + 1;
			this->value_16 = (1 + NMath::sin_f_fast(t_rand_value * a_k12 * (NMath::pi() - 0.001f))) * 0.5f * this->speed_inverse_range;

			t_rand_value = (t_rand.Get() % 1000) + 1;
			this->value_17 = (1 + NMath::sin_f_fast(t_rand_value * a_k13 * (NMath::pi() - 0.001f))) * 0.5f * this->speed_inverse_range;
		}

		/** 取得。
		*/
		f32 Get(f32 a_time)
		{
			//0 - 1
			f32 t_per_1 = (1 + NImpl_RandomCurve::sinf((a_time + this->value_0) / (this->speed_inverse + this->value_1))) / 2;

			//0 - 1
			f32 t_per_2 = (1 + NImpl_RandomCurve::sinf((a_time + this->value_0) / (this->speed_inverse + this->value_2))) / 2;

			//0 - 1
			f32 t_per_3 = (1 + NImpl_RandomCurve::sinf((a_time + this->value_0) / (this->speed_inverse + this->value_3))) / 2;

			//0 - 1
			f32 t_per_4 = (1 + NImpl_RandomCurve::sinf((a_time + this->value_0) / (this->speed_inverse + this->value_4))) / 2;

			//0 - 1
			f32 t_per_5 = (1 + NImpl_RandomCurve::sinf((a_time + this->value_0) / (this->speed_inverse + this->value_5))) / 2;

			//0 - 1
			f32 t_per_6 = (1 + NImpl_RandomCurve::sinf((a_time + this->value_0) / (this->speed_inverse + this->value_6))) / 2;

			//0 - 1
			f32 t_value_1 = NImpl_RandomCurve::sinf((a_time + this->value_0) / (this->speed_inverse + this->value_11));
			f32 t_value_2 = NImpl_RandomCurve::sinf((a_time + this->value_0) / (this->speed_inverse + this->value_12));
			f32 t_value_3 = NImpl_RandomCurve::sinf((a_time + this->value_0) / (this->speed_inverse + this->value_13));
			f32 t_value_4 = NImpl_RandomCurve::sinf((a_time + this->value_0) / (this->speed_inverse + this->value_14));
			f32 t_value_5 = NImpl_RandomCurve::sinf((a_time + this->value_0) / (this->speed_inverse + this->value_15));
			f32 t_value_6 = NImpl_RandomCurve::sinf((a_time + this->value_0) / (this->speed_inverse + this->value_16));
			f32 t_value_7 = NImpl_RandomCurve::sinf((a_time + this->value_0) / (this->speed_inverse + this->value_17));

			//0 - 1
			return (((((((
			                  t_value_1 
				) * t_per_1 + t_value_2 * (1.0f - t_per_1)
				) * t_per_2 + t_value_3 * (1.0f - t_per_2)
				) * t_per_3 + t_value_4 * (1.0f - t_per_3)
				) * t_per_4 + t_value_5 * (1.0f - t_per_4)
				) * t_per_5 + t_value_6 * (1.0f - t_per_5)
				) * t_per_6 + t_value_7 * (1.0f - t_per_6)
			);
		}
	};


}}
#pragma warning(pop)
#endif

