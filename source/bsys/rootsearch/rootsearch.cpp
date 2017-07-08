

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
#include "./rootsearch.h"


/** NBsys::NRootSearch
*/
#if(BSYS_ROOTSEARCH_ENABLE)
namespace NBsys{namespace NRootSearch
{

	





	#if(0)

	/** constructor
	*/
	RootSearch::RootSearch()
	{
	}

	/** destructor
	*/
	nonvirtual RootSearch::~RootSearch()
	{
	}

	/** �N���A�B
	*/
	void RootSearch::Clear()
	{
		this->node_pool.clear();
		this->connect_pool.clear();
	}

	/** �ڑ��B
	*/
	void RootSearch::Connect(s32 a_node_index_a,s32 a_node_index_b)
	{
		RootSearch_Node& t_node_a = this->node_pool.at(a_node_index_a);
		RootSearch_Node& t_node_b = this->node_pool.at(a_node_index_b);

		s32 t_cost = static_cast<s32>((t_node_a.pos - t_node_b.pos).Length());

		this->connect_pool.push_back(RootSearch_Connect(a_node_index_b,t_cost));
		s32 t_connect_index_a = this->connect_pool.size() - 1;
		t_node_a.connect_index_list.push_back(t_connect_index_a);

		this->connect_pool.push_back(RootSearch_Connect(a_node_index_a,t_cost));
		s32 t_connect_index_b = this->connect_pool.size() - 1;
		t_node_b.connect_index_list.push_back(t_connect_index_b);
	}

	/** �m�[�h�ǉ��B
	*/
	s32 RootSearch::AddNode(const NGeometry::Geometry_Vector3& a_pos)
	{
		this->node_pool.push_back(RootSearch_Node(a_pos));

		return static_cast<s32>(this->node_pool.size() - 1);
	}

	/** �m�[�h�C���f�b�N�X�擾�B
	*/
	s32 RootSearch::GetNodeIndexFromPos(const NGeometry::Geometry_Vector3& a_pos)
	{
		s32 t_index = -1;
		f32 t_length_min = -1;

		s32 t_node_index = 0;
		STLVector< RootSearch_Node >::iterator t_it_end = this->node_pool.end();
		for(STLVector< RootSearch_Node >::iterator t_it = this->node_pool.begin();t_it != t_it_end;++t_it){
			f32 t_length = (t_it->pos - a_pos).Length();
			if(t_index < 0 || t_length < t_length_min){
				t_index = t_node_index;
				t_length_min = t_length;
			}

			t_node_index++;
		}

		return t_index;
	}

	/** �o�H�T���B
	*/
	NGeometry::Geometry_Vector3 RootSearch::SearchRoot(const NGeometry::Geometry_Vector3& a_start,const NGeometry::Geometry_Vector3& a_end)
	{
		//�v�Z���ʑ���B
		sharedptr< RootSearch_CalcTemp > t_calctemp_list_ptr(new RootSearch_CalcTemp[this->node_pool.size()],default_delete< RootSearch_CalcTemp[] >());
		RootSearch_CalcTemp* t_calctemp_list = t_calctemp_list_ptr.get();

		//�v�Z�����Ǘ��B
		STLVector< s32 >::Type t_list_temp_1;
		STLVector< s32 >::Type t_list_temp_2;

		STLVector< s32 >::Type* t_current_list = &t_list_temp_1;
		STLVector< s32 >::Type* t_next_list = &t_list_temp_2;

		//�I�[�B
		s32 t_node_index_end = this->GetNodeIndexFromPos(a_end);

		if(t_node_index_end >= 0){
			//�I�[����v�Z�B
			t_calctemp_list[t_node_index_end].cost = 0;
			t_calctemp_list[t_node_index_end].to_node_index = -1;
			t_current_list->push_back(t_node_index_end);
		}

		while(t_current_list->size()){
			STLVector< s32 >::iterator t_it_node_end = t_current_list->end();
			for(STLVector< s32 >::iterator t_it_node = t_current_list->begin();t_it_node != t_it_node_end;++t_it_node){

				RootSearch_Node& t_node = this->node_pool.at(*t_it_node);
				RootSearch_CalcTemp& t_calctemp = t_calctemp_list[*t_it_node];

				STLVector< s32 >::Type& t_connect_index_list = t_node.connect_index_list;
				STLVector< s32 >::iterator t_it_connect_end = t_connect_index_list.end();
				for(STLVector< s32 >::iterator t_it_connect = t_connect_index_list.begin();t_it_connect != t_it_connect_end;++t_it_connect){

					RootSearch_Connect& t_connect = this->connect_pool.at(*t_it_connect);
					
					s32 t_total_cost = t_connect.cost + t_calctemp.cost;

					RootSearch_CalcTemp& t_to_calctemp = t_calctemp_list[t_connect.node_index];

					if(t_to_calctemp.cost == -1 || t_total_cost < t_to_calctemp.cost){

						t_to_calctemp.cost = t_total_cost;
						t_to_calctemp.to_node_index = *t_it_node;

						//�\�񃊃X�g�ɒǉ��B
						t_next_list->push_back(t_connect.node_index);
					}
				}
			}

			//�\�񃊃X�g���J�����g�ɁB
			{
				STLVector< s32 >::Type* t_temp = t_current_list;
				t_current_list = t_next_list;
				t_next_list = t_temp;
			}

			//�\�񃊃X�g���N���A�B
			t_next_list->clear();
		}
		
		return a_end;
	}

	#endif
}}
#endif

