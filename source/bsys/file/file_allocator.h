#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ファイル。
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

		/** 継承先でロード時の確保処理を記述する。
		*/
		virtual void* Alloc(u32 a_size) = 0;

		/** 継承先で解放処理を記述する。
		*/
		virtual void Free(void* a_pointer) = 0;

	};


	/** 削除子。
	*/
	struct File_Alloc_Deleter
	{

		/** 削除に使用するアロケータ。
		*/
		sharedptr<File_Allocator> allocator;

		/** constructor
		*/
		explicit File_Alloc_Deleter(sharedptr<File_Allocator>& a_allocator) noexcept
			:
			allocator(a_allocator)
		{
		}

		/** 解放処理。
		*/
		void operator ()(void* a_pointer) noexcept
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
