#pragma once

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief 算術。
*/


/** include
*/
#include "./types.h"
#include "./platform.h"


/** include
*/
#pragma warning(push)
#pragma warning(disable:4710 4514 4987 4365 4820 4242 4244)
#include <algorithm>
#pragma warning(pop)


/** include
*/
#pragma warning(push)
#pragma warning(disable:4710 4514)
#include <cmath>
#pragma warning(pop)


/** define
*/
#define BLIB_MATH_DEG_TO_RAD(DEG)	((DEG)*(NMath::pi()/180.0f))
#define BLIB_MATH_RAD_TO_DEG(RAD)	((RAD)*(180.0f/NMath::pi()))


#define BLIB_MATH_PI	std::



/** NBlib
*/
#pragma warning(push)
#pragma warning(disable:4514 4711)
namespace NBlib
{
	/** NMath
	*/
	namespace NMath
	{
		/** SinCosSample
		*/
		struct SinCosSample
		{
			f32 sin_val;
			f32 cos_val;
		};


		/** SinCosSampleList
		*/
		typedef SinCosSample SinCosSampleList[BLIB_MATH_SINCOSFAST_TABLESIZE + 1];


		/** pi
		*/
		constexpr f32 pi()
		{
			return (3.141592653589793f);
		}


		/** Initialize
		*/
		void Initialize();


		/** GetSinCosTable
		*/
		SinCosSampleList& GetSinCosTable();


		/** Min
		*/
		template <typename T> inline T GetMin(T a_1,T a_2)
		{
			return ((a_1)<=(a_2))?(a_1):(a_2);
		}


		/** Max
		*/
		template <typename T> inline T GetMax(T a_1,T a_2)
		{
			return ((a_1)>=(a_2))?(a_1):(a_2);
		}


		/** Tの値をa_min以上a_max以下にする。
		*/
		template <typename T> inline T GetClamp(T a_value,T a_min,T a_max)
		{
			return ((a_value)>=(a_max))?(a_max):(((a_value)<=(a_min))?(a_min):(a_value));
		}


		/** 非数チェック。
		*/
		inline bool is_nan(f32 a_value)
		{
			return std::isnan(a_value);
		}


		/** a_x/a_yの余剰。
		*/
		inline f32 mod_f(f32 a_x,f32 a_y)
		{
			return std::fmodf(a_x,a_y);
		}


		/** xのy乗。
		*/
		inline f32 pow_f(f32 a_x,f32 a_y)
		{
			return std::powf(a_x,a_y);
		}


		/** 平方根。
		*/
		inline f32 sqrt_f(f32 a_value)
		{
			return std::sqrtf(a_value);
		}


		/** 2を底とする対数。
		*/
		inline f32 log2_f(f32 a_value)
		{
			return std::log2f(a_value);
		}


		/** 切り上げ。
		*/
		inline f32 ceil_f(f32 a_value)
		{
			return std::ceilf(a_value);
		}
			

		/** 絶対値。
		*/
		inline f32 abs_f(f32 a_value)
		{
			return std::fabsf(a_value);
		}


		/** eのvalue乗。
		*/
		inline f32 exp_f(f32 a_value)
		{
			return std::expf(a_value);
		}


		/** サイン。
		*/
		inline f32 sin_f(f32 a_rad)
		{
			return std::sinf(a_rad);
		}


		/** コサイン。
		*/
		inline f32 cos_f(f32 a_rad)
		{
			return std::cosf(a_rad);
		}


		/** タンジェント。
		*/
		inline f32 tan_f(f32 a_rad)
		{
			return std::tanf(a_rad);
		}


		/** アークサイン。
		*/
		inline f32 asin_f(f32 a_value)
		{
			return std::asinf(a_value);
		}


		/** アークコサイン。
		*/
		inline f32 acos_f(f32 a_value)
		{
			return std::acosf(a_value);
		}


		/** アークタンジェント。
		*/
		inline f32 atan_f(f32 a_value)
		{
			return std::atanf(a_value);
		}


		/** サイン（テーブル参照）。
		*/
		inline f32 sin_f_fast(f32 a_rad)
		{
			SinCosSampleList& t_table = GetSinCosTable();

			if(a_rad >= 0){
				u32 t_index = static_cast<u32>( (a_rad * ((COUNTOF(t_table) - 1) / (2.0f * NMath::pi())) + 0.5f)) % (COUNTOF(t_table) - 1);
				return  t_table[t_index].sin_val;
			}else{
				u32 t_index = static_cast<u32>(-(a_rad * ((COUNTOF(t_table) - 1) / (2.0f * NMath::pi())) - 0.5f)) % (COUNTOF(t_table) - 1);
				return -t_table[t_index].sin_val;
			}
		}


		/** コサイン（テーブル参照）。
		*/
		inline f32 cos_f_fast(f32 a_rad)
		{
			SinCosSampleList& t_table = GetSinCosTable();

			if(a_rad >= 0){
				u32 t_index = static_cast<u32>( (a_rad * ((COUNTOF(t_table) - 1) / (2.0f * NMath::pi())) + 0.5f)) % (COUNTOF(t_table) - 1);
				return t_table[t_index].cos_val;
			}else{
				u32 t_index = static_cast<u32>(-(a_rad * ((COUNTOF(t_table) - 1) / (2.0f * NMath::pi())) - 0.5f)) % (COUNTOF(t_table) - 1);
				return t_table[t_index].cos_val;
			}
		}


		/** タンジェント（テーブル参照）。
		*/
		inline f32 tan_f_fast(f32 a_rad)
		{
			f32 t_sin = NMath::sin_f_fast(a_rad);
			f32 t_cos = NMath::cos_f_fast(a_rad);

			if(t_cos != 0.0f){
				return t_sin / t_cos;
			}

			return t_sin / 0.0001f;
		}

		
	};


}
#pragma warning(pop)

