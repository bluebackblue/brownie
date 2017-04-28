#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �t�@�C���B
*/


/** include
*/
#include "../types/types.h"


/** NBsys::NFile
*/
#if(BSYS_FILE_ENABLE)
namespace NBsys{namespace NFile
{
	/** File_Allocator
	*/
	class File_Allocator
	{
	public:
		/** constructor
		*/
		explicit File_Allocator(){}

		/** destructor
		*/
		virtual ~File_Allocator(){}

	public:
		/** �p����Ń��[�h���̊m�ۏ������L�q����B
		*/
		virtual void* Alloc(u32 a_size) = 0;

		/** �p����ŉ���������L�q����B
		*/
		virtual void Free(void* a_pointer) = 0;
	};

	/** �폜�q�B
	*/
	struct File_Alloc_Deleter
	{
		/** �폜�Ɏg�p����A���P�[�^�B
		*/
		sharedptr< File_Allocator > allocator;

		/** constructor
		*/
		explicit File_Alloc_Deleter(sharedptr< File_Allocator >& a_allocator) throw()
			:
			allocator(a_allocator)
		{
		}

		/** ��������B
		*/
		void operator ()(void* a_pointer) throw()
		{
			if(this->allocator){
				this->allocator->Free(a_pointer);
			}else{
				ASSERT(0);
			}
		}
	};

}}
#endif
