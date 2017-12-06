

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �o�H�T���B
*/


/** include
*/
#include <bsys_pch.h>


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

	/** �ڑ���A�m�[�h�C���f�N�X�擾�B
	*/
	RootSearch_NodeIndex RootSearch_Connect::GetNodeIndex()
	{
		return this->nodeindex_to;
	}

	/** �R�X�g�B
	*/
	s32 RootSearch_Connect::GetCost()
	{
		return this->cost;
	}
}}
#endif

