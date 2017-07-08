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
	/** �f�[�^�B
	*/
	class RootSearch_Data
	{
		/** node_pool
		*/
		STLVector< RootSearch_Node >::Type node_pool;

		/** connect_pool
		*/
		STLVector< RootSearch_Connect >::Type connect_pool;

	public:
		/** constructor
		*/
		RootSearch_Data();

		/** destructor
		*/
		~RootSearch_Data();

	private:
		/** �R�l�N�g�`�F�b�N�B
		*/
		bool ConnectCheck(NodeIndex& a_nodeindex_from,NodeIndex& a_nodeindex_to,bool a_root);

	public:

		/** �N���A�B
		*/
		void Clear();

		/** �m�[�h�A�ǉ��B
		*/
		NodeIndex AddNode(const NGeometry::Geometry_Vector3& a_pos,f32 a_radius,bool a_root);

		/** �R�l�N�g�B
		*/
		void Connect(NodeIndex a_nodeindex_a,NodeIndex a_nodeindex_b,bool a_root,s32 a_cost);

		/** �ʒu����m�[�h�C���f�b�N�X�擾�B
		*/
		NodeIndex GetNodeIndexFromPos(const NBsys::NGeometry::Geometry_Vector3& a_pos);

	};
}}
#endif

