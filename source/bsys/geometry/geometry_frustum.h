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

		/** constructor
		*/
		inline Geometry_Frustum();

		/** destructor
		*/
		inline nonvirtual ~Geometry_Frustum();

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

