#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �o�H�T���B
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
	/** �R�l�N�g�B
	*/
	class RootSearch_Connect
	{
		/** �ڑ���B
		*/
		NodeIndex nodeindex_to;

		/** �R�X�g�B
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

		/** �ڑ���A�m�[�h�C���f�N�X�擾�B
		*/
		NodeIndex GetNodeIndex();

		/** �R�X�g�B
		*/
		s32 GetCost();

	};
}}
#endif

