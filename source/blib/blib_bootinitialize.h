#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief 初期化。
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
	/** 起動時初期化。
	*/
	void BootInitialize();

	/** 初期化済みかどうか。
	*/
	bool IsBootInitialize();

	/** グローバル固定長アロケータ。
	*/
	#if(BLIB_GLOBALFIXEDALLOCATOR_ENABLE)
	typedef FixedAllocator<BLIB_GLOBALFIXEDALLOCATOR_BLOCKSIZE,BLIB_GLOBALFIXEDALLOCATOR_SIZE> GlobalFixedAllocator_Type;
	GlobalFixedAllocator_Type& GlobalFixedAllocator_Get();
	#endif

	/** グローバル固定長アロケータ。ロックオブジェクト。
	*/
	#if(BLIB_GLOBALFIXEDALLOCATOR_ENABLE)
	LockObject& GlobalFixedAllocator_LockObject();
	#endif

	/** グローバル乱数。
	*/
	RandomTemplate<Random_LinearCongruentialGenerators>& GlobalRand_Get();

	/** グローバル乱数。ロックオブジェクト。
	*/
	LockObject& GlobalRand_LockObject();
}


