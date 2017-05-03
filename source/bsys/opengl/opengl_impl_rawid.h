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

		/** �����`�F�b�N�B
		*/
		bool IsInvalid() const
		{
			if(this->rawid == 0){
				//�����B
				return true;
			}

			//�L���B
			return false;
		}

		/** �����B
		*/
		void SetInvalid()
		{
			this->rawid = 0;
		}
	};

}}
#endif

