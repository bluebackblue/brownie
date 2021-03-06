﻿#pragma once

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief バーテックス。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** include
*/
#include "./vertex_type.h"


/** NBsys::NVertex
*/
#if(BSYS_VERTEX_ENABLE)
namespace NBsys{namespace NVertex
{
	/** Vertex
	*/
	template <typename T> class Vertex
	{
	private:

		/** VertexType
		*/
		typedef T VertexType;

		/** Parts
		*/
		struct Parts
		{
			/** パーツ名。
			*/
			STLString name;

			/** バーテックスオフセット。
			*/
			s32 vertex_offset;

			/** バーテックス数。
			*/
			s32 vertex_countof;
		};

		/** parts_list
		*/
		typename STLVector<sharedptr<Parts>>::Type parts_list;

		/** バーテックス。
		*/
		typename STLVector<VertexType>::Type vertex_list;

	public:

		/** constructor
		*/
		Vertex();

		/** constructor
		*/
		Vertex(const sharedptr<JsonItem>& a_jsonitem);

		/** destructor
		*/
		nonvirtual ~Vertex();

	public:

		/** 新規パーツを追加。
		*/
		void AddParts(const STLString& a_parts_name);

		/** 最後のパーツにバーテックスを追加。
		*/
		void AddVertex(const T& a_vertex);

		/** バーテックスの容量確保。
		*/
		void ReserveVertex(s32 a_count_of);

		/** バーテクスのクリア。
		*/
		void ClearVertex();

	public:

		/** GetMaxParts
		*/
		s32 GetMaxParts();

		/** バーテックス数。
		*/
		template <typename T2> s32 GetVertexCountOf(T2 a_parts_index);

		/** 全バーテックス数。
		*/
		s32 GetVertexAllCountOf();

		/** バーテックスオフセット。
		*/
		template <typename T2> s32 GetVertexOffset(T2 a_parts_index);

		/** GetVertexPointer。
		*/
		const typename Vertex<T>::VertexType* GetVertexPointer() const;

		/** GetVertexStrideByte
		*/
		s32 GetVertexStrideByte() const;

	};


}}
#endif


/** include
*/
#include "./vertex.inl"

