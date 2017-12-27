#pragma once

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief バーテックス。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


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
	template <typename T> sharedptr<Vertex<T>> Preset_Plane();


	/** Preset_Box
	*/
	template <typename T> sharedptr<Vertex<T>> Preset_Box();


}}
#endif


/** include
*/
#include "./vertex_preset.inl"

