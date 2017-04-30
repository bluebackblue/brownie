#pragma once

/**
* Copyright (c) 2016 blueback
* @brief モデル。
* $Revision: 941 $
* $Author: bbbproject $
* $Date:: 2016-12-08 00:13:53 +0900#$
* $HeadURL: svn+ssh://bbbproject@bbbproject.sakura.ne.jp/home/bbbproject/svn-repos/www/artemis/asys/model/model_vertex.h $
* $Id: model_vertex.h 941 2016-12-07 15:13:53Z bbbproject $
*/


/** include
*/
#include "../types/types.h"


/** NBsys::NModel
*/
#if(BSYS_MODEL_ENABLE)
namespace NBsys{namespace NModel
{
	/** Model_Vertex
	*/
	template < typename T > class Model_Vertex
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
		typename STLVector< sharedptr< Parts > >::Type parts_list;

		/** バーテックス。
		*/
		typename STLVector< VertexType >::Type vertex_list;

	public:
		/** constructor
		*/
		Model_Vertex();

		/** constructor
		*/
		Model_Vertex(const sharedptr< JsonItem >& a_jsonitem);

		/** destructor
		*/
		nonvirtual ~Model_Vertex();

	public:

		/** 新規パーツを追加。
		*/
		void AddParts(const STLString& a_parts_name);

		/** 最後のパーツにバーテックスを追加。
		*/
		void AddVertex(const T& a_vertex);

	public:
		/** GetMaxParts
		*/
		s32 GetMaxParts();

		/** バーテックス数。
		*/
		s32 GetVertexCountOf(s32 a_parts_index);

		/** 全バーテックス数。
		*/
		s32 GetVertexAllCountOf();

		/** バーテックスオフセット。
		*/
		s32 GetVertexOffset(s32 a_parts_index);

		/** GetVertexPointer。
		*/
		const typename Model_Vertex< T >::VertexType* GetVertexPointer() const;

		/** GetVertexStrideByte
		*/
		s32 GetVertexStrideByte() const;
	};

}}
#endif
