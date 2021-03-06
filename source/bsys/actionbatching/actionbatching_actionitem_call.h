﻿#pragma once

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief アクションのバッチ処理。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** include
*/
#include "./actionbatching_actionitem_base.h"


/** NBsys::NActionBatching
*/
#if(BSYS_ACTIONBATCHING_ENABLE)
#pragma warning(push)
#pragma warning(disable:4514)
namespace NBsys{namespace NActionBatching
{
	/** ActionBatching_Action_Call
	*/
	class ActionBatching_Action_Call : public ActionBatching_ActionItem_Base
	{
	private:

		/** actionlist
		*/
		sharedptr<NBsys::NActionBatching::ActionBatching_ActionList> actionlist;

	public:

		/** constructor
		*/
		ActionBatching_Action_Call(sharedptr<NBsys::NActionBatching::ActionBatching_ActionList>& a_actionlist)
			:
			actionlist(a_actionlist)
		{
		}

		/** destructor
		*/
		virtual ~ActionBatching_Action_Call()
		{
		}

	public:

		/** アクション開始。
		*/
		virtual void Start()
		{
			this->actionlist->Start();
		}

		/** アクション中。
		*/
		virtual s32 Do(f32& a_delta,bool a_endrequest)
		{
			if(a_endrequest == true){
				this->actionlist->EndRequest();
			}

			bool t_ret = this->actionlist->Do(a_delta);
			a_delta = 0.0f;

			if(t_ret == true){
				return 1;
			}

			return 0;
		}

	};


}}
#pragma warning(pop)
#endif

