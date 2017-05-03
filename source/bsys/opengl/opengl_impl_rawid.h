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
#include "./opengl_impl_include.h"


/** NBsys::NOpengl
*/
#if(BSYS_OPENGL_ENABLE)
namespace NBsys{namespace NOpengl
{
	/** RawID
	*/
	struct RawID
	{
		/** rawid
		*/
		GLuint rawid;

		/** constructor
		*/
		RawID()
			:
			rawid(0)
		{
		}

		/** destructor
		*/
		nonvirtual ~RawID()
		{
		}

		/** 無効チェック。
		*/
		bool IsInvalid() const
		{
			if(this->rawid == 0){
				//無効。
				return true;
			}

			//有効。
			return false;
		}

		/** 無効。
		*/
		void SetInvalid()
		{
			this->rawid = 0;
		}
	};

}}
#endif

