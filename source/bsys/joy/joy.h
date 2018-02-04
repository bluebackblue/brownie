#pragma once

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ジョイスティック。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** include
*/
#include "./joy_impl_decl.h"


/** NBsys::NJoy
*/
#if(BSYS_JOY_ENABLE)
#pragma warning(push)
#pragma warning(disable:4710 4820)
namespace NBsys{namespace NJoy
{
	/** Joy
	*/
	class Joy
	{
	private:

		/** impl
		*/
		sharedptr<Joy_Impl> impl;

	public:

		/** constructor
		*/
		Joy(s32 a_index);

		/** destructor
		*/
		nonvirtual ~Joy();

	public:

		/** 更新。
		*/
		void Update();

		/** 接続確認。
		*/
		bool IsConnected() const;

		/** 上。
		*/
		bool Up() const;

		/** 下。
		*/
		bool Down() const;

		/** 左。
		*/
		bool Left() const;

		/** 右。
		*/
		bool Right() const;

	};


}}
#pragma warning(pop)
#endif

