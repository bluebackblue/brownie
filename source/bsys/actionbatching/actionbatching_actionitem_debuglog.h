#pragma once

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


/** include
*/
#include "./actionbatching_actionitem_base.h"


/** NBsys::NActionBatching
*/
#if(BSYS_ACTIONBATCHING_ENABLE)
namespace NBsys{namespace NActionBatching
{
	/** ActionBatching_Action_DebugLog
	*/
	class ActionBatching_Action_DebugLog : public ActionBatching_ActionItem_Base
	{
	private:

		/** string
		*/
		STLString string;

	public:

		/** constructor
		*/
		ActionBatching_Action_DebugLog(const STLString& a_string)
			:
			string(a_string)
		{
		}

		/** destructor
		*/
		virtual ~ActionBatching_Action_DebugLog()
		{
		}

	public:

		/** アクション開始。
		*/
		virtual void Start()
		{
			DEBUGLOG(this->string.c_str());
		}

		/** アクション中。
		*/
		virtual s32 Do(f32& /*a_delta*/,bool /*a_endrequest*/)
		{
			return 1;
		}

	};


}}
#endif

