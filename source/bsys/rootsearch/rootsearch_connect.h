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


/**
*/
#include "./rootsearch_type.h"


/** NBsys::NRootSearch
*/
#if(BSYS_ROOTSEARCH_ENABLE)
namespace NBsys{namespace NRootSearch
{
	/** コネクト。
	*/
	class RootSearch_Connect
	{
		/** 接続先。
		*/
		NodeIndex nodeindex_to;

		/** コスト。
		*/
		s32 cost;

	public:
		/** constructor
		*/
		RootSearch_Connect(NodeIndex a_nodeindex_to,s32 a_cost);

		/** destructor
		*/
		~RootSearch_Connect();

	public:

		/** 接続先、ノードインデクス取得。
		*/
		NodeIndex GetNodeIndex();

		/** コスト。
		*/
		s32 GetCost();

	};
}}
#endif

