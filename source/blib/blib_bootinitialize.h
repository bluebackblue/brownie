﻿#pragma once

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
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
#include "./stlvector.h"
#include "./sharedptr.h"


/** include
*/
#pragma warning(push)
#pragma warning(disable:4710 4711 4548 4987 4820 4514 4365 4623 5027 4626 4625)
#include <functional>
#pragma warning(pop)


/** NBlib
*/
namespace NBlib
{
	/** Blib
	*/
	class Blib
	{
	public:

		/** call_list
		*/
		STLVector<std::function<void(void)>>::Type call_list;

	public:

		/** constructor
		*/
		Blib();

		/** destructor
		*/
		nonvirtual ~Blib();

	};


	/** 起動時初期化。
	*/
	sharedptr<Blib> BootInitialize();


	/** 初期化済みかどうか。
	*/
	bool IsBootInitialize();


	/** 終了時に呼び出す関数の登録。
	*/
	void CallOnExit(const std::function<void(void)>& a_function);


	/** グローバル固定長アロケータ。
	*/
	#if(BLIB_GLOBALFIXEDALLOCATOR_ENABLE)
	typedef FixedAllocator<BLIB_GLOBALFIXEDALLOCATOR_BLOCKSIZE,BLIB_GLOBALFIXEDALLOCATOR_BLOCKMAX> GlobalFixedAllocator_Type;
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

