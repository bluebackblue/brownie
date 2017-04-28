#pragma once

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief OpenGL�B
*/


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./opengl_type.h"


/** include
*/
#include "../file/file.h"


/** NBsys::NOpengl
*/
#if(BSYS_OPENGL_ENABLE)
namespace NBsys{namespace NOpengl
{
	#if(0)
	/** Opengl_ShaderInitializeList
	*/
	class Opengl_ShaderInitializeList
	{
	public:

		/** Uniform
		*/
		struct Uniform
		{
			/** �ϐ����B
			*/
			STLString name;

			/** shadervaluetype
			*/
			Opengl_ShaderValueType::Id shadervaluetype;

			/** �z�񐔁B
			*/
			s32 countof;

			/** �R���X�g���N�^�B
			*/
			Uniform(const STLString& a_name,Opengl_ShaderValueType::Id a_shadervaluetype,s32 a_countof)
				:
				name(a_name),
				shadervaluetype(a_shadervaluetype),
				countof(a_countof)
			{
			}

			/** �f�X�g���N�^�B
			*/
			nonvirtual ~Uniform()
			{
			}
		};

		/** Attribute
		*/
		struct Attribute
		{
			/** �ϐ����B
			*/
			STLString name;

			/** shadervaluetype
			*/
			Opengl_ShaderValueType::Id shadervaluetype;
			
			/** �R���X�g���N�^�B
			*/
			Attribute(const STLString& a_name,Opengl_ShaderValueType::Id a_shadervaluetype)
				:
				name(a_name),
				shadervaluetype(a_shadervaluetype)
			{
			}

			/** �f�X�g���N�^�B
			*/
			nonvirtual ~Attribute()
			{
			}
		};

		/** InitializeItem
		*/
		struct InitializeItem
		{
			/** shaderid
			*/
			s32 shaderid;

			/** vertex_fileobject
			*/
			//sharedptr< NBsys::NFile::File_Object > vertex_fileobject;

			/** fragment_fileobject
			*/
			//sharedptr< NBsys::NFile::File_Object > fragment_fileobject;

			/** uniform_list
			*/
			sharedptr< STLVector< Opengl_ShaderInitializeList::Uniform >::Type > uniform_list;

			/** vertex_attribute_list
			*/
			sharedptr< STLVector< Opengl_ShaderInitializeList::Attribute >::Type > attribute_list;

			/** �R���X�g���N�^�B
			*/
			#if(0)
			InitializeItem::InitializeItem(s32 a_shaderid,const sharedptr< NBsys::NFile::File_Object >& a_vertex_fileobject,const sharedptr< NBsys::NFile::File_Object >& a_fragment_fileobject,const sharedptr< STLVector< Opengl_ShaderInitializeList::Uniform >::Type >& a_uniform_list,const sharedptr< STLVector< Opengl_ShaderInitializeList::Attribute >::Type >& a_attribute_list)
				:
				shaderid(a_shaderid),
				vertex_fileobject(a_vertex_fileobject),
				fragment_fileobject(a_fragment_fileobject),
				uniform_list(a_uniform_list),
				attribute_list(a_attribute_list)
			{
			}
			#else
			InitializeItem::InitializeItem()
			{
			}
			#endif

			/** �f�X�g���N�^�B
			*/
			InitializeItem::~InitializeItem()
			{
			}
		};

	private:
		/** list
		*/
		STLVector< InitializeItem >::Type list;

	public:
		/** �R���X�g���N�^�B
		*/
		Opengl_ShaderInitializeList();

		/** �f�X�g���N�^�B
		*/
		nonvirtual ~Opengl_ShaderInitializeList();

	public:

		/** AddInitializeItem
		*/
		void AddInitializeItem(Opengl_ShaderInitializeList::InitializeItem& a_item);

		/** IsBusy
		*/
		bool IsBusy() const;

		/** GetMax
		*/
		s32 GetMax() const;

		/** GetInitializeItem
		*/
		InitializeItem& GetInitializeItem(s32 a_index);

	};
	#endif
}}
#endif

