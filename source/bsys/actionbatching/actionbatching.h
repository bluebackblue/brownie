#pragma once

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
#include "./actionbatching_actionlist.h"
#include "./actionbatching_actionitem_delay.h"
#include "./actionbatching_actionitem_debuglog.h"
#include "./actionbatching_actionitem_call.h"


/** NBsys::NActionBatching
*/
#if(BSYS_ACTIONBATCHING_ENABLE)
namespace NBsys{namespace NActionBatching
{
	/** ActionBatching
	*/
	class ActionBatching
	{
	private:

		/** worklist
		*/
		STLList<sharedptr<ActionBatching_ActionList>>::Type worklist;

	public:

		/** constructor
		*/
		ActionBatching();

		/** destructor
		*/
		nonvirtual ~ActionBatching();

	public:

		/** Update
		*/
		void Update(f32 a_delta);

		/** StartBatching
		*/
		void StartBatching(sharedptr<ActionBatching_ActionList>& a_actionlist);

		/** IsBusy
		*/
		bool IsBusy() const;

	};


}}
#endif

