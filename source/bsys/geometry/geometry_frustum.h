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


/** include
*/
#include "./geometry_identity.h"
#include "./geometry_vector.h"
#include "./geometry_matrix.h"
#include "./geometry_quaternion.h"
#include "./geometry_plane.h"


/** NBsys::NGeometry
*/
#if(BSYS_GEOMETRY_ENABLE)
namespace NBsys{namespace NGeometry
{

	/** Geometry_Frustum
	*/
	class Geometry_Frustum
	{
	public:

		/** コンストラクタ。
		*/
		inline Geometry_Frustum();

		/** デストラクタ。
		*/
		nonvirtual inline ~Geometry_Frustum();

	public:

		/** コンフィグ。
		*/
		struct Config
		{
			enum Id
			{
				PlaneMax = 6,
			};
		};

	private:

		/** projection
		*/
		Geometry_Matrix_44 projection;

		/** view 
		*/
		Geometry_Matrix_44 view;

		/** plane
		*/
		Geometry_Plane plane[Config::PlaneMax];

	public:

		/** SetProjection
		*/
		inline void SetProjection(const Geometry_Matrix_44& a_projection);

		/** SetView
		*/
		inline void SetView(const Geometry_Matrix_44& a_view);

		/** Calc
		*/
		inline void Calc();

		/** InFrustumCheck
		*/
		inline bool InFrustumCheck(Geometry_Vector3& a_position);
		
	};

}}
#endif

