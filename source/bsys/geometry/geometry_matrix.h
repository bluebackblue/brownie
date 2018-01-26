#pragma once

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ジオメトリ。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** include
*/
#include "./geometry_matrix_44.h"


/** NBsys::NGeometry
*/
#if(BSYS_GEOMETRY_ENABLE)
#pragma warning(push)
#pragma warning(disable:4514 4710)
namespace NBsys{namespace NGeometry
{
	/** NBsys::NGeometry::NImpl_Matrix
	*/
	namespace NImpl_Matrix
	{
		/** sinf
		*/
		inline f32 sinf(f32 a_rad)
		{
			#if(BSYS_GEOMETRY_MATRIX_SINCOSFAST_ENABLE)
			return NMath::sin_f_fast(a_rad);
			#else
			return NMath::sinf(a_rad);
			#endif
		}


		/** cosf
		*/
		inline f32 cosf(f32 a_rad)
		{
			#if(BSYS_GEOMETRY_MATRIX_SINCOSFAST_ENABLE)
			return NMath::cos_f_fast(a_rad);
			#else
			return NMath::cosf(a_rad);
			#endif
		}
	}


}}
#pragma warning(pop)
#endif

