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
		template <typename T> static inline T Min(T a_1,T a_2)
		{
			return ((a_1)<=(a_2))?(a_1):(a_2);
		}

		/** Max
		*/
		template <typename T> static inline T Max(T a_1,T a_2)
		{
			return ((a_1)>=(a_2))?(a_1):(a_2);
		}

		/** Clamp
		*/
		template <typename T> static inline T Clamp(T a_value,T a_min,T a_max)
		{
			return ((a_value)>=(a_max))?(a_max):(((a_value)<=(a_min))?(a_min):(a_value));
		}

		/** [static]is_nan
		*/
		static bool is_nan(f32 a_value);

		/** [static]a_x/a_yの余剰。
		*/
		static f32 modf(f32 a_x,f32 a_y);

		/** [static]xのy乗。
		*/
		static f32 powf(f32 a_x,f32 a_y);

		/** [static]平方根。
		*/
		static f32 sqrtf(f32 a_value);

		/** [static]2を底とする対数。
		*/
		static f32 log2f(f32 a_value);

		/** [static]切り上げ。
		*/
		static f32 ceilf(f32 a_value);

		/** [static]絶対値。
		*/
		static f32 absf(f32 a_value);

		/** [static]自然対数の底e(ネイピア数)のvalue乗。
		*/
		static f32 expf(f32 a_value);

		/** [static]sinf.
		*/
		static f32 sinf(f32 a_rad);

		/** [static]cosf.
		*/
		static f32 cosf(f32 a_rad);

		/** [static]tanf.
		*/
		static f32 tanf(f32 a_rad);

		/** [static]asinf.
		*/
		static f32 asinf(f32 a_x);

		/** [static]acosf.
		*/
		static f32 acosf(f32 a_x);

		/** [static]atanf.
		*/
		static f32 atanf(f32 a_x);

		/** [static]sinf_fast
		*/
		static f32 sinf_fast(f32 a_rad);

		/** [static]cosf_fast
		*/
		static f32 cosf_fast(f32 a_rad);

		/** [static]tanf_fast
		*/
		static f32 tanf_fast(f32 a_rad);
		
	};
}

