

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ジョイスティック。
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
#include "./joy.h"
#include "./joy_impl.h"


/** warning

4710 : この関数はインライン展開のために選択されましたが、コンパイラはインライン展開を実行しませんでした。

*/
#pragma warning(disable:4710)


/** NBsys::NHttp
*/
#if(BSYS_JOY_ENABLE)
namespace NBsys{namespace NJoy
{
	/** constructor
	*/
	Joy::Joy(s32 a_index)
	{
		this->impl.reset(new Joy_Impl(a_index));
	}


	/** destructor
	*/
	Joy::~Joy()
	{
	}


	/** 更新。
	*/
	void Joy::Update()
	{
		this->impl->Update();
	}


	/** 接続確認。
	*/
	bool Joy::IsConnected() const
	{
		return this->impl->IsConnected();
	}


	/** 上。
	*/
	bool Joy::Up() const
	{
		return this->impl->Up();
	}


	/** 下。
	*/
	bool Joy::Down() const
	{
		return this->impl->Down();
	}


	/** 左。
	*/
	bool Joy::Left() const
	{
		return this->impl->Left();
	}


	/** 右。
	*/
	bool Joy::Right() const
	{
		return this->impl->Right();
	}


}}
#endif

