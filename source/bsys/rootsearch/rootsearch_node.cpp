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
#include <bsys_pch.h>


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./rootsearch_node.h"


/** NBsys::NRootSearch
*/
#if(BSYS_ROOTSEARCH_ENABLE)
namespace NBsys{namespace NRootSearch
{
	/** constructor
	*/
	RootSearch_Node::RootSearch_Node(const NGeometry::Geometry_Vector3& a_pos,f32 a_radius,bool a_root)
		:
		pos(a_pos),
		radius(a_radius),
		root(a_root),
		connectindex_list(),
		connectindex_root_list()
	{
	}

	/** destructor
	*/
	RootSearch_Node::~RootSearch_Node()
	{
	}

	/** �ʒu�B
	*/
	NBsys::NGeometry::Geometry_Vector3& RootSearch_Node::GetPos()
	{
		return this->pos;
	}

	/** ���a�B
	*/
	f32 RootSearch_Node::GetRadius()
	{
		return this->radius;
	}

	/** ���[�g���ǂ����B
	*/
	bool RootSearch_Node::IsRoot()
	{
		return this->root;
	}

	/** �R�l�N�g���X�g�B
	*/
	STLVector<RootSearch_ConnectIndex>::Type& RootSearch_Node::ConnectIndexList(bool a_root)
	{
		if(a_root){
			//���[�g�ǂ����̃R�l�N�g�B
			return this->connectindex_root_list;
		}

		return this->connectindex_list;
	}
}}
#endif

