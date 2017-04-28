

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �A�N�V�����̃o�b�`�����B
*/


/** include
*/
#include <bsys_pch.h>


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./actionbatching.h"


/** NBsys::NActionBatching
*/
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
		STLList< sharedptr< ActionBatching_ActionList > >::iterator t_it = this->worklist.begin();
		while(t_it != this->worklist.end()){
			if((*t_it)->Do(a_delta) == true){

				//�����B
				t_it = this->worklist.erase(t_it);

			}else{
				++t_it;
			}
		}
	}

	/** StartBatching
	*/
	void ActionBatching::StartBatching(sharedptr< ActionBatching_ActionList >& a_actionlist)
	{
		//�J�n�B
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

