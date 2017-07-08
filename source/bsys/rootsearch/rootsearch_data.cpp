

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
#include "./rootsearch_data.h"


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
		STLVector< RootSearch_ConnectIndex >::Type& t_connectindex_list = this->node_pool[a_nodeindex_from.GetValue()].ConnectIndexList(a_root);

		s32 ii_max = t_connectindex_list.size();
		for(s32 ii=0;ii<ii_max;ii++){
			if(this->connect_pool[t_connectindex_list[ii].GetValue()].GetNodeIndex() == a_nodeindex_to){
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

	/** ノード、追加。
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
		RootSearch_Node& t_node_a = this->node_pool[a_nodeindex_a.GetValue()];
		RootSearch_Node& t_node_b = this->node_pool[a_nodeindex_b.GetValue()];

		if(this->ConnectCheck(a_nodeindex_a,a_nodeindex_b,a_root) == false){
			this->connect_pool.push_back(RootSearch_Connect(a_nodeindex_b,a_cost));
			t_node_a.ConnectIndexList(a_root).push_back(RootSearch_ConnectIndex(this->connect_pool.size()-1));
		}

		if(this->ConnectCheck(a_nodeindex_b,a_nodeindex_a,a_root) == false){
			this->connect_pool.push_back(RootSearch_Connect(a_nodeindex_a,a_cost));
			t_node_a.ConnectIndexList(a_root).push_back(RootSearch_ConnectIndex(this->connect_pool.size()-1));
		}
	}

	/** 位置からノードインデックス取得。
	*/
	RootSearch_NodeIndex RootSearch_Data::GetNodeIndexFromPos(const NBsys::NGeometry::Geometry_Vector3& a_pos)
	{
		s32 t_index = -1;
		f32 t_min = -1;

		s32 ii_max = this->node_pool.size();
		for(s32 ii=0;ii<ii_max;ii++){
			f32 t_square_length = (this->node_pool[ii].GetPos() - a_pos).SquareLength();
			if(t_index < 0 || t_index < t_min){
				t_index = ii;
				t_min = t_square_length;
			}
		}

		return RootSearch_NodeIndex(t_index);
	}


}}
#endif

