

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
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
#include <cmath>


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
			s_sin_cos_table[ii].sin_val = Math::sinf(t_rad);
			s_sin_cos_table[ii].cos_val = Math::cosf(t_rad);
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
	f32 Math::modf(f32 a_x,f32 a_y)
	{
		return std::fmodf(a_x,a_y);
	}
	/** [static]xのy乗。
	*/
	f32 Math::powf(f32 a_x,f32 a_y)
	{
		return std::powf(a_x,a_y);
	}

	/** [static]平方根。
	*/
	f32 Math::sqrtf(f32 a_value)
	{
		return std::sqrtf(a_value);
	}

	/** [static]2を底とする対数。
	*/
	f32 Math::log2f(f32 a_value)
	{
		return std::log2f(a_value);
	}

	/** [static]切り上げ。
	*/
	f32 Math::ceilf(f32 a_value)
	{
		return std::ceilf(a_value);
	}

	/** [static]絶対値。
	*/
	f32 Math::absf(f32 a_value)
	{
		return std::fabsf(a_value);
	}

	/** [static]自然対数の底のa_value乗。
	*/
	f32 Math::expf(f32 a_value)
	{
		return std::expf(a_value);
	}

	/** [static]サイン。
	*/
	f32 Math::sinf(f32 a_rad)
	{
		return std::sinf(a_rad);
	}

	/** [static]コサイン。
	*/
	f32 Math::cosf(f32 a_rad)
	{
		return std::cosf(a_rad);
	}

	/** [static]タンジェント。
	*/
	f32 Math::tanf(f32 a_rad)
	{
		return std::tanf(a_rad);
	}

	/** [static]アークサイン。
	*/
	f32 Math::asinf(f32 a_value)
	{
		return std::asinf(a_value);
	}

	/** [static]アークコサイン。
	*/
	f32 Math::acosf(f32 a_value)
	{
		return std::acosf(a_value);
	}

	/** [static]アークタンジェント。
	*/
	f32 Math::atanf(f32 a_value)
	{
		return std::atanf(a_value);
	}

	/** [static]サイン（テーブル参照）。
	*/
	f32 Math::sinf_fast(f32 a_rad)
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
	f32 Math::cosf_fast(f32 a_rad)
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
	f32 Math::tanf_fast(f32 a_rad)
	{
		f32 t_sin = Math::sinf_fast(a_rad);
		f32 t_cos = Math::cosf_fast(a_rad);

		if(t_cos != 0.0f){
			return t_sin / t_cos;
		}

		return t_sin / 0.0001f;
	}

}

