#pragma once

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief OpenGL。
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
			/** 変数名。
			*/
			STLString name;

			/** shadervaluetype
			*/
			Opengl_ShaderValueType::Id shadervaluetype;

			/** 配列数。
			*/
			s32 countof;

			/** コンストラクタ。
			*/
			Uniform(const STLString& a_name,Opengl_ShaderValueType::Id a_shadervaluetype,s32 a_countof)
				:
				name(a_name),
				shadervaluetype(a_shadervaluetype),
				countof(a_countof)
			{
			}

			/** デストラクタ。
			*/
			nonvirtual ~Uniform()
			{
			}
		};

		/** Attribute
		*/
		struct Attribute
		{
			/** 変数名。
			*/
			STLString name;

			/** shadervaluetype
			*/
			Opengl_ShaderValueType::Id shadervaluetype;
			
			/** コンストラクタ。
			*/
			Attribute(const STLString& a_name,Opengl_ShaderValueType::Id a_shadervaluetype)
				:
				name(a_name),
				shadervaluetype(a_shadervaluetype)
			{
			}

			/** デストラクタ。
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

			/** コンストラクタ。
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

			/** デストラクタ。
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
		/** コンストラクタ。
		*/
		Opengl_ShaderInitializeList();

		/** デストラクタ。
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

