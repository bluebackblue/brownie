#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief 経路探査。
*/


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./rootsearch_data.h"
#include "./rootsearch_node.h"
#include "./rootsearch_connect.h"
#include "./rootsearch_type.h"


/** NBsys::NRootSearch
*/
#if(BSYS_ROOTSEARCH_ENABLE)
namespace NBsys{namespace NRootSearch
{



	#if(0)

	/** RootSearch_Connect
	*/
	struct RootSearch_Connect
	{
		/** node_index
		*/
		s32 node_index;

		/** cost
		*/
		s32 cost;

		/** constructor
		*/
		RootSearch_Connect(s32 a_node_index,s32 a_cost)
			:
			node_index(a_node_index),
			cost(a_cost)
		{
		}

		/** destructor
		*/
		nonvirtual ~RootSearch_Connect()
		{
		}
	};
	
	/** RootSearch_Node
	*/
	struct RootSearch_Node
	{
		/** pos
		*/
		NGeometry::Geometry_Vector3 pos;

		/** connect_index_list
		*/
		STLVector<s32>::Type connect_index_list;

		/** constructor
		*/
		RootSearch_Node(const NGeometry::Geometry_Vector3& a_pos)
			:
			pos(a_pos),
			connect_index_list()
		{
		}

		/** destructor
		*/
		nonvirtual ~RootSearch_Node()
		{
		}
	};

	/** RootSearch_CalcTemp
	*/
	struct RootSearch_CalcTemp
	{
		s32 cost;
		s32 to_node_index;

		RootSearch_CalcTemp()
			:
			cost(-1),
			to_node_index(-1)
		{
		}
	};

	/** RootSearch
	*/
	struct RootSearch
	{
		/** node_pool
		*/
		STLVector<RootSearch_Connect>::Type connect_pool;

		/** node_pool
		*/
		STLVector<RootSearch_Node>::Type node_pool;

		/** constructor
		*/
		RootSearch();

		/** destructor
		*/
		nonvirtual ~RootSearch();

		/** クリア。
		*/
		void Clear();

		/** 接続。
		*/
		void Connect(s32 a_node_index_a,s32 a_node_index_b);

		/** ノード追加。
		*/
		s32 AddNode(const NGeometry::Geometry_Vector3& a_pos);

		/** ノードインデックス取得。
		*/
		s32 GetNodeIndexFromPos(const NGeometry::Geometry_Vector3& a_pos);

		/** 経路探査。
		*/
		NGeometry::Geometry_Vector3 SearchRoot(const NGeometry::Geometry_Vector3& a_start,const NGeometry::Geometry_Vector3& a_end);

	};

	#endif

}}
#endif

