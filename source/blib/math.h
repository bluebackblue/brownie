#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief 算術。
*/


/** include
*/
#include "./types.h"
#include "./platform.h"


/** include
*/
#include <algorithm>


/** define
*/
#define BLIB_MATH_DEG_TO_RAD(DEG)	((DEG)*(Math::PI/180.0f))
#define BLIB_MATH_RAD_TO_DEG(RAD)	((RAD)*(180.0f/Math::PI))


/** NBlib
*/
namespace NBlib
{
	/** Math
	*/
	class Math
	{
	public:

		/** PI
		*/
		static f32 PI;

		/** Initialize
		*/
		static void Initialize();

		/** Min
		*/
		template <typename T> static inline T GetMin(T a_1,T a_2)
		{
			return ((a_1)<=(a_2))?(a_1):(a_2);
		}

		/** Max
		*/
		template <typename T> static inline T GetMax(T a_1,T a_2)
		{
			return ((a_1)>=(a_2))?(a_1):(a_2);
		}

		/** Tの値をa_min以上a_max以下にする。
		*/
		template <typename T> static inline T GetClamp(T a_value,T a_min,T a_max)
		{
			return ((a_value)>=(a_max))?(a_max):(((a_value)<=(a_min))?(a_min):(a_value));
		}

		/** [static]is_nan
		*/
		static bool is_nan(f32 a_value);

		/** [static]a_x/a_yの余剰。
		*/
		static f32 mod_f(f32 a_x,f32 a_y);

		/** [static]xのy乗。
		*/
		static f32 pow_f(f32 a_x,f32 a_y);

		/** [static]平方根。
		*/
		static f32 sqrt_f(f32 a_value);

		/** [static]2を底とする対数。
		*/
		static f32 log2_f(f32 a_value);

		/** [static]切り上げ。
		*/
		static f32 ceil_f(f32 a_value);

		/** [static]絶対値。
		*/
		static f32 abs_f(f32 a_value);

		/** [static]eのvalue乗。
		*/
		static f32 exp_f(f32 a_value);

		/** [static]サイン。
		*/
		static f32 sin_f(f32 a_rad);

		/** [static]コサイン。
		*/
		static f32 cos_f(f32 a_rad);

		/** [static]タンジェント。
		*/
		static f32 tan_f(f32 a_rad);

		/** [static]アークサイン。
		*/
		static f32 asin_f(f32 a_x);

		/** [static]アークコサイン。
		*/
		static f32 acos_f(f32 a_x);

		/** [static]アークタンジェント。
		*/
		static f32 atan_f(f32 a_x);

		/** [static]サイン（テーブル参照）。
		*/
		static f32 sin_f_fast(f32 a_rad);

		/** [static]コサイン（テーブル参照）。
		*/
		static f32 cos_f_fast(f32 a_rad);

		/** [static]タンジェント（テーブル参照）。
		*/
		static f32 tan_f_fast(f32 a_rad);
		
	};


}

