

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief 算術。
*/


/** include
*/
#include <blib_pch.h>


/** include
*/
#include "./types.h"
#include "./platform.h"


/** include
*/
#include "./math.h"


/** include
*/
#pragma warning(push)
#pragma warning(disable:4514)
#include <cmath>
#pragma warning(pop)


/** NBlib
*/
namespace NBlib
{
	/** SinCosSample
	*/
	struct SinCosSample
	{
		f32 sin_val;
		f32 cos_val;
	};


	/** sincosテーブル。
	*/
	static SinCosSample s_sin_cos_table[BLIB_MATH_SINCOSFAST_TABLESIZE + 1] = {0};


	/** [static]PI
	*/
	f32 Math::PI = (3.141592653589793f);


	/** 初期化。
	*/
	void Math::Initialize()
	{
		for(s32 ii=0;ii<(COUNTOF(s_sin_cos_table));ii++){
			f32 t_rad = (2.0f * Math::PI * ii) / (COUNTOF(s_sin_cos_table) - 1);
			s_sin_cos_table[ii].sin_val = Math::sin_f(t_rad);
			s_sin_cos_table[ii].cos_val = Math::cos_f(t_rad);
		}
	}


	/** [static]非数チェック。
	*/
	bool Math::is_nan(f32 a_value)
	{
		return std::isnan(a_value);
	}


	/** [static]a_x/a_yの余剰。
	*/
	f32 Math::mod_f(f32 a_x,f32 a_y)
	{
		#if defined(PLATFORM_VCWIN)
		
			return std::fmodf(a_x,a_y);
		
		#elif defined(PLATFORM_GNUCWIN)

			return ::fmodf(a_x,a_y);

		#else

			#warning
			return 0.0f;

		#endif
	}


	/** [static]xのy乗。
	*/
	f32 Math::pow_f(f32 a_x,f32 a_y)
	{
		#if defined(PLATFORM_VCWIN)

			return std::powf(a_x,a_y);

		#elif defined(PLATFORM_GNUCWIN)

			return ::powf(a_x,a_y);

		#else

			#warning
			return 0.0f;

		#endif
	}


	/** [static]平方根。
	*/
	f32 Math::sqrt_f(f32 a_value)
	{
		#if defined(PLATFORM_VCWIN)

			return std::sqrtf(a_value);

		#elif defined(PLATFORM_GNUCWIN)

			return ::sqrtf(a_value);

		#else

			#warning
			return 0.0f;

		#endif
	}


	/** [static]2を底とする対数。
	*/
	f32 Math::log2_f(f32 a_value)
	{
		#if defined(PLATFORM_VCWIN)

			return std::log2f(a_value);

		#elif defined(PLATFORM_GNUCWIN)

			return ::log2f(a_value);

		#else

			#warning
			return 0.0f;

		#endif
	}


	/** [static]切り上げ。
	*/
	f32 Math::ceil_f(f32 a_value)
	{
		#if defined(PLATFORM_VCWIN)

			return std::ceilf(a_value);

		#elif defined(PLATFORM_GNUCWIN)

			return ::ceilf(a_value);

		#else

			#warning
			return 0.0f;

		#endif
	}


	/** [static]絶対値。
	*/
	f32 Math::abs_f(f32 a_value)
	{
		#if defined(PLATFORM_VCWIN)

			return std::fabsf(a_value);

		#elif defined(PLATFORM_GNUCWIN)

			return ::fabsf(a_value);

		#else

			#warning
			return 0.0f;

		#endif
	}


	/** [static]eのvalue乗。
	*/
	f32 Math::exp_f(f32 a_value)
	{
		#if defined(PLATFORM_VCWIN)

			return std::expf(a_value);

		#elif defined(PLATFORM_GNUCWIN)

			return ::expf(a_value);

		#else

			#warning
			return 0.0f;

		#endif
	}


