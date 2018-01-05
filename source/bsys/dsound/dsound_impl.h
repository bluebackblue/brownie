#pragma once

/**
 * Copyright (c) 2016-2018 blueback
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
#if(BSYS_DSOUND_ENABLE)

	#pragma warning(push)
	#pragma warning(disable:4464)
	#include <brownie_config/dsound_include.h>
	#pragma warning(pop)

#endif


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../wave/wave.h"
#include "../window/window.h"
#include "../actionbatching/actionbatching.h"
#pragma warning(pop)


/** include
*/
#include "./dsound_impl_type.h"


/** NBsys::NDsound
*/
#if(BSYS_DSOUND_ENABLE)
#pragma warning(push)
#pragma warning(disable:4710)
namespace NBsys{namespace NDsound
{
	/** Dsound
	*/
	class Dsound_Impl
	{
	private:

		/** directsound
		*/
		sharedptr<IDirectSound8> directsound;

		/** soundbuffer_primary
		*/
		sharedptr<IDirectSoundBuffer> soundbuffer_primary;

		/** soundlistener
		*/
		sharedptr<IDirectSound3DListener8> soundlistener;

		/** id_maker
		*/
		IDMaker id_maker;

		/** アクションバッチング。ロックオブジェクト。
		*/
		LockObject actionbatching_lockobject;

		/** アクションバッチング。
		*/
		NBsys::NActionBatching::ActionBatching actionbatching;

		/** soundbuffer_list
		*/
		STLMap<s32,sharedptr<Dsound_Impl_SoundBuffer>>::Type soundbuffer_list;

	public:

		/** constructor
		*/
		Dsound_Impl();

		/** destructor
		*/
		nonvirtual ~Dsound_Impl();

	private:

		/** copy constructor禁止。
		*/
		Dsound_Impl(const Dsound_Impl& a_this) = delete;

		/** コピー禁止。
		*/
		void operator =(const Dsound_Impl& a_this) = delete;

	public:

		/** Create
		*/
		bool Create(const sharedptr<NBsys::NWindow::Window>& a_window);

		/** Delete
		*/
		void Delete();

		/** デフォルト設定。
		*/
		void SetListenerParam_Default();

		/** GetDirectSound
		*/
		sharedptr<IDirectSound8>& GetDirectSound();

		/** GetDirectSound
		*/
		const sharedptr<IDirectSound8>& GetDirectSound() const;

		/** リクエスト登録。
		*/
		void StartBatching(sharedptr<NBsys::NActionBatching::ActionBatching_ActionList>& a_actionlist);

		/** リクエスト処理。
		*/
		void Player_Main();

	public:

		/** [複数スレッドから]サウンドバッファ作成。
		*/
		s32 CreateSoundBuffer(const sharedptr<NBsys::NWave::Wave>& a_wave,bool a_is_3d);

		/** [複数スレッドから]サウンドバッファ削除。
		*/
		void DeleteSoundBuffer(s32 a_id);

		/** [複数スレッドから]再生。
		*/
		s32 Play(s32 a_id,bool a_duplicate,bool a_loop,bool a_auto_delete);

	public:

		/** Player_CreateSoundBuffer
		*/
		void Player_CreateSoundBuffer(sharedptr<Dsound_Impl_SoundBuffer>& a_soundbuffer);

		/** Player_DeleteSoundBuffer
		*/
		void Player_DeleteSoundBuffer(s32 a_id);

		/** Player_Play
		*/
		void Player_Play(s32 a_id,s32 a_duplicate_id,bool a_loop,bool a_auto_delete);

		/** Player_AutoDelete
		*/
		bool Player_AutoDelete(s32 a_id);

	};


}}
#pragma warning(pop)
#endif

