

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


/** lib
*/
#if(BSYS_DSOUND_ENABLE)

	#include <brownie_config/dsound_lib.h>

#endif


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../window/window_impl.h"
#include "../actionbatching/actionbatching.h"
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
#include "./dsound_impl.h"
#include "./dsound_impl_actionbatching_soundbuffer_create.h"
#include "./dsound_impl_actionbatching_soundbuffer_delete.h"
#include "./dsound_impl_actionbatching_play.h"
#include "./dsound_impl_actionbatching_playnow.h"
#include "./dsound_streamcallback_base.h"


/** NBsys::NDsound
*/
#if(BSYS_DSOUND_ENABLE)
#pragma warning(push)
#pragma warning(disable:4710 4820)
namespace NBsys{namespace NDsound
{
	/** constructor
	*/
	Dsound_Impl::Dsound_Impl()
		:
		directsound(),
		soundbuffer_primary(),
		soundlistener(),
		id_maker(),
		actionbatching_lockobject(),
		actionbatching(),
		soundbuffer_list_lockobject(),
		soundbuffer_list()
	{
	}


	/** destructor
	*/
	Dsound_Impl::~Dsound_Impl()
	{
	}


	/** Create
	*/
	bool Dsound_Impl::Create(const sharedptr<NBsys::NWindow::Window>& a_window)
	{
		//CoCreateInstance
		{
			IDirectSound8* t_raw = nullptr;

			DEEPDEBUG_TAGLOG(BSYS_DSOUND_DEBUG_ENABLE,L"dsound_impl","CoCreateInstance");
			HRESULT t_ret = ::CoCreateInstance(CLSID_DirectSound,nullptr,CLSCTX_INPROC_SERVER,IID_IDirectSound,(void**)&t_raw);
			if(t_raw != nullptr){
				this->directsound.reset(t_raw,release_delete<IDirectSound8>());
			}
			if(FAILED(t_ret)){
				DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
				this->directsound.reset();
				return false;
			}
		}

		//Initialize
		if(this->directsound){

			DEEPDEBUG_TAGLOG(BSYS_DSOUND_DEBUG_ENABLE,L"dsound_impl","Initialize");
			HRESULT t_ret = this->directsound->Initialize(nullptr);
			if(FAILED(t_ret)){
				DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
				return false;
			}
		}

		//SetCooperativeLevel
		if(this->directsound != nullptr){

			DEEPDEBUG_TAGLOG(BSYS_DSOUND_DEBUG_ENABLE,L"dsound_impl","SetCooperativeLevel");

			HWND t_handle = a_window->GetImpl()->GetHandle();
			HRESULT t_ret = this->directsound->SetCooperativeLevel(t_handle,DSSCL_PRIORITY);
			if(FAILED(t_ret)){
				DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
				return false;
			}
		}

		//CreateSoundBuffer
		if(this->directsound != nullptr){
			DSBUFFERDESC t_desc = {0};
			{
				t_desc.dwSize = sizeof(t_desc); 
				t_desc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRL3D;
				t_desc.dwBufferBytes = 0; 
				t_desc.lpwfxFormat = nullptr;
			}

			DEEPDEBUG_TAGLOG(BSYS_DSOUND_DEBUG_ENABLE,L"dsound_impl","CreateSoundBuffer : DSBCAPS_PRIMARYBUFFER : DSBCAPS_CTRL3D");

			IDirectSoundBuffer* t_raw = nullptr;
			HRESULT t_ret = this->directsound->CreateSoundBuffer(&t_desc,&t_raw,nullptr); 
			if(t_raw != nullptr){
				this->soundbuffer_primary.reset(t_raw,release_delete<IDirectSoundBuffer>());
			}
			if(FAILED(t_ret)){
				DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
				this->soundbuffer_primary.reset();
				return false;
			}
		}

		//IID_IDirectSound3DListener
		if(this->soundbuffer_primary != nullptr){

			DEEPDEBUG_TAGLOG(BSYS_DSOUND_DEBUG_ENABLE,L"dsound_impl","IID_IDirectSound3DListener");

			IDirectSound3DListener* t_raw = nullptr;
			HRESULT t_ret = this->soundbuffer_primary->QueryInterface(IID_IDirectSound3DListener,reinterpret_cast<LPVOID*>(&t_raw));
			if(t_raw != nullptr){
				this->soundlistener.reset(t_raw,release_delete<IDirectSound3DListener>());
			}
			if(FAILED(t_ret)){
				DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
				this->soundlistener.reset();
				return false;
			}
		}
	
		//デフォルト設定。
		this->SetListenerParam_Default();

		return true;
	}


