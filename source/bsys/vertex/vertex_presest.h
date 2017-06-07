#pragma once

/**
* Copyright (c) 2017 blueback
* Released under the MIT License
* https://github.com/bluebackblue/brownie/blob/master/LICENSE
* http://bbbproject.sakura.ne.jp/wordpress/mitlicense
* @brief ÉÇÉfÉãÅB
*/


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./model_vertex.h"


/** NBsys::NModel
*/
#if(BSYS_MODEL_ENABLE)
namespace NBsys{namespace NModel
{
	/** Preset_Plane
	*/
	template < typename T > sharedptr< Model_Vertex< T > > Preset_Plane();

	/** Preset_Box
	*/
	template < typename T > sharedptr< Model_Vertex< T > > Preset_Box();
}}
#endif

