#pragma once

/**
* Copyright (c) 2016 blueback
* @brief ÉÇÉfÉãÅB
* $Revision: 941 $
* $Author: bbbproject $
* $Date:: 2016-12-08 00:13:53 +0900#$
* $HeadURL: svn+ssh://bbbproject@bbbproject.sakura.ne.jp/home/bbbproject/svn-repos/www/artemis/asys/model/model_vertex.h $
* $Id: model_vertex.h 941 2016-12-07 15:13:53Z bbbproject $
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

