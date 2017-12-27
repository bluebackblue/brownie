

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief アクションのバッチ処理。
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
#include "./actionbatching.h"


/** NBsys::NActionBatching
*/
#if(BSYS_ACTIONBATCHING_ENABLE)
namespace NBsys{namespace NActionBatching
{
	/** constructor
	*/
	ActionBatching::ActionBatching()
	{
	}


	/** destructor
	*/
	nonvirtual ActionBatching::~ActionBatching()
	{
	}


	/** Update
	*/
	void ActionBatching::Update(f32 a_delta)
	{
		STLList<sharedptr<ActionBatching_ActionList>>::iterator t_it = this->worklist.begin();
		while(t_it != this->worklist.end()){
			if((*t_it)->Do(a_delta) == true){

				//完了。
				t_it = this->worklist.erase(t_it);

			}else{
				++t_it;
			}
		}
	}


	/** StartBatching
	*/
	void ActionBatching::StartBatching(sharedptr<ActionBatching_ActionList>& a_actionlist)
	{
		//開始。
		a_actionlist->Start();

		this->worklist.push_back(a_actionlist);
	}


	/** IsBusy
	*/
	bool ActionBatching::IsBusy() const
	{
		if(this->worklist.size() > 0){
			return true;
		}

		return false;
	}


}}
#endif


