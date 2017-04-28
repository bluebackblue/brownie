

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief OpenGL。
*/


/** include
*/
#include <bsys_pch.h>


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./opengl_shaderinitializelist.h"


/** NBsys::NOpengl
*/
#if(BSYS_OPENGL_ENABLE)
namespace NBsys{namespace NOpengl
{
	#if(0)

	/** constructor
	*/
	Opengl_ShaderInitializeList::Opengl_ShaderInitializeList()
	{
	}

	/** デストラクタ。
	*/
	Opengl_ShaderInitializeList::~Opengl_ShaderInitializeList()
	{
	}

	/** AddInitializeItem
	*/
	void Opengl_ShaderInitializeList::AddInitializeItem(Opengl_ShaderInitializeList::InitializeItem& a_initialize_item)
	{	
		this->list.push_back(a_initialize_item);
	}

	/** IsBusy
	*/
	bool Opengl_ShaderInitializeList::IsBusy() const
	{
		#if(0)
		s32 ii_max = static_cast<s32>(this->list.size());
		for(s32 ii=0;ii<ii_max;ii++){
			if(this->list[ii].vertex_fileobject->IsBusy() == true){
				return true;
			}
			if(this->list[ii].fragment_fileobject->IsBusy() == true){
				return true;
			}
		}
		#endif

		return false;
	}

	/** GetMax
	*/
	s32 Opengl_ShaderInitializeList::GetMax() const
	{
		return static_cast<s32>(this->list.size());
	}

	/** GetItem
	*/
	Opengl_ShaderInitializeList::InitializeItem& Opengl_ShaderInitializeList::GetInitializeItem(s32 a_index)
	{
		return this->list[a_index];
	}

	#endif
}}
#endif

