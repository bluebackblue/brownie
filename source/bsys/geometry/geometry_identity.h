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


/** NBsys::NGeometry
*/
#if(BSYS_GEOMETRY_ENABLE)
namespace NBsys{namespace NGeometry
{
	/** �P�ʌ^�B
	*/
	struct Geometry_Identity_Type
	{
	};

	/** Geometry_Identity
	*/
	inline Geometry_Identity_Type Geometry_Identity()
	{
		return Geometry_Identity_Type();
	}
}}
#endif

