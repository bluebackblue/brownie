

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
/*
#pragma warning(push)
#pragma warning(disable:4464)
#include "../window/window_impl.h"
#include "../actionbatching/actionbatching.h"
#pragma warning(pop)
*/


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
#include "./dsound_impl_soundbuffer.h"


/** NBsys::NDsound
*/
#if(BSYS_DSOUND_ENABLE)
#pragma warning(push)
#pragma warning(disable:4710 4820)
namespace NBsys{namespace NDsound
{
	/** constructor
	*/
	Dsound_Impl_SoundBuffer::Dsound_Impl_SoundBuffer()
		:
		playstate(PlayState::Stop),
		soundbuffer(),
		soundbuffer_size(-1),
		wave(),
		is_3d(false),
		is_loop(false),
		is_duplicate(false),
		is_stream(false),
		soundbuffer_3d(),
		soundnotify_event(),
		stream_callback(),
		stream_buffer()
	{
	}


	/** destructor
	*/
	Dsound_Impl_SoundBuffer::~Dsound_Impl_SoundBuffer()
	{
		auto t_it_end = this->soundnotify_event.cend();
		for(auto t_it = this->soundnotify_event.cbegin();t_it != t_it_end;++t_it){
			if(t_it->hEventNotify != WIN_NULL){
				::CloseHandle(t_it->hEventNotify);
			}
		}
	}


	/** ストリーミング再生コールバックの呼び出し。
	*/
	void Dsound_Impl_SoundBuffer::StreamCallback(s32 a_copyto_offset,s32 a_need_size,bool a_is_loop)
	{
		//コールバックの呼び出し。
		this->stream_callback->Callback_GetData(*this->stream_buffer,a_need_size,a_is_loop);

		if(this->stream_buffer->GetUseSize() >= a_need_size){

			u8* t_lock_data = nullptr;
			DWORD t_lock_size = 0;
			HRESULT t_ret_lock = this->soundbuffer->Lock(a_copyto_offset,a_need_size,(void**)&t_lock_data,&t_lock_size,WIN_NULL,WIN_NULL,0);
			if(SUCCEEDED(t_ret_lock)){

				s32 t_copy_to_size = a_need_size;

				if(t_copy_to_size > static_cast<s32>(t_lock_size)){
					//ロックサイズが足りない。
					t_copy_to_size = t_lock_size;
					DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
				}

				//ロックした領域にコピー。
				this->stream_buffer->CopyFromBuffer(t_lock_data,t_copy_to_size);

				HRESULT t_ret_unlock = this->soundbuffer->Unlock(t_lock_data,t_copy_to_size,WIN_NULL,0);
				if(FAILED(t_ret_unlock)){
					//アンロックに失敗。
					DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
					return;
				}
			}else{
				//ロックに失敗。
				DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
				return;
			}

		}else{
			//バッファサイズが足りない。
			DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);

			u8* t_lock_data = nullptr;
			DWORD t_lock_size = 0;
			HRESULT t_ret_lock = this->soundbuffer->Lock(a_copyto_offset,a_need_size,(void**)&t_lock_data,&t_lock_size,WIN_NULL,WIN_NULL,0);
			if(SUCCEEDED(t_ret_lock)){

				s32 t_copy_to_size = a_need_size;

				if(t_copy_to_size > static_cast<s32>(t_lock_size)){
					//ロックサイズが足りない。
					t_copy_to_size = t_lock_size;
					DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
				}

				//ロックした領域をクリア。
				NMemory::Set(t_lock_data,0,t_copy_to_size);

				HRESULT t_ret_unlock = this->soundbuffer->Unlock(t_lock_data,t_copy_to_size,WIN_NULL,0);
				if(FAILED(t_ret_unlock)){
					//アンロックに失敗。
					DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
					return;
				}
			}else{
				//ロックに失敗。
				DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
				return;
			}

			return;
		}

		//完了。
		return;
	}


	/** CreateNotify
	*/
	void Dsound_Impl_SoundBuffer::CreateNotify()
	{
		STLVector<DSBPOSITIONNOTIFY>::Type t_soundnotify_event_list;
		{
			this->soundnotify_event.resize(Dsound_Impl_SoundBuffer::NorifyEventType::Max);

			//バッファの真ん中を通過。
			{
				u32 t_index = Dsound_Impl_SoundBuffer::NorifyEventType::HalfPoint;

				if(this->is_stream == true){
					//ストリーミング再生。

					this->soundnotify_event[t_index].dwOffset = this->soundbuffer_size / 2;
					this->soundnotify_event[t_index].hEventNotify = ::CreateEvent(NULL,FALSE,FALSE,NULL);
					t_soundnotify_event_list.push_back(this->soundnotify_event[t_index]);
				}else{
					this->soundnotify_event[t_index].dwOffset = -1;
					this->soundnotify_event[t_index].hEventNotify = WIN_NULL;
				}
			}

			//バッファの最後を通過。
			{
				u32 t_index = Dsound_Impl_SoundBuffer::NorifyEventType::EndPoint;

				this->soundnotify_event[t_index].dwOffset =  this->soundbuffer_size - 1;
				this->soundnotify_event[t_index].hEventNotify = ::CreateEvent(NULL,FALSE,FALSE,NULL);
				t_soundnotify_event_list.push_back(this->soundnotify_event[t_index]);
			}
		}

		if(t_soundnotify_event_list.size() > 0){
			sharedptr<IDirectSoundNotify> t_soundnotify;

			DEEPDEBUG_TAGLOG(BSYS_DSOUND_DEBUG_ENABLE,L"dsound_impl_soundbuffer","IID_IDirectSoundNotify");

			IDirectSoundNotify* t_raw = nullptr;
			HRESULT t_ret = this->soundbuffer->QueryInterface(IID_IDirectSoundNotify,(LPVOID*)(&t_raw));
			if(t_raw != nullptr){
				t_soundnotify.reset(t_raw,release_delete<IDirectSoundNotify>());
			}
			if(FAILED(t_ret)){
				DEEPDEBUG_ASSERT(BSYS_DSOUND_DEBUG_ENABLE,0);
				t_soundnotify.reset();
				return;
			}
			if(t_soundnotify){
				t_soundnotify->SetNotificationPositions(t_soundnotify_event_list.size(),&t_soundnotify_event_list.at(0));
				t_soundnotify.reset();
			}
		}
	}

}}
#pragma warning(pop)
#endif

