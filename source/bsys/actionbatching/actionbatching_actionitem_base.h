﻿#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief アクションのバッチ処理。
*/


/** include
*/
#include "../types/types.h"


/** NBsys::NActionBatching
*/
#if(BSYS_ACTIONBATCHING_ENABLE)
namespace NBsys{namespace NActionBatching
{
	/** ActionBatching_ActionItem_Base
	*/
	class ActionBatching_ActionItem_Base
	{
	public:

		/** constructor
		*/
		ActionBatching_ActionItem_Base()
		{
		}

		/** destructor
		*/
		virtual ~ActionBatching_ActionItem_Base()
		{
		}

	public:

		/** アクション開始。
		*/
		virtual void Start() = 0;

		/** アクション中。

		return : 1 == 次のインデックス。0 == 継続。-1 == 戻る。
		a_delta : 0 < 処理時間残量。0 == 連続処理を一時中断。
		
		*/
		virtual s32 Do(f32& a_delta,bool a_endrequest) = 0;

	};


}}
#endif

