#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �A�N�V�����̃o�b�`�����B
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
	/** ActionBatching_Action_Delay
	*/
	class ActionBatching_Action_Delay : public ActionBatching_ActionItem_Base
	{
	private:

		/** param_delay
		*/
		f32 param_delay;

		/** time
		*/
		f32 time;

	public:

		/** constructor
		*/
		ActionBatching_Action_Delay(f32 a_delay)
			:
			param_delay(a_delay),
			time(0.0f)
		{
		}

		/** destructor
		*/
		virtual ~ActionBatching_Action_Delay()
		{
		}

	public:

		/** �A�N�V�����J�n�B
		*/
		virtual void Start()
		{
			this->time = 0.0f;
		}

		/** �A�N�V�������B
		*/
		virtual int Do(f32& a_delta,bool a_endrequest)
		{
			this->time += a_delta;

			if(a_endrequest == true){
				this->time = this->param_delay;
			}

			if(this->time >= this->param_delay){
				//�]��������ԊҁB
				a_delta = this->time - this->param_delay;
				return 1;
			}else{
				//�S����B
				a_delta = 0.0f;
			}

			return 0;
		}

	};

}}
#endif
