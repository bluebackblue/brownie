#pragma once

/**
* Copyright (c) 2017 blueback
* Released under the MIT License
* https://github.com/bluebackblue/brownie/blob/master/LICENSE
* http://bbbproject.sakura.ne.jp/wordpress/mitlicense
* @brief �o�[�e�b�N�X�B
*/


/** include
*/
#include "../types/types.h"


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
			/** �p�[�c���B
			*/
			STLString name;

			/** �o�[�e�b�N�X�I�t�Z�b�g�B
			*/
			s32 vertex_offset;

			/** �o�[�e�b�N�X���B
			*/
			s32 vertex_countof;
		};

		/** parts_list
		*/
		typename STLVector<sharedptr<Parts>>::Type parts_list;

		/** �o�[�e�b�N�X�B
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

		/** �V�K�p�[�c��ǉ��B
		*/
		void AddParts(const STLString& a_parts_name);

		/** �Ō�̃p�[�c�Ƀo�[�e�b�N�X��ǉ��B
		*/
		void AddVertex(const T& a_vertex);

	public:
		/** GetMaxParts
		*/
		s32 GetMaxParts();

		/** �o�[�e�b�N�X���B
		*/
		s32 GetVertexCountOf(s32 a_parts_index);

		/** �S�o�[�e�b�N�X���B
		*/
		s32 GetVertexAllCountOf();

		/** �o�[�e�b�N�X�I�t�Z�b�g�B
		*/
		s32 GetVertexOffset(s32 a_parts_index);

		/** GetVertexPointer�B
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


