

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief アクションのバッチ処理。
*/


/** include
*/
#include <bsys_pch.h>

 
/** include
*/
#include "../types/types.h"


/** include
*/
#include "./actionbatching_actionlist.h"


/** NBsys::NActionBatching
*/
#if(BSYS_ACTIONBATCHING_ENABLE)
namespace NBsys{namespace NActionBatching
{
	/** constructor
	*/
	ActionBatching_ActionList::ActionBatching_ActionList()
		:
		index(-1),
		endrequest(false)
	{
	}


	/** destructor
	*/
	ActionBatching_ActionList::~ActionBatching_ActionList()
	{
	}


	/** Add
	*/
	void ActionBatching_ActionList::Add(const sharedptr<ActionBatching_ActionItem_Base> a_actionitem)
	{
		this->actionlist.push_back(a_actionitem);
	}


	/** アクション開始。
	*/
	void ActionBatching_ActionList::Start()
	{
		this->index = 0;
		this->endrequest = false;

		if(this->index < static_cast<s32>(this->actionlist.size())){
			this->actionlist[this->index]->Start();
		}else{
			//空。
			ASSERT(0);
		}
	}


	/** アクション中。
	*/
	bool ActionBatching_ActionList::Do(f32 a_delta)
	{
		ASSERT(this->index >= 0);

		f32 t_delta = a_delta;

		while(t_delta > 0.0f){
			s32 t_next = this->actionlist[this->index]->Do(t_delta,this->endrequest);
			if(t_next != 0){
				this->index += t_next;

				if(this->index < static_cast<s32>(this->actionlist.size())){
					if(this->endrequest == true){
						//中断。
						this->index = -1;
						return true;
					}else{
						//次。
						this->actionlist[this->index]->Start();
					}
				}else{
					//完了。
					this->index = -1;
					return true;
				}
			}
		}

		//継続。
		return false;
	}


	/** GetCurrentIndex
	*/
	s32 ActionBatching_ActionList::GetCurrentIndex() const
	{
		return this->index;
	}


	/** 中断。
	*/
	void ActionBatching_ActionList::EndRequest()
	{
		if(this->index >= 0){
			this->endrequest = true;
		}
	}


}}
#endif
