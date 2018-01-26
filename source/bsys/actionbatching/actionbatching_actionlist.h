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
#include "./actionbatching_actionitem_base.h"


/** NBsys::NActionBatching
*/
#if(BSYS_ACTIONBATCHING_ENABLE)
#pragma warning(push)
#pragma warning(disable:4820)
namespace NBsys{namespace NActionBatching
{
	/** ActionBatching_ActionList
	*/
	class ActionBatching_ActionList
	{
	private:

		/** index
		*/
		s32 index;

		/** endrequest
		*/
		bool endrequest;

	public:

		/** constructor
		*/
		ActionBatching_ActionList();

		/** destructor
		*/
		nonvirtual ~ActionBatching_ActionList();

	private:

		/** actionlist
		*/
		STLVector<sharedptr<ActionBatching_ActionItem_Base>>::Type actionlist;

	public:

		/** Add
		*/
		void Add(const sharedptr<ActionBatching_ActionItem_Base> a_actionitem);

		/** アクション開始。
		*/
		void Start();

		/** アクション中。	
		*/
		bool Do(f32 a_delta);

		/** GetCurrentIndex
		*/
		s32 GetCurrentIndex() const;

		/** 中断。
		*/
		void EndRequest();

	};


}}
#pragma warning(pop)
#endif

