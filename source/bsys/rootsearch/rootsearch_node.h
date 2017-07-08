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
#include "../geometry/geometry.h"


/** include
*/
#include "./rootsearch_type.h"
#include "./rootsearch_connect.h"


/** NBsys::NRootSearch
*/
#if(BSYS_ROOTSEARCH_ENABLE)
namespace NBsys{namespace NRootSearch
{
	/** �m�[�h�B
	*/
	class RootSearch_Node
	{
		/** �ʒu�B
		*/
		NBsys::NGeometry::Geometry_Vector3 pos;

		/** ���a�B
		*/
		f32 radius;

		/** ���[�g�B
		*/
		bool root;

		/** �R�l�N�g�C���f�b�N�X���X�g�B
		*/
		STLVector< ConnectIndex >::Type connectindex_list;

		/** �R�l�N�g�C���f�b�N�X���X�g�B���[�g�B
		*/
		STLVector< ConnectIndex >::Type connectindex_root_list;

	public:
		/** constructor
		*/
		RootSearch_Node(const NBsys::NGeometry::Geometry_Vector3& a_pos,f32 a_radius,bool a_root);

		/** destructor
		*/
		nonvirtual ~RootSearch_Node();

	public:

		/** �ʒu�B
		*/
		NBsys::NGeometry::Geometry_Vector3& GetPos();

		/** ���a�B
		*/
		f32 GetRadius();

		/** ���[�g���ǂ����B
		*/
		bool IsRoot();

		/** �R�l�N�g���X�g�B
		*/
		STLVector< ConnectIndex >::Type& ConnectIndexList(bool a_root);


	};
}}
#endif

