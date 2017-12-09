#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief 経路探査。
*/


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./rootsearch_node.h"
#include "./rootsearch_connect.h"
#include "./rootsearch_type.h"


/** NBsys::NRootSearch
*/
#if(BSYS_ROOTSEARCH_ENABLE)
namespace NBsys{namespace NRootSearch
{
	/** データ。
	*/
	class RootSearch_Data
	{
		/** node_pool
		*/
		STLVector<RootSearch_Node>::Type node_pool;

		/** connect_pool
		*/
		STLVector<RootSearch_Connect>::Type connect_pool;

	public:
		/** constructor
		*/
		RootSearch_Data();

		/** destructor
		*/
		~RootSearch_Data();

	private:
		/** コネクトチェック。
		*/
		bool ConnectCheck(RootSearch_NodeIndex& a_nodeindex_from,RootSearch_NodeIndex& a_nodeindex_to,bool a_root);

	public:

		/** クリア。
		*/
		void Clear();

		/** ノード追加。
		*/
		RootSearch_NodeIndex AddNode(const NGeometry::Geometry_Vector3& a_pos,f32 a_radius,bool a_root);

		/** コネクト。
		*/
		void Connect(RootSearch_NodeIndex a_nodeindex_a,RootSearch_NodeIndex a_nodeindex_b,bool a_root,s32 a_cost);

		/** 位置からノードインデックス取得。
		*/
		RootSearch_NodeIndex GetNodeIndexFromPos(const NBsys::NGeometry::Geometry_Vector3& a_pos);

		/** ノード取得。
		*/
		RootSearch_Node& GetNode(RootSearch_NodeIndex a_nodeindex);

		/** ルートノードの計算。
		*/
		void CalcRootNode();

	};
}}
#endif

