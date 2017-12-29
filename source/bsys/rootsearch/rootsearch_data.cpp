

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief 経路探査。
*/


/** include
*/
#include <bsys_pch.h>


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** include
*/
#include "./rootsearch_data.h"


/** warning

4710 : The given function was selected for inline expansion, but the compiler did not perform the inlining.

*/
#pragma warning(disable:4710)


/** NBsys::NRootSearch
*/
#if(BSYS_ROOTSEARCH_ENABLE)
namespace NBsys{namespace NRootSearch
{
	/** constructor
	*/
	RootSearch_Data::RootSearch_Data()
		:
		node_pool(),
		connect_pool()
	{
	}

	/** destructor
	*/
	RootSearch_Data::~RootSearch_Data()
	{
	}

	/** コネクトチェック。
	*/
	bool RootSearch_Data::ConnectCheck(RootSearch_NodeIndex& a_nodeindex_from,RootSearch_NodeIndex& a_nodeindex_to,bool a_root)
	{
		STLVector<RootSearch_ConnectIndex>::Type& t_connectindex_list = this->node_pool[static_cast<u32>(a_nodeindex_from.GetValue())].ConnectIndexList(a_root);

		u32 ii_max = static_cast<u32>(t_connectindex_list.size());
		for(u32 ii=0;ii<ii_max;ii++){
			if(this->connect_pool[static_cast<u32>(t_connectindex_list[ii].GetValue())].GetNodeIndex() == a_nodeindex_to){
				return true;
			}
		}

		return false;
	}

	/** クリア。
	*/
	void RootSearch_Data::Clear()
	{
		this->node_pool.clear();
		this->connect_pool.clear();
	}

	/** ノード追加。
	*/
	RootSearch_NodeIndex RootSearch_Data::AddNode(const NGeometry::Geometry_Vector3& a_pos,f32 a_radius,bool a_root)
	{
		this->node_pool.push_back(RootSearch_Node(a_pos,a_radius,a_root));
		return RootSearch_NodeIndex(static_cast<s32>(this->node_pool.size() - 1));
	}

	/** コネクト。
	*/
	void RootSearch_Data::Connect(RootSearch_NodeIndex a_nodeindex_a,RootSearch_NodeIndex a_nodeindex_b,bool a_root,s32 a_cost)
	{
		RootSearch_Node& t_node_a = this->node_pool[static_cast<u32>(a_nodeindex_a.GetValue())];
		//RootSearch_Node& t_node_b = this->node_pool[static_cast<u32>(a_nodeindex_b.GetValue())];

		if(this->ConnectCheck(a_nodeindex_a,a_nodeindex_b,a_root) == false){
			this->connect_pool.push_back(RootSearch_Connect(a_nodeindex_b,a_cost));
			t_node_a.ConnectIndexList(a_root).push_back(RootSearch_ConnectIndex(static_cast<s32>(this->connect_pool.size())-1));
		}

		if(this->ConnectCheck(a_nodeindex_b,a_nodeindex_a,a_root) == false){
			this->connect_pool.push_back(RootSearch_Connect(a_nodeindex_a,a_cost));
			t_node_a.ConnectIndexList(a_root).push_back(RootSearch_ConnectIndex(static_cast<s32>(this->connect_pool.size())-1));
		}
	}

	/** 位置からノードインデックス取得。
	*/
	RootSearch_NodeIndex RootSearch_Data::GetNodeIndexFromPos(const NBsys::NGeometry::Geometry_Vector3& a_pos)
	{
		s32 t_index = -1;
		f32 t_min = -1;

		u32 ii_max = static_cast<u32>(this->node_pool.size());
		for(u32 ii=0;ii<ii_max;ii++){
			f32 t_square_length = (this->node_pool[ii].GetPos() - a_pos).SquareLength();
			if(t_index < 0 || t_index < t_min){
				t_index = static_cast<s32>(ii);
				t_min = t_square_length;
			}
		}

		return RootSearch_NodeIndex(t_index);
	}

	/** ノード取得。
	*/
	RootSearch_Node& RootSearch_Data::GetNode(RootSearch_NodeIndex a_nodeindex)
	{
		return this->node_pool[static_cast<std::size_t>(a_nodeindex.GetValue())];
	}

	/** ルートノードの計算。
	*/
	void RootSearch_Data::CalcRootNode()
	{
		STLVector<RootSearch_Node*>::Type t_root_node_list;

		u32 ii_max = static_cast<u32>(this->node_pool.size());
		for(u32 ii=0;ii<ii_max;ii++){
			if(this->node_pool[ii].IsRoot()){
				t_root_node_list.push_back(&this->node_pool[ii]);
			}
		}


	}

}}
#endif

