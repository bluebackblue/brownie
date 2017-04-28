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


/** NBsys::NActionBatching
*/
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

		/** �A�N�V�����J�n�B
		*/
		virtual void Start() = 0;

		/** �A�N�V�������B

		return : 1 == ���̃C���f�b�N�X�B0 == �p���B-1 == �߂�B
		a_delta : 0 < �������Ԏc�ʁB0 == �A���������ꎞ���f�B
		
		*/
		virtual int Do(f32& a_delta,bool a_endrequest) = 0;

	};

}}