	/** [static]サイン。
	*/
	f32 Math::sin_f(f32 a_rad)
	{
		#if defined(PLATFORM_VCWIN)

			return std::sinf(a_rad);

		#elif defined(PLATFORM_GNUCWIN)

			return ::sinf(a_rad);

		#else

			#warning
			return 0.0f;

		#endif
	}


	/** [static]コサイン。
	*/
	f32 Math::cos_f(f32 a_rad)
	{
		#if defined(PLATFORM_VCWIN)

			return std::cosf(a_rad);

		#elif defined(PLATFORM_GNUCWIN)

			return ::cosf(a_rad);

		#else

			#warning
			return 0.0f;

		#endif
	}


	/** [static]タンジェント。
	*/
	f32 Math::tan_f(f32 a_rad)
	{
		#if defined(PLATFORM_VCWIN)

			return std::tanf(a_rad);

		#elif defined(PLATFORM_GNUCWIN)

			return ::tanf(a_rad);

		#else

			#warning
			return 0.0f;

		#endif
	}


	/** [static]アークサイン。
	*/
	f32 Math::asin_f(f32 a_value)
	{
		#if defined(PLATFORM_VCWIN)

			return std::asinf(a_value);

		#elif defined(PLATFORM_GNUCWIN)

			return ::asinf(a_value);

		#else

			#warning
			return 0.0f;

		#endif
	}


	/** [static]アークコサイン。
	*/
	f32 Math::acos_f(f32 a_value)
	{
		#if defined(PLATFORM_VCWIN)

			return std::acosf(a_value);

		#elif defined(PLATFORM_GNUCWIN)

			return ::acosf(a_value);

		#else

			#warning
			return 0.0f;

		#endif
	}


	/** [static]アークタンジェント。
	*/
	f32 Math::atan_f(f32 a_value)
	{
		#if defined(PLATFORM_VCWIN)

			return std::atanf(a_value);

		#elif defined(PLATFORM_GNUCWIN)

			return ::atanf(a_value);

		#else

			#warning
			return 0.0f;

		#endif
	}


	/** [static]サイン（テーブル参照）。
	*/
	f32 Math::sin_f_fast(f32 a_rad)
	{
		if(a_rad >= 0){
			u32 t_index = static_cast<u32>( (a_rad * ((COUNTOF(s_sin_cos_table) - 1) / (2.0f * Math::PI)) + 0.5f)) % (COUNTOF(s_sin_cos_table) - 1);
			return  s_sin_cos_table[t_index].sin_val;
		}else{
			u32 t_index = static_cast<u32>(-(a_rad * ((COUNTOF(s_sin_cos_table) - 1) / (2.0f * Math::PI)) - 0.5f)) % (COUNTOF(s_sin_cos_table) - 1);
			return -s_sin_cos_table[t_index].sin_val;
		}
	}


	/** [static]コサイン（テーブル参照）。
	*/
	f32 Math::cos_f_fast(f32 a_rad)
	{
		if(a_rad >= 0){
			u32 t_index = static_cast<u32>( (a_rad * ((COUNTOF(s_sin_cos_table) - 1) / (2.0f * Math::PI)) + 0.5f)) % (COUNTOF(s_sin_cos_table) - 1);
			return s_sin_cos_table[t_index].cos_val;
		}else{
			u32 t_index = static_cast<u32>(-(a_rad * ((COUNTOF(s_sin_cos_table) - 1) / (2.0f * Math::PI)) - 0.5f)) % (COUNTOF(s_sin_cos_table) - 1);
			return s_sin_cos_table[t_index].cos_val;
		}
	}


	/** [static]タンジェント（テーブル参照）。
	*/
	f32 Math::tan_f_fast(f32 a_rad)
	{
		f32 t_sin = Math::sin_f_fast(a_rad);
		f32 t_cos = Math::cos_f_fast(a_rad);

		if(t_cos != 0.0f){
			return t_sin / t_cos;
		}

		return t_sin / 0.0001f;
	}


}

