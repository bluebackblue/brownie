

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
#include "./rootsearch_connect.h"


/** NBsys::NRootSearch
*/
#if(BSYS_ROOTSEARCH_ENABLE)
namespace NBsys{namespace NRootSearch
{
	/** constructor
	*/
	RootSearch_Connect::RootSearch_Connect(RootSearch_NodeIndex a_nodeindex_to,s32 a_cost)
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
	RootSearch_NodeIndex RootSearch_Connect::GetNodeIndex()
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

