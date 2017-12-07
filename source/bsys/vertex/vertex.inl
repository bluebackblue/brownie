#pragma once

/**
* Copyright (c) 2017 blueback
* Released under the MIT License
* https://github.com/bluebackblue/brownie/blob/master/LICENSE
* http://bbbproject.sakura.ne.jp/wordpress/mitlicense
* @brief バーテックス。
*/


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./vertex.h"


/** NBsys::NVertex
*/
#if(BSYS_VERTEX_ENABLE)
namespace NBsys{namespace NVertex
{
	/** constructor
	*/
	template <typename T> Vertex<T>::Vertex()
	{
	}

	/** constructor
	*/
	template <typename T> Vertex<T>::Vertex(const sharedptr<JsonItem>& a_jsonitem)
		:
		parts_list()
	{
		s32 t_parts_list_max = a_jsonitem->GetListMax();

		for(s32 ii=0;ii<t_parts_list_max;ii++){
			sharedptr<Vertex<T>::Parts> t_parts(new Vertex<T>::Parts());
			this->parts_list.push_back(t_parts);
		}

		for(s32 ii=0;ii<t_parts_list_max;ii++){
			const sharedptr<JsonItem>& t_parts_json = a_jsonitem->GetItem(ii);

			{
				//パーツインデックス。
				s32 t_parts_index = t_parts_json->GetItem("parts_index")->GetInteger();

				//オフセット。
				this->parts_list[t_parts_index]->vertex_offset = static_cast<s32>(this->vertex_list.size());

				//バーテックスリスト。
				const sharedptr<JsonItem>& t_vertexlist_json = t_parts_json->GetItem("vertex_list");
				s32 jj_max = t_vertexlist_json->GetListMax();
				for(s32 jj=0;jj<jj_max;jj++){
					const sharedptr<JsonItem>& t_vertex_json = t_vertexlist_json->GetItem(jj);

					T t_vertex;

					{
						f32 t_pos_x = t_vertex_json->GetItem("pos")->GetItem(0)->GetFloat();
						f32 t_pos_y = t_vertex_json->GetItem("pos")->GetItem(1)->GetFloat();
						f32 t_pos_z = t_vertex_json->GetItem("pos")->GetItem(2)->GetFloat();

						SetPos<T>(t_vertex,t_pos_x,t_pos_y,t_pos_z);
					}

					{
						f32 t_uv_x = t_vertex_json->GetItem("uv")->GetItem(0)->GetFloat();
						f32 t_uv_y = t_vertex_json->GetItem("uv")->GetItem(1)->GetFloat();

						SetUv<T>(t_vertex,t_uv_x,t_uv_y);
					}

					{
						s32 t_matrix_index_0 = t_vertex_json->GetItem("matrix_index")->GetItem(0)->GetInteger();
						s32 t_matrix_index_1 = t_vertex_json->GetItem("matrix_index")->GetItem(1)->GetInteger();
						s32 t_matrix_index_2 = t_vertex_json->GetItem("matrix_index")->GetItem(2)->GetInteger();
						s32 t_matrix_index_3 = t_vertex_json->GetItem("matrix_index")->GetItem(3)->GetInteger();

						SetMatrixIndex<T>(t_vertex,t_matrix_index_0,t_matrix_index_1,t_matrix_index_2,t_matrix_index_3);
					}

					{
						f32 t_matrix_weight_0 = t_vertex_json->GetItem("matrix_weight")->GetItem(0)->GetFloat();
						f32 t_matrix_weight_1 = t_vertex_json->GetItem("matrix_weight")->GetItem(1)->GetFloat();
						f32 t_matrix_weight_2 = t_vertex_json->GetItem("matrix_weight")->GetItem(2)->GetFloat();
						f32 t_matrix_weight_3 = t_vertex_json->GetItem("matrix_weight")->GetItem(3)->GetFloat();

						SetMatrixWeight<T>(t_vertex,t_matrix_weight_0,t_matrix_weight_1,t_matrix_weight_2,t_matrix_weight_3);
					}

					{
						SetDummy<T>(t_vertex,0.0f);
					}

					this->vertex_list.push_back(t_vertex);
				}

				//カウントオブ。
				this->parts_list[t_parts_index]->vertex_countof = jj_max;
			}
		}
	}

	/** destructor
	*/
	template <typename T> Vertex<T>::~Vertex()
	{
	}

	/** 新規パーツを追加。
	*/
	template <typename T> void Vertex<T>::AddParts(const STLString& a_parts_name)
	{
		this->parts_list.push_back(new Vertex<T>::Parts());

		this->parts_list[this->parts_list.size() - 1]->name = a_parts_name;
		this->parts_list[this->parts_list.size() - 1]->vertex_offset = static_cast<s32>(this->vertex_list.size());
		this->parts_list[this->parts_list.size() - 1]->vertex_countof = 0;
	}

	/** 最後のパーツにバーテックスを追加。
	*/
	template <typename T> void Vertex<T>::AddVertex(const T& a_vertex)
	{
		ASSERT(this->vertex_list.capacity() > this->vertex_list.size());

		this->vertex_list.push_back(a_vertex);
		this->parts_list[this->parts_list.size() - 1]->vertex_countof++;
	}

	/** バーテックスの容量確保。
	*/
	template <typename T> void Vertex<T>::ReserveVertex(s32 a_count_of)
	{
		this->vertex_list.reserve(a_count_of);
	}

	/** バーテクスのクリア。
	*/
	template <typename T> void Vertex<T>::ClearVertex()
	{
		this->vertex_list.clear();
		this->parts_list[0]->vertex_countof = 0;
	}

	/** GetMaxParts
	*/
	template <typename T> s32 Vertex<T>::GetMaxParts()
	{
		return static_cast<s32>(this->parts_list.size());
	}

	/** GetVertexCountOf
	*/
	template <typename T> s32 Vertex<T>::GetVertexCountOf(s32 a_parts_index)
	{
		return this->parts_list[a_parts_index]->vertex_countof;
	}

	/** 全バーテックス数。
	*/
	template <typename T> s32 Vertex<T>::GetVertexAllCountOf()
	{
		return static_cast<s32>(this->vertex_list.size());
	}

	/** GetVertexOffset
	*/
	template <typename T> s32 Vertex<T>::GetVertexOffset(s32 a_parts_index)
	{
		return this->parts_list[a_parts_index]->vertex_offset;
	}

	/** GetVertexPointer
	*/
	template <typename T> const typename Vertex<T>::VertexType* Vertex<T>::GetVertexPointer() const
	{
		return &this->vertex_list[0];
	}

	/** GetVertexStrideByte
	*/
	template <typename T> s32 Vertex<T>::GetVertexStrideByte() const
	{
		return sizeof(VertexType);
	}

}}
#endif

