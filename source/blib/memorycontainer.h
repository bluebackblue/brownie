#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �������[�R���e�i�[�B
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
		static s32 GetContainerIndex();

	};
}