	/** Delete
	*/
	void Dsound_Impl::Delete()
	{
		{
			AutoLock t_autolock(this->soundbuffer_list_lockobject);
			this->soundbuffer_list.clear();
		}

		this->soundlistener.reset();
		this->soundbuffer_primary.reset();
		this->directsound.reset();
	}


	/** デフォルト設定。
	*/
	void Dsound_Impl::SetListenerParam_Default()
	{
		//soundlistenerのデフォルト設定。
		if(this->soundlistener != nullptr){
			HRESULT t_ret_position = this->soundlistener->SetPosition(0,0,0,DS3D_IMMEDIATE);
			DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,SUCCEEDED(t_ret_position));
			UNUSED(t_ret_position);

			HRESULT t_ret_velocity = this->soundlistener->SetVelocity(0,0,0,DS3D_IMMEDIATE);
			DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,SUCCEEDED(t_ret_velocity));
			UNUSED(t_ret_velocity);

			HRESULT t_ret_orientation = this->soundlistener->SetOrientation(0,0,1,0,1,0,DS3D_IMMEDIATE);
			DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,SUCCEEDED(t_ret_orientation));
			UNUSED(t_ret_orientation);

			HRESULT t_ret_rollofffactor = this->soundlistener->SetRolloffFactor(1.0f,DS3D_IMMEDIATE);
			DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,SUCCEEDED(t_ret_rollofffactor));
			UNUSED(t_ret_rollofffactor);

			HRESULT t_ret_dopplerfactor = this->soundlistener->SetDopplerFactor(1.0f,DS3D_IMMEDIATE);
			DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,SUCCEEDED(t_ret_dopplerfactor));
			UNUSED(t_ret_dopplerfactor);
		}else{
			DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
		}
	}


	/** GetDirectSound
	*/
	sharedptr<IDirectSound8>& Dsound_Impl::GetDirectSound()
	{
		return this->directsound;
	}


	/** GetDirectSound
	*/
	const sharedptr<IDirectSound8>& Dsound_Impl::GetDirectSound() const
	{
		return this->directsound;
	}


	/** リクエスト登録。
	*/
	void Dsound_Impl::StartBatching(sharedptr<NBsys::NActionBatching::ActionBatching_ActionList>& a_actionlist)
	{
		//アクションバッチング実行中はロック。
		AutoLock t_autolock_actionbatching(this->actionbatching_lockobject);

		//ワークリストへの追加とStartの呼び出し。
		this->actionbatching.StartBatching(a_actionlist);
	}


	/** リクエスト処理。
	*/
	void Dsound_Impl::Player_Main()
	{
		//アクションバッチング実行中はロック。
		AutoLock t_autolock_actionbatching(this->actionbatching_lockobject);

		//ワークリストからの削除とDoの呼び出し。
		this->actionbatching.Update(1.0f);
	}


	/** [複数スレッドから]サウンドバッファ作成。
	*/
	s32 Dsound_Impl::CreateSoundBuffer(const sharedptr<NBsys::NWave::Wave>& a_wave,bool a_is_3d)
	{
		//ＩＤ。
		s32 t_soundbuffer_id = this->id_maker.MakeID();

		sharedptr<Dsound_Impl_SoundBuffer> t_soundbuffer = new Dsound_Impl_SoundBuffer();
		t_soundbuffer->Create_FromWave(a_wave,a_is_3d);

		//管理リスト。
		{
			AutoLock t_autolock(this->soundbuffer_list_lockobject);
			this->soundbuffer_list.insert(std::make_pair(t_soundbuffer_id,t_soundbuffer));
		}

		//プレイヤーコマンド。
		sharedptr<NBsys::NActionBatching::ActionBatching_ActionList> t_actionlist = new NBsys::NActionBatching::ActionBatching_ActionList();
		{ 
			t_actionlist->Add(new Dsound_Impl_ActionBatching_SoundBuffer_Create(*this,t_soundbuffer_id));
		}
		this->StartBatching(t_actionlist);

		return t_soundbuffer_id;
	}


	/** [複数スレッドから]サウンドバッファ削除。
	*/
	void Dsound_Impl::DeleteSoundBuffer(s32 a_id)
	{
		//プレイヤーコマンド。
		sharedptr<NBsys::NActionBatching::ActionBatching_ActionList> t_actionlist = new NBsys::NActionBatching::ActionBatching_ActionList();
		{ 
			t_actionlist->Add(new Dsound_Impl_ActionBatching_SoundBuffer_Delete(*this,a_id));
		}
		this->StartBatching(t_actionlist);
	}


	/** ストリーミングサウンドバッファ作成。
	*/
	s32 Dsound_Impl::CreateStreamSoundBuffer(const sharedptr<NBsys::NDsound::Dsound_StreamCallback_Base>& a_stream_callback,bool a_is_3d)
	{
		//ＩＤ。
		s32 t_soundbuffer_id = this->id_maker.MakeID();

		sharedptr<Dsound_Impl_SoundBuffer> t_soundbuffer = new Dsound_Impl_SoundBuffer();
		t_soundbuffer->Create_FromStream(a_stream_callback,a_is_3d);

		//管理リスト。
		{
			AutoLock t_autolock(this->soundbuffer_list_lockobject);
			this->soundbuffer_list.insert(std::make_pair(t_soundbuffer_id,t_soundbuffer));
		}

		//プレイヤーコマンド。
		sharedptr<NBsys::NActionBatching::ActionBatching_ActionList> t_actionlist = new NBsys::NActionBatching::ActionBatching_ActionList();
		{ 
			t_actionlist->Add(new Dsound_Impl_ActionBatching_SoundBuffer_Create(*this,t_soundbuffer_id));
		}
		this->StartBatching(t_actionlist);

		return t_soundbuffer_id;
	}


	/** ストリーミングサウンドバッファ作成。
	*/
	void Dsound_Impl::DeleteStreamSoundBuffer(s32 a_id)
	{
		//プレイヤーコマンド。
		sharedptr<NBsys::NActionBatching::ActionBatching_ActionList> t_actionlist = new NBsys::NActionBatching::ActionBatching_ActionList();
		{ 
			t_actionlist->Add(new Dsound_Impl_ActionBatching_SoundBuffer_Delete(*this,a_id));
		}
		this->StartBatching(t_actionlist);
	}


	/** [複数スレッドから]再生。
	*/
	s32  Dsound_Impl::Play(s32 a_id,bool a_duplicate,bool a_is_loop,bool a_auto_delete)
	{
		sharedptr<Dsound_Impl_SoundBuffer> t_soundbuffer;
		{
			AutoLock t_autolock(this->soundbuffer_list_lockobject);
			auto t_it = this->soundbuffer_list.find(a_id);
			if(t_it != this->soundbuffer_list.end()){
				t_soundbuffer = t_it->second;
			}
		}

		if(t_soundbuffer == nullptr){
			DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
			return -1;
		}

		s32 t_duplicate_id = -1;

		if(t_soundbuffer->IsStream() == true){
			//ストリーミング再生。
			t_soundbuffer->SetState_PlayState(Dsound_Impl_SoundBuffer::PlayState::Play);
			t_soundbuffer->SetState_LoopFlag(a_is_loop);

			DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,a_auto_delete == false);
		}else{
			//複製ＩＤ。
			if(a_duplicate){
				//ＩＤ。
				t_duplicate_id = this->id_maker.MakeID();

				sharedptr<Dsound_Impl_SoundBuffer> t_soundbuffer_duplicate = new Dsound_Impl_SoundBuffer();
				t_soundbuffer_duplicate->Create_FromSoundbuffer(t_soundbuffer,a_auto_delete);
				
				t_soundbuffer_duplicate->SetState_PlayState(Dsound_Impl_SoundBuffer::PlayState::Play);
				t_soundbuffer->SetState_LoopFlag(a_is_loop);

				//管理リスト。
				{
					AutoLock t_autolock(this->soundbuffer_list_lockobject);
					this->soundbuffer_list.insert(std::make_pair(t_duplicate_id,t_soundbuffer_duplicate));
				}
			}
		}

		//プレイヤーコマンド。
		{
			sharedptr<NBsys::NActionBatching::ActionBatching_ActionList> t_actionlist = new NBsys::NActionBatching::ActionBatching_ActionList();
			{
				t_actionlist->Add(new Dsound_Impl_ActionBatching_Play(*this,a_id,t_duplicate_id));
			}
			this->StartBatching(t_actionlist);
		}

		//ワンショット再生の場合は外部から操作できないほうが安全。
		if(a_auto_delete){
			return -1;
		}

		return t_duplicate_id;
	}


	/** [複数スレッドから]再生中チェック。
	*/
	bool Dsound_Impl::IsPlay(s32 a_id)
	{
		sharedptr<Dsound_Impl_SoundBuffer> t_soundbuffer;
		{
			AutoLock t_autolock(this->soundbuffer_list_lockobject);
			auto t_it = this->soundbuffer_list.find(a_id);
			if(t_it != this->soundbuffer_list.end()){
				t_soundbuffer = t_it->second;
			}
		}

		if(t_soundbuffer == nullptr){
			//削除済み。
			return false;
		}

		if(t_soundbuffer->GetState_PlayState() == Dsound_Impl_SoundBuffer::PlayState::Play){
			//再生中。
			return true;
		}

		//停止中。
		return false;
	}


	/** [複数スレッドから]有効チェック。
	*/
	bool Dsound_Impl::IsExist(s32 a_id)
	{
		sharedptr<Dsound_Impl_SoundBuffer> t_soundbuffer;
		{
			AutoLock t_autolock(this->soundbuffer_list_lockobject);
			auto t_it = this->soundbuffer_list.find(a_id);
			if(t_it != this->soundbuffer_list.end()){
				t_soundbuffer = t_it->second;
			}
		}

		if(t_soundbuffer == nullptr){
			//削除済み。
			return false;
		}

		return true;
	}


	/** Player_CreateSoundBuffer
	*/
	void Dsound_Impl::Player_CreateSoundBuffer(s32 a_id)
	{
		sharedptr<Dsound_Impl_SoundBuffer> t_soundbuffer;
		{
			AutoLock t_autolock(this->soundbuffer_list_lockobject);
			auto t_it = this->soundbuffer_list.find(a_id);
			if(t_it != this->soundbuffer_list.end()){
				t_soundbuffer = t_it->second;
			}
		}

		if(t_soundbuffer == nullptr){
			//削除済み。
			return;
		}

		if(this->directsound == nullptr){
			DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
			return;
		}

		t_soundbuffer->CreateSoundBuffer(this->directsound);

		//通知設定。
		t_soundbuffer->CreateNotify();

		//サウンドバッファーの初期化。
		t_soundbuffer->InitializeSoundBuffer();
	}


	/** Player_DeleteSoundBuffer
	*/
	void Dsound_Impl::Player_DeleteSoundBuffer(s32 a_id)
	{
		sharedptr<Dsound_Impl_SoundBuffer> t_soundbuffer;
		{
			AutoLock t_autolock(this->soundbuffer_list_lockobject);
			auto t_it = this->soundbuffer_list.find(a_id);
			if(t_it != this->soundbuffer_list.end()){
				t_soundbuffer = t_it->second;
				this->soundbuffer_list.erase(t_it);
			}
		}

		if(t_soundbuffer == nullptr){
			//削除済み。
			return;
		}

		//停止。
		t_soundbuffer->Soundbuffer_Stop();
	}


	/** Player_Play
	*/
	void Dsound_Impl::Player_Play(s32 a_id,s32 a_duplicate_id)
	{
		sharedptr<Dsound_Impl_SoundBuffer> t_soundbuffer;
		sharedptr<Dsound_Impl_SoundBuffer> t_soundbuffer_duplicate;
		{
			AutoLock t_autolock(this->soundbuffer_list_lockobject);
			{
				auto t_it = this->soundbuffer_list.find(a_id);
				if(t_it != this->soundbuffer_list.end()){
					t_soundbuffer = t_it->second;
				}
			}
			if(a_duplicate_id >= 0){
				auto t_it = this->soundbuffer_list.find(a_duplicate_id);
				if(t_it != this->soundbuffer_list.end()){
					t_soundbuffer_duplicate = t_it->second;
				}
			}
		}

		if(t_soundbuffer == nullptr){
			//削除済み。
			return;
		}

		if(a_duplicate_id >= 0){
			if(t_soundbuffer_duplicate == nullptr){
				//削除済み。
				return;
			}
		}

		s32 t_id = a_id;

		//複製。
		if(a_duplicate_id >= 0){
		
			//複製。
			t_soundbuffer_duplicate->DuplicateSoundBuffer(this->directsound,t_soundbuffer);

			//通知設定。
			t_soundbuffer_duplicate->CreateNotify();

			t_soundbuffer = t_soundbuffer_duplicate;
			t_id = a_duplicate_id;

		}

		//停止。
		t_soundbuffer->Soundbuffer_Stop();

		//位置設定。
		t_soundbuffer->Soundbuffer_SetPosition(0);

		//フラグ。
		bool t_loop;
		
		if(t_soundbuffer->IsStream() == true){
			//ストリーミング再生。

			t_soundbuffer->StreamCallback_Play();
			t_soundbuffer->StreamCallback_GetData(0,t_soundbuffer->GetSoundBufferSize(),t_soundbuffer->GetState_LoopFlag());

			//ループ再生。
			t_loop = true;
		}

		if(t_soundbuffer->GetState_LoopFlag() == true){
			t_loop = true;
		}

		//再生。
		DEEPDEBUG_TAGLOG(BSYS_DSOUND_DEBUG_ENABLE,L"dsound_impl","Play");
		t_soundbuffer->Soundbuffer_Play(t_loop);

		if(t_soundbuffer->GetState_PlayNow() == false){
			t_soundbuffer->SetStaet_PlayNow(true);

			//プレイヤーコマンド。
			sharedptr<NBsys::NActionBatching::ActionBatching_ActionList> t_actionlist = new NBsys::NActionBatching::ActionBatching_ActionList();
			{
				t_actionlist->Add(new Dsound_Impl_ActionBatching_PlayNow(*this,t_id));
			}
			this->StartBatching(t_actionlist);
		}

		return;
	}


	/** Player_PlayNow
	*/
	bool Dsound_Impl::Player_PlayNow(s32 a_id)
	{
		sharedptr<Dsound_Impl_SoundBuffer> t_soundbuffer;
		{
			AutoLock t_autolock(this->soundbuffer_list_lockobject);
			auto t_it = this->soundbuffer_list.find(a_id);
			if(t_it != this->soundbuffer_list.end()){
				t_soundbuffer = t_it->second;
			}
		}

		if(t_soundbuffer == nullptr){
			//削除済み。
			return true;
		}

		if(t_soundbuffer->IsStream() == true){
			//ストリーミング再生。

			s32 t_copy_to_offset = t_soundbuffer->CheckNotify_Stream();
			if(t_copy_to_offset >= 0){

				if(t_soundbuffer->GetState_LoopFlag() == false){
					if(t_soundbuffer->StreamCallback_IsPlayEnd() == true){

						//停止。
						t_soundbuffer->Soundbuffer_Stop();

						//完了。
						t_soundbuffer->SetState_PlayState(Dsound_Impl_SoundBuffer::PlayState::Stop);
						t_soundbuffer->SetStaet_PlayNow(false);

						if(t_soundbuffer->IsAutoDelete()){
							//削除。
							this->Player_DeleteSoundBuffer(a_id);
						}
						return true;
					}
				}

				t_soundbuffer->StreamCallback_GetData(t_copy_to_offset,t_soundbuffer->GetSoundBufferSize() / 2,t_soundbuffer->GetState_LoopFlag());
			}

		}else{
		
			bool t_notify = t_soundbuffer->CheckNotify_Wave();
			if(t_notify == true){

				if(t_soundbuffer->GetState_LoopFlag() == false){

					//停止。
					t_soundbuffer->Soundbuffer_Stop();

					//完了。
					t_soundbuffer->SetState_PlayState(Dsound_Impl_SoundBuffer::PlayState::Stop);
					t_soundbuffer->SetStaet_PlayNow(false);

					if(t_soundbuffer->IsAutoDelete()){
						//削除。
						this->Player_DeleteSoundBuffer(a_id);
					}
					return true;

				}

			}

		}

		//継続。
		return false;
	}


}}
#pragma warning(pop)
#endif

