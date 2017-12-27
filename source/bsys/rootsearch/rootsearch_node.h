#pragma once

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief 経路探査。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** include
*/
#include "../geometry/geometry.h"


/** include
*/
#include "./rootsearch_type.h"
#include "./rootsearch_connect.h"


/** NBsys::NRootSearch
*/
#if(BSYS_ROOTSEARCH_ENABLE)
namespace NBsys{namespace NRootSearch
{
	/** ノード。
	*/
	class RootSearch_Node
	{
		/** 位置。
		*/
		NBsys::NGeometry::Geometry_Vector3 pos;

		/** 半径。
		*/
		f32 radius;

		/** ルート。
		*/
		bool root;

		/** コネクトインデックスリスト。
		*/
		STLVector<RootSearch_ConnectIndex>::Type connectindex_list;

		/** コネクトインデックスリスト。ルート。
		*/
		STLVector<RootSearch_ConnectIndex>::Type connectindex_root_list;

	public:
		/** constructor
		*/
		RootSearch_Node(const NBsys::NGeometry::Geometry_Vector3& a_pos,f32 a_radius,bool a_root);

		/** destructor
		*/
		nonvirtual ~RootSearch_Node();

	public:

		/** 位置。
		*/
		NBsys::NGeometry::Geometry_Vector3& GetPos();

		/** 半径。
		*/
		f32 GetRadius();

		/** ルートかどうか。
		*/
		bool IsRoot();

		/** コネクトリスト。
		*/
		STLVector<RootSearch_ConnectIndex>::Type& ConnectIndexList(bool a_root);


	};
}}
#endif

