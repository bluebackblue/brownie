#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
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
		STLVector< sharedptr< ActionBatching_ActionItem_Base > >::Type actionlist;

	public:

		/** Add
		*/
		void Add(const sharedptr< ActionBatching_ActionItem_Base >& a_actionitem);

		/** アクション開始。
		*/
		void Start();

		/** アクション中。	
		*/
		bool Do(f32 a_delta);

		/** GetCurrentIndex
		*/
		int GetCurrentIndex() const;

		/** 中断。
		*/
		void EndRequest();

	};

}}
#endif

