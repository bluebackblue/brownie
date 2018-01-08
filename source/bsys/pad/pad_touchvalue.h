#pragma once

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief パッド。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** NBsys::NPad
*/
#if(BSYS_PAD_ENABLE)
#pragma warning(push)
#pragma warning(disable:4514 4820)
namespace NBsys{namespace NPad
{
	/** TouchValue
	*/
	struct TouchValue
	{
		/** pos
		*/
		Position2DType<f32> pos;

		/** flag
		*/
		bool flag;

		/** constructor
		*/
		TouchValue()
			:
			pos(0.0f),
			flag(false)
		{
		}

		/** constructor
		*/
		TouchValue(const Position2DType<f32>& a_pos,bool a_flag)
			:
			pos(a_pos),
			flag(a_flag)
		{
		}

		/** Set
		*/
		void Set(const Position2DType<f32>& a_pos,bool a_flag)
		{
			this->pos = a_pos;
			this->flag = a_flag;
		}

		/** Zero
		*/
		static TouchValue& Zero()
		{
			static TouchValue s_zero;
			return s_zero;
		}
	};


}}
#pragma warning(pop)
#endif

