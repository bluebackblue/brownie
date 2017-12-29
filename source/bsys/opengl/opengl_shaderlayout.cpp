

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief OpenGL。
*/


/** include
*/
#include <bsys_pch.h>


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** include
*/
#include "./opengl_shaderlayout.h"


/** warning

4710 : The given function was selected for inline expansion, but the compiler did not perform the inlining.

*/
#pragma warning(disable:4710)


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
		u32 ii_max = static_cast<u32>(this->list.size());
		for(u32 ii=0;ii<ii_max;ii++){
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
		return this->list[static_cast<std::size_t>(a_index)];
	}
}}
#endif

