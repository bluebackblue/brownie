#pragma once

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief パッド。
*/


/** include
*/
#include "../types/types.h"


/** NBsys::NPad
*/
#if(BSYS_PAD_ENABLE)
namespace NBsys{namespace NPad
{
	/** TouchValue
	*/
	struct TouchValue
	{
		f32		x;
		f32		y;
		bool	flag;

		/** constructor
		*/
		TouchValue()
			:
			x(0.0f),
			y(0.0f),
			flag(false)
		{
		}

		/** constructor
		*/
		TouchValue(f32 a_x,f32 a_y,bool a_flag)
			:
			x(a_x),
			y(a_y),
			flag(a_flag)
		{
		}

		/** Set
		*/
		void Set(f32 a_x,f32 a_y,bool a_flag)
		{
			this->x = a_x;
			this->y = a_y;
			this->flag = a_flag;
		}

		/** Zero
		*/
		static TouchValue& Zero()
		{
			static TouchValue s_zero(0.0f,0.0f,false);
			return s_zero;
		}
	};


}}
#endif

