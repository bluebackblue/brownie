﻿#pragma once

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief DirectSound
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../actionbatching/actionbatching.h"
#pragma warning(pop)


/** include
*/
#include "./dsound_impl.h"


/** NBsys::NDsound
*/
#if(BSYS_DSOUND_ENABLE)
#pragma warning(push)
#pragma warning(disable:4710 4820)
namespace NBsys{namespace NDsound
{
	/** 再生。
	*/
	class Dsound_Impl_ActionBatching_Play : public NBsys::NActionBatching::ActionBatching_ActionItem_Base
	{
	private:

		/** Dsound_impl
		*/
		Dsound_Impl& dsound_impl;

		/** id
		*/
		s32 id;

		/** duplicate_id
		*/
		s32 duplicate_id;

	public:

		/** constructor
		*/
		Dsound_Impl_ActionBatching_Play(Dsound_Impl& a_dsound_impl,s32 a_id,s32 a_duplicate_id)
			:
			dsound_impl(a_dsound_impl),
			id(a_id),
			duplicate_id(a_duplicate_id)
		{
		}

		/** destructor
		*/
		virtual ~Dsound_Impl_ActionBatching_Play()
		{
		}

	private:

		/** copy constructor禁止。
		*/
		Dsound_Impl_ActionBatching_Play(const Dsound_Impl_ActionBatching_Play& a_this) = delete;

		/** コピー禁止。
		*/
		void operator =(const Dsound_Impl_ActionBatching_Play& a_this) = delete;

	public:

		/** アクション開始。
		*/
		virtual void Start()
		{
		}

		/** アクション中。
		*/
		virtual s32 Do(f32& a_delta,bool a_endrequest)
		{
			if(a_endrequest == true){
				//中断。
			}

			//Player_Play
			this->dsound_impl.Player_Play(this->id,this->duplicate_id);

			//成功。
			return 1;
		}

	};


}}
#pragma warning(pop)
#endif

