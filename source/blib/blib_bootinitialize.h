#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �������B
*/


/** include
*/
#include "./types.h"
#include "./platform.h"


/** include
*/
#include "./fixedallocator.h"
#include "./lockobject.h"
#include "./random.h"


/** NBlib
*/
namespace NBlib
{
	/** �N�����������B
	*/
	void BootInitialize();

	/** �������ς݂��ǂ����B
	*/
	bool IsBootInitialize();

	/** �O���[�o���Œ蒷�A���P�[�^�B
	*/
	#if(BLIB_GLOBALFIXEDALLOCATOR_ENABLE)
	typedef FixedAllocator<BLIB_GLOBALFIXEDALLOCATOR_BLOCKSIZE,BLIB_GLOBALFIXEDALLOCATOR_SIZE> GlobalFixedAllocator_Type;
	GlobalFixedAllocator_Type& GlobalFixedAllocator_Get();
	#endif

	/** �O���[�o���Œ蒷�A���P�[�^�B���b�N�I�u�W�F�N�g�B
	*/
	#if(BLIB_GLOBALFIXEDALLOCATOR_ENABLE)
	LockObject& GlobalFixedAllocator_LockObject();
	#endif

	/** �O���[�o�������B
	*/
	RandomTemplate<Random_LinearCongruentialGenerators>& GlobalRand_Get();

	/** �O���[�o�������B���b�N�I�u�W�F�N�g�B
	*/
	LockObject& GlobalRand_LockObject();
}


