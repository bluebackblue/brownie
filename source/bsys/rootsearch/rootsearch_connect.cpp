

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
#include "./rootsearch_connect.h"


/** NBsys::NRootSearch
*/
#if(BSYS_ROOTSEARCH_ENABLE)
namespace NBsys{namespace NRootSearch
{
	/** constructor
	*/
	RootSearch_Connect::RootSearch_Connect(NodeIndex a_nodeindex_to,s32 a_cost)
		:
		nodeindex_to(a_nodeindex_to),
		cost(a_cost)
	{
	}

	/** destructor
	*/
	RootSearch_Connect::~RootSearch_Connect()
	{
	}

	/** 接続先、ノードインデクス取得。
	*/
	NodeIndex RootSearch_Connect::GetNodeIndex()
	{
		return this->nodeindex_to;
	}

	/** コスト。
	*/
	s32 RootSearch_Connect::GetCost()
	{
		return this->cost;
	}
}}
#endif

