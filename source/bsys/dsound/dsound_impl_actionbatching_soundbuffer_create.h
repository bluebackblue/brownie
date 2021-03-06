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
#include "./dsound_impl_soundbuffer.h"


/** NBsys::NDsound
*/
#if(BSYS_DSOUND_ENABLE)
#pragma warning(push)
#pragma warning(disable:4710 4820)
namespace NBsys{namespace NDsound
{
	/** テクスチャー作成。
	*/
	class Dsound_Impl_ActionBatching_SoundBuffer_Create : public NBsys::NActionBatching::ActionBatching_ActionItem_Base
	{
	private:

		/** Dsound_impl
		*/
		Dsound_Impl& dsound_impl;

		/** id
		*/
		s32 id;

	public:

		/** constructor
		*/
		Dsound_Impl_ActionBatching_SoundBuffer_Create(Dsound_Impl& a_dsound_impl,s32 a_id)
			:
			dsound_impl(a_dsound_impl),
			id(a_id)
		{
		}

		/** destructor
		*/
		virtual ~Dsound_Impl_ActionBatching_SoundBuffer_Create()
		{
		}

	private:

		/** copy constructor禁止。
		*/
		Dsound_Impl_ActionBatching_SoundBuffer_Create(const Dsound_Impl_ActionBatching_SoundBuffer_Create& a_this) = delete;

		/** コピー禁止。
		*/
		void operator =(const Dsound_Impl_ActionBatching_SoundBuffer_Create& a_this) = delete;

	public:

		/** アクション開始。
		*/
		virtual void Start()
		{
		}

		/** アクション中。
		*/
		virtual s32 Do(f32& /*a_delta*/,bool a_endrequest)
		{
			if(a_endrequest == true){
				//中断。
			}

			//Player_CreateSoundBuffer
			this->dsound_impl.Player_CreateSoundBuffer(this->id);

			//成功。
			return 1;
		}

	};


}}
#pragma warning(pop)
#endif

