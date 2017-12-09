#pragma once

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ジオメトリ。
*/


/** include
*/
#include "../types/types.h"


/** NBsys::NGeometry
*/
#if(BSYS_GEOMETRY_ENABLE)
namespace NBsys{namespace NGeometry
{

	/** Geometry_Vector2
	*/
	struct Geometry_Vector2;

	/** Geometry_Vector3
	*/
	struct Geometry_Vector3;

	/** Geometry_Vector4
	*/
	struct Geometry_Vector4;

}}
#endif

