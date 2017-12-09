

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief OpenGLÅB
*/


/** include
*/
#include <bsys_pch.h>


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./opengl_shaderlayout.h"


/** NBsys::NOpengl
*/
#if(BSYS_OPENGL_ENABLE)
namespace NBsys{namespace NOpengl
{
	/** constructor
	*/
	Opengl_ShaderLayout::Opengl_ShaderLayout()
	{
	}

	/** destructor
	*/
	Opengl_ShaderLayout::~Opengl_ShaderLayout()
	{
	}

	/** AddItem
	*/
	void Opengl_ShaderLayout::AddItem(Opengl_ShaderLayout::Item& a_item)
	{	
		this->list.push_back(a_item);
	}

	/** IsBusy
	*/
	bool Opengl_ShaderLayout::IsBusy() const
	{
		s32 ii_max = static_cast<s32>(this->list.size());
		for(s32 ii=0;ii<ii_max;ii++){
			if(this->list[ii].vertex_fileobject->IsBusy() == true){
				return true;
			}
			if(this->list[ii].fragment_fileobject->IsBusy() == true){
				return true;
			}
		}
		return false;
	}

	/** GetMax
	*/
	s32 Opengl_ShaderLayout::GetMax() const
	{
		return static_cast<s32>(this->list.size());
	}

	/** GetItem
	*/
	Opengl_ShaderLayout::Item& Opengl_ShaderLayout::GetItem(s32 a_index)
	{
		return this->list[a_index];
	}
}}
#endif

