#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief FoveHMD�B
*/


/** include
*/
#include "../types/types.h"


/** include
*/
#include "../geometry/geometry.h"


/** NBsys::NFovehmd
*/
#if(BSYS_DIJKSTRA_ENABLE)
namespace NBsys{namespace NDijkstra
{
	/** Dijkstra_Connect
	*/
	struct Dijkstra_Connect
	{
		/** node_index
		*/
		s32 node_index;

		/** cost
		*/
		s32 cost;

		/** constructor
		*/
		Dijkstra_Connect(s32 a_node_index,s32 a_cost)
			:
			node_index(a_node_index),
			cost(a_cost)
		{
		}

		/** destructor
		*/
		nonvirtual ~Dijkstra_Connect()
		{
		}
	};
	
	/** Dijkstra_Node
	*/
	struct Dijkstra_Node
	{
		/** pos
		*/
		NGeometry::Geometry_Vector3 pos;

		/** connect_index_list
		*/
		STLVector< s32 >::Type connect_index_list;

		/** constructor
		*/
		Dijkstra_Node(const NGeometry::Geometry_Vector3& a_pos)
			:
			pos(a_pos),
			connect_index_list()
		{
		}

		/** destructor
		*/
		nonvirtual ~Dijkstra_Node()
		{
		}
	};

	/** Dijkstra_CalcTemp
	*/
	struct Dijkstra_CalcTemp
	{
		s32 cost;
		s32 to_node_index;

		Dijkstra_CalcTemp()
			:
			cost(-1),
			to_node_index(-1)
		{
		}
	};

	/** Dijkstra
	*/
	struct Dijkstra
	{
		/** node_pool
		*/
		STLVector< Dijkstra_Connect >::Type connect_pool;

		/** node_pool
		*/
		STLVector< Dijkstra_Node >::Type node_pool;

		/** constructor
		*/
		Dijkstra();

		/** destructor
		*/
		nonvirtual ~Dijkstra();

		/** �N���A�B
		*/
		void Clear();

		/** �ڑ��B
		*/
		void Connect(s32 a_node_index_a,s32 a_node_index_b);

		/** �m�[�h�ǉ��B
		*/
		s32 AddNode(const NGeometry::Geometry_Vector3& a_pos);

		/** �m�[�h�C���f�b�N�X�擾�B
		*/
		s32 GetNodeIndexFromPos(const NGeometry::Geometry_Vector3& a_pos);

		/** �o�H�T���B
		*/
		NGeometry::Geometry_Vector3 SearchRoot(const NGeometry::Geometry_Vector3& a_start,const NGeometry::Geometry_Vector3& a_end);

	};

}}
#endif

