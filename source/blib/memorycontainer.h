#pragma once

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief メモリーコンテナー。
*/


/** include
*/
#include "./types.h"
#include "./platform.h"


/** NBlib
*/
namespace NBlib
{
	/** MemoryContainer
	*/
	class MemoryContainer
	{
	public:

		/** constructor
		*/
		MemoryContainer(s32 a_containerindex);

		/** destructor
		*/
		nonvirtual ~MemoryContainer();

	public:

		/** GetContainerIndex
		*/
		static s32 GetContainerIndex();

	};


}

