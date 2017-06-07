#pragma once

/**
* Copyright (c) 2017 blueback
* Released under the MIT License
* https://github.com/bluebackblue/brownie/blob/master/LICENSE
* http://bbbproject.sakura.ne.jp/wordpress/mitlicense
* @brief バーテックス。
*/


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./vertex.h"


/** NBsys::NVertex
*/
#if(BSYS_VERTEX_ENABLE)
namespace NBsys{namespace NVertex
{
	/** Preset_Plane
	*/
	template < typename T > sharedptr< Vertex< T > > Preset_Plane();

	/** Preset_Box
	*/
	template < typename T > sharedptr< Vertex< T > > Preset_Box();

}}
#endif

/** include
*/
#include "./vertex_preset.inl"

